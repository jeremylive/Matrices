#include "file_thread_constructor.h"
#include "math.h"
#include "QDebug"


file_thread_constructor::file_thread_constructor()
{
    remaining = new QVector<line*>();
    remaining_bytes = new QVector<st_byte*>();
    mg = new file_manager;
    paused = false;
}

void file_thread_constructor::w_set_up(QPoint s, int c_s, int thr, QFile *r)
{


    size = QPoint(s.x(),s.y());
    cell_size = c_s;
    running = true;
    res = r;
    r_t = thr;

}

QByteArray file_thread_constructor::get_arr(int n,int cs)
{
    QByteArray r;
    int tn = n;
    char * c = new char[cs];
    for(int i  =0; i < cs; i++){
        c[i] =(char)(tn%256);
        tn/=256;
    }
    r = QByteArray(c,cs);
    return r;
}

void file_thread_constructor::on_line(int *l, int line_number)
{
    //qDebug()<<"got line";
    QMutex lock;
    lock.lock();
    remaining->push_back(new line(l,line_number));
    lock.unlock();
}

void file_thread_constructor::on_byte(int byte, QPoint place)
{

    QMutex lock;
    lock.lock();
    remaining_bytes->push_back(new st_byte(byte,place.x(),place.y()));
    lock.unlock();
}

//codigo de trabajo en el thread
void file_thread_constructor::run()
{
    qDebug()<<"running,  file size: "<<size.x()*size.y()*cell_size+9;
    //se reserve el espacio necesario para guardar la matriz
    res->resize(size.x()*size.y()*cell_size+9);

    line *l;
    st_byte* b;
    //se colocan los datos del archivo en el header
    QByteArray s_s;
    s_s.push_back(char(size.x()/16777216));
    s_s.push_back(char(size.x()/65536));
    s_s.push_back(char(size.x()/256));
    s_s.push_back(char(size.x()%256));
    s_s.push_back(char(size.y()/16777216));
    s_s.push_back(char(size.y()/65536));
    s_s.push_back(char(size.y()/256));
    s_s.push_back(char(size.y()%256));
    s_s.push_back((char)cell_size);
    res->seek(0);
    res->write(s_s);
    QByteArray to_write;
    to_write.resize(size.x()*cell_size);
    qDebug()<<"Writter waiting";

    while(running){
        //ser procesa una linea a escribir
        if(remaining->size() > 0){

            l = remaining->at(remaining->size()-1);
            remaining->pop_back();
            for(int i = 0; i < size.x();i++){
                for(int j = 0; j < cell_size; j++){
                    if(j)
                    to_write[i*cell_size+j] = (l->content[i]/256*(cell_size-j));
                    else
                    to_write[i*cell_size+j] = (l->content[i]%256);
                }
            }

            res->seek(9 + l->line_number*size.x()*cell_size);
            res->write(to_write);
        }else if(remaining_bytes->size() > 0){
            b = remaining_bytes->at(remaining_bytes->size()-1);
            remaining_bytes->pop_back();
            QByteArray ba = get_arr(b->data,cell_size);
            res->seek(9+b->y*cell_size*size.x() + b->x);
            res->write(ba);//escribe un byte
            /*delete b;*/
            //qDebug()<<"writing byte: "<<r_t;
        }else if(r_t <= 0){
            qDebug()<<"Respuesta Guardada";
            emit finished();
            break;
        }

    }
}

void file_thread_constructor::stop()
{
    r_t--;
}

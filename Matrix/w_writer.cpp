#include "w_writer.h"
#include "math.h"
#include "QDebug"


w_writer::w_writer()
{
    remaining = new QVector<line*>();
    remaining_bytes = new QVector<st_byte*>();
    mg = new file_manager;
}

void w_writer::w_set_up(QPoint s, int c_s, int thr)
{
    size = s;
    cell_size = c_s;
    running = true;
    res = mg->createFile("answer.m");
    r_t = thr;

}

void w_writer::on_line(int *l, int line_number)
{
    qDebug()<<"got line";
    QMutex lock;
    lock.lock();
    remaining->push_back(new line(l,line_number));
    lock.unlock();
}

void w_writer::on_byte(char byte, QPoint place)
{

}

//codigo de trabajo en el thread
void w_writer::work()
{
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

        }else if(r_t <= 0){
            qDebug()<<"Respuesta Guardada";
            emit finished();
            break;
        }

    }
}

void w_writer::stop()
{
    r_t--;
}

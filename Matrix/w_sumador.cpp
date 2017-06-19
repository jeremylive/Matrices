#include "w_sumador.h"
#include "QStringList"
#include "QMutex"
#include "QDebug"
#include "QChar"
#include "QByteArray"
#include "math.h"
#include "QDataStream"

w_sumador::w_sumador(QObject *parent) : QObject(parent),
m_cancelRequested(false),
m_pauseRequired(false)
{
    running = true;
    working = false;
}


w_sumador::~w_sumador()
{

}

void w_sumador::addWork(QFile *f, QFile *f0, QPoint si, int n, int Total, int c_s1, int c_s2)
{
    QMutex lock;
    lock.lock();
    file = f;
    file0 = f0;
    size = QPoint(si.x(),si.y());

    id = n;
    total = Total;
    line = n;
    cell_size1 = c_s1;
    cell_size2 = c_s2;
    working = true;
    lock.unlock();
}

void w_sumador::process()
{

        QByteArray read_data;
        int* line1= new int[size.x()];
        int* line2= new int[size.x()];

        int pos1 = 9;
        int pos2 = 9;
        QMutex lock;
        QDataStream stream1(file);
        QDataStream stream2(file0);
        while(working){
                int* res= new int[size.x()];//reservo memoria para el resultado, se debe liberar al escribirlo en el documento
                //qDebug()<<"thread: "<<id<<"working on: "<<line<<" bytes: "<<size.x()*cell_size1;
                pos1 = size.x()*line*cell_size1 + 9;

                unsigned int size1 = size.x()*cell_size1;
                char* tmp = new char[size.x()*cell_size1];
                lock.lock();

                file->seek(pos1);//Coloca puntero al inicio de la linea
                stream1.readBytes(tmp, size1);
                //read_data = file->read(size.x()*cell_size1);//eliminar +1
                lock.unlock();
                read_data = QByteArray(tmp,size.x()*cell_size1-1);
                delete tmp;
                qDebug()<<"read data: "<<read_data.size();

                //convierto la linea leidas a enteros
                get_array(line1,read_data,cell_size1);

                pos2 = size.x()*line*cell_size2+ 9;
                tmp = new char[size.x()*cell_size2];
                unsigned int size2 = size.x()*cell_size2;
                lock.lock();
                file0->seek(pos2);
                stream2.readBytes(tmp, size2);
                //read_data = file0->read(size.x()*cell_size2);
                lock.unlock();

                read_data = QByteArray(tmp,size2);
                delete tmp;
                //convierto la linea leidas a enteros
                qDebug()<<"read data2: "<<read_data.size();
                get_array(line2,read_data,cell_size1);

                for(int i  = 0; i< size.x(); i++){
                    res[i] = line1[i] + line2[i];
                }

                //qDebug()<<"sent line";
                emit done(res, line);
                line+=total;



                if(line >=size.x()-1)break;
                if (m_pauseRequired) {
                       m_pauseManager.wait(&m_continue);
               }
            }
            emit w_done();
            m_pauseManager.wait(&m_continue);


}

void w_sumador::destroy()
{
    this -> m_pauseRequired = false;
    this -> m_pauseManager.wakeAll();
    qDebug()<<"sumador: "<<id<<" trabajo finalizado";
    emit finished();
}

void w_sumador::pause()
{
    QMutex lock;
    lock.lock();
    this -> m_pauseRequired = true;
    lock.unlock();
}

void w_sumador::cont()
{   QMutex lock;
    lock.lock();
    this -> m_pauseRequired = false;
    this -> m_pauseManager.wakeAll();
    lock.unlock();
    qDebug()<<"thread: "<<id<<"  continuando";
}

void w_sumador::get_array(int *arr, QByteArray original, int c_s)
{
    for(int i = 0; i < original.size(); i+=c_s){
        arr[i] = 0;
        for(short int j = 0; j < c_s; j++){
            arr[i] += (int)(((unsigned char)original.at(i*c_s))*(pow(256,c_s-j-1)));
            //qDebug()<<"cell: "<<arr[i];
        }
    }
}

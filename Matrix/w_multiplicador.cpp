#include "w_multiplicador.h"
#include "QStringList"
#include "QMutex"

w_multiplicador::w_multiplicador(QObject *parent = 0) :
    QObject(parent),
    m_cancelRequested(false),
    m_pauseRequired(false)
{
    running = true;
    working = false;

}


w_multiplicador::~w_multiplicador()
{

}

void w_multiplicador::addWork(QFile *f, QFile *f0, int X, int Y, int n, int Total, int h_s)
{
    file = f;
    file0 = f0;
    x = X;
    y = Y;

    id = n;
    total = Total;
    line = n;
    header_size = h_s;
    working = true;

}

void w_multiplicador::pause()
{
    this->m_pauseRequired = true;
}

void w_multiplicador::process()
{

        QString s1;
        QString s2;
        int pos = 0;
        QMutex lock;
        while(working){
                pos = x*4*line + header_size;
                lock.lock();
                file->seek(pos);//Coloca puntero al inicio de la linea
                s1 = file->readLine(x*4+1);//eliminar +1
                lock.unlock();

                lock.lock();
                file0->seek(pos);
                s2 = file0->readLine(x*4+1);
                lock.unlock();

                QStringList list1 = s1.split(" ", QString::SkipEmptyParts);
                QStringList list2 = s2.split(" ", QString::SkipEmptyParts);
                int size = list1.size();
                QString nwln;//answer
                QString sn;//new number
                for(int i = 0; i < size; i++){
                    sn = QString::number(list1.at(i).toInt() * list2.at(i).toInt());
                while(sn.size() < 4){
                    sn = QString(" ").append(sn);
                }
                nwln.append(sn);

                emit done(nwln, line);
                line++;

            }
    }
    emit finished();



}

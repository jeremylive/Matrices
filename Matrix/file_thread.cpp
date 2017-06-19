#include "file_thread.h"
#include <QDebug>
#include <QtGlobal>
#include <QTime>
#include <QByteArray>

file_thread::file_thread(QObject *parent) : QThread(parent)
{
     abort = false;
     restart = false;

}

file_thread::~file_thread()
{

}

void file_thread::w_document(QFile *file, int x, int y, int max, int min)
{
        x_s = x;
        y_s = y;
        ma = max;
        mi = min;
        working = file;

        start();
}

void file_thread::run()
{
    qsrand(QTime::currentTime().msec());
    long int total = x_s * y_s;
    QString r;
    QByteArray s_s;
    char cell_size = 1;
    s_s.push_back(char(x_s/16777216));
    s_s.push_back(char(x_s/65536));
    s_s.push_back(char(x_s/256));
    s_s.push_back(char(x_s%256));
    s_s.push_back(char(y_s/16777216));
    s_s.push_back(char(y_s/65536));
    s_s.push_back(char(y_s/256));
    s_s.push_back(char(y_s%256));
    s_s.push_back(cell_size);

    working->write(s_s);
    for(long int i = 0; i < total; i++){
        if(i%x_s == 0){
            emit progress((100*i)/total);
        }
        r = QString((unsigned char)(qrand()%(ma+1-mi) + mi));
        /*while(r.size() < max_n_size){
            r = QString(" ").append(r);
        }*/
        working->write(r.toUtf8());
    }
    working->resize(working->pos());
    emit n_m();

    return;
}

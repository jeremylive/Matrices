#include "t_transpuesta.h"
#include "QMutex"
#include "QDebug"

t_transpuesta::t_transpuesta()
{

}

void t_transpuesta::set_up(QFile *file, QFile *r, QPoint size, int c_S, int o_cs)
{
    original = file;
    t = r;
    s = size;
    c_s = o_cs;
}

void t_transpuesta::run()
{
    t->resize(s.x()*s.y()*c_s+9);

    QByteArray s_s;
    s_s.push_back(char(s.y()/16777216));
    s_s.push_back(char(s.y()/65536));
    s_s.push_back(char(s.y()/256));
    s_s.push_back(char(s.y()%256));
    s_s.push_back(char(s.x()/16777216));
    s_s.push_back(char(s.x()/65536));
    s_s.push_back(char(s.x()/256));
    s_s.push_back(char(s.x()%256));
    s_s.push_back((char)c_s);
    t->seek(0);
    t->write(s_s);
    QByteArray line;
    line.resize(s.x()*c_s);
    qDebug()<<"Writter waiting";
    QPoint * n_s = new QPoint(s.y(),s.x());
    for(int i = 0; i < n_s->x(); i++){
        original->seek(9+i*n_s->y()*c_s);//apunto a la linea actual
        line = original->read(n_s->y()*c_s);
        for(int j  = 0; j < line.size();j+=c_s){
            char * wrt = new char[c_s];
            for(int k = 0; k < c_s; k++){
                wrt[k] = line.at(j*c_s+k);
            }
            t->seek(j*n_s->x()*c_s+9 +i);
            t->write(wrt,c_s);

        }

    }
    qDebug()<<"terminado transpuesta";
    emit finished();
}

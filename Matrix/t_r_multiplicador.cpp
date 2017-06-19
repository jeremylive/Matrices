#include "t_r_multiplicador.h"
#include "QDebug"

t_r_multiplicador::t_r_multiplicador()
{

}

void t_r_multiplicador::set_up(QFile *f, QFile *f2, QPoint S, QPoint S2, QPoint C_s, int thr)
{
    total = thr;
    //ya que estan en la pila los invierto
    file = f;
    file2 = f2;
    s = S;
    s2 = S2;
    c_s = C_s;

}

QByteArray t_r_multiplicador::get_col(int c,QFile* f,int cs)
{
    QByteArray r;
    //qDebug()<<"c: "<<c;
    for(int i = 0; i < s.x(); i++){
        f->seek(i*s.x()*cs+9+c);//calculo posicion del byte
        r.append(f->read(cs));
    }

    return r;
}

void t_r_multiplicador::run()
{
    QByteArray l1;
    QByteArray l2;

    int pos1;
    int pos2;


        //cargo las linea
        for(int c = 0; c <s.x();c++){
            a_line = 0;
            emit progres(100.0*c/s.x());
            while(a_line < s.x()){

            QMutex lock;
            lock.lock();//cargo las lineas
            file->seek(9+a_line*c_s.x()*s.x());
            l1 = file->read(s.x()*c_s.x());
            l2 = get_col(c,file2,c_s.y());
            lock.unlock();

            /*
            QString t;
            t = QString("linea").append(QString::number(a_line).append(": "));
            for(int i  = 0; i< s.x(); i++){
                t.append(QString::number((int)l1.at(i)));
                t.append(" ");

            }
            t.append("--- ");
            for(int i  = 0; i< s.x(); i++){
                t.append(QString::number((int)l2.at(i)));
                t.append(" ");
            }
            qDebug()<<t;*/


            //qDebug()<<"line1 size: " <<l1.size()<<" line2 size: "<<l2.size();
            emit work(l1,l2,c,a_line,(c * s.x()+a_line)%total);//paso al thread trabajador la linea a procesar

            a_line++;//aumento el contador de este thread;
            }
        }
        emit end();





}

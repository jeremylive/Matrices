#include "t_r_suma.h"
#include "QDebug"

t_r_suma::t_r_suma()
{
    give = new QVector<int>();
}

void t_r_suma::set_up(QFile *f, QFile *f2, QPoint S, QPoint C_s, int thr)
{
    total = thr;
    file = f;
    file2 = f2;
    pend = total;
    s = S;
    c_s = C_s;
    conts = new int[thr];

    for(int i = 0; i < thr; i++){
        conts[i] = 0;
    }

}

void t_r_suma::run()
{
    QByteArray l1;
    QByteArray l2;

    a_line = 0;
    while(true){
        //cargo las lineas

            if(a_line < s.x()){
            emit progres(100.0*a_line/s.x());
            QMutex lock;
            lock.lock();//cargo las lineas
            file->seek(9+a_line*c_s.x()*s.x());
            file2->seek(9+a_line*c_s.y()*s.x());
            l1 = file->read(s.x()*c_s.x());
            l2 = file2->read(s.x()*c_s.y());
            lock.unlock();

           /*QString t;
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
            emit work(l1,l2,a_line,a_line%total);//paso al thread trabajador la linea a procesar

            a_line++;//aumento el contador de este thread;
            }else{
                emit end();

        }
        if(pend <= 0){
            break;
        }

    }

}

void t_r_suma::ask_work(int id)
{
    QMutex lock;
    lock.lock();
    give->push_back(id);
    lock.unlock();
}

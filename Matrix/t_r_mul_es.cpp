#include "t_r_mul_es.h"
#include "QMutex"

t_r_mul_es::t_r_mul_es()
{

}

void t_r_mul_es::set_up(QFile *f, int n_c_s, int o_c_s, int x_s, int thr)
{
    file = f;
    c_s = o_c_s;
    x = x_s;
    pend = thr;
    total = thr;
}

void t_r_mul_es::run()
{
    QByteArray l1;

    int a_line = 0;
    while(true){
        //cargo las lineas

            if(a_line < x){
            emit progres(100.0*a_line/x);
            QMutex lock;
            lock.lock();//cargo las lineas
            file->seek(9+a_line*c_s*x);
            l1 = file->read(x*c_s);
            lock.unlock();




            //qDebug()<<"line1 size: " <<l1.size()<<" line2 size: "<<l2.size();
            emit work(l1,a_line,a_line%total);//paso al thread trabajador la linea a procesar

            a_line++;//aumento el contador de este thread;
            }else{
                emit end();
                break;

        }
        if(pend <= 0){
            break;
        }

    }
    emit finished();
}

void t_r_mul_es::onStop()
{
    pend--;
}

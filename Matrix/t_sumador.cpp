#include "t_sumador.h"
#include "math.h"
#include "QDebug"

t_sumador::t_sumador()
{
    pend = 0;
    pending = new QVector<cc*>();
    lines = new QVector<int>();
    ending = false;
}

void t_sumador::set_up(int Id, QPoint s, QPoint m_c)
{
    id = Id;
    size = s;
    c_size = m_c;

}

void t_sumador::get_array(int *arr, QByteArray* original, int c_s)
{
    for(int i = 0; i < original->size(); i+=c_s){
        arr[i] = 0;
        for(short int j = 0; j < c_s; j++){
            arr[i] += (int)(((unsigned char)original->at(i*c_s))*(pow(256,c_s-j-1)));
        }
    }
}

void t_sumador::run()
{


    int*l1,*l2;
    l1 = new int[size.x()];
    l2 = new int[size.x()];

    waiting = false;
    while(true){
        if(pending->size() >0){
            int *r = new int[size.x()];
            //acomodo las lineas a procesar
            line1 = pending->at(pending->size()-1)->a;
            line2 = pending->at(pending->size()-1)->b;





            get_array(l1,line1,c_size.x());
            get_array(l2,line2,c_size.y());




            //qDebug()<<"1: "<<c_size.x()<<"2: "<<c_size.y();
            //sumo los datos

            //QString f = QString("linea: ").append(QString::number(lines->size()-1)).append(": ");
            for(int i = 0; i< size.x();i++){

                r[i] = l1[i]+l2[i];
                //f.append(QString::number(l2[i])).append(" ");
            }
            //qDebug()<<f;

            //qDebug()<<"line sent "<<lines->at(lines->size()-1);
            emit done(r, pending->at(pending->size()-1)->p);
            pending->pop_back();

        }else{
            if(ending){

            break;}
        }


        }
        emit finished();
    }




void t_sumador::add_work(QByteArray a1, QByteArray a2, int l, int Id)
{
    if(id == Id){
    QByteArray* x1 = new QByteArray(a1.data(),a1.size());
    QByteArray* x2 = new  QByteArray(a2.data(),a2.size());

    cc* n = new cc(x1,x2,l);
    //qDebug()<<"thread "<<id<<" working on line "<<l;
    pending->push_back(n);

    }

}

void t_sumador::onEnd()
{
    ending = true;
}

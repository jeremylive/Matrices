#include "t_multiplicador.h"

#include "QDebug"
#include "math.h"


t_multiplicador::t_multiplicador()
{
    lines = new QVector<cs*>();
    directons = new QVector<QPoint*>();
}

void t_multiplicador::set_up(int Id, int size, QPoint c_S)
{
    id = Id;
    s = size;
    c_s = c_S;
}

void t_multiplicador::get_array(int *arr, QByteArray *original, int c_s)
{
    for(int i = 0; i < s; i+=c_s){
        arr[i] = 0;
        for(short int j = 0; j < c_s; j++){
            //qDebug()<<i*c_s<<"   "<<original->size();
            arr[i] += (int)(((unsigned char)original->at(i*c_s))*(pow(256,c_s-j-1)));
        }
    }
}

void t_multiplicador::run()
{
    int*l1,*l2;
    l1 = new int[s];
    l2 = new int[s];
    pend  = 0;
    ending = false;
    while(true){
        if(lines->size() > 0){
            int r = 0;
            //acomodo las lineas a procesar
            //qDebug()<<lines->size();
            line1 = lines->at(lines->size()-1);





            get_array(l1,line1->a,c_s.x());
            get_array(l2,line1->b,c_s.y());



           // QString f;
            for(int i = 0; i< s;i++){

                r += l1[i]*l2[i];
                //f.append(QString::number((int)line1->a->at(i))).append(" ");
            }
            /*f.append("--- ");
            for(int i = 0; i< s;i++){

                f.append(QString::number((int)line1->b->at(i))).append(" ");
            }*/

            //qDebug()<<f<<"r:"<< r;
            //guardo el resultado*/

            emit byte(r,QPoint(line1->p->x(),line1->p->y()));
            lines->pop_back();
            pend--;
        }else{
            if(ending){

            break;}
        }


        }
        emit finished();
}

void t_multiplicador::work(QByteArray l, QByteArray c, int col, int lin, int i)
{
    if(i == id){
    //qDebug()<<"got_work"<<col<<" "<<lin<<"  id: "<<id;
    QByteArray* L = new QByteArray(l, l.size());
    QByteArray* C = new QByteArray(c, c.size());
    QPoint* p = new QPoint(col, lin);
    cs * element = new cs(L,C,p);
    //qDebug()<<"size"<<L->size()<< C->size();
    lines->push_back(element);
    pend++;
    }
}

void t_multiplicador::n_m_w()
{
    ending = true;
}

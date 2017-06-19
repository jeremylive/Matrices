#include "t_mult_escalar.h"
#include "QDebug"
#include "math.h"

t_mult_escalar::t_mult_escalar()
{
    ending = false;
    pending = new QVector<node*>();
}

void t_mult_escalar::set_up(int n,int o_cs ,int cs, int x_s,int Id)
{

    escalar = n;
    n_cs = cs;
    c_s = o_cs;
    x = x_s;
    id = Id;
}

void t_mult_escalar::run()
{
    int*l1;
    l1 = new int[x];

    while(true){
        if(pending->size() >0){
            int *r = new int[x];

            //acomodo las lineas a procesar
            line1 = pending->at(pending->size()-1);




            get_array(r,line1->arr,c_s);







            //operacion en ensamblador
            mul_es(escalar,x,r);


            /*QString f;
            for(int i  = 0;  i< x; i++){
                f.append(QString::number(r[i])).append(" ");
            }
            f.append("  n: ").append(QString::number(escalar));
            qDebug()<<f;
            //qDebug()<<"line sent "<<lines->at(lines->size()-1);*/
            emit done(r,line1->l);
            pending->pop_back();

        }else{
            if(ending){

            break;}
        }


        }
        emit finished();
    }






void t_mult_escalar::get_array(int *arr, QByteArray* original, int c_s)
{
    for(int i = 0; i < original->size(); i+=c_s){
        arr[i] = 0;
        for(short int j = 0; j < c_s; j++){
            arr[i] += (int)(((unsigned char)original->at(i*c_s))*(pow(256,c_s-j-1)));
        }
    }
}

void t_mult_escalar::onWork(QByteArray arr, int n, int Id)
{
    if(Id == id){
    QByteArray* a = new QByteArray(arr,arr.size());
    node *t = new node(a, n);
    pending->push_back(t);}
}

void t_mult_escalar::onEnd()
{
    ending = true;
}

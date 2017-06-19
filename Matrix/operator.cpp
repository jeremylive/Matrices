#include "operator.h"
#include <QString>
#include <QStringList>
#include <QDebug>
#include <cmath>
#include <QByteArray>
#include <QPoint>

Operator::Operator()
{
    corriendo = 0;
    r = mg->createFile("answer.m");
    a_c_s = 1;
}

QFile *Operator::sumar(QFile *f1, QFile *f2, int thr)
{

    //se cargan los datos de los archivos
    f1->seek(0);
    f2->seek(0);
    QByteArray h1 = f1->read(9);
    QByteArray h2 = f2->read(9);
    m1 = sToInt(h1);
    m2 = sToInt(h2);
    //revisa si ambas matrices miden lo mismo
    if(m1 != m2)
    {   emit finished_op();
        return 0;

    }
    int size_m1 = h1.at(8);
    int size_m2 = h2.at(8);

    //revisa si las matrices son del mismo tamaño
    //if(size_m1 != size_m2)return 0;

    qDebug()<<"Sumando matrices\nTamaño:  "<<m1.x()<<", "<<m1.y()<<"  matriz2:"<<m2.x()<<", "<<m2.y();


    t_r_suma* repartidor = new t_r_suma();
    repartidor->set_up(f1,f2,m1,QPoint(size_m1,size_m2),thr);

    //thread escritor
    file_thread_constructor* w = new file_thread_constructor();

    if(size_m1 > size_m2){
        w->w_set_up(m1, size_m1,thr,r);
    }else{
        w->w_set_up(m1, size_m2,thr,r);
    }
    connect(w,SIGNAL(finished()),this, SLOT(onF_op()));
    w->start();

    for(int i = 0; i < thr;i++){
        t_sumador* sumador = new t_sumador();
        sumador->set_up(i,m1,QPoint(size_m1,size_m2));
        connect(sumador,SIGNAL(n_w(int)),repartidor,SLOT(ask_work(int)));
        connect(repartidor,SIGNAL(work(QByteArray,QByteArray,int,int)),sumador,SLOT(add_work(QByteArray,QByteArray,int,int)));
        connect(sumador,SIGNAL(done(int*,int)),w,SLOT(on_line(int*,int)));
        connect(repartidor,SIGNAL(end()),sumador,SLOT(onEnd()));
        connect(sumador,SIGNAL(finished()),sumador,SLOT(deleteLater()));
        connect(sumador,SIGNAL(finished()),w,SLOT(stop()));
        connect(repartidor,SIGNAL(progres(double)),this,SLOT(onProgres(double)));
        sumador->start();

    }
    repartidor->start();
    /*
    //se genera el thread que guarda archivos
    file_thread_constructor* w = new file_thread_constructor();

    if(size_m1 > size_m2){
        w->w_set_up(m1, size_m1,thr,r);
    }else{
        w->w_set_up(m1, size_m2,thr,r);
    }
    w->start();

    qDebug()<<"archivo creado";

    //se generan los threads que operan
    for(int i = 0; i < thr;i++){
        QThread *thread = new QThread;
        w_sumador *s = new w_sumador();
        s->addWork(f1,f2,m1,i,thr,size_m1,size_m2);

        s->moveToThread(thread);
        //connect(s, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
        connect(thread, SIGNAL(started()), s, SLOT(process()));
        connect(s, SIGNAL(finished()), thread, SLOT(quit()));
        connect(s, SIGNAL(finished()), s, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        connect(s,SIGNAL(done(int*,int)),w,SLOT(on_line(int*,int)));
        connect(s,SIGNAL(w_done()),w,SLOT(stop()));
        connect(w,SIGNAL(r_pause()),s,SLOT(pause()));
        connect(w,SIGNAL(r_cont()),s,SLOT(cont()));
        connect(w,SIGNAL(finished()),s,SLOT(destroy()));
        qDebug()<<"corriendo suma  "<<i;
        thread->start();
    }
    qDebug()<<"terminado";
    */
    return r;


}

QFile *Operator::sumar_escalar(QFile *f1, int n,int c_s, int thr)
{   //se cargan los datos de los archivos
    f1->seek(0);
    QByteArray h1 = f1->read(9);
    m1 = sToInt(h1);
    //revisa si ambas matrices miden lo mismo
    //alrevez ya que estan en la pila
    int size_m1 = h1.at(8);

    //revisa si las matrices son del mismo tamaño
    //if(size_m1 != size_m2)return 0;

    qDebug()<<"Multiplicando matrices\nTamaño:  "<<m1.x()<<", "<<m1.y()<<"  matriz2:"<<m2.x()<<", "<<m2.y();

    //thread escritor
    file_thread_constructor* w = new file_thread_constructor();


    w->w_set_up(m1, size_m1,thr,r);


    connect(w,SIGNAL(finished()),this, SLOT(onF_op()));
    w->start();

    t_r_mul_es* repartidor = new t_r_mul_es();
    repartidor->set_up(f1,c_s,size_m1,m1.x(),thr);

    for(int i  = 0; i < thr; i ++){
        t_mult_escalar* multiplicador =  new t_mult_escalar();
        multiplicador->set_up(n,size_m1,c_s,m1.x(),i);
        connect(repartidor,SIGNAL(work(QByteArray,int,int)),multiplicador,SLOT(onWork(QByteArray,int,int)));
        connect(multiplicador,SIGNAL(finished()),w,SLOT(stop()));
        connect(multiplicador,SIGNAL(finished()),multiplicador,SLOT(deleteLater()));
        connect(multiplicador,SIGNAL(done(int*,int)),w,SLOT(on_line(int*,int)));
        connect(repartidor,SIGNAL(finished()),multiplicador,SLOT(onEnd()));
        connect(repartidor,SIGNAL(progres(double)),this,SLOT(onProgres(double)));
        multiplicador->start();
    }


    repartidor->start();

}

QFile *Operator::multiplicar(QFile *f1, QFile *f2, int thr)
{
    //se cargan los datos de los archivos
    f1->seek(0);
    f2->seek(0);
    QByteArray h1 = f1->read(9);
    QByteArray h2 = f2->read(9);
    m1 = sToInt(h1);
    m2 = sToInt(h2);
    //revisa si ambas matrices miden lo mismo
    //alrevez ya que estan en la pila
    if(m1.y() != m2.x()){
        emit finished_op();
    return 0;}
    int size_m1 = h1.at(8);
    int size_m2 = h2.at(8);

    //revisa si las matrices son del mismo tamaño
    //if(size_m1 != size_m2)return 0;

    qDebug()<<"Multiplicando matrices\nTamaño:  "<<m1.x()<<", "<<m1.y()<<"  matriz2:"<<m2.x()<<", "<<m2.y();

    t_r_multiplicador* repartidor = new t_r_multiplicador();
    repartidor->set_up(f2,f1,m2,m1,QPoint(size_m2,size_m1),thr);

    //thread escritor
    file_thread_constructor* w = new file_thread_constructor();

    if(size_m1 > size_m2){
        w->w_set_up(m1, size_m1,thr,r);
    }else{
        w->w_set_up(m1, size_m2,thr,r);
    }
    connect(w,SIGNAL(finished()),this, SLOT(onF_op()));
    w->start();

    //codigo de los threads multiplicadores

    for(int i  = 0; i < thr; i++){
        t_multiplicador* multiplicador = new t_multiplicador();
        multiplicador->set_up(i,m1.x(),QPoint(size_m1,size_m2));
        connect(repartidor,SIGNAL(work(QByteArray,QByteArray,int,int,int)),multiplicador,SLOT(work(QByteArray,QByteArray,int,int,int)));
        connect(multiplicador,SIGNAL(byte(int,QPoint)),w,SLOT(on_byte(int,QPoint)));
        connect(multiplicador,SIGNAL(finished()),multiplicador,SLOT(deleteLater()));
        connect(multiplicador,SIGNAL(finished()),w,SLOT(stop()));
        connect(repartidor,SIGNAL(end()),multiplicador,SLOT(n_m_w()));
        connect(repartidor,SIGNAL(progres(double)),this,SLOT(onProgres(double)));
        multiplicador->start();
    }

    repartidor->start();

    return r;
}

QFile *Operator::transpuesta(QFile *f1,int c_s)
{
    //se cargan los datos de los archivos
    f1->seek(0);
    QByteArray h1 = f1->read(9);
    m1 = sToInt(h1);
    //revisa si ambas matrices miden lo mismo
    //alrevez ya que estan en la pila
    int size_m1 = h1.at(8);
    //revisa si las matrices son del mismo tamaño
    //if(size_m1 != size_m2)return 0;

    qDebug()<<"inviertiendo matriz\nTamaño:  "<<m1.x()<<", "<<m1.y();

    t_transpuesta* tran = new t_transpuesta();
    tran->set_up(f1,r,m1,c_s,size_m1);
    connect(tran,SIGNAL(finished()),this,SLOT(onF_op()));
    connect(tran,SIGNAL(finished()),tran,SLOT(deleteLater()));
    int x =m1.x();
    int y = m1.y();
    m1.setX(y);
    m1.setY(x);
    tran->start();


    return r;
}

QFile *Operator::rango(QFile *f1)
{

}

void Operator::verficar(QFile *f1)
{

}

//retorna las caracteristicas de una matriz leyendo los primeros 8 bytes
QPoint Operator::sToInt(QByteArray s)
{
    QPoint re;
    //qDebug()<<"convirtiendo  "<<s.size();
    int r = 0;
    for(int i  = 0; i < 4; i++){
        r += ((unsigned char)s.at(i))*(pow(256,(3-i)));
        //qDebug()<<((unsigned char)s.at(i))*(pow(256,(3-i)));
    }
    re.setX(r);
    r = 0;
    for(int i  = 4; i < 8; i++){
        r += ((unsigned char)s.at(i))*(pow(256,(7-i)));
    }
    re.setY(r);

    return re;

}

void Operator::n_f()
{
    r = mg->createFile("answer.m");
}

QPoint *Operator::getSize()
{
    QPoint* n = new QPoint(m1.x(),m1.y());
    return n;
}

QFile *Operator::get_res()
{
    return r;
}

void Operator::onProgres(double n)
{
    emit progres(n);
}

void Operator::onF_op()
{
    emit finished_op();
}

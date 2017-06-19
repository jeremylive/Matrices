#ifndef OPERATOR_H
#define OPERATOR_H

#include <QFile>
#include <QThread>
#include <w_sumador.h>
#include <w_multiplicador.h>
#include <QObject>
#include <w_writer.h>
#include <file_thread_constructor.h>
#include <file_manager.h>
#include <t_r_suma.h>
#include <t_sumador.h>
#include <t_r_multiplicador.h>
#include <t_multiplicador.h>
#include <t_transpuesta.h>
#include "t_r_mul_es.h"
#include "t_mult_escalar.h"

class Operator:public QObject
{
    Q_OBJECT
public:

    Operator();

    QFile *sumar(QFile* f1,QFile* f2, int thr);
    QFile* sumar_escalar(QFile* f1, int n, int c_s, int thr);
    QFile* multiplicar(QFile *f1, QFile *f2, int thr);
    QFile* transpuesta(QFile* f1, int c_s);
    QFile* rango(QFile* f1);
    void verficar(QFile* f1);//verifica el tipo de matriz
    QPoint sToInt(QByteArray s);
    void n_f();
    QPoint* getSize();
    QFile* get_res();
private:
    int corriendo;
    QFile *r;
    file_manager* mg;
    QPoint m1;
    QPoint m2;
    int a_c_s;
private slots:
    void onProgres(double n);
    void onF_op();
signals:
    void progres(double);
    void finished_op();
};

#endif // OPERATOR_H

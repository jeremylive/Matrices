#ifndef T_SUMADOR_H
#define T_SUMADOR_H

#include "QThread"
#include "QObject"
#include "QFile"
#include "QPoint"
#include "QVector"
#include "QByteArray"
struct cc{
    QByteArray *a;
    QByteArray *b;
    int p;
    cc(QByteArray * b1,QByteArray *b2, int  b3){
        a = b1;
        b = b2;
        p = b3;
    }

};

class t_sumador : public QThread
{
    Q_OBJECT
public:
    t_sumador();
    void set_up(int Id, QPoint s, QPoint m_c);
private:
    void get_array(int* arr, QByteArray* original,int c_s);

    QFile* file;
    QByteArray *line1;
    QByteArray *line2;
    QVector<cc*>* pending;//todas las lineas por operar
    QVector<int>* lines;

    //sizes
    QPoint size;
    QPoint c_size;//tamaño de las celdas de la matriz

    bool ending;
    bool waiting;
    int id;
    int pend;
protected:
    void run();

public slots:
    void add_work(QByteArray a1, QByteArray a2, int l, int Id);
     void onEnd();
signals:
    void finished();
    void n_w(int);
    void done(int*,int);


};

#endif // T_SUMADOR_H

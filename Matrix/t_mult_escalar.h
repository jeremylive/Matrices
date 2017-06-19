#ifndef T_MULT_ESCALAR_H
#define T_MULT_ESCALAR_H
#include "QThread"
#include "QObject"
#include "QFile"
#include "QPoint"
#include "QVector"
#include "QByteArray"

extern "C" void mul_es(int,int,int*);

struct node{
    QByteArray *arr;
    int l;
    node(QByteArray*a, int n){
        l = n;
        arr = a;
    }

};

class t_mult_escalar : public QThread
{   Q_OBJECT
public:
    t_mult_escalar();
    void set_up(int n , int o_cs, int cs, int x_s, int Id);
protected:
    void run();
signals:
    void finished();
    void done(int*,int);
private:
    void get_array(int* arr, QByteArray* original,int c_s);
    QVector<node*>* pending;
    node* line1;
    int escalar;
    int n_cs;
    int c_s;
    int x;
    bool ending;
    int id;
public slots:
    void onWork(QByteArray arr,int n, int Id);
    void onEnd();

};

#endif // T_MULT_ESCALAR_H

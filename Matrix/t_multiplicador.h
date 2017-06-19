#ifndef T_MULTIPLICADOR_H
#define T_MULTIPLICADOR_H

#include "QThread"
#include "QObject"
#include "QFile"
#include "QPoint"
#include "QVector"
#include "QByteArray"

struct cs{
    QByteArray *a;
    QByteArray *b;
    QPoint *p;
    cs(QByteArray * b1,QByteArray *b2, QPoint * b3){
        a = b1;
        b = b2;
        p = b3;
    }

};


class t_multiplicador : public QThread
{
    Q_OBJECT
public:
    t_multiplicador();
    void set_up(int Id, int size,QPoint c_S);
protected:
    void get_array(int* arr, QByteArray* original,int c_s);
    void run();
private:
    QPoint c_s;
    int s;
    int id;
    QVector<QPoint*>* directons;
    QVector<cs*>* lines;
    cs* line1;
    QByteArray *line2;
    bool ending;
    int pend;
public slots:
    void work(QByteArray l,QByteArray c,int colo,int lin,int i);
    void n_m_w();

signals:
    void finished();
    void byte(int n, QPoint place);
};

#endif // T_MULTIPLICADOR_H

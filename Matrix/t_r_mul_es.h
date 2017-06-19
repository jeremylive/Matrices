#ifndef T_R_MUL_ES_H
#define T_R_MUL_ES_H
#include "QThread"
#include "QObject"
#include "QFile"
#include "QPoint"
#include "QVector"
#include "QByteArray"


class t_r_mul_es : public QThread
{   Q_OBJECT
public:
    t_r_mul_es();
    void set_up(QFile *f, int n_c_s, int o_c_s, int x_s,int thr);
protected:
    void run();
private:
    QFile * file;
    int c_s;
    int x;
    int pend;
    int total;
signals:
    void finished();
    void work(QByteArray,int,int);
    void progres(double);
    void end();
public slots:
    void onStop();
};

#endif // T_R_MUL_ES_H

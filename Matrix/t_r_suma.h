#ifndef T_R_SUMA_H
#define T_R_SUMA_H

#include "QThread"
#include "QObject"
#include "QFile"
#include "QPoint"
#include "QVector"
#include "QByteArray"
#include "QMutex"

class t_r_suma : public QThread
{
    Q_OBJECT
public:
    t_r_suma();
    void set_up(QFile* f,QFile*f2, QPoint S,QPoint C_s, int thr);
private:
    QFile* file;
    QFile* file2;
    QPoint s;
    QPoint c_s;
    int total;
    QVector<int>* give;
    int* conts;
    int pend;
    int a_line;
protected:
    void run();
public slots:
    void ask_work(int id);
signals:
    void work(QByteArray, QByteArray, int, int);
    void end();
    void progres(double);

};

#endif // T_R_SUMA_H

#ifndef T_R_MULTIPLICADOR_H
#define T_R_MULTIPLICADOR_H

#include "QThread"
#include "QObject"
#include "QFile"
#include "QPoint"
#include "QVector"
#include "QByteArray"
#include "QMutex"

class t_r_multiplicador : public QThread
{
    Q_OBJECT
public:
    t_r_multiplicador();
    void set_up(QFile* f,QFile*f2, QPoint S,QPoint S2,QPoint C_s, int thr);
    QByteArray get_col(int c, QFile *f, int cs);


private:
    QFile* file;
    QFile* file2;
    QPoint s;
    QPoint s2;
    QPoint c_s;
    int total;
    int a_line;
protected:
    void run();
public slots:

signals:
    void work(QByteArray,QByteArray,int,int,int);
    void end();
    void progres(double);
};

#endif // T_R_MULTIPLICADOR_H

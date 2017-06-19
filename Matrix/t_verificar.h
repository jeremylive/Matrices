#ifndef T_VERIFICAR_H
#define T_VERIFICAR_H

#include "QThread"
#include "QObject"
#include "QFile"
#include "QPoint"
#include "QVector"
#include "QByteArray"
#include "st_prop.h"

class t_verificar : public QThread
{   Q_OBJECT
public:
    t_verificar();
    void set_up(QFile *F);
protected:
    void run();
public slots:
    void on_clear();
signals:
    void finished();
    void res(QString);
private:
    QPoint sToInt(QByteArray s);
    s_prop* r;
    QFile* f;
    QPoint size;
    bool breaking;

};

#endif // T_VERIFICAR_H

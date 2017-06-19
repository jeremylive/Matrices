#ifndef T_TRANSPUESTA_H
#define T_TRANSPUESTA_H

#include "QThread"
#include "QObject"
#include "QFile"
#include "QPoint"
#include "QVector"
#include "QByteArray"
#include "QMutex"

class t_transpuesta : public QThread
{   Q_OBJECT
public:
    t_transpuesta();
    void set_up(QFile *file, QFile* r, QPoint size, int c_S, int o_cs);
protected:
    void run();
private:
    int c_s;
    QFile* original;
    QFile* t;
    QPoint s;
public slots:

signals:
    void finished();
};

#endif // T_TRANSPUESTA_H

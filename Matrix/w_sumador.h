#ifndef W_SUMADOR_H
#define W_SUMADOR_H

#include <QObject>
#include <QString>
#include <QFile>
#include "QPoint"
#include <QWaitCondition>
#include <QMutex>



class w_sumador: public QObject {
    Q_OBJECT

public:
    w_sumador(QObject *parent = 0);
    ~w_sumador();
    void addWork(QFile* f, QFile* f0, QPoint si, int n, int Total, int c_s1, int c_s2);

public slots:
    void process();
    void destroy();
    void pause();
    void cont();

signals:
    void finished();
    void error(QString err);
    void ask_work(int);
    void done(int *,int);
    void w_done();

private:
    void get_array(int* arr, QByteArray original,int c_s);
    // add your variables here
    QFile *file;
    QFile *file0;
    QPoint size;
    bool running;
    bool working;
    long int id;
    int total;
    int line;
    int cell_size1;
    int cell_size2;

    //Elementos necesarios para pausar el worker
    QWaitCondition m_pauseManager;
    QMutex m_continue;
    bool m_cancelRequested;
    bool m_pauseRequired;
};

#endif // W_SUMADOR_H

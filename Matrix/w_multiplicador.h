#ifndef W_MULTIPLICADOR_H
#define W_MULTIPLICADOR_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QWaitCondition>
#include <QMutex>

class w_multiplicador: public QObject {
    Q_OBJECT

public:
    w_multiplicador(QObject *parent);
    ~w_multiplicador();
    void addWork(QFile* f,QFile* f0,int X, int Y,int n, int Total, int h_s);
    void pause();
    void restart();

public slots:
    void process();

signals:
    void finished();
    void error(QString err);
    void ask_work(int);
    void done(QString, long int);

private:
    // add your variables here
    QFile *file;
    QFile *file0;
    int x,y;
    bool running;
    bool working;
    long int id;
    int total;
    int line;
    int header_size;

    //Elementos necesarios para pausar el worker
    QWaitCondition m_pauseManager;
    QMutex m_continue;
    bool m_cancelRequested;
    bool m_pauseRequired;
};

#endif W_MULTIPLICADOR_H

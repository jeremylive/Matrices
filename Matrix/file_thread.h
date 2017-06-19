#ifndef FILE_THREAD_H
#define FILE_THREAD_H

#include "QThread"
#include "QFile"
#include "QObject"

class file_thread : public QThread
{
    Q_OBJECT
public:
    file_thread(QObject *parent = 0);
    ~file_thread();
    void w_document(QFile *file, int x, int y, int max, int min);
private:
    int x_s, y_s, ma, mi;
    bool restart;
    bool abort;
    QFile *working;
protected:
    void run();
signals:
    void n_m();
    void progress(int);
};

#endif // FILE_THREAD_H

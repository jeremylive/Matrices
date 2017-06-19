#ifndef FILE_THREAD_CONSTRUCTOR_H
#define FILE_THREAD_CONSTRUCTOR_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QFile>
#include <QVector>
#include <QPoint>
#include <st_line.h>
#include <st_byte.h>
#include <file_manager.h>
#include <QByteArray>
#include <QMutex>

class file_thread_constructor : public QThread
{
    Q_OBJECT
public:
    file_thread_constructor();
    void w_set_up(QPoint s, int c_s, int thr, QFile* r);
    QByteArray get_arr(int n, int cs);
public slots:
    void on_line(int *l, int line_number);
    void on_byte(int byte, QPoint place);

    void stop();
protected:
    void run();
signals:
    void finished();
    void r_pause();
    void r_cont();
private:
    bool paused;
    QPoint size;
    int cell_size;
    QVector<line*>* remaining;
    QVector<st_byte*>* remaining_bytes;
    bool running;
    QFile* res;
    file_manager* mg;
    int r_t;
};

#endif // FILE_THREAD_CONSTRUCTOR_H

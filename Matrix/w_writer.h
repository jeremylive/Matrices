#ifndef W_WRITER_H
#define W_WRITER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QVector>
#include <QPoint>
#include <st_line.h>
#include <st_byte.h>
#include <file_manager.h>
#include <QByteArray>
#include <QMutex>

class w_writer : public QObject
{
    Q_OBJECT
public:
    w_writer();

    void w_set_up(QPoint s, int c_s, int thr);
public slots:
    void on_line(int *l, int line_number);
    void on_byte(char byte, QPoint place);
    void work();
    void stop();
signals:
    void finished();
private:
    QPoint size;
    int cell_size;
    QVector<line*>* remaining;
    QVector<st_byte*>* remaining_bytes;
    bool running;
    QFile* res;
    file_manager* mg;
    int r_t;
};

#endif // W_WRITER_H

#ifndef V_MATIX_DISPLAY_H
#define V_MATIX_DISPLAY_H

#include <QObject>
#include <QLabel>
#include <QFile>
#include <QVector>
#include <QGraphicsView>
#include <QPushButton>
#include <QString>
#include <QPoint>

class v_matix_Display : public QObject
{
    Q_OBJECT
public:
    v_matix_Display(QGraphicsView *v);
    void set_visibility(bool v);
    void actualize(QFile* f, QPoint* p);
    void redraw();
public slots:

    void onUp();
    void onDown();
    void onLeft();
    void onRight();
signals:

private:
    QVector<QLabel*>* labels;
    QFile *observed;


    QGraphicsView *view;
    QPushButton* up;
    QPushButton* down;
    QPushButton* left;
    QPushButton* rigth;
    QPoint* size;
    QLabel* x_t;
    QLabel* y_t;
    int x_l;
    int y_l;
    int cell_size;


};

#endif // V_MATIX_DISPLAY_H

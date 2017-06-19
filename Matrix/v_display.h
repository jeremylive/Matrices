#ifndef V_DISPLAY_H
#define V_DISPLAY_H

#include "QObject"
#include "QLabel"
#include "QGraphicsView"

class v_display:QObject
{
public:
    v_display(QGraphicsView *v, int x, int y);
    void actualizar(QVector<QString> *s);
    void move(int x, int y);
    void set_visible(bool v);
private:
    QVector<QLabel*> * content;
    int x_space;
    int y_space;
    QGraphicsView * view;

};

#endif // V_DISPLAY_H

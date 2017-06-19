#ifndef LIST_DISPLAY_H
#define LIST_DISPLAY_H

#include <QObject>
#include <QString>
#include <QGraphicsView>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsScene>




class List_Display : public QObject{
    Q_OBJECT
public:
    List_Display(QGraphicsScene * sc);
    QGraphicsScene * scene;
    void add_element(QString string);
    void actualizar();

private:
    QVector<QString> * content;
    QVector<QPushButton*> * titulos;
    int x_space;
    int y_space;

signals:
    void on_button(int);
private slots:
    void onButton(int id);
};

#endif // LIST_DISPLAY_H

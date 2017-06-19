#include "list_display.h"
#include "QDebug"
#include "QPoint"
#include "QApplication"
#include <QSignalMapper>
#include <QGraphicsProxyWidget>


List_Display::List_Display(QGraphicsScene *sc)
{
    //guardo mi referencia a la clase contenedora
    scene = sc;
    content = new QVector<QString>();
    titulos = new QVector<QPushButton*>();
    //mapper, encargado de las señales de los botones

    x_space = 100;
    y_space = 20;

    //label vacia para que se centre el objeto
    QLabel *lb = new QLabel();
    QGraphicsProxyWidget * proxy = scene->addWidget(lb);
    proxy->setPos(0,0);
    lb->move(600,650);
    lb->setStyleSheet("QLabel{background-color: rgba(0,0,0,0)}");

    //segundo label vacio
    QLabel *lb2 = new QLabel();
    QGraphicsProxyWidget * proxy2 = scene->addWidget(lb);
    proxy2->setPos(0,0);
    lb2->move(0,0);
    lb2->setStyleSheet("QLabel{background-color: rgba(0,0,0,0)}");



}

//agrega un elemento al contenido del objeto
void List_Display::add_element(QString string)
{
      content->push_back(string);
      actualizar();

}

//actualiza la interfaz
void List_Display::actualizar()
{
    int total;
    for(total = 0; total < content->size(); total++){
        //si no existe el label lo creo

        if(titulos->size() < total + 1){
            QPushButton *tmp = new QPushButton();

            //tmp->setParent(vista);
            //agrego el boton a la scena
            QGraphicsProxyWidget * proxy = scene->addWidget(tmp);
            proxy->setPos(0,0);
            tmp->setStyleSheet("QPushButton{color: rgb(255,255,255);background-color: rgba(0,0,53,190);font-size: 20px}");


            //tamaño fijo del boton
            tmp->setFixedWidth(80);
            tmp->setFixedHeight(80);

            //asigna posicion del boton
            tmp->move(x_space*total + 30, y_space);

            titulos->push_back(tmp);

            //mapper excesivo, mapea las señales a una id
            QSignalMapper *mapper = new QSignalMapper(this);
            connect(mapper,SIGNAL(mapped(int)),this,SLOT(onButton(int)));


            //conecto la señal del boton al ser liberado
            connect(tmp,SIGNAL(released()),mapper,SLOT(map()));
            mapper->setMapping(tmp,total);



        }

        if(titulos->at(total)){
        titulos->at(total)->setText(content->at(total));
        titulos->at(total)->setVisible(true);
        }

    }

    while(total < titulos->size()){
        titulos->at(total)->setVisible(false);
        total++;
    }
}

void List_Display::onButton(int id)
{

    //qDebug()<<"clicked: "<<id;
    emit(on_button(id));
}


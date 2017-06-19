#include "v_matix_display.h"
#include <QByteArray>
#include <QDebug>

v_matix_Display::v_matix_Display(QGraphicsView *v)
{
    view = v;
    labels = new QVector<QLabel*>();
    observed = 0;


    int gap = 25;
    int x_desp = 150;
    int y_desp = 185;
    for(int i = 0;  i< 401; i++){
        labels->push_back(new QLabel(view));
        labels->at(i)->move((i%20 * gap)+x_desp,(i/20)*gap+y_desp);
        labels->at(i)->setVisible(false);
        labels->at(i)->setFixedSize(20,20);
        labels->at(i)->setStyleSheet("QLabel{ text-align: center;color: rgb(0,0,0);background-color: rgba(0,153,255,200);font-size: 10px}");
    }
    x_l = 0;
    y_l = 0;

    //botones
    up = new QPushButton( "Arriba",view);
    down = new QPushButton( "Abajo",view);
    left = new QPushButton( "Izquierda",view);
    rigth = new QPushButton( "Derecha",view);
    up->move(x_desp+600,y_desp+160);
    down->move(x_desp+600,y_desp+310);
    left->move(x_desp+525,y_desp+235);
    rigth->move(x_desp+675,y_desp+235);
    int r_size = 70;
    up->setFixedSize(r_size,r_size);
    down->setFixedSize(r_size,r_size);
    left->setFixedSize(r_size,r_size);
    rigth->setFixedSize(r_size,r_size);
    x_t= new QLabel("X: 0",view);
    y_t= new QLabel("Y: 0",view);
    x_t->setStyleSheet("QLabel{color: rgb(255,255,255);background-color: rgba(0,102,102,20);font-size: 25px}");
    y_t->setStyleSheet("QLabel{color: rgb(255,255,255);background-color: rgba(0,102,102,20);font-size: 25px}");

    x_t->move(x_desp +530, y_desp + 30);
    y_t->move(x_desp +530, y_desp + 90);
    x_t->setFixedSize(200,30);
    y_t->setFixedSize(200,30);
    //aciones de los botones
    connect(up,SIGNAL(released()),this,SLOT(onUp()));
    connect(down,SIGNAL(released()),this,SLOT(onDown()));
    connect(left,SIGNAL(released()),this,SLOT(onLeft()));
    connect(rigth,SIGNAL(released()),this,SLOT(onRight()));

}

void v_matix_Display::set_visibility(bool v)
{
    for(int i = 0; i < 400; i++){
        labels->at(i)->setVisible(false);
    }
    up->setVisible(v);
    down->setVisible(v);
    left->setVisible(v);
    rigth->setVisible(v);
    x_t->setVisible(v);
    y_t->setVisible(v);
}

void v_matix_Display::actualize(QFile* f, QPoint* p)
{

    x_l = 0;
    y_l = 0;
    x_t->setText(QString("X: ").append(QString::number(x_l)));
    y_t->setText(QString("Y: ").append(QString::number(y_l)));
    observed = f;
    size = p;
    f->seek(8);
    QByteArray c_s = f->read(5);
    cell_size = c_s.at(0);
    QByteArray line;
    int n;
    for(int i = 0; i < 20; i++){
        if(i < size->y()){
        f->seek(9 + i*size->x()*cell_size);
        line = observed->read(size->x()*cell_size + 9);
        }
        for(int j = 0; j < 20;j++){
            if(i < size->y() && j < size->x()){
                n=0;
                for(int k = 0; k < cell_size;k++){
                    n *=256;
                    n += (unsigned char)line.at(j*cell_size+k);
                    }
                     //decodificamos el signo
             if(line.at(j) >127){
                        n *= -1;
                 }

             labels->at(i*20 + j)->setText(QString::number(n));
             labels->at(i*20 + j)->setVisible(true);
             }else{
                 labels->at(i*20 + j)->setVisible(false);
             }
      }
    }
}

void v_matix_Display::onUp()
{
    if(y_l > 0 && observed){
        y_l--;
        redraw();
    }

}

void v_matix_Display::onDown()
{
    if(y_l +20 < size->y() && observed){
        y_l++;
        redraw();
    }

}

void v_matix_Display::onLeft()
{
    if(x_l > 0 && observed){
        x_l--;
        redraw();
    }

}

void v_matix_Display::onRight()
{
    if(x_l +20 < size->x() && observed){
        x_l++;
        redraw();
    }

}

void v_matix_Display::redraw()
                    {

                        x_t->setText(QString("X: ").append(QString::number(x_l)));
                        y_t->setText(QString("Y: ").append(QString::number(y_l)));
                        int n;
                        QByteArray line;
                        for(int i = 0; i < 20; i++){
                            if(i + y_l < size->y()){
                            observed->seek(9 + (i + y_l)*size->x()*cell_size);
                            line = observed->read(size->x()*cell_size + 9);
                            }
                            for(int j = 0; j < 20;j++){
                                if((i+y_l) < size->y() && (j + x_l) < size->x()){
                                    n=0;
                                    for(int k = 0; k < cell_size;k++){
                                        n *=256;
                                        n += (unsigned char)line.at((j + x_l)*cell_size+k);

                                    }
                                    //decodificamos el signo
                                    if(line.at(j) >127){
                                        n *= -1;
                                    }
                                    labels->at(i*20 + j)->setText(QString::number(n));
                                    labels->at(i*20 + j)->setVisible(true);
                                }else{
                                    labels->at(i*20 + j)->setVisible(false);
                                }
                            }
                        }
                    }

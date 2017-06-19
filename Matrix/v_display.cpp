#include "v_display.h"

v_display::v_display(QGraphicsView *v, int x, int y)
{
    content = new QVector<QLabel*>();
    x_space = x;
    y_space = y;
    view = v;
}

void v_display::actualizar(QVector<QString> *s)
{
    int s_size = s->size();
    int l_size = content->size();
    int v_gap = 30;
    for(int i = 0; i < s_size; i++){
        if(i < l_size){
            content->at(i)->setText(s->at(i));
            content->at(i)->move(x_space,y_space -(s_size - i)*v_gap);
            content->at(i)->setVisible(true);
        }else{
            content->push_back(new QLabel(s->at(i),view));
            content->at(i)->move(x_space,y_space -(s_size - i)*v_gap);
            content->at(i)->setStyleSheet("QLabel{color: rgb(255,255,255);background-color: rgba(30,0,53,60);font-size: 20px;border: 2px solid}");
            content->at(i)->setVisible(true);
        }
    }
    for(int i = s_size; i < l_size;i++){
        content->at(i)->setVisible(false);
    }

}

void v_display::move(int x, int y)
{
    x_space = x;
    y_space = y;
}

void v_display::set_visible(bool v)
{
    for(int i = 0 ; i < content->size();i++){
        content->at(i)->setVisible(v);
    }
}

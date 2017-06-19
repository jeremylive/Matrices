#include "t_verificar.h"
#include "math.h"

t_verificar::t_verificar()
{

}

void t_verificar::set_up(QFile *F)
{
    f=F;
}

void t_verificar::run()
{
    f->seek(0);

    QByteArray h1 = f->read(9);
    size = sToInt(h1);
    breaking = false;
    //revisa si ambas matrices miden lo mismo
    int size_m1 = h1.at(8);
    r = new s_prop(size.x(),size.y());
    QByteArray to_w;
    for(int i = 0; i < size.x(); i++){
        f->seek(i*size.x()*size_m1 + 9);
        to_w = f->read(size.x()*size_m1 + 9);
        if(breaking)break;
        for(int j = 0; j < to_w.size(); j+=size_m1){
            int n = 0;
            for(int k = 0; k < size_m1;k++){
                n+=(int)(unsigned char)(to_w.at(j))*pow(256,size_m1-k-1);
            }
            if(n!= 0)r->m_nul = false;
            if(i==j/size_m1){
                if(n==0){
                    r->diag = false;
                    r->id = false;

                }else if(n != 1){
                    r->id = false;
                }
                if(n != 0){
                    r->t_inf = false;
                    r->t_sup = false;
                }

            }
            if(i>j/size_m1){
                if(n != 0){
                    r->t_inf = false;
                }
            }else if(i<j/size_m1){
                if(n != 0){
                    r->t_sup = false;
                }
            }
        }
    }
    QString s;
    if(r->col)s.append("Matriz columna, ");
    if(r->cuadrada)s.append("Matriz cuadrada, ");
    if(r->diag)s.append("Matriz diagonal, ");
    if(r->fila)s.append("Matriz fila, ");
    if(r->m_nul)s.append("Matriz nula, ");
    if(r->rect)s.append("Matriz rectangular, ");
    if(r->t_inf)s.append("Triangular inferior, ");
    if(r->t_sup)s.append("Triangular superior");
    emit res(s);
    emit finished();
}

void t_verificar::on_clear()
{
    breaking = true;
}

QPoint t_verificar::sToInt(QByteArray s)
{
    QPoint re;
    //qDebug()<<"convirtiendo  "<<s.size();
    int r = 0;
    for(int i  = 0; i < 4; i++){
        r += ((unsigned char)s.at(i))*(pow(256,(3-i)));
        //qDebug()<<((unsigned char)s.at(i))*(pow(256,(3-i)));
    }
    re.setX(r);
    r = 0;
    for(int i  = 4; i < 8; i++){
        r += ((unsigned char)s.at(i))*(pow(256,(7-i)));
    }
    re.setY(r);

    return re;
}


#ifndef ST_PROP_H
#define ST_PROP_H

struct s_prop{
    bool fila;
    bool col;
    bool cuadrada;
    bool rect;

    bool diag;
    bool nula;
    bool t_sup;
    bool t_inf;
    bool id;
    bool m_nul;
    s_prop(int x,int y){
        fila = col = cuadrada = rect = false;
        nula = t_sup = t_inf = id = diag = true;
        if(x == y){
            cuadrada = true;
        }else{
            rect = true;
            id = false;
            diag = false;
        }
        if(x == 1){
            col = true;
        }
        if(y == 1){
            fila = true;
        }

    }



};

#endif // ST_PROP_H

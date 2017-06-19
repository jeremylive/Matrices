#ifndef ST_BYTE_H
#define ST_BYTE_H

struct st_byte{
    int data;
    int x, y;
    st_byte(int c, int X, int Y){
        data = c;
        x = X;
        y = Y;
    }
};



#endif // ST_BYTE_H

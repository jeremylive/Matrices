#ifndef ST_LINE_H
#define ST_LINE_H
struct line{
    int *content;
    int line_number;
    line(int* arr, int l){
        content = arr;
        line_number = l;
    }
};
#endif // ST_LINE_H

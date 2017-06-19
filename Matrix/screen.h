#ifndef SCREEN_H
#define SCREEN_H

#include <QMainWindow>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <list_display.h>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QVector>
#include <QPoint>
#include <QTextEdit>
#include <file_manager.h>
#include <QFile>
#include <file_thread.h>
#include <QProgressBar>
#include "v_display.h"
#include "operator.h"
#include <v_matix_display.h>
#include <QTime>
#include <t_verificar.h>

class screen : public QMainWindow{
    Q_OBJECT
public:
    screen();
    void mostrar();
private slots:

public slots:
    void on_l_button(int id);
    void onCrear();
    void onObservar();
    void onEditar();
    void closeEvent();
    void onNewMatrix();
    void onProgressMatrix(int v);
    void onOperar();
    void onSumar();
    void onMultiplicar();
    void onMultiplicar_e();
    void onTrans();
    void onSalvar();
    void onProgresOp(double p);
    void onFinishedOp();
    void onProps(QString s);
signals:
    void clear();
private:
    void crear_visibilidad(bool v);
    void operar_visibilidad(bool v);
    void random_matrix(QFile *m, int x, int y, int max, int min);
    void op_vis(bool v);

    QGraphicsView *container;
    QGraphicsScene *scene;
    List_Display * matrices;

    //variables
    int contador;//cantidad de matrices existentes;
    QVector<QFile*> *all_matrix;//vector que contiene todas las matrices
    QVector<QPoint*> *all_matrix_size;//contiene los tamaños de todas las matrices
    int selected;//indice de la matriz seleccionada actualmente
    int f_x, f_y;

    //elementos de crear matriz
    QPushButton *b_crear;
    QSpinBox *sb_min;
    QSpinBox *sb_max;
    QSpinBox *sb_x_size;
    QSpinBox *sb_y_size;
    QLabel *l_min;
    QLabel *l_max;
    QLabel *l_x_size;
    QLabel *l_y_size;
    QLabel *l_titulo_crear;
    QLabel *l_name;
    QLineEdit *te_name;
    QLabel *l_fondo_crear;
    QLabel *l_fondo_n;
    file_manager *files;
    file_thread *f_thread;
    QProgressBar *pb_crear;


    //opciones
    QPushButton *b_observar;
    QPushButton *b_editar;
    QPushButton *b_operar;



    //elemntos de operar
    QPushButton *b_sumar;
    QPushButton *b_multiplicar;
    QPushButton *b_transpuesta;
    QPushButton *b_sumar_escalar;
    QPushButton *b_rango;

    QPushButton *b_salvar;
    QPushButton *b_remove;
    QLineEdit *le_name;

    QProgressBar* pb_operar;
    v_display *operandos;
    QSpinBox* sb_threads;
    QSpinBox* sb_cell_size;
    QSpinBox* sb_escal;
    QLabel* l_n_threads;
    QLabel* l_cell_Size;
    QLabel* l_prop;

    QLabel *l_elementos;
    QVector<int> *pendientes;
    QVector<QString> *names;
    QVector<QString> *pending_names;
    bool operando;
    bool observando;

    Operator *op;

    //elementos de observar
    v_matix_Display* m_disp;

};

#endif // SCREEN_H

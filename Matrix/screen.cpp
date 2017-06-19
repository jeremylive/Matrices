#include "screen.h"
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QtGlobal>
#include <QTime>
#include <QString>
#include <QFont>
#include <QGraphicsProxyWidget>
#include <QScrollBar>



screen::screen()
{
    //variables---------------------------------------
    contador = 0;
    selected = -1;
    all_matrix = new QVector<QFile*>();
    all_matrix_size = new QVector<QPoint*>();
    qsrand(QTime::currentTime().msec());
    files = new file_manager();
    f_thread = new file_thread();
    f_x = f_y = 0;
    observando = false;

    //escena -----------------------------------------
    scene = new QGraphicsScene(this);
    QBrush fondo(QColor(00,0,00,255));
    scene->setBackgroundBrush(fondo);


    //view -------------------------------------------
    container = new QGraphicsView();


    //cambiar titulo de la ventana -------------------
    this->setWindowTitle("Matrix operator");






    int y_disp = -50;
    int x_disp = 20;
    unsigned int maxmimo = 2147483640;
    //Elementos para crear una matriz---------------------------------------
    l_fondo_crear = new QLabel();
    l_fondo_crear->setParent(container);
    l_fondo_crear->setStyleSheet("QLabel{background-color: rgba(0,0,53,190); border: 2px solid}");
    l_fondo_crear->setFixedSize(480,350);
    l_fondo_crear->move(10 + x_disp,300 + y_disp);
    /*l_fondo_n = new QLabel();
    l_fondo_n->setParent(container);
    l_fondo_n->setStyleSheet("QLabel{background-color: rgba(120,120,200,80); border: 1px solid}");
    l_fondo_n->setFixedSize(1600,180);
    l_fondo_n->move(0,20);*/

    b_crear = new QPushButton(container);
    b_crear->setStyleSheet("QPushButton{color: rgb(255,255,255);background-color: rgba(0,0,53,190);font-size: 20px}");
    b_crear->move(180 + x_disp,560 + y_disp);
    b_crear->setText("Crear matriz");

    //labels
    l_titulo_crear = new QLabel("Crear una nueva matriz");
    l_titulo_crear->setStyleSheet("QLabel{color: rgb(60,180,60);font-size: 30px}");
    l_titulo_crear->setParent(container);
    l_titulo_crear->move(60 + x_disp,330 + y_disp);


    int line1 = 460 + y_disp;
    int line2 = 500 + y_disp;
    l_min = new QLabel("Minimo :");
    l_max = new QLabel("Maximo:");
    l_min->setParent(container);
    l_max->setParent(container);
    l_min->setStyleSheet("QLabel{color: rgb(70,150,70);font-size: 25px}");
    l_max->setStyleSheet("QLabel{color: rgb(70,150,70);font-size: 25px}");
    l_min->move(50 + x_disp, line1);
    l_max->move(50 + x_disp, line2);

    l_x_size = new QLabel("Ancho:");
    l_y_size = new QLabel("Alto   :");
    l_x_size->setParent(container);
    l_y_size->setParent(container);
    l_x_size->setStyleSheet("QLabel{color: rgb(70,150,70);font-size: 25px}");
    l_y_size->setStyleSheet("QLabel{color: rgb(70,150,70);font-size: 25px}");
    l_x_size->move(260 + x_disp, line1);
    l_y_size->move(260 + x_disp, line2);
    //spin boxes
    sb_min = new QSpinBox(container);
    sb_min->setMinimum(-100);
    sb_min->setMaximum(0);
    sb_min->setValue(0);
    sb_min->move(160 + x_disp, line1);
    sb_min->setFixedHeight(30);
    sb_min->setFixedWidth(80);
    sb_min->setStyleSheet("QSpinBox{color: rgb(255,255,255);background-color: rgba(0,120,0,60);font-size: 15px}");

    sb_max= new QSpinBox(container);
    sb_max->setMinimum(1);
    sb_max->setMaximum(100);
    sb_max->setValue(1);
    sb_max->move(160 + x_disp, line2);
    sb_max->setFixedHeight(30);
    sb_max->setFixedWidth(80);
    sb_max->setStyleSheet("QSpinBox{color: rgb(255,255,255);background-color: rgba(0,120,0,60);font-size: 15px}");

    sb_x_size = new QSpinBox(container);
    sb_x_size->setMinimum(1);
    sb_x_size->setMaximum(maxmimo);
    sb_x_size->setValue(10);
    sb_x_size->move(370+ x_disp,line1);
    sb_x_size->setFixedHeight(30);
    sb_x_size->setFixedWidth(80);
    sb_x_size->setStyleSheet("QSpinBox{color: rgb(255,255,255);background-color: rgba(0,120,0,60);font-size: 15px}");

    sb_y_size= new QSpinBox(container);
    sb_y_size->setMinimum(1);
    sb_y_size->setMaximum(maxmimo);
    sb_y_size->setValue(10);
    sb_y_size->move(370 + x_disp, line2);
    sb_y_size->setFixedHeight(30);
    sb_y_size->setFixedWidth(80);
    sb_y_size->setStyleSheet("QSpinBox{color: rgb(255,255,255);background-color: rgba(0,120,0,60);font-size: 15px}");

    //name
    l_name = new QLabel("Nombre:");
    l_name->setParent(container);
    l_name->move(x_disp+50,y_disp+400);
    l_name->setStyleSheet("QLabel{color: rgb(70,150,70);font-size: 25px}");

    te_name = new QLineEdit();
    te_name->setText("0");
    te_name->setParent(container);
    te_name->move(x_disp+160,y_disp+400);
    te_name->setStyleSheet("QLineEdit{color: rgb(255,255,255);background-color: rgba(0,120,0,60);font-size: 18px}");

    pb_crear = new QProgressBar (container);
    pb_crear->move(50 + x_disp, 570 + y_disp);
    pb_crear->setFixedSize(400,40);
    pb_crear->setVisible(false);




    //botones de opciones
    b_editar = new QPushButton("editar",container);
    b_observar = new QPushButton("Observar",container);
    b_operar = new QPushButton("Operar",container);
    b_editar->move(30, 140);
    b_observar->move(150, 140);
    b_operar->move(280, 140);
    b_editar->setStyleSheet("QPushButton{background-color: rgba(0,80,10,120);font-size: 18px}");
    b_observar->setStyleSheet("QPushButton{background-color: rgba(0,120,25,120);font-size: 18px}");
    b_operar->setStyleSheet("QPushButton{background-color: rgba(0,140,60,120);font-size: 18px}");

    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(10);


    //elementos de operar--------------------------------------------------
    x_disp = 0;
    y_disp = 0;

    b_sumar = new QPushButton("Sumar",container);
    b_multiplicar = new QPushButton("Multiplicar",container);
    b_transpuesta = new QPushButton("Transpuesta",container);
    b_sumar_escalar = new QPushButton("Mult escalar",container);
    b_rango = new QPushButton("Rango",container);
    b_salvar = new QPushButton("Salvar Ultima respuesta",container);
    b_remove = new QPushButton("Remover",container);
    b_sumar->move(60+x_disp,400+y_disp);
    b_multiplicar->move(120+x_disp,480+y_disp);
    b_transpuesta->move(190+x_disp,400+y_disp);
    b_sumar_escalar->move(250+x_disp,480+y_disp);
    b_rango->move(320+x_disp,400+y_disp);
    b_salvar->move(750+x_disp,450+y_disp);
    b_remove->move(680+x_disp,600+y_disp);
    b_sumar->setStyleSheet("QPushButton{color: rgb(255,255,255);background-color: rgba(10,53,0,60);font-size: 18px}");
    b_multiplicar->setStyleSheet("QPushButton{color: rgb(255,255,255);background-color: rgba(10,53,0,60);font-size: 18px}");
    b_transpuesta->setStyleSheet("QPushButton{color: rgb(255,255,255);background-color: rgba(10,53,0,60);font-size: 20px}");
    b_sumar_escalar->setStyleSheet("QPushButton{color: rgb(255,255,255);background-color: rgba(10,53,0,60);font-size: 18px}");
    b_rango->setStyleSheet("QPushButton{color: rgb(150,150,150);background-color: rgba(10,10,10,60);font-size: 18px}");
    b_sumar->setFixedSize(130,60);
    b_multiplicar->setFixedSize(130,60);
    b_transpuesta->setFixedSize(130,60);
    b_sumar_escalar->setFixedSize(130,60);
    b_rango->setFixedSize(130,60);

    pb_operar = new QProgressBar(container);
    pb_operar->move(x_disp+105,y_disp+300);
    pb_operar->setFixedSize(300,50);
    pb_operar->setVisible(false);

    sb_threads = new QSpinBox(container);
    sb_cell_size = new QSpinBox(container);
    sb_threads->setMinimum(1);
    sb_threads->setMaximum(1000);
    sb_cell_size->setMinimum(1);
    sb_cell_size->setMaximum(4);
    sb_cell_size->move(780+x_disp,200+y_disp);
    sb_threads->move(780+x_disp,250+y_disp);
    sb_cell_size->setFixedWidth(80);
    sb_threads->setFixedWidth(80);
    l_n_threads = new QLabel("Threads: ",container);
    l_cell_Size = new QLabel("Tamaño(bytes):",container);
    l_n_threads->move(x_disp+680,y_disp+250);
    l_cell_Size->move(x_disp+680,y_disp+200);
    sb_threads->setVisible(false);
    sb_cell_size->setVisible(false);
    l_n_threads->setVisible(false);
    l_cell_Size->setVisible(false);

    sb_escal = new QSpinBox(container);
    sb_escal->setMinimum(-100);
    sb_escal->setMaximum(100);
    sb_escal->move(x_disp+380,y_disp+500);
    sb_escal->setStyleSheet("QSpinBox{background-color: rgba(40,80,40,30);font-size: 20;color: rgba(130,130,130,150)}");
    sb_escal->setValue(5);


    le_name = new QLineEdit(container);
    le_name->move(765+x_disp,480+y_disp);

    l_elementos = new QLabel(container);



    operandos = new v_display(container,600+x_disp,630+y_disp);

    operar_visibilidad(false);
    operando  =false;

    names = new QVector<QString>();
    pending_names = new QVector<QString>();
    pendientes = new QVector<int>();


    //elementos de observar matriz------------------------------------------
    m_disp = new v_matix_Display(container);
    m_disp->set_visibility(false);
    l_prop = new QLabel(container);
    l_prop->setStyleSheet("QLabel{font-size: 15px}");
    l_prop->move(450,120);
    l_prop->setFixedSize(700,50);

    //operador---------------------------------------------------------------
    op = new Operator();

    //objeto que contiene las matrices---------------------------------------
    matrices = new List_Display(scene);
    /*matrices->add_element(QString("Gato"));
    matrices->add_element(QString("Perro"));
    matrices->add_element(QString("Avion"));*/

    //se asigna la scena ----------------------------------------------------
    container->setScene(scene);
    container->setMinimumSize(640,480);


    //signals y slots---------------------------------------------------------
    connect(matrices,SIGNAL(on_button(int)),this,SLOT(on_l_button(int)));
    connect(b_crear,SIGNAL(released()),this,SLOT(onCrear()));
    connect(b_observar,SIGNAL(released()),this,SLOT(onObservar()));
    connect(b_editar,SIGNAL(released()),this,SLOT(onEditar()));
    connect(f_thread,SIGNAL(progress(int)),this,SLOT(onProgressMatrix(int)));
    connect(f_thread,SIGNAL(n_m()),this,SLOT(onNewMatrix()));
    connect(b_operar,SIGNAL(released()),this,SLOT(onOperar()));
    connect(b_sumar,SIGNAL(released()),this,SLOT(onSumar()));
    connect(b_multiplicar,SIGNAL(released()),this,SLOT(onMultiplicar()));
    connect(b_sumar_escalar,SIGNAL(released()),this,SLOT(onMultiplicar_e()));
    connect(b_transpuesta,SIGNAL(released()),this,SLOT(onTrans()));
    connect(b_salvar,SIGNAL(released()),this,SLOT(onSalvar()));
    connect(op,SIGNAL(progres(double)),this,SLOT(onProgresOp(double)));
    connect(op,SIGNAL(finished_op()),this,SLOT(onFinishedOp()));

}

void screen::mostrar()
{

    container->show();


}

void screen::on_l_button(int id)
{
    //qDebug()<<"matriz: "<<id<<"   x: "<<all_matrix_size->at(id)->x()<<"   y: "<<all_matrix_size->at(id)->y();

    if(operando){
        pendientes->push_back(id);
        pending_names->push_back(names->at(id));
        qDebug()<<"agregado: "<<names->at(id);
        operandos->actualizar(pending_names);
    }else if (observando){
        m_disp->actualize(all_matrix->at(id),all_matrix_size->at(id));
        emit clear();
        t_verificar * t = new t_verificar();
        t->set_up(all_matrix->at(id));

        connect(t,SIGNAL(res(QString)),this,SLOT(onProps(QString)));
        connect(this,SIGNAL(clear()),t,SLOT(on_clear()));
        connect(t,SIGNAL(finished()),t,SLOT(deleteLater()));
        t->start();}
}

void screen::onCrear()
{
    b_editar->setVisible(false);
    b_observar->setVisible(false);
    b_crear->setVisible(false);
    pb_crear->setVisible(true);
    b_operar->setVisible(false);

    container->horizontalScrollBar()->setSliderPosition(0);
    container->verticalScrollBar()->setSliderPosition(0);

    QFile* arr = files->createFile(te_name->text().append(".m"));
    all_matrix->push_back(arr);
    all_matrix_size->push_back(new QPoint(sb_x_size->value(),sb_y_size->value()));
    random_matrix(arr,sb_x_size->value(),sb_y_size->value(),sb_max->value(),sb_min->value());

    contador++;
    matrices->add_element(te_name->text());
    names->push_back(te_name->text());
    te_name->setText(QString::number(contador));
    le_name->setText(QString::number(contador));



}

void screen::onObservar()
{   m_disp->set_visibility(true);
    crear_visibilidad(false);
    operar_visibilidad(false);
    l_prop->setVisible(true);
    container->horizontalScrollBar()->setSliderPosition(0);
    container->verticalScrollBar()->setSliderPosition(0);
    operando = false;
    observando = true;
}

void screen::onEditar()
{
    l_prop->setVisible(false);
    m_disp->set_visibility(false);
    crear_visibilidad(true);
    operar_visibilidad(false);
    container->horizontalScrollBar()->setSliderPosition(0);
    container->verticalScrollBar()->setSliderPosition(0);
    operando = false;
    observando = false;
}

void screen::closeEvent()
{
    QFile *del;
    for(int i = 0; i < all_matrix->size(); i++){
        del = all_matrix->at(i);
        all_matrix->removeAt(i);
        delete del;
    }
}

void screen::onNewMatrix()
{
    b_crear->setVisible(true);
    pb_crear->setVisible(false);
    b_editar->setVisible(true);
    b_observar->setVisible(true);
    b_operar->setVisible(true);
}

void screen::onProgressMatrix(int v)
{
    pb_crear->setValue(v);
}

void screen::onOperar()
{
    emit clear();
    m_disp->set_visibility(false);
    crear_visibilidad(false);
    operar_visibilidad(true);
    operando = true;
    observando = false;
    l_prop->setVisible(false);
}

void screen::onSumar()
{
    if(pendientes->size()>1){
        pb_operar->setVisible(true);
        op_vis(false);
        op->sumar(all_matrix->at(pendientes->at(pendientes->size()-1)),all_matrix->at(pendientes->at(pendientes->size()-2)),sb_threads->value());
        pendientes->pop_back();
        pendientes->pop_back();
        pending_names->pop_back();
        pending_names->pop_back();
        operandos->actualizar(pending_names);

    }
}

void screen::onMultiplicar()
{
    if(pendientes->size()>1){
        pb_operar->setVisible(true);
        op_vis(false);
        op->multiplicar(all_matrix->at(pendientes->at(pendientes->size()-1)),all_matrix->at(pendientes->at(pendientes->size()-2)),sb_threads->value());
        pendientes->pop_back();
        pendientes->pop_back();
        pending_names->pop_back();
        pending_names->pop_back();
        operandos->actualizar(pending_names);
    }
}

void screen::onMultiplicar_e()
{
    if(pendientes->size()>0){
        pb_operar->setVisible(true);
        op_vis(false);
        op->sumar_escalar(all_matrix->at(pendientes->at(pendientes->size()-1)),sb_escal->value(),sb_cell_size->value(),sb_threads->value());
        pendientes->pop_back();
        pending_names->pop_back();
        operandos->actualizar(pending_names);

    }
}

void screen::onTrans()
{
    if(pendientes->size()>0){
        pb_operar->setVisible(true);
        op_vis(false);
        op->transpuesta(all_matrix->at(pendientes->at(pendientes->size()-1)),sb_cell_size->value());
        pendientes->pop_back();
        pending_names->pop_back();
        operandos->actualizar(pending_names);

    }
}

void screen::onSalvar()
{

    container->horizontalScrollBar()->setSliderPosition(0);
    container->verticalScrollBar()->setSliderPosition(0);

    QString name =le_name->text().append("r.m");
    //elimino el archivo si ya existe
    QFile::remove(name);

    QFile* arr = op->get_res();
    arr->rename(name);
    qDebug()<<"guardado como"<<arr->fileName();

    arr->close();

    arr = new QFile(name);
    qDebug()<<arr<<name;
    arr->open(QIODevice::ReadWrite| QIODevice::ReadOnly );
    all_matrix->push_back(arr);
    all_matrix_size->push_back(op->getSize());
    op->n_f();

    contador++;
    matrices->add_element(le_name->text().append("r"));
    names->push_back(le_name->text().append("r"));
    te_name->setText(QString::number(contador));
    le_name->setText(QString::number(contador));
}

void screen::onProgresOp(double p)
{
    pb_operar->setValue((int)p);

}

void screen::onFinishedOp()
{
    pb_operar->setVisible(false);
    op_vis(true);
}

void screen::onProps(QString s)
{
    //qDebug()<<s;
    l_prop->setText(s);
}


void screen::crear_visibilidad(bool v)
{
    b_crear->setVisible(v);
    sb_min->setVisible(v);
    sb_max->setVisible(v);
    sb_x_size->setVisible(v);
    sb_y_size->setVisible(v);
    l_min->setVisible(v);
    l_max->setVisible(v);
    l_x_size->setVisible(v);
    l_y_size->setVisible(v);
    l_titulo_crear->setVisible(v);
    l_name->setVisible(v);
    te_name->setVisible(v);
    l_fondo_crear->setVisible(v);
}

void screen::operar_visibilidad(bool v)
{
    b_sumar->setVisible(v);
    b_multiplicar->setVisible(v);
    b_transpuesta->setVisible(v);
    b_sumar_escalar->setVisible(v);
    b_rango->setVisible(v);

    b_salvar->setVisible(v);
    b_remove->setVisible(v);
    le_name->setVisible(v);

    l_elementos->setVisible(v);
    operandos->set_visible(v);

    sb_threads->setVisible(v);
    sb_cell_size->setVisible(v);
    l_n_threads->setVisible(v);
    l_cell_Size->setVisible(v);
    sb_escal->setVisible(v);

}

void screen::random_matrix(QFile *m, int x, int y, int max, int min)
{

    f_thread->w_document(m,x,y,max,min);


}

void screen::op_vis(bool v)
{
    b_sumar->setVisible(v);
    b_sumar_escalar->setVisible(v);
    b_transpuesta->setVisible(v);
    b_multiplicar->setVisible(v);
    b_rango->setVisible(v);
    b_editar->setVisible(v);
    b_observar->setVisible(v);
    b_operar->setVisible(v);
    b_salvar->setVisible(v);
    le_name->setVisible(v);
}

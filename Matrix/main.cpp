#include <QApplication>
#include "screen.h"
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    screen *ventana = new screen();
    ventana->mostrar();
    QObject::connect(&a,SIGNAL(aboutToQuit()),ventana,SLOT(closeEvent()));

    return a.exec();
}

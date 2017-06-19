#include "file_manager.h"
#include <QIODevice>
#include <QDebug>


file_manager::file_manager()
{

}

QFile* file_manager::createFile(QString s)
{
    QFile* file = new QFile(s);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ReadWrite))
    {
        qDebug() << "FAIL TO CREATE FILE / FILE NOT EXIT***";
    }
    return file;
}

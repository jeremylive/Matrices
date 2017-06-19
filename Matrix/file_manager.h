#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "QString"
#include "QFile"

class file_manager
{

public:
    file_manager();
    QFile* createFile(QString s);
private:
};

#endif // FILE_MANAGER_H

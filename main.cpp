#include "home.h"

#include <QApplication>
#include <opedb.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    opedb::getInstance().init();

    home w;
    w.show();
    return a.exec();
}

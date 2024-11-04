#include "home.h"

#include <QApplication>
#include <opedb.h>
#include <getinfo.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    opedb::getInstance().init();
    //getinfo::getinstance().getDev("521xueweihan");


    home w;
    w.show();
    return a.exec();
}

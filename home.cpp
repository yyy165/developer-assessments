#include "home.h"
#include "ui_home.h"

home::home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::home)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
}

home::~home()
{
    delete ui;
}

void home::on_closeBT_clicked()
{
    sp->close();
    this->close();
}


void home::on_selectNameBT_clicked()
{
    sp->close();
    QRect rect = this->geometry();
    int x = rect.x();
    int y = rect.y();
    rect = this->ui->selectNameBT->geometry();
    x += rect.x();
    y += rect.y();
    sp->setGeometry(x - 220,y + 20,255,100);
    sp->show();
}


void home::on_selectNationBT_clicked()
{
    sp->close();
    QRect rect = this->geometry();
    int x = rect.x();
    int y = rect.y();
    rect = this->ui->selectNationBT->geometry();
    x += rect.x();
    y += rect.y();
    sp->setGeometry(x - 220,y + 20,255,100);
    sp->show();
}


void home::on_selectAreaBT_clicked()
{
    sp->close();
    QRect rect = this->geometry();
    int x = rect.x();
    int y = rect.y();
    rect = this->ui->selectAreaBT->geometry();
    x += rect.x();
    y += rect.y();
    sp->setGeometry(x - 220,y + 20,255,100);
    sp->show();
}


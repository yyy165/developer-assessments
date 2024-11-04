#include "selectpage.h"
#include "ui_selectpage.h"

selectPage::selectPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::selectPage)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
}

selectPage::~selectPage()
{
    delete ui;
}

void selectPage::on_clearBt_clicked()
{
    ui->selectEdit->clear();
    this->close();
}


void selectPage::on_selectBt_clicked()
{
    QString name = ui->selectEdit->text();
    emit nameInfoReady(name);
    ui->selectEdit->clear();
}


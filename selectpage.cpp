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
    this->close();
}


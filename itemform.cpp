#include "itemform.h"
#include "ui_itemform.h"

itemform::itemform(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::itemform)
{
    ui->setupUi(this);
    ui->areaLB->setWordWrap(true);
}

itemform::~itemform()
{
    delete ui;
}

void itemform::setInfo(int id, dev info)
{
    ui->IDLB->setText(QString::number(id));
    ui->nameLB->setText(info.username);
    ui->nationLB->setText(info.nation);
    if(info.nation_confidence == 0)
    {
        ui->confidenceLB->setText("N/A");
    }
    else
    {
        ui->confidenceLB->setText(QString::number(info.nation_confidence));
    }
    ui->scoreLB->setText(QString::number(info.talent_rank));
    ui->areaLB->setText(info.area);
}

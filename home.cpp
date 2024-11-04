#include "home.h"
#include "ui_home.h"

home::home(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::home)
    , sp(nullptr)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    QVector<dev> info = opedb::getInstance().select();
    for(int i = 0;i < info.size();i++)
    {
        itemform* stuitem = new itemform;
        stuitem->setInfo(i + 1, info[i]);
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(780, 60));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, stuitem);

    }
}

home::~home()
{
    delete ui;
}

void home::on_closeBT_clicked()
{
    this->close();
}


void home::on_selectNameBT_clicked()
{
    if(!sp)
    {
        sp = new selectPage(this);
    }
    connect(sp, &selectPage::infoReady, this, &home::receiveNameInfo);
    QRect rect = this->ui->selectNameBT->geometry();
    int x = rect.x();
    int y = rect.y();
    sp->setGeometry(x - 200,y + 20,255,100);
    sp->show();
}


void home::on_selectNationBT_clicked()
{
    if(!sp)
    {
        sp = new selectPage(this);
    }
    connect(sp, &selectPage::infoReady, this, &home::receiveNationInfo);
    QRect rect = this->ui->selectNationBT->geometry();
    int x = rect.x();
    int y = rect.y();
    sp->setGeometry(x - 200,y + 20,255,100);
    sp->show();

}


void home::on_selectAreaBT_clicked()
{
    if(!sp)
    {
        sp = new selectPage(this);
    }
    connect(sp, &selectPage::infoReady, this, &home::receiveAreaInfo);
    QRect rect = this->ui->selectAreaBT->geometry();
    int x = rect.x();
    int y = rect.y();
    sp->setGeometry(x - 200,y + 20,255,100);
    sp->show();
}

void home::receiveNameInfo(const QString &name)
{
    qDebug() << name;
    QVector<dev> info;
    if(name == "")
    {
        info = opedb::getInstance().select();
    }
    else
    {
        info = opedb::getInstance().selectByName(name);
    }
    ui->listWidget->clear();
    for(int i = 0;i < info.size();i++)
    {
        itemform* stuitem = new itemform;
        stuitem->setInfo(i + 1, info[i]);
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(780, 60));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, stuitem);
    }
}

void home::receiveNationInfo(const QString &nation)
{
    qDebug() << nation;
    QVector<dev> info = opedb::getInstance().selectByNation(nation);
    ui->listWidget->clear();
    for(int i = 0;i < info.size();i++)
    {
        itemform* stuitem = new itemform;
        stuitem->setInfo(i + 1, info[i]);
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(780, 60));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, stuitem);
    }
}

void home::receiveAreaInfo(const QString &area)
{
    qDebug() << area;
    QVector<dev> info = opedb::getInstance().selectByArea(area);
    ui->listWidget->clear();
    for(int i = 0;i < info.size();i++)
    {
        itemform* stuitem = new itemform;
        stuitem->setInfo(i + 1, info[i]);
        QListWidgetItem* item = new QListWidgetItem;
        item->setSizeHint(QSize(780, 60));
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, stuitem);
    }
}


#include "opedb.h"

opedb::opedb(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

opedb &opedb::getInstance()
{
    static opedb instance;
    return instance;
}

//连接数据库
void opedb::init()
{
    db.setHostName("localhost");
    db.setDatabaseName("D:\\QT\\Project\\sqltry\\devassess.db");
    if(db.open())
    {
        qDebug() << "连接数据库成功" ;
    }
    else
    {
        qDebug() << "连接数据库失败" ;
    }
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON"); // 开启外键约束
}

//建表
void opedb::createTable()
{
    QSqlQuery query;
    QString create = "create table developers(ID integer primary key not null" //开发者id
                     ", username varchar(255) not null" // 开发者名
                     ", nation varchar(255)" // 地区
                     ", nation_confidence double" // 地区置信度
                     ", talent_rank integer" // 评分
                     ", area varchar(255))"; // 领域
    qDebug() << create;
    if(query.exec(create))
    {
        qDebug() << "成功建立developers" ;
    }
    else
    {
        qDebug() << "建立developers失败" ;
    }
    create = "create table projects(ID integer primary key not null" // 项目id
             ", name varchar(255) not null" // 项目名称
             ", importance double)"; // 重要性
    qDebug() << create;
    if(query.exec(create))
    {
        qDebug() << "成功建立projects" ;
    }
    else
    {
        qDebug() << "建立projects失败" ;
    }
    create = "create table contributions(ID integer primary key not null" // 项目贡献度id
             ", developer_id integer not null" // 项目参与者id
             ", project_id integer not null" // 项目id
             ", ratio double" // 贡献度
             ", foreign key(developer_id) references developers(ID)"
             ", foreign key(project_id) references projects(ID))";
    qDebug() << create;
    if(query.exec(create))
    {
        qDebug() << "成功建立contributions" ;
    }
    else
    {
        qDebug() << "建立contributions失败" ;
    }
}

//关闭数据库
opedb::~opedb()
{
    db.close();
}

//插入
void opedb::insertDev(int ID, QString username, QString nation, double nation_confidence, int talent_rank, QString area)
{
    QSqlQuery query;
    QString insert = QString("insert into developers (id, username, nation, nation_confidence, talent_rank, area)"
                             " values (%1, '%2', '%3', %4, %5, '%6')").arg(ID).arg(username).arg(nation).arg(nation_confidence).arg(talent_rank).arg(area);

    qDebug() << insert;
    if(query.exec(insert))
    {
        qDebug() << "插入developers成功" ;
    }
    else
    {
        qDebug() << "插入developers失败" ;
    }
}

void opedb::insertPro(int ID, QString name, double importance)
{
    QSqlQuery query;
    QString insert = QString("insert into projects (id, name, importance)"
                             " values (%1, '%2', %3)").arg(ID).arg(name).arg(importance);

    qDebug() << insert;
    if(query.exec(insert))
    {
        qDebug() << "插入projects成功" ;
    }
    else
    {
        qDebug() << "插入projects失败" ;
    }
}

void opedb::insertCon(int developer_id, int project_id, double ratio)
{
    QSqlQuery query;
    QString insert = QString("insert into contributions (developer_id, project_id, ratio)"
                             " values (%1, %2, %3)").arg(developer_id).arg(project_id).arg(ratio);

    qDebug() << insert;
    if(query.exec(insert))
    {
        qDebug() << "插入contributions成功" ;
    }
    else
    {
        qDebug() << "插入contributions失败" ;
    }
}

//查看developers信息
QVector<dev> opedb::select()
{
    QVector<dev> result;
    QSqlQuery query;
    QString select = "select * from developers";
    query.exec(select);
    if(query.next())
    {
        dev* d = new dev();
        d->ID = query.value(0).toInt();
        d->username = query.value(1).toString();
        d->nation = query.value(2).toString();
        d->nation_confidence = query.value(3).toDouble();
        d->talent_rank = query.value(4).toInt();
        d->area = query.value(5).toString();
        result.append(*d);
    }
    for(int i = 0;i < result.size();i++)
    {
        qDebug() << result[i].ID << result[i].username;
    }
    return result;
}

// 按用户名搜索
dev opedb::selectByName(QString username)
{
    QSqlQuery query;
    QString select = QString("select * from developers where username = '%1'").arg(username);
    qDebug() << select;
    query.exec(select);
    dev* d = new dev();
    while(query.next())
    {
        d->ID = query.value(0).toInt();
        d->username = query.value(1).toString();
        d->nation = query.value(2).toString();
        d->nation_confidence = query.value(3).toDouble();
        d->talent_rank = query.value(4).toInt();
        d->area = query.value(5).toString();
        qDebug() << d->ID << d->username;
    }

    return *d;
}

QVector<dev> opedb::selectByNation(QString nation)
{
    QVector<dev> result;
    QSqlQuery query;
    QString select = QString("select * from developers where nation like '%%1%'").arg(nation);
    query.exec(select);
    while(query.next())
    {
        dev* d = new dev();
        d->ID = query.value(0).toInt();
        d->username = query.value(1).toString();
        d->nation = query.value(2).toString();
        d->nation_confidence = query.value(3).toDouble();
        d->talent_rank = query.value(4).toInt();
        d->area = query.value(5).toString();
        result.append(*d);
    }
    for(int i = 0;i < result.size();i++)
    {
        qDebug() << result[i].ID << result[i].username;
    }
    return result;
}

QVector<dev> opedb::selectByArea(QString area)
{
    QVector<dev> result;
    QSqlQuery query;
    QString select = QString("select * from developers where area like '%%1%' order by talent_rank DESC").arg(area);
    qDebug() << select;
    query.exec(select);
    while(query.next())
    {
        dev* d = new dev();
        d->ID = query.value(0).toInt();
        d->username = query.value(1).toString();
        d->nation = query.value(2).toString();
        d->nation_confidence = query.value(3).toDouble();
        d->talent_rank = query.value(4).toInt();
        d->area = query.value(5).toString();
        result.append(*d);
    }
    qDebug() << result.size();
    for(int i = 0;i < result.size();i++)
    {
        qDebug() << result[i].ID << result[i].username << result[i].nation << result[i].talent_rank << result[i].area;
    }
    return result;
}

void opedb::updateArea(QString username, QString area)
{
    QSqlQuery query;
    QString update = QString("update developers set area = '%1' where username = '%2'").arg(area).arg(username);
    qDebug() << update;
    if(query.exec(update))
    {
        qDebug() << "area更新成功";
    }
    else
    {
        qDebug() << "area更新失败";
    }
}

void opedb::updateNation(QString username, QString nation)
{
    QSqlQuery query;
    QString update = QString("update developers set nation = '%1' where username = '%2'").arg(nation).arg(username);
    qDebug() << update;
    if(query.exec(update))
    {
        qDebug() << "nation更新成功";
    }
    else
    {
        qDebug() << "nation更新失败";
    }
}

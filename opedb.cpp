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
    db.setDatabaseName("D:\\QT\\Project\\dev-assess\\devassess.db");
    if(db.open())
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "连接数据库成功" ;
    }
    else
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "连接数据库失败" ;
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
    qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << create;
    if(query.exec(create))
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "成功建立developers" ;
    }
    else
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "建立developers失败" ;
    }
    create = "create table projects(ID integer primary key not null" // 项目id
             ", name varchar(255) not null" // 项目名称
             ", importance double)"; // 重要性
    qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << create;
    if(query.exec(create))
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "成功建立projects" ;
    }
    else
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "建立projects失败" ;
    }
    create = "create table contributions(ID integer primary key not null" // 项目贡献度id
             ", developer_id integer not null" // 项目参与者id
             ", project_id integer not null" // 项目id
             ", ratio double" // 贡献度
             ", foreign key(developer_id) references developers(ID)"
             ", foreign key(project_id) references projects(ID))";
    qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << create;
    if(query.exec(create))
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "成功建立contributions" ;
    }
    else
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "建立contributions失败" ;
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

    qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << insert;
    if(query.exec(insert))
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "插入developers成功" ;
    }
    else
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "插入developers失败" ;
    }
}

void opedb::insertPro(int ID, QString name, double importance)
{
    QSqlQuery query;
    QString insert = QString("insert into projects (id, name, importance)"
                             " values (%1, '%2', %3)").arg(ID).arg(name).arg(importance);

    qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << insert;
    if(query.exec(insert))
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "插入projects成功" ;
    }
    else
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "插入projects失败" ;
    }
}

void opedb::insertCon(int developer_id, int project_id, double ratio)
{
    QSqlQuery query;
    QString insert = QString("insert into contributions (developer_id, project_id, ratio)"
                             " values (%1, %2, %3)").arg(developer_id).arg(project_id).arg(ratio);

    qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << insert;
    if(query.exec(insert))
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "插入contributions成功" ;
    }
    else
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "插入contributions失败" ;
    }
}

//查看developers信息
QVector<dev> opedb::select()
{
    QVector<dev> result;
    QSqlQuery query;
    QString select = "select * from developers order by talent_rank DESC";
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
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << result[i].ID << result[i].username;
    }
    return result;
}

// 按用户名搜索
QVector<dev> opedb::selectByName(QString username)
{
    QVector<dev> result;
    QSqlQuery query;
    QString select = QString("select * from developers where username = '%1'").arg(username);
    qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << select;
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
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << d->ID << d->username;
        result.append(*d);
    }

    return result;
}

QVector<dev> opedb::selectByNation(QString nation)
{
    QVector<dev> result;
    QSqlQuery query;
    QString select = QString("select * from developers where nation like '%%1%' order by talent_rank DESC").arg(nation);
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
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << result[i].ID << result[i].username;
    }
    return result;
}

QVector<dev> opedb::selectByArea(QString area)
{
    QVector<dev> result;
    QSqlQuery query;
    QString select = QString("select * from developers where area like '%%1%' order by talent_rank DESC").arg(area);
    qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << select;
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
    qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << result.size();
    for(int i = 0;i < result.size();i++)
    {
        qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << result[i].ID << result[i].username << result[i].nation << result[i].talent_rank << result[i].area;
    }
    return result;
}

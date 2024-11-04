#ifndef OPEDB_H
#define OPEDB_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QVector>

struct dev{
    int ID;
    QString username;
    QString nation;
    double nation_confidence;
    int talent_rank;
    QString area;
};

class opedb : public QObject
{
    Q_OBJECT
public:
    explicit opedb(QObject *parent = nullptr);
    static opedb& getInstance();
    void init();
    void createTable(); // 建表
    ~opedb();
    void insertDev(int ID, QString username, QString nation, double nation_confidence, int talent_rank, QString area);
    void insertPro(int ID, QString name, double importance);
    void insertCon(int developer_id, int project_id, double ratio);
    QVector<dev> select();
    QVector<dev> selectByName(QString username);
    QVector<dev> selectByNation(QString nation);
    QVector<dev> selectByArea(QString area);
private:
    QSqlDatabase db;
signals:
};

#endif // OPEDB_H

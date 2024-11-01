#ifndef GETINFO_H
#define GETINFO_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <opedb.h>
#include <unordered_set>
#include <unordered_map>
#include <QMessageBox>

class getinfo : public QObject
{
    Q_OBJECT
public:
    explicit getinfo(QObject *parent = nullptr);
    void getDev(QString username);
    static getinfo& getinstance();
    void getPro(QString username);
    void getCon(QString username, int project_id, QString name);
    QString getNation(QString username);
    void location(QString followname);

signals:

private:
    std::unordered_set<QString> area_set;
    std::unordered_map<QString, int> locHash;

};

#endif // GETINFO_H

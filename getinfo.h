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

class getinfo : public QObject
{
    Q_OBJECT
public:
    explicit getinfo(QObject *parent = nullptr);
    void getDev(QString username);
    static getinfo& getinstance();
    void getPro(QString username);
    void getCon(QString username, int project_id, QString name);

signals:

private:

};

#endif // GETINFO_H

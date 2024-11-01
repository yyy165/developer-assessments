#include "getinfo.h"

getinfo::getinfo(QObject *parent)
    : QObject{parent}
{

}

void getinfo::getDev(QString username)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QString url = "https://api.github.com/users/" + username;
    qDebug() << url;
    QNetworkRequest request((QUrl(url)));
    QNetworkReply *reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished,[=](){
        if(reply->error() == QNetworkReply::NoError)
        {
            dev *d = new dev();
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObj = jsonDoc.object();
            //int ID, QString username, QString nation, double nation_confidence, int talent_rank, QString area
            d->ID = jsonObj["id"].toInt();
            d->username = jsonObj["login"].toString();
            if(jsonObj["location"].toString() == "")
            {
                d->nation = getNation(username);
            }
            else
            {
                d->nation = jsonObj["location"].toString();
            }
            d->nation_confidence = 0;
            d->talent_rank = 0;
            d->area = 0;
            opedb::getInstance().insertDev(d->ID, d->username,d->nation,  d->nation_confidence, d->talent_rank, d->area);
        }
        else
        {
            qDebug() << "获取开发者信息错误：" << reply->errorString();
        }
        reply->deleteLater();
    });
    getPro(username);
}

getinfo &getinfo::getinstance()
{
    static getinfo instance;
    return instance;
}

void getinfo::getPro(QString username)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QString url = "https://api.github.com/search/repositories?q=user:" + username + "&sort=stars";
    qDebug() << url;
    QNetworkRequest request((QUrl(url)));
    QNetworkReply *reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished,[=](){
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObject = jsonDoc.object();

            QJsonArray reposArray = jsonObject.value("items").toArray();
            double star_ratio = 0.7;
            double fork_ratio = 0.3;
            int star_max = 400000;
            int fork_max = 8000;
            area_set.clear();

            for (const QJsonValue &repoValue : reposArray) {
                QJsonObject repoObj = repoValue.toObject();
                int id = repoObj.value("id").toInt();
                QString name = repoObj.value("name").toString();
                double stars = repoObj.value("stargazers_count").toDouble();
                double forks = repoObj.value("forks_count").toDouble();
                double importance = stars / star_max * star_ratio + forks / fork_max * fork_ratio;
                QString language = repoObj.value("language").toString();
                qDebug() << language;
                if(language != "")
                {
                    area_set.insert(language);
                }
                qDebug() << id << " " << name << " "<< stars << " " << forks << " " << importance;
                opedb::getInstance().insertPro(id, name, importance);
                getCon(username, id, name);
            }
            QString area = "";
            for(const QString& language : area_set)
            {
                area = area + language + "、";
            }
            area.chop(1);
            opedb::getInstance().updateArea(username, area);
        }
        else
        {
            qDebug() << "获取项目信息错误：" << reply->errorString();
        }
        reply->deleteLater();
    });
}

void getinfo::getCon(QString username, int project_id, QString name)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QString url = "https://api.github.com/repos/" + username + "/" + name + "/contributors";
    QNetworkRequest request((QUrl(url)));
    QNetworkReply *reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished,[=](){
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObject = jsonDoc.object();
            QJsonArray reposArray = jsonDoc.array();
            int dev_con = 0; // 开发者贡献
            int sum_con = 0; // 所有人总贡献
            int developer_id = 0; // 开发者id
            qDebug() << url;

            for (const QJsonValue &repoValue : reposArray) {
                QJsonObject repoObj = repoValue.toObject();
                int n = repoObj.value("contributions").toInt();
                if(repoObj.value("login").toString() == username)
                {
                    developer_id = repoObj.value("id").toInt();
                    dev_con = n;
                }
                sum_con += n;
            }
            double ratio =  (double)dev_con / sum_con;
            opedb::getInstance().insertCon(developer_id, project_id, ratio);
        }
        else
        {
            qDebug() << "获取项目信息错误：" << reply->errorString();
        }
        reply->deleteLater();
    });
}

QString getinfo::getNation(QString username)
{
    QString nation = "";
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QString url = "https://api.github.com/users/" + username + "/following";
    qDebug() << url;
    QNetworkRequest request((QUrl(url)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "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");
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished,[=](){
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObject = jsonDoc.object();
            QJsonArray reposArray = jsonDoc.array();

            for (const QJsonValue &repoValue : reposArray) {
                QJsonObject repoObj = repoValue.toObject();
                QString followname = repoObj.value("login").toString();
                location(followname);
            }
        }
        else
        {
            qDebug() << "getNation错误：" << reply->errorString();
        }
        reply->deleteLater();
    });
    int sum = 0;
    int ans = 0;
    for(const auto& loc : locHash)
    {
        sum += loc.second;
        if(loc.second > ans)
        {
            nation = loc.first;
            ans = loc.second;
        }
    }
    qDebug() << nation << " " << ans << " " << sum;
    return nation;
}

void getinfo::location(QString followname)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QString url = "https://api.github.com/users/" + followname;
    qDebug() << url;
    QNetworkRequest request((QUrl(url)));
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished,[=](){
        if(reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObject = jsonDoc.object();
            QString location = jsonObject.value("location").toString();
            if(location != "")
            {
                locHash[location]++;
            }
            qDebug() << location;
        }
        else
        {
            qDebug() << "getLocation错误：" << reply->errorString();
        }
        reply->deleteLater();
    });
}

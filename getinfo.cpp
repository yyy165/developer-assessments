#include "getinfo.h"

getinfo::getinfo(QObject *parent)
    : QObject{parent}
{

}

void getinfo::getDev(QString username)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QString url = "https://api.github.com/users/" + username;
    qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << url;
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
                d->nation = "null";
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
            qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "获取开发者信息错误：" << reply->errorString();
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
    qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << url;
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

            for (const QJsonValue &repoValue : reposArray) {
                QJsonObject repoObj = repoValue.toObject();
                int id = repoObj.value("id").toInt();
                QString name = repoObj.value("name").toString();
                double stars = repoObj.value("stargazers_count").toDouble();
                double forks = repoObj.value("forks_count").toDouble();
                double importance = stars / star_max * star_ratio + forks / fork_max * fork_ratio;
                QString language = repoObj.value("language").toString();
                qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << language;

                qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << id << " " << name << " "<< stars << " " << forks << " " << importance;
                opedb::getInstance().insertPro(id, name, importance);
                getCon(username, id, name);
            }
        }
        else
        {
            qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "获取项目信息错误：" << reply->errorString();
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
            qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << url;

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
            qDebug() <<  __FILE__ <<  __LINE__ << Q_FUNC_INFO << ":" << "获取项目信息错误：" << reply->errorString();
        }
        reply->deleteLater();
    });
}

#include "ListThread.h"

ListThread::ListThread(QString id, QHash<int, QString> &musicList, bool is_album, ExtensionListWidget *parent)
    : parent(parent),musicList(musicList),id(id),is_album(is_album)
{
    url = QString("http://music.163.com/api/playlist/detail?id=%1"
            "&offset=0&total=true&limit=1001&csrf_token=358c82d006c539e72c6f68583a95ceb9").arg(id);
    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(finished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(url)));
}

ListThread::~ListThread()
{

}

void ListThread::run()
{

}

void ListThread::finished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError)
        return;
    QJsonObject obj = json.object().find("result").value().toObject();
    QJsonArray objList = obj.find("tracks").value().toArray();
    parent->tableClear();
    musicList.clear();
    for (int i = 0; i < objList.count(); i++)
    {
        QJsonObject songObj = objList.at(i).toObject();
        QString name = songObj.find("name").value().toString();
        QString url = songObj.find("mp3Url").value().toString();
        QJsonObject albumObj = songObj.find("album").value().toObject();
        QString album = albumObj.find("name").value().toString();
        QJsonArray artistsList = songObj.find("artists").value().toArray();
        QString artists = "";
        for (int j = 0; j < artistsList.count(); j++)
            artists.append(tr(" ") + artistsList.at(j).toObject().find("name").value().toString());
        musicList.insert(i + 1, url);
//        qDebug() << name << artists ;
        int num = parent->rowCount();
        QTableWidgetItem *temp = new QTableWidgetItem(QString::number(num + 1));
        temp->setTextAlignment(Qt::AlignCenter);
        parent->insertRow(num);
        parent->setItem(num, 0, temp);
        parent->setItem(num, 1, new QTableWidgetItem(name));
        parent->setItem(num, 2, new QTableWidgetItem(artists));
        if(is_album)
            parent->setItem(num, 3, new QTableWidgetItem(album));
    }
    reply->deleteLater();
    this->deleteLater();
}


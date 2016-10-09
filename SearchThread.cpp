#include "SearchThread.h"

SearchThread::SearchThread(QString keyWord, QHash<int,QString> &musicList, QHash<int, QString> &picList,
                           QHash<int, int> &songsId, ExtensionWidget *parent)
    : keyWord(keyWord), musicList(musicList), songsId(songsId), picList(picList),parent(parent)
{
    manager = new QNetworkAccessManager;
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(finished(QNetworkReply*)));
    startFunc();
}

SearchThread::~SearchThread()
{
    qDebug() <<"delete thread";
}

void SearchThread::run()
{

}

void SearchThread::startFunc()
{
    QUrl url("http://music.163.com/api/search/get/web");
    QNetworkRequest request(url);
    request.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    request.setRawHeader("Accept-Language", "zh-CN,zh;q=0.8,en-US;q=0.5,en;q=0.3");
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
    request.setRawHeader("Host", "music.163.com");
    request.setRawHeader("Referer", "http://music.163.com/");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (X11; Linux x86_64; rv:38.0) Gecko/20100101 Firefox/38.0");

    QByteArray data = "";
    data.append("s=" + keyWord + "&type=1&offset=0&total=true&limit=60");
    pe = DATA;
    qDebug() << "ok";
    manager->post(request, data);
}

void SearchThread::dealSearch(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError)
        return;
    QJsonObject obj = json.object().find("result").value().toObject();
    QJsonArray objList = obj.find("songs").value().toArray();
//test
    QFile writeFile("test2.xml");
    writeFile.open(QIODevice::WriteOnly | QIODevice::Text);
    Q_ASSERT(writeFile.isOpen());

    QTextStream out(&writeFile);
    out.setCodec("UTF-8");
    out << json.toJson(QJsonDocument::Indented);
    writeFile.flush();
    writeFile.close();
//
    parent->tableClear();
    musicList.clear();
    songsId.clear();
    picList.clear();
    for (int i = 0; i < objList.count(); i++)
    {
        QJsonObject songObj = objList.at(i).toObject();
        int songId = songObj.find("id").value().toInt();
        QString name = songObj.find("name").value().toString();
        QJsonArray artistsList = songObj.find("artists").value().toArray();
        QString artists = "";
        for (int j = 0; j < artistsList.count(); j++)
            artists.append(tr(" ") + artistsList.at(j).toObject().find("name").value().toString());
        QString album = songObj.find("album").value().toObject().find("name").value().toString();
        songsId.insert(songId, i + 1);
        qDebug() << name << artists <<songId << album;
        int num = parent->getTableList()->rowCount();
        QTableWidgetItem *temp = new QTableWidgetItem(QString::number(num + 1));
        temp->setTextAlignment(Qt::AlignCenter);
        parent->getTableList()->insertRow(num);
        parent->getTableList()->setItem(num, 0, temp);
        parent->getTableList()->setItem(num, 1, new QTableWidgetItem(name));
        parent->getTableList()->setItem(num, 2, new QTableWidgetItem(artists));
        parent->getTableList()->setItem(num, 3, new QTableWidgetItem(album));
    }
}

void SearchThread::getSongsUrl()
{

    QHash<int, int>::const_iterator it = songsId.begin();
    while (it != songsId.end())
    {
        QUrl url = QString("http://music.163.com/api/song/detail?ids=[%1]").arg(it.key());
        QNetworkRequest request(url);
        pe = URL;
        manager->get(request);
        it++;
    }
}

void SearchThread::dealSongId(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError)
        return;
    QJsonArray obj = json.object().find("songs").value().toArray();
    QString url = obj.at(0).toObject().find("mp3Url").value().toString();
    int id = obj.at(0).toObject().find("id").value().toInt();

    QJsonObject album = obj.at(0).toObject().find("album").value().toObject();
    QString url2 = album.find("blurPicUrl").value().toString();
    musicList.insert(songsId.value(id), url);
    picList.insert(songsId.value(id), url2);
}

void SearchThread::finished(QNetworkReply *reply)
{
    int statues = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    //http返回的状态码  200表示请求成功 403禁止 401未授权
    if (reply->error() != QNetworkReply::NoError)
    {
        pe = OTHER;
        reply->deleteLater();
        return;
    }
    if (statues == 200)
    {
        switch (pe)
        {
            case DATA:
                dealSearch(reply);
                getSongsUrl();
                break;
            case URL:
                dealSongId(reply);
                break;
            case OTHER:
                break;
            default:
                break;
        }
    }
    else
        qDebug()<<"请求失败";
    reply->deleteLater();
    //    this->deleteLater();		//释放当前线程
}

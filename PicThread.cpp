#include "PicThread.h"

PicThread::PicThread(QString musicName, QString musicArtist, QString picFilePath)
    : musicName(musicName), musicArtist(musicArtist), picFilePath(picFilePath)
{
    currentPicture = new QPixmap;
    manager = new QNetworkAccessManager;
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(finished(QNetworkReply*)));
    startFunc();
}

PicThread::~PicThread()
{

}

void PicThread::run()
{

}

void PicThread::finished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        pe = OTHER;
        reply->deleteLater();
        return;
    }
    switch (pe)
    {
        case DATA:
            dealSearch(reply);
            getSongUrl();
            break;
        case URL:
            dealSongId(reply);
        case DOWN:
            getPic(reply);
        default:
            break;
    }
    reply->deleteLater();
}

void PicThread::startFunc()
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
    data.append("s=" + musicName + musicArtist + "&type=1&offset=0&total=true&limit=1");
    pe = DATA;
    manager->post(request, data);
}

void PicThread::dealSearch(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError)
        return;
    QJsonObject obj = json.object().find("result").value().toObject();
    QJsonArray objList = obj.find("songs").value().toArray();
    QJsonObject songObj = objList.at(0).toObject();

    songId = songObj.find("id").value().toInt();

    if(songId == 0)
    {
        emit downloadPicOk(false, picFilePath);		//发送下载完毕信号
        return;
    }
    QString name = songObj.find("name").value().toString();
    QJsonArray artistsList = songObj.find("artists").value().toArray();
    QString artists = "";
    for (int j = 0; j < artistsList.count(); j++)
        artists.append(tr(" ") + artistsList.at(j).toObject().find("name").value().toString());
    QString album = songObj.find("album").value().toObject().find("name").value().toString();
    qDebug() << name << artists <<songId << album;
}

void PicThread::getSongUrl()
{
    QUrl url = QString("http://music.163.com/api/song/detail?ids=[%1]").arg(songId);
    QNetworkRequest request(url);
    pe = URL;
    manager->get(request);
}

void PicThread::dealSongId(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();
    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError)
        return;
    QJsonArray obj = json.object().find("songs").value().toArray();
    QJsonObject album = obj.at(0).toObject().find("album").value().toObject();
    picUrl = album.find("blurPicUrl").value().toString();           //获取到了图片链接
    qDebug()<<picUrl;
    if(picUrl.isEmpty())
    {
        emit downloadPicOk(false, picFilePath);		//发送下载完毕信号
        return;
    }

    pe = DOWN;
    manager->get(QNetworkRequest(QUrl(picUrl)));
}

void PicThread::getPic(QNetworkReply *reply)
{
//    picFile.setFileName(picFilePath);
//    picFile.open(QIODevice::WriteOnly);
//    picFile.write(reply->readAll());   //写入文件中
//    picFile.flush();
    currentPicture->loadFromData(reply->readAll());
    currentPicture->save(picFilePath);
//    if (picFile.isOpen())
//    {
//        picFile.close();
//    }
    emit downloadPicOk(true, picFilePath);		//发送下载完毕信号
}













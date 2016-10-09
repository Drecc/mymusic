#include "MusicDownThread.h"

MusicDownThread::MusicDownThread(QString urlString, QString musicFilePath)
        :urlString(urlString), musicFilePath(musicFilePath)
{
    musicFile.setFileName(musicFilePath);
    musicFile.open(QIODevice::WriteOnly);
    url = QUrl(urlString);
    manager = new QNetworkAccessManager(this);
    reply = manager->get(QNetworkRequest(url));
    connect(reply,SIGNAL(readyRead()),this,SLOT(getMusic()));
    connect(reply,SIGNAL(finished()),this,SLOT(finish()));
}

MusicDownThread::~MusicDownThread()
{

}

void MusicDownThread::run()
{

}

void MusicDownThread::getMusic()
{
    musicFile.write(reply->readAll());
}

void MusicDownThread::finish()
{
    musicFile.flush();
    musicFile.close();
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(reply->error())     //下载音乐失败
    {
        musicFile.remove();     //删除文件
        qDebug()<< "下载失败";
        emit downloadMusic(false, musicFilePath);        //发送下载失败完毕信号
    }
    else if (!redirectionTarget.isNull())   //下载百度音乐需要二次请求
    {
        QUrl newUrl = url.resolved(redirectionTarget.toUrl());
        reply->deleteLater();
        musicFile.open(QIODevice::WriteOnly);
        musicFile.resize(0);
        reply = manager->get(QNetworkRequest(newUrl));

        connect(reply, SIGNAL(finished()), this, SLOT(finish()));
        connect(reply, SIGNAL(readyRead()), this, SLOT(getMusic()));
        return;
    }
    else
    {
        QMessageBox::information(0, tr("音乐"), tr("下载成功"));
        qDebug() <<  "下载歌曲 :" << musicFile.fileName();
        emit downloadMusic(true, musicFilePath);        //发送下载完毕信号
    }
    reply->deleteLater();
    this->deleteLater();
}



#include "MusicThread.h"

MusicThread::MusicThread(QString musicName, QString musicArtist, QString musicFilePath, DownloadWidget *downWidget)
    : musicName(musicName), musicArtist(musicArtist), musicFilePath(musicFilePath), downWidget(downWidget)
{
    startFunc();
}
void MusicThread::run()
{

}
void MusicThread::startFunc()
{
    QString urlStr = "http://box.zhangmen.baidu.com/x?op=12&count=1&title=" + musicName + "$$" + musicArtist + "$$$$";
    manager = new QNetworkAccessManager;
    manager->get(QNetworkRequest(QUrl(urlStr)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getMusicXML(QNetworkReply*)));
}

MusicThread::~MusicThread()
{

}

void MusicThread::getMusicXML(QNetworkReply *reply)     //先得到xml，解析
{
    qDebug() << "下载歌曲xml成功";
    QString errorString;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    if (!doc.setContent(reply->readAll(), false, &errorString, &errorLine, &errorColumn))
    {
        qDebug() << "Error: " << errorString << "int row: " << errorLine << "Column: " << errorColumn;
    }
    else
    {
        qDebug() <<"开始解析xml";
        QDomElement root = doc.documentElement();//<result>
        qDebug() << root.tagName();
        QDomNodeList list = root.childNodes();//获取<result>的节点列表
        if(list.count() <= 1)
        {
            qDebug ()<<"xml文件无信息";
            QMessageBox::information(0, tr("音乐"), tr("下载失败"));
            downWidget->setBtnVisible(true);      //下载框复原
            downWidget->setMusicName(tr(""));
            downWidget->setArtistName(tr(""));
        }
        else
        {
            QDomElement urlText = list.item(1).toElement();//直接取第二个节点<url>
            qDebug() << urlText.tagName();
            QDomNodeList list2 = urlText.childNodes();
            QDomElement encode = list2.item(0).toElement();//再其获取第一个节点<encode>
            qDebug() << encode.tagName();
            qDebug() << encode.text();
            int i = encode.text().count('/');       //计算'/'个数
            qDebug() << i;
            QString link = encode.text().section("/",0,i - 1);//截取
            qDebug() <<link;
            QDomElement decode = list2.item(1).toElement();//再获取第二个节点<decode>
            qDebug() <<decode.tagName();
            qDebug() <<decode.text();
            link.append(tr("/") + decode.text());       //两个拼接得到下载链接
            qDebug() <<link;

            musicUrl = QUrl(link);     //下载链接
            this->getMusicFromURL(musicUrl, musicFilePath);

        }

    }
    reply->deleteLater();   //最后要释放reply对象
}
void MusicThread::getMusicFromURL(QUrl musicUrl, QString musicFilePath)
{
    musicFile.setFileName(musicFilePath);
    musicFile.open(QIODevice::WriteOnly);

    musicManager = new QNetworkAccessManager;
    musicReply = musicManager->get(QNetworkRequest(musicUrl));

    connect(musicReply, SIGNAL(downloadProgress(qint64, qint64)), downWidget, SLOT(downloadProgress(qint64,qint64)));
    connect(musicReply, SIGNAL(finished()), this, SLOT(replyFinished()));
    connect(musicReply, SIGNAL(readyRead()), this, SLOT(getMusic()));
    downWidget->setBarVisible(true);        //进度条可见
}

void MusicThread::replyFinished()
{
    musicFile.flush();
    musicFile.close();

    QVariant redirectionTarget = musicReply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(musicReply->error())     //下载音乐失败
    {
        musicFile.remove();     //删除文件
        qDebug()<< "下载失败";
        emit downloadMusic(false, musicFilePath);        //发送下载失败完毕信号
    }
    else if (!redirectionTarget.isNull())   //下载百度音乐需要二次请求
    {
        QUrl newUrl = musicUrl.resolved(redirectionTarget.toUrl());
        musicReply->deleteLater();
        musicFile.open(QIODevice::WriteOnly);
        musicFile.resize(0);
        musicReply = musicManager->get(QNetworkRequest(newUrl));

        connect(musicReply, SIGNAL(downloadProgress(qint64, qint64)), downWidget, SLOT(downloadProgress(qint64,qint64)));
        connect(musicReply, SIGNAL(finished()), this, SLOT(replyFinished()));
        connect(musicReply, SIGNAL(readyRead()), this, SLOT(getMusic()));
        return;
    }
    else
    {
        QMessageBox::information(0, tr("音乐"), tr("下载成功"));
        qDebug() <<  "下载歌曲 :" << musicFile.fileName();
        emit downloadMusic(true, musicFilePath);        //发送下载完毕信号
    }
    downWidget->setBarVisible(false);       //下载框复原
    downWidget->setBtnVisible(true);
    downWidget->setMusicName(tr(""));
    downWidget->setArtistName(tr(""));

    musicReply->deleteLater();
    this->deleteLater();        //释放当前线程
}

void MusicThread::getMusic()        //写入文件
{
    musicFile.write(musicReply->readAll());
}



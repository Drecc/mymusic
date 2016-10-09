#include "LrcThread.h"

LrcThread::LrcThread(QString musicName, QString musicArtist, QString lrcFileName,QObject *parent)
    : musicName(musicName), musicArtist(musicArtist), lrcFilePath(lrcFileName),QThread(parent)
{
    startFunc();
}
void LrcThread::run()
{

}

void LrcThread::startFunc()
{
    QString urlStr = "http://box.zhangmen.baidu.com/x?op=12&count=1&title=" + musicName + "$$" + musicArtist + "$$$$";
    lrcManager = new QNetworkAccessManager;
    lrcManager->get(QNetworkRequest(QUrl(urlStr)));//得到url
    //信号与槽
    connect(lrcManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getMusicXML(QNetworkReply*)));
}

void LrcThread::getMusicXML(QNetworkReply *reply) //先得到xml文件，解析
{
    qDebug() << "下载xml成功";
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
            qDebug ()<<"xml文件无歌词信息";
        else
        {
            QDomElement url = list.item(1).toElement();//直接取第二个节点<url>
            qDebug() << url.tagName();
            QDomNodeList list2 = url.childNodes();
            QDomElement lrcid = list2.item(3).toElement();//再其获取第四个节点<lrcid>
            qDebug() << lrcid.tagName();
            int id = lrcid.text().toInt();//获取<lrcid>的内容
            qDebug() << id;
            int decodeId = id / 100;
            if(id != 0)     //发出下载歌词的请求
            {
                QString lrcUrl = QString("http://box.zhangmen.baidu.com/bdlrc/%1/%2.lrc").arg(decodeId).arg(id);
                this->getLrcFromURL(lrcUrl);        //再次发送下载歌词的请求
            }
            else
            {
                qDebug() <<"没有歌词";
            }
        }

    }
    reply->deleteLater();      //最后要释放reply对象
}

void LrcThread::getLrc(QNetworkReply *reply)
{
    lrcFile.write(reply->readAll());   //写入文件中
    lrcFile.flush();
    if (lrcFile.isOpen())
    {
        lrcFile.close();
    }
    emit downloadLrcOk(lrcFilePath);		//发送下载完毕信号
    reply->deleteLater();		//最后要释放reply对象
    this->deleteLater();		//释放当前线程
}

void LrcThread::getLrcFromURL(QString url)
{
    lrcFile.setFileName(lrcFilePath);
    lrcFile.open(QIODevice::WriteOnly);

    lrcManager2 = new QNetworkAccessManager;
    lrcManager2->get(QNetworkRequest(QUrl(url)));

    connect(lrcManager2, SIGNAL(finished(QNetworkReply*)), this, SLOT(getLrc(QNetworkReply*)));
}

LrcThread::~LrcThread()
{

}


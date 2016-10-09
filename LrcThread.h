#ifndef LRCTHREAD_H
#define LRCTHREAD_H

#include <QObject>
#include <QThread>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QDomDocument>
#include <QFile>
#include <QDebug>

class LrcThread : public QThread
{
    Q_OBJECT
public:
    LrcThread(QString musicName, QString musicArtist, QString lrcFileName,QObject *parent = 0);
    ~LrcThread();
protected:
    void run();
signals:
    void downloadLrcOk(QString);

public slots:
    void getMusicXML(QNetworkReply *replay);
    void getLrc(QNetworkReply *replay);
private:
    void startFunc();
    void getLrcFromURL(QString url);
    QFile lrcFile;
    QString musicName;
    QString musicArtist;
    QString lrcFilePath;

    QNetworkAccessManager *lrcManager;
    QNetworkAccessManager *lrcManager2;
};

#endif // LRCTHREAD_H

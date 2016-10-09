#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QString>

class Network : public QObject
{
    Q_OBJECT
public:
    explicit Network(QObject *parent = 0);
    ~Network();

    QNetworkReply *get(const QString &url);

signals:
    void finished(QNetworkReply *reply);        //转发

public slots:

private:
    QNetworkAccessManager *manager;
};

#endif // NETWORK_H

#include "Network.h"

Network::Network(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SIGNAL(finished(QNetworkReply*)));
}

Network::~Network()
{

}

QNetworkReply *Network::get(const QString &url)
{
    return manager->get(QNetworkRequest(QUrl(url)));
}


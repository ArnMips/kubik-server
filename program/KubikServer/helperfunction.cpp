#include "helperfunction.h"

#include <QNetworkInterface>

QHostAddress getHostAddress2()
{
    auto addresses = QNetworkInterface::allAddresses();
    for (auto addres : addresses) {
        if(addres.protocol() == QAbstractSocket::IPv4Protocol
                && addres != QHostAddress::LocalHost) {
            return addres;
        }
    }
    return QHostAddress::LocalHost;
}

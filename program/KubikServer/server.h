#pragma once
#include <QWidget>

class QTcpServer;
class QTcpSocket;
class QHostAddress;

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(int port, QWidget *parent = nullptr);
    ~Server();

public slots:
    void slotNewConnection();
    void slotReadClient();

private:
    void sentToClient(QTcpSocket* pSocket, const QString& str);

private:
    Ui::Server *ui;
    QTcpServer* m_ptcpServer;
    quint16 m_nNectBlockSize;

};

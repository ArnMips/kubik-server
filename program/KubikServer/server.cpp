#include "server.h"
#include "ui_server.h"

#include "helperfunction.h"

#include <QTcpServer>
#include <QMessageBox>
#include <QDataStream>
#include <QTcpSocket>
#include <QTime>
#include <QByteArray>
#include <QNetworkInterface>

Server::Server(int nPort, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server),
    m_nNectBlockSize(0)
{
    ui->setupUi(this);

    auto hostAddr = getHostAddress2();

    m_ptcpServer = new QTcpServer(this);
    if(!m_ptcpServer->listen(hostAddr, nPort)){
        QMessageBox::critical(nullptr, "Server Error",
                              "Unable to start the server: "
                              + m_ptcpServer->errorString());
        m_ptcpServer->close();
        return;
    }

    auto serverAdress = m_ptcpServer->serverAddress().toString();
    ui->serverName->setText(serverAdress);


    connect(m_ptcpServer, SIGNAL(newConnection()), SLOT(slotNewConnection()));
}

Server::~Server()
{
    delete ui;
}

void Server::slotNewConnection()
{
    auto pClientSocket = m_ptcpServer->nextPendingConnection();
    connect(pClientSocket, SIGNAL(disconnected()), pClientSocket, SLOT(deleteLater()));
    connect(pClientSocket, SIGNAL(readyRead()), SLOT(slotReadClient()));
    sentToClient(pClientSocket, "Server Response: Connected!");
}

void Server::slotReadClient()
{
    auto pClientSocket = reinterpret_cast<QTcpSocket*>(sender());
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_3);
    for(;;){
        if(!m_nNectBlockSize){
            if(pClientSocket->bytesAvailable() < sizeof(quint16)){
                break;
            }
            in >> m_nNectBlockSize;
        }
        if(pClientSocket->bytesAvailable() < m_nNectBlockSize){
            break;
        }

        QTime time;
        QString str;
        quint32 clientAddress;
        in >> time >> clientAddress >> str;

        QString strMessage = QString("%1: Client %2 has sent - %3")
                .arg(time.toString())
                .arg(QHostAddress(clientAddress).toString())
                .arg(str);
        ui->textEdit->append(strMessage);

        m_nNectBlockSize = 0;

        sentToClient(pClientSocket, QString("Server Response: Received \"%1\"").arg(str));
    }
}

void Server::sentToClient(QTcpSocket *pSocket, const QString &str)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}


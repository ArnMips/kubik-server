#include "client.h"
#include "ui_client.h"
#include "helperfunction.h"

#include <QTcpServer>
#include <QMessageBox>
#include <QDataStream>
#include <QTcpSocket>
#include <QTime>
#include <QByteArray>


Client::Client(int nPort, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client),
    m_nPort(nPort)
{
    ui->setupUi(this);

    m_pTcpSocket = new QTcpSocket(this);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            SLOT(slotError(QAbstractSocket::SocketError)));

    connect(ui->connectToServer, SIGNAL(pressed()), SLOT(slotOnPushButtonConnect()));
    connect(ui->sendToServer, SIGNAL(pressed()), SLOT(slotSendToServer()));


    connect(ui->pushButton_web, SIGNAL(pressed()), SLOT(openBrowserPage()));
}

Client::~Client()
{
    delete ui;
}

void Client::slotOnPushButtonConnect()
{
    if(m_pTcpSocket->isOpen()){
        m_pTcpSocket->close();
    }

    auto hostName = ui->serverName->text();
    m_pTcpSocket->connectToHost(hostName, m_nPort);
}

void Client::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_3);
    for(;;){
        if(!m_nNextBlockSize){
            if(m_pTcpSocket->bytesAvailable() < sizeof(qint16)){
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize){
            break;
        }
        QTime time;
        QString str;
        in >> time >> str;

        ui->textEdit->append(time.toString() + " " + str);
        m_nNextBlockSize = 0;
    }
}

void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                         "The host was not found." :
                         err == QAbstractSocket::RemoteHostClosedError ?
                         "The remote host is closed." :
                         err == QAbstractSocket::ConnectionRefusedError ?
                         "The connection was refused.":
                         QString(m_pTcpSocket->errorString())
                        );
    ui->textEdit->append(strError);
}

void Client::slotSendToServer()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    out << quint16(0) << QTime::currentTime() << getHostAddress2().toIPv4Address() << ui->msgToServer->text();

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    m_pTcpSocket->write(arrBlock);
    ui->msgToServer->clear();
}

void Client::slotConnected()
{
    ui->textEdit->append("Reseived the connected() signal");
}

void Client::openBrowserPage()
{
    m_webBrowser.openPage(QUrl("http://codecombat.com"));
}

void Client::closeBrowserWindow()
{
    m_webBrowser.close();
}

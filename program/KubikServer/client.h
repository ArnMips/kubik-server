#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QAbstractSocket>
#include "webbrowser.h"
//#include "blockwindow.h"

class QTcpSocket;

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(int port, QWidget *parent = nullptr);
    ~Client();

private slots:
    void slotOnPushButtonConnect();
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotSendToServer();
    void slotConnected();

//private:
    void openBrowserPage();
    void closeBrowserWindow();

private:
    Ui::Client *ui;
    QTcpSocket* m_pTcpSocket;
    quint16 m_nNextBlockSize;
    int m_nPort;

    WebBrowser m_webBrowser;
    //BlockWindow m_blockWindow;
};

#endif // CLIENT_H

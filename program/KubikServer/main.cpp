#include "mainwindow.h"
#include "client.h"
#include "server.h"
#include <QApplication>
#include <QCommandLineParser>
#include <iostream>
#include <QHostAddress>

const auto SERVER_PORT = 2323;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption clientOption({"c", "client"}, "Load client version program");
    QCommandLineOption serverOption({"s", "server"}, "Load server version program");
    parser.addOptions({ clientOption, serverOption });
    parser.process(a);

    MainWindow w;
    if (parser.isSet(clientOption) && !parser.isSet(serverOption)){
        Client *client = new Client(SERVER_PORT, &w);
        w.setCentralWidget(client);
    } else if (!parser.isSet(clientOption) && parser.isSet(serverOption)){        
        Server *server = new Server(SERVER_PORT, &w);
        w.setCentralWidget(server);
    } else {
        std::cout << "error, select 'client / server'" << std::endl;
        exit(1);
    }
    w.show();

    return a.exec();
}

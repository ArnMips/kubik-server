#include "webbrowser.h"
#include "ui_webbrowser.h"

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebBrowser)
{
    ui->setupUi(this);

    connect(ui->browser, SIGNAL(loadFinished(bool)), SLOT(loadFinished(bool)));
}

WebBrowser::~WebBrowser()
{
    delete ui;
}

void WebBrowser::openPage(QUrl url)
{
    setWindowTitle("Browser");
    ui->browser->load(url);
    ui->browser->show();
}

void WebBrowser::closeWindow()
{
    close();
}

void WebBrowser::loadFinished(bool ok)
{
    const auto browserInxPage = 0;
    const auto errorInxPage = 1;

    ui->stackedWidget->setCurrentIndex(
                ok ? browserInxPage : errorInxPage
                     );
    showFullScreen();
}

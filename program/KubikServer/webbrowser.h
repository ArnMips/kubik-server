#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QWidget>

namespace Ui {
class WebBrowser;
}

class WebBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit WebBrowser(QWidget *parent = nullptr);
    ~WebBrowser();

    void openPage(QUrl );
    void closeWindow();

private slots:
    void loadFinished(bool ok);

private:
    Ui::WebBrowser *ui;
};

#endif // WEBBROWSER_H

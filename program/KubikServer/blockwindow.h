#ifndef BLOCKWINDOW_H
#define BLOCKWINDOW_H

#include <QWidget>

namespace Ui {
class BlockWindow;
}

class BlockWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BlockWindow(QWidget *parent = nullptr);
    ~BlockWindow();

    //void activateBlock();
    //void diactivateBlock();

private:
    Ui::BlockWindow *ui;
};

#endif // BLOCKWINDOW_H

#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include "Register.h"
#include "Login.h"

namespace Ui {
    class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget* parent = 0);
    ~StartWindow();

public slots:
    void changePageAfterLogin();
    void changePageAfterRegister();

private slots:
    void on_openButton_clicked();
    void on_openButton_2_clicked();

private:
    Ui::StartWindow* ui;
    //You want to keep a pointer to a new Website window
    Register* registerWindow;
    Login* loginWindow;
};

#endif // MAINWINDOW_H

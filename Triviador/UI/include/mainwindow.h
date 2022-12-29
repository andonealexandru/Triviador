#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "Register.h"
#include "Login.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    void paintEvent(QPaintEvent* pe = nullptr) override;
    ~MainWindow();

public slots:
    void changePageAfterLogin();
    void changePageAfterRegister();
    void changePageAfterExitRegister();

private slots:
    void on_openButton_clicked();
    void on_openButton_2_clicked();

private:
    Ui::MainWindow* ui;
    Register* registerWindow;
    Login* loginWindow;
};

#endif // MAINWINDOW_H

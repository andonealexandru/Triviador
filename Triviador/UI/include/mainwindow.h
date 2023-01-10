#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "Register.h"
#include "Login.h"
#include "Profile.h"
#include <lobby.h>
#include <Map.h>

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
    void changePageAfterLobby();
    void changePageAfterExitRegister();
    void changePageAfterExitLogin();
    void changePageAfterExitLobby();
    void changePageAfterExitProfile();

private slots:
    void on_openButton_clicked();
    void on_openButton_2_clicked();
    void on_startButton_clicked();
    void on_profileButton_clicked();

private:
    Ui::MainWindow* ui;
    DB::User user;
    Register* registerWindow;
    Login* loginWindow;
    Lobby* lobbyWindow;
    Profile* profileWindow;
    Map* gameWindow;
};

#endif // MAINWINDOW_H

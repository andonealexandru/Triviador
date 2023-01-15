#ifndef TRIVIADOR_LOBBY_H
#define TRIVIADOR_LOBBY_H

#include <QMainWindow>
#include <vector>
#include <User.h>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Lobby;
}
QT_END_NAMESPACE

class Lobby : public QMainWindow
{
Q_OBJECT

public:
    explicit Lobby(DB::User user, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* pe = nullptr) override;
    ~Lobby() override;

    void Active();

signals:
    void exitButtonPressed();
    void startButtonPressed();

private slots:
    void on_startButton_clicked();
    void on_exitButton_clicked();

private:
    void UpdateUsers();
    void ShowUsers() const;

    Ui::Lobby *ui;
    DB::User m_user;
    QTimer* m_timer;
    std::vector<DB::User> m_players;
};


#endif //TRIVIADOR_LOBBY_H

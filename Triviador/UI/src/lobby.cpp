#include "lobby.h"
#include <QPainter>
#include "ui_Lobby.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


Lobby::Lobby(DB::User user, QWidget *parent)
    : QMainWindow{ parent }
    , ui{ new Ui::Lobby }
    , m_user{ user }
    , timer{ new QTimer{this} }
    , m_players{}
{
    ui->setupUi(this);
    UpdateUsers();
    ShowUsers();
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Lobby::Active));
    timer->start(5000);
}


void Lobby::paintEvent(QPaintEvent* pe)
{
    QPixmap px;
    std::string imagePath = std::string(RESOURCE_DIR) + "/triviador.jpg";
    px.load(imagePath.data());
    QPainter paint(this);
    int widWidth = this->ui->centralwidget->width();
    int widHeight = this->ui->centralwidget->height();
    px = px.scaled(widWidth, widHeight, Qt::IgnoreAspectRatio);
    paint.drawPixmap(0, 0, px);
}

Lobby::~Lobby()
{
    delete ui;
    delete timer;
}

void Lobby::on_startButton_clicked()
{
    emit startButtonPressed();
}

void Lobby::on_exitButton_clicked()
{
    cpr::Response response = cpr::Get(cpr::Url{"localhost:18080/lobby/leave"},
                                      cpr::Header{{"ID", std::to_string(m_user.GetId())}});

    emit exitButtonPressed();
}

void Lobby::UpdateUsers()
{
    cpr::Response response = cpr::Get(cpr::Url{"localhost:18080/lobby/players"},
                                      cpr::Header{{"ID", std::to_string(m_user.GetId())}});

    auto players = json::parse(response.text)["players"];

    m_players.clear();
    for(const auto& player : players)
    {
        auto id = player["id"].get<int>();
        auto name = player["name"].get<std::string>();
        m_players.emplace_back(DB::User(id, name, ""));
    }
}

void Lobby::ShowUsers() const
{
    ui->listWidget->clear();
    for(const auto& player : m_players)
    {
        ui->listWidget->addItem(player.GetName().data());
    }
}

void Lobby::Active()
{
    cpr::Response response = cpr::Get(cpr::Url{"localhost:18080/lobby"},
                                      cpr::Header{{"ID", std::to_string(m_user.GetId())}});

    auto status = json::parse(response.text)["status"].get<std::string>();
    if(status == "InLobby")
    {
        return;
    }
    else if(status == "PlayersModified")
    {
        UpdateUsers();
        ShowUsers();
    }
    else if(status == "InGame")
    {
        // TODO ..
    }
}

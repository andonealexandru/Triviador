#include "lobby.h"
#include <QPainter>
#include "ui_Lobby.h"
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;


Lobby::Lobby(DB::User user, QWidget *parent)
    : QMainWindow{ parent }
    , ui{ new Ui::Lobby }
    , m_user{ user }
    , m_timer{ new QTimer{this} }
    , m_players{}
{
    ui->setupUi(this);
    ui->startButton->setEnabled(false);
    UpdateUsers();
    ShowUsers();
    connect(m_timer, &QTimer::timeout, this, QOverload<>::of(&Lobby::Active));
    m_timer->start(1000);
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
    delete m_timer;
}

void Lobby::on_startButton_clicked()
{
    cpr::Post(cpr::Url{"localhost:18080/game/start"});
    emit startButtonPressed();
}

void Lobby::on_exitButton_clicked()
{
    cpr::Response response = cpr::Post(cpr::Url{"localhost:18080/lobby/leave"},
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
    if(m_players.size() >= 2)
        ui->startButton->setEnabled(true);
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
    auto response =  cpr::Get(cpr::Url{"localhost:18080/lobby"},
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
        emit startButtonPressed();
    }
}

#include "Map.h"
#include <QPainter>
#include <QColor>
#include <QLabel>
#include "Tile.h"
#include <QBrush>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Map::Map(DB::User* user, QWidget* parent)
        : QMainWindow{ parent }
        , m_user{ user }
        , m_timer{ new QTimer{this} }
        , m_question{ nullptr }
        , m_nQuestion{ nullptr }
        , m_duelResult{ nullptr }
        , m_selectedRegion { -1 }
{
    ui.setupUi(this);
    connect(m_timer, &QTimer::timeout, this, QOverload<>::of(&Map::OnGoing));
    m_timer->start(1000);
}


Map::~Map()
{
    delete m_user;
    delete m_timer;
}

void Map::paintEvent(QPaintEvent* event)
{
    if (g.GetNrPlayers())
    {
        std::vector<std::pair<QColor, QColor>> colors(5);
        colors[0].first = Qt::white;
        colors[0].second = QColor(205, 200, 200);
        colors[1].first = Qt::red;
        colors[1].second = QColor(223, 127, 127);
        colors[2].first = Qt::blue;
        colors[2].second = QColor(104, 104, 229);
        colors[3].first = Qt::green;
        colors[3].second = QColor(157, 232, 157);
        colors[4].first = Qt::yellow;
        colors[4].second = QColor(232, 232, 156);


        QPainter painter(this);
        painter.setPen(Qt::black);

        int nLongitudinalSectors = 300;
        int nTransveralSectors = 112;
        float width = 8 * (this->size().width() / 10);
        float height = this->size().height();
        float sectorWidth = width / nLongitudinalSectors;
        float sectorHeight = height / nTransveralSectors;

        QPixmap pixmap(sectorWidth + 1, sectorHeight + 1);
        pixmap.fill(Qt::black);

        //border
        for (std::vector<Tile> t : g.getTiles())
            for (Tile tt : t)
                if (tt.IsBorder())
                {
                    QPointF punct(tt.GetCoordinate().second * sectorWidth, tt.GetCoordinate().first * sectorHeight);
                    painter.drawPixmap(punct, pixmap);
                }

        //fill

        std::vector<std::pair<QPixmap, QPixmap>> colorPixmaps;
        for (const auto& color : colors)
        {
            QPixmap pixmap1(sectorWidth + 1, sectorHeight + 1);
            pixmap1.fill(color.first);
            QPixmap pixmap2(sectorWidth + 1, sectorHeight + 1);
            pixmap2.fill(color.second);
            colorPixmaps.emplace_back(pixmap1, pixmap2);
        }

        std::vector<std::vector<Tile>> aux = g.getTiles();
        for (std::vector<Tile> t : aux)
            for (Tile tt : t)
                if (!tt.IsBorder())
                    if (!tt.getParentRegion()->GetHighlight())
                    {
                        QPointF punct(tt.GetCoordinate().second * sectorWidth, tt.GetCoordinate().first * sectorHeight);
                        painter.drawPixmap(punct, colorPixmaps[tt.getParentRegion()->GetUserId() == -1 ? 0 : tt.getParentRegion()->GetUserId()].first);
                    }
                    else
                    {
                        QPointF punct(tt.GetCoordinate().second * sectorWidth, tt.GetCoordinate().first * sectorHeight);
                        painter.drawPixmap(punct, colorPixmaps[tt.getParentRegion()->GetUserId() == -1 ? 0 : tt.getParentRegion()->GetUserId()].second);
                    }

        ////paint score

        float widthLabel = this->size().width() / 25;
        float heightLabel = this->size().height() / 25;

        std::vector<std::shared_ptr<Region>> map = g.getMap();
        for (auto i : map)
        {
            if (i->GetNumber())
            {
                QPainter painter1(this);
                QFont font("Arial", 10);
                painter1.setFont(font);
                QPen pen(Qt::black, 2);
                QBrush brush(Qt::white);
                painter1.setPen(pen);
                painter1.setBrush(brush);

                std::pair<int, int>p = i->GetCenter();

                if (i->IsBase())
                {
                    QRect rect(p.first * sectorWidth - widthLabel / 2, p.second * sectorHeight - heightLabel / 2, widthLabel, heightLabel);
                    painter1.drawEllipse(rect);
                    QString s = QString::number(i->GetValue());
                    painter1.drawText(rect, Qt::AlignCenter, s);
                }
                else
                {
                    QRect rect(p.first * sectorWidth - widthLabel / 2, p.second * sectorHeight - heightLabel / 2, widthLabel, heightLabel / 1.2);
                    painter1.drawRect(rect);
                    QString s = QString::number(i->GetValue());
                    painter1.drawText(rect, Qt::AlignCenter, s);
                }
            }
        }

        //desenare playeri
        for (int i = 0;i < g.GetNrPlayers();i++)
        {
            QPainter pt(this);
            QFont font("Arial", 12, QFont::Bold);
            pt.setFont(font);
            QPen pent(Qt::black, 3);
            QBrush brusht(QColor(185, 91, 36));
            pt.setPen(pent);
            pt.setBrush(brusht);

            QRect player(width, (height / g.GetNrPlayers()) * i, 2 * (this->size().width() / 10) + 5, this->size().height() / g.GetNrPlayers());
            pt.drawRect(player);
            pt.drawText(player, Qt::AlignCenter, "Monigga:\n200");
        }
    }
}


void Map::mouseReleaseEvent(QMouseEvent* ev)
{
    QPoint point = ev->pos();
    int x = point.x();
    int y = point.y();
    int ok = 0;
    int nLongitudinalSectors = 300;
    int nTransveralSectors = 112;
    float width = 8 * (this->size().width() / 10);
    float height = this->size().height();
    float sectorWidth = width / nLongitudinalSectors;
    float sectorHeight = height / nTransveralSectors;
    x = x/ sectorWidth;
    y = y/sectorHeight;
    for (std::vector<Tile> t : g.getTiles())
    {
        for (Tile tt : t)
            if (tt.GetCoordinate().second== x  && tt.GetCoordinate().first == y)
            {
                // TODO: check if region is highlighted
                m_selectedRegion = tt.getParentRegion()->GetNumber();
                ok = 1;
                break;
            }
        if (ok == 1)
            break;
    }
    emit MousePressed();
}

void Map::NumericAnswerSent()
{
    SendAnswer(m_nQuestion->GetAnswer(), m_nQuestion->GetRemainingTime());
    delete m_nQuestion;
}

void Map::AnswerSent()
{
    SendAnswer(m_question->GetSelection(), m_question->GetRemainingTime());
    delete m_question;
}


void Map::OnGoing()
{
    cpr::Response response = cpr::Get(cpr::Url{"localhost:18080/game"},
                                      cpr::Header{{"ID", std::to_string(m_user->GetId())}});

    auto status = json::parse(response.text)["status"].get<std::string>();
    if(status == "InGame")
    {
        return;
    }
    else if(status == "StartNewGame")
    {
        cpr::Response mapResponse = cpr::Get(cpr::Url{"localhost:18080/game/map/first"},
                                             cpr::Header{{"ID", std::to_string(m_user->GetId())}});

        auto mapId = json::parse(mapResponse.text)["mapId"].get<int>();
        g.ReadMap(mapId);
    }
    else if(status == "FirstQuestion")
    {
        cpr::Response firstQuestion = cpr::Get(cpr::Url{"localhost:18080/game/firstQuestion"},
                                          cpr::Header{{"ID", std::to_string(m_user->GetId())}});

        auto question = json::parse(firstQuestion.text)["question"].get<std::string>();
        NextQuestion(QuestionType::NUMERIC, question);
    }
    else if(status == "WaitingForAnswers")
    {
        return;
    }
    else if(status == "AllPlayersAnswered")
    {
        cpr::Response allAnswers = cpr::Get(cpr::Url{"localhost:18080/game/allAnswers"},
                                            cpr::Header{{"ID", std::to_string(m_user->GetId())}});
        auto answers = json::parse(allAnswers.text)["answers"].get<std::vector<json>>();

        std::vector<std::tuple<int, std::string, int>> players;
        for(const auto& answer : answers)
        {
            auto timeRemaining = json::parse(to_string(answer))["timeRemaining"].get<int>();
            auto name = json::parse(to_string(answer))["name"].get<std::string>();
            auto playerAnswer = json::parse(to_string(answer))["answer"].get<int>();
            players.emplace_back(std::make_tuple(timeRemaining, name, playerAnswer));
        }
        ShowResults(players);
    }
    else if(status == "BaseChoice")
    {
        /// GET REGIONS
        cpr::Response getMap = cpr::Get(cpr::Url{"localhost:18080/game/map"},
                                        cpr::Header{{"ID", std::to_string(m_user->GetId())}});

        auto regionsJson = json::parse(getMap.text).get<std::vector<json>>();
        std::vector<Region> regions;
        for(const auto& region : regionsJson)
        {
            auto id = json::parse(to_string(region))["id"].get<int>();
            auto userId = json::parse(to_string(region))["userId"].get<int>();
            auto isBase = json::parse(to_string(region))["isBase"].get<bool>();
            auto score = json::parse(to_string(region))["score"].get<int>();
            regions.emplace_back(score, userId, id, isBase);
        }
        g.UpdateMap(regions);
        repaint();

        /// GET BASECHOICE
           cpr::Response getBaseChoice = cpr::Get(cpr::Url{"localhost:18080/game/baseChoice"},
                                            cpr::Header{{"ID", std::to_string(m_user->GetId())}});
          auto regionIDs = json::parse(getBaseChoice.text).get<std::vector<int>>();
          g.selectRegions(regionIDs);

        /// POST SELECTED REGION

        QEventLoop loop;
        connect(this, &Map::MousePressed, &loop, &QEventLoop::quit);
        loop.exec();

        if(m_selectedRegion != -1)
        {
            cpr::Post(cpr::Url{"localhost:18080/game/baseChoice"},
                      cpr::Body{to_string(json{{"base", m_selectedRegion}})},
                      cpr::Header{{"ID", std::to_string(m_user->GetId())}});
            g.selectRegions(regionIDs);
            m_selectedRegion = -1;
        }
    }
    else if(status == "MapChanged")
    {
        cpr::Response getMap = cpr::Get(cpr::Url{"localhost:18080/game/map"},
                                        cpr::Header{{"ID", std::to_string(m_user->GetId())}});

        auto regionsJson = json::parse(getMap.text).get<std::vector<json>>();
        std::vector<Region> regions;
        for(const auto& region : regionsJson)
        {
            auto id = json::parse(to_string(region))["id"].get<int>();
            auto userId = json::parse(to_string(region))["userId"].get<int>();
            auto isBase = json::parse(to_string(region))["isBase"].get<bool>();
            auto score = json::parse(to_string(region))["score"].get<int>();
            regions.emplace_back(score, userId, id, isBase);
        }
        g.UpdateMap(regions);
        repaint();
    }
    else if(status == "RegionQuestion")
    {
        cpr::Response getMap = cpr::Get(cpr::Url{"localhost:18080/game/map"},
                                        cpr::Header{{"ID", std::to_string(m_user->GetId())}});

        auto regionsJson = json::parse(getMap.text).get<std::vector<json>>();
        std::vector<Region> regions;
        for(const auto& region : regionsJson)
        {
            auto id = json::parse(to_string(region))["id"].get<int>();
            auto userId = json::parse(to_string(region))["userId"].get<int>();
            auto isBase = json::parse(to_string(region))["isBase"].get<bool>();
            auto score = json::parse(to_string(region))["score"].get<int>();
            regions.emplace_back(score, userId, id, isBase);
        }
        g.UpdateMap(regions);
        repaint();
        // TODO
    }
}

void Map::NextQuestion(const Map::QuestionType type, const std::string& question, const std::vector<std::pair<uint32_t, std::string>>* answers)
{
    switch(type)
    {
        case QuestionType::MULTIPLE_CHOICE:
            m_question = new MCQuestion(question, *answers);
            QObject::connect(m_question, SIGNAL(clicked()), this, SLOT(AnswerSent()));
            m_nQuestion->show();
            break;
        case QuestionType::NUMERIC:
            m_nQuestion = new NumericQuestion(question);
            QObject::connect(m_nQuestion, SIGNAL(sendButtonPressed()), this, SLOT(NumericAnswerSent()));
            m_nQuestion->show();
            break;
    }
}

void Map::SendAnswer(const std::variant<int, std::string>& answer, int remainingTime) const
{
    std::visit([&](auto& arg)
               {
                   using T = std::decay_t<decltype(arg)>;
                   if constexpr (std::is_same_v<T, std::string>)
                   {
                       json body =
                       {
                           {"answer", arg},
                           {"timeRemaining", std::to_string(remainingTime)},
                       };
                       cpr::Response response = cpr::Post(cpr::Url{"localhost:18080/game/answer"},
                                                          cpr::Body{to_string(body)},
                                                          cpr::Header{{"ID", std::to_string(m_user->GetId())}});
                   }
                   else
                   {
                       json body =
                       {
                           {"answer", arg},
                           {"timeRemaining", std::to_string(remainingTime)},
                       };
                       cpr::Response response = cpr::Post(cpr::Url{"localhost:18080/game/answer"},
                                                          cpr::Body{to_string(body)},
                                                          cpr::Header{{"ID", std::to_string(m_user->GetId())}});
                   }
               }, answer);
}

void Map::ShowResults(const std::vector<std::tuple<int, std::string, int>>& players)
{
    m_duelResult = new DuelResult{ players };
    m_duelResult->show();
    QTimer::singleShot(5000, this, [&](){ delete m_duelResult; });
}
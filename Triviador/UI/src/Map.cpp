#include "Map.h"
#include <QPainter>
#include <QColor>
#include <QLabel>
#include "Tile.h"
#include <QBrush>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <sstream>
#include <algorithm>
using json = nlohmann::json;

#define HEADER {"ID", std::to_string(m_user->GetId())}

Map::Map(DB::User* user, QWidget* parent)
        : QMainWindow{ parent }
        , g{}
        , m_user{ user }
        , m_players{}
        , m_timer{ new QTimer{this} }
        , m_question{ nullptr }
        , m_nQuestion{ nullptr }
        , m_duelResult{ nullptr }
        , m_selectedRegion{ -1 }
        , m_stateHandler{}
        , m_requestHandler{ "localhost:18080" }
{
    ui.setupUi(this);
    InitStateHandler();
    connect(m_timer, &QTimer::timeout, this, QOverload<>::of(&Map::OnGoing));
    m_timer->start(500);
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
                        int userId = tt.getParentRegion()->GetUserId() == -1 ? 0 : tt.getParentRegion()->GetUserId();
                        int index = 0;
                        if(userId)
                        {
                            for(const auto& player : m_players)
                            {
                                const auto&[id, playerId, score, name] = player;
                                if (id == userId)
                                {
                                    index = playerId;
                                    break;
                                }
                            }
                        }
                        QPointF punct(tt.GetCoordinate().second * sectorWidth, tt.GetCoordinate().first * sectorHeight);
                        painter.drawPixmap(punct, colorPixmaps[index].first);
                    }
                    else
                    {
                        int userId = tt.getParentRegion()->GetUserId() == -1 ? 0 : tt.getParentRegion()->GetUserId();
                        int index = 0;
                        if(userId)
                        {
                            for(const auto& player : m_players)
                            {
                                const auto&[id, playerId, score, name] = player;
                                if (id == userId)
                                {
                                    index = playerId;
                                    break;
                                }
                            }
                        }
                        QPointF punct(tt.GetCoordinate().second * sectorWidth, tt.GetCoordinate().first * sectorHeight);
                        painter.drawPixmap(punct, colorPixmaps[index].second);
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
        for (int i = 0; i < m_players.size(); i++)
        {
            const auto&[id, playerId, score, name] = m_players[i];

            QPainter pt(this);
            QFont font("Arial", 12, QFont::Bold);
            pt.setFont(font);
            QPen pent(Qt::black, 3);
            QBrush brusht(id == m_user->GetId() ? colorPixmaps[playerId].first : colorPixmaps[playerId].second);
            pt.setPen(pent);
            pt.setBrush(brusht);

            std::ostringstream  oss;
            oss << name << ":"
                << "\n"
                << score;

            QRect player(width, (height / g.GetNrPlayers()) * i, 2 * (this->size().width() / 10) + 5, this->size().height() / g.GetNrPlayers());
            pt.drawRect(player);
            pt.drawText(player, Qt::AlignCenter, oss.str().data());
        }
    }
}
void Map::mouseReleaseEvent(QMouseEvent* ev)
{
    QPoint point = ev->pos();
    int x = point.x();
    int y = point.y();
    bool regionSelected = false;
    int nLongitudinalSectors = 300;
    int nTransveralSectors = 112;
    float width = 8 * (this->size().width() / 10);
    float height = this->size().height();
    float sectorWidth = width / nLongitudinalSectors;
    float sectorHeight = height / nTransveralSectors;
    x = x / sectorWidth;
    y = y /sectorHeight;
    for (const std::vector<Tile>& t : g.getTiles())
    {
        for (const Tile& tt : t)
        {
            bool canClickOnRegion = ((tt.GetCoordinate().second == x &&
                                      tt.GetCoordinate().first == y) &&
                                     tt.getParentRegion()->GetHighlight());

            if (canClickOnRegion)
            {
                m_selectedRegion = tt.getParentRegion()->GetNumber();
                regionSelected = true;
                break;
            }
        }
        if (regionSelected)
            break;
    }
    emit MousePressed();
}

void Map::NumericAnswerSent()
{
    bool isPoweredUp = m_nQuestion->PoweredUp();
    int answer = m_nQuestion->GetAnswer();
    int remainingTime = m_nQuestion->GetRemainingTime();
    delete m_nQuestion;

    SendAnswer(answer, remainingTime);
    if(isPoweredUp)
    {
        PostChosenRegion("/game/powerup", "region");
        UpdatePlayers();
        UpdateRegions();
    }
}

void Map::AnswerSent()
{
    bool isPoweredUp = m_question->PoweredUp();
    int answer = m_question->GetSelection();
    int remainingTime = m_question->GetRemainingTime();
    delete m_question;

    SendAnswer(answer, remainingTime);
    if(isPoweredUp)
    {
        PostChosenRegion("/game/powerup", "region");
        UpdatePlayers();
        UpdateRegions();
    }
}

void Map::OnGoing()
{
    const auto requestStatus = m_requestHandler.Get("/game", HEADER);
    const auto state = StringToState(json::parse(requestStatus.text)["status"].get<std::string>());
    std::cout << json::parse(requestStatus.text)["status"].get<std::string>() <<"\n";
    if(m_stateHandler.find(state) != m_stateHandler.end())
        m_stateHandler[state](); /// \brief calls the function bound to this state

    if(state == State::Endgame)
        m_timer->stop();
}

void Map::NextQuestion(const Map::QuestionType type,
                       const std::string& question,
                       const std::array<std::pair<uint32_t, std::string>, 4>* answers)
{
    auto name = std::find_if(m_players.begin(), m_players.end(),
                             [&](decltype(m_players[0])& player)
                             {
                                 return std::get<0>(player) == m_user->GetId();
                             });

    auto powerup = m_requestHandler.Get("/game/powerup", HEADER);
    auto availablePowerups = json::parse(powerup.text);

    switch(type)
    {
        case QuestionType::MULTIPLE_CHOICE:
            m_question = new MCQuestion(question, m_user->GetId(), std::get<3>(*name), *answers,
                                        availablePowerups["fiftyFifty"].get<bool>());
            QObject::connect(m_question, SIGNAL(clicked()), this, SLOT(AnswerSent()));
            m_question->show();
            break;
        case QuestionType::NUMERIC:
            m_nQuestion = new NumericQuestion(question, m_user->GetId(), std::get<3>(*name),
                    { availablePowerups["chooseAnswer"].get<bool>(), availablePowerups["suggestAnswer"].get<bool>() });
            QObject::connect(m_nQuestion, SIGNAL(sendButtonPressed()), this, SLOT(NumericAnswerSent()));
            m_nQuestion->show();
            break;
    }
}

void Map::SendAnswer(const int answer, int remainingTime) const
{
    json body =
    {
        { "answer", answer },
        { "timeRemaining", std::to_string(remainingTime) },
    };
    (void)m_requestHandler.Post("/game/answer", to_string(body), HEADER);
}

void Map::ShowResults(const std::vector<std::tuple<int, std::string, std::string>>& players, const std::string& correctAnswer)
{
    m_duelResult = new DuelResult{ players, correctAnswer };
    m_duelResult->show();
    QTimer::singleShot(5000, this, [&](){ delete m_duelResult; });
}

void Map::UpdateRegions()
{
    auto getMap = m_requestHandler.Get("/game/map", HEADER);
    auto regionsJson = json::parse(getMap.text).get<std::vector<json>>();

    std::vector<Region> regions;
    std::for_each(regionsJson.begin(), regionsJson.end(), [&](const auto& regionJson)
    {
        auto region = json::parse(to_string(regionJson));
        auto id = region["id"].get<int>();
        auto userId = region["userId"].get<int>();
        auto isBase = region["isBase"].get<bool>();
        auto score = region["score"].get<int>();
        regions.emplace_back(score, userId, id, isBase);
    });

    g.UpdateMap(regions);
    repaint();
}

void Map::PostChosenRegion(const std::string& endPoint, const std::string toPost)
{
    auto getBaseChoice = m_requestHandler.Get(endPoint, HEADER);
    std::vector<int> regionIDs;
    if(endPoint == "/game/powerup")
        regionIDs = json::parse(getBaseChoice.text)["regions"].get<std::vector<int>>();
    else
        regionIDs = json::parse(getBaseChoice.text).get<std::vector<int>>();
    g.selectRegions(regionIDs);

    QEventLoop loop;
    connect(this, &Map::MousePressed, &loop, &QEventLoop::quit);
    loop.exec();

    if (m_selectedRegion != -1)
    {
        m_requestHandler.Post(endPoint,
                              to_string(json{{ toPost, m_selectedRegion }}),
                              HEADER);

        g.selectRegions(regionIDs);
        m_selectedRegion = -1;
    }
}

void Map::UpdatePlayers()
{
    auto getPlayers = m_requestHandler.Get("/game/players", HEADER);
    auto players = json::parse(getPlayers.text)["players"].get<std::vector<json>>();

    m_players.clear();
    std::for_each(players.begin(), players.end(), [&](const auto& playerJson)
    {
        auto player =  json::parse(to_string(playerJson));
        auto id = player["id"].get<int>();
        auto playerId = player["playerId"].get<int>();
        auto score = player["score"].get<int>();
        auto name = player["name"].get<std::string>();
        m_players.emplace_back(id, playerId, score, name);
    });
    repaint();
}

void Map::InitStateHandler()
{
    m_stateHandler.emplace(Map::State::InGame, [&]()
    {
        UpdatePlayers();
        return;
    });

    m_stateHandler.emplace(Map::State::StartNewGame, [&]()
    {
        auto mapResponse = m_requestHandler.Get("/game/map/first", HEADER);
        auto mapId = json::parse(mapResponse.text)["mapId"].get<int>();
        g.ReadMap(mapId);
        UpdatePlayers();
    });

    m_stateHandler.emplace(Map::State::FirstQuestion, [&]()
    {
        auto firstQuestion = m_requestHandler.Get("/game/firstQuestion", HEADER);
        auto question = json::parse(firstQuestion.text)["question"].get<std::string>();
        NextQuestion(QuestionType::NUMERIC, question);
    });

    m_stateHandler.emplace(Map::State::WaitingForAnswers, [&]()
    {
        return;
    });

    m_stateHandler.emplace(Map::State::AllPlayersAnswered, [&]()
    {
        auto allAnswers = m_requestHandler.Get("/game/allAnswers", HEADER);
        auto answerData = json::parse(allAnswers.text);
        auto answers = answerData["answers"].get<std::vector<json>>();
        auto correctAnswer = answerData["correctAnswer"].get<std::string>();

        std::vector<std::tuple<int, std::string, std::string>> players;
        std::for_each(answers.begin(), answers.end(), [&](decltype(answers[0])& answerJson)
        {
            auto answer = json::parse(to_string(answerJson));
            auto timeRemaining = answer["timeRemaining"].get<int>();
            auto name = answer["name"].get<std::string>();
            auto playerAnswer = answer["answer"].get<std::string>();
            players.emplace_back(std::make_tuple(timeRemaining, name, playerAnswer));
        });
        ShowResults(players, correctAnswer);
    });

    m_stateHandler.emplace(Map::State::BaseChoice, [&]()
    {
        UpdateRegions();
        UpdatePlayers();
        PostChosenRegion("/game/baseChoice", "base");
    });

    m_stateHandler.emplace(Map::State::MapChanged, [&]()
    {
        UpdatePlayers();
        UpdateRegions();
    });

    m_stateHandler.emplace(Map::State::RegionQuestion, [&]()
    {
        UpdatePlayers();
        UpdateRegions();
        auto regionQuestion = m_requestHandler.Get("/game/regionQuestion", HEADER);

        auto question = json::parse(regionQuestion.text)["question"].get<std::string>();
        NextQuestion(QuestionType::NUMERIC, question);
    });

    m_stateHandler.emplace(Map::State::RegionChoice, [&]()
    {
        PostChosenRegion("/game/regionChoice", "region");
        UpdateRegions();
        UpdatePlayers();
    });

    m_stateHandler.emplace(Map::State::Duel, [&]()
    {
        UpdateRegions();
        PostChosenRegion("/game/attackRegion", "region");
    });

    m_stateHandler.emplace(Map::State::AttackQuestion, [&]()
    {
        auto firstQuestion = m_requestHandler.Get("/game/attackQuestion", HEADER);
        auto questionData = json::parse(firstQuestion.text);
        auto question = questionData["question"].get<std::string>();
        auto type = StringToQuestionType(questionData["type"].get<std::string>());

        switch(type)
        {
            case QuestionType::NUMERIC:
                NextQuestion(type, question);
                break;
            case QuestionType::MULTIPLE_CHOICE:
                auto choicesJson = questionData["choices"].get<std::vector<json>>();
                std::array<std::pair<uint32_t, std::string>, 4> choices;
                uint32_t index = 0;
                std::for_each(choicesJson.begin(), choicesJson.end(), [&](const auto& choiceJson)
                {
                    auto choice = json::parse(to_string(choiceJson));
                    choices[index++] = std::make_pair(choice["id"].get<int>(), choice["choice"].get<std::string>());
                });
                NextQuestion(type, question, &choices);
                break;
        }
    });

    m_stateHandler.emplace(Map::State::PowerupRegionChoice, [&]()
    {
        return;
    });

    m_stateHandler.emplace(Map::State::Endgame, [&]()
    {
        auto endgameResponse = m_requestHandler.Get("/game/endgame", HEADER);
        auto endGameJson = json::parse(endgameResponse.text).get<std::vector<json>>();

        std::vector<std::tuple<int, std::string, std::string>> results;
        std::for_each(endGameJson.begin(), endGameJson.end(), [&](decltype(endGameJson[0])& resultJson)
        {
            auto result = json::parse(to_string(resultJson));
            auto name = result["name"].get<std::string>();
            auto score = result["score"].get<int>();
            results.emplace_back(std::make_tuple(score, name, ""));
        });
        ShowResults(results, "End Game");
    });


}

Map::State Map::StringToState(const std::string &state)
{
    if (state == "InGame") return State::InGame;
    if (state == "StartNewGame") return State::StartNewGame;
    if (state == "FirstQuestion") return State::FirstQuestion;
    if (state == "BaseChoice") return State::BaseChoice;
    if (state == "RegionQuestion") return State::RegionQuestion;
    if (state == "RegionChoice") return State::RegionChoice;
    if (state == "WaitingForAnswers") return State::WaitingForAnswers;
    if (state == "MapChanged") return State::MapChanged;
    if (state == "Answer") return State::Answer;
    if (state == "AllPlayersAnswered") return State::AllPlayersAnswered;
    if (state == "Duel") return State::Duel;
    if (state == "AttackQuestion") return State::AttackQuestion;
    if (state == "PowerupRegionChoice") return State::PowerupRegionChoice;
    if (state == "Endgame") return State::Endgame;
    return State{};
}

Map::QuestionType Map::StringToQuestionType(const std::string &state)
{
    if(state == "single_choice") return QuestionType::NUMERIC;
    if(state == "multiple_choice") return QuestionType::MULTIPLE_CHOICE;
    return QuestionType{};
}



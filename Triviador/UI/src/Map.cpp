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
	g.ReadMap();
    connect(m_timer, &QTimer::timeout, this, QOverload<>::of(&Map::OnGoing));
    m_timer->start(5000);
}


Map::~Map()
{
    delete m_user;
    delete m_timer;
}

void Map::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setPen(Qt::black);

	int nLongitudinalSectors = 300;
	int nTransveralSectors = 112;
	float width = 8*(this->size().width()/10);
	float height = this->size().height();
	float sectorWidth = width / nLongitudinalSectors;
	float sectorHeight = height / nTransveralSectors;

	QPixmap pixmap(sectorWidth+1, sectorHeight+1);
	pixmap.fill(Qt::black);

	for (std::vector<Tile> t : g.getTiles())
		for (Tile tt : t)
			if (tt.IsBorder())
			{
				QPointF punct(tt.GetCoordinate().second * sectorWidth, tt.GetCoordinate().first * sectorHeight);
				painter.drawPixmap(punct, pixmap);
			}

	pixmap.fill(Qt::blue);
	for (std::vector<Tile> t : g.getTiles())
		for (Tile tt : t)
			if (tt.getParentRegion()->GetNumber()==1&&!tt.IsBorder())
				painter.drawPixmap(tt.GetCoordinate().second * sectorWidth, tt.GetCoordinate().first * sectorHeight, pixmap);

	////paint score

	QPainter painter1(this);
	QFont font("Arial", 10, QFont::Bold);
	painter1.setFont(font);
	QPen pen(Qt::black,2);
	QBrush brush(Qt::blue);
	painter1.setPen(pen);
	painter1.setBrush(brush);
	
	float widthLabel = this->size().width()/25;
	float heightLabel = this->size().height()/25;

	std::vector<std::shared_ptr<Region>> map = g.getMap();
	for (auto i:map)
	{
		if (i->GetNumber())
		{
			std::pair<int,int>p=i->GetCenter();
			QRect rect(p.first*sectorWidth-widthLabel/2, p.second*sectorHeight-heightLabel/2, widthLabel, heightLabel);
			painter1.drawRect(rect);
			QString s = QString::number(300);
			painter1.drawText(rect, Qt::AlignCenter, s);
		}
	}
	//desenare playeri
	int nr_players = 2;
	for (int i = 0;i < nr_players;i++)
	{
		QPainter pt(this);
		QFont font("Arial", 12, QFont::Bold);
		pt.setFont(font);
		QPen pent(Qt::black, 3);
		QBrush brusht(Qt::yellow);
		pt.setPen(pent);
		pt.setBrush(brusht);


		QRect player(width, (height/nr_players)*i, 2 * (this->size().width() / 10)+5, this->size().height()/nr_players);
		pt.drawRect(player);
		pt.drawText(player, Qt::AlignCenter, "Monica:\n200");
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
    emit mousePressed();
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
        g.ReadMap();
    }
    else if(status == "FirstQuestion")
    {
        cpr::Response response = cpr::Get(cpr::Url{"localhost:18080/game/firstQuestion"},
                                          cpr::Header{{"ID", std::to_string(m_user->GetId())}});

        auto question = json::parse(response.text)["question"].get<std::string>();
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
            regions.emplace_back(score, userId, id);
        }
        /// GET BASECHOICE
     //   cpr::Response getBaseChoice = cpr::Get(cpr::Url{"localhost:18080/game/baseChoice"},
     //                                    cpr::Header{{"ID", std::to_string(m_user->GetId())}});
      //  auto regionIDs = json::parse(getBaseChoice.text).get<std::vector<int>>();

        /// POST SELECTED REGION

        QEventLoop loop;
        connect(this, &Map::mousePressed, &loop, &QEventLoop::quit);
        loop.exec();
        if(m_selectedRegion != -1)
        {
            cpr::Post(cpr::Url{"localhost:18080/game/baseChoice"},
                      cpr::Body{to_string(json{{"base", m_selectedRegion}})},
                      cpr::Header{{"ID", std::to_string(m_user->GetId())}});
            std::cout << m_selectedRegion << "\n";
        }
    }
    else if(status == "RegionQuestion")
    {
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


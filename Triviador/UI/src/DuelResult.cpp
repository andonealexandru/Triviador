#include "DuelResult.h"
#include <sstream>

DuelResult::DuelResult(const std::vector<std::tuple<int, std::string, std::string>>& players,
                       const std::string& correctAnswer, QWidget *parent)
	: m_players(players)
    , QMainWindow(parent)
{
    ui.setupUi(this);

    ui.correctAnswer->setText(("Correct answer: " + correctAnswer).data());

    std::array<QLabel*, 4> labels = { ui.lb1, ui.lb2, ui.lb3, ui.lb4 };
    for (int i = 0; i < players.size(); ++i)
    {
        std::ostringstream oss;
        const auto&[timeRemaining, name, answer] = players[i];

        if(timeRemaining == -1)
        {
            oss << i+1 << ": " << name << "\n"
                << "\t Nu a raspuns. ";
        }
        else oss << i+1 << ": " << name << "\n"
                 << "\t time: " << timeRemaining
                 << ", answer: " << answer;

        labels[i]->setText(QString::fromStdString(oss.str()));
    }
}

void DuelResult::paintEvent(QPaintEvent* pe)
{
    QPixmap px;
    std::string imagePath = std::string(RESOURCE_DIR) + "/duel.jpg";
    px.load(imagePath.data());
    QPainter paint(this);
    int widWidth = this->ui.centralWidget->width();
    int widHeight = this->ui.centralWidget->height();
    px = px.scaled(widWidth, widHeight, Qt::IgnoreAspectRatio);
    paint.drawPixmap(0, 0, px);
}

DuelResult::~DuelResult()
{}

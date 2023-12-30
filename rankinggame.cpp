#include "rankinggame.h"
#include "ui_rankinggame.h"

RankingGame::RankingGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RankingGame)
{
    ui->setupUi(this);
}

RankingGame::~RankingGame()
{
    delete ui;
}

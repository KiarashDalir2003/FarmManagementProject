#include "rankingpage.h"
#include "ui_rankingpage.h"

RankingPage::RankingPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RankingPage)
{
    ui->setupUi(this);
}

RankingPage::~RankingPage()
{
    delete ui;
}

#include "rankingpage.h"
#include "ui_rankingpage.h"

#include <QSqlQuery>
#include <QMessageBox>

RankingPage::RankingPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RankingPage)
{
    ui->setupUi(this);

    tbModel.setTable("coins");
    tbModel.setSort(tbModel.fieldIndex("coins"), Qt::DescendingOrder);
    tbModel.select();

    ui->tableView->setModel(&tbModel);
    ui->tableView->show();

    QSqlQuery q;
    if (!q.exec("UPDATE coins SET coins = 10"))
    {
        QMessageBox::warning(this, "Error", "Failed to reset coin values!");
        return;
    }
}

RankingPage::~RankingPage()
{
    delete ui;
}

#ifndef RANKINGPAGE_H
#define RANKINGPAGE_H

#include <QMainWindow>

#include <QSqlQuery>
#include<QSqlTableModel>

#include<QTableView>

namespace Ui {
class RankingPage;
}

class RankingPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit RankingPage(QWidget *parent = nullptr);
    ~RankingPage();

private:
    Ui::RankingPage *ui;

    QSqlTableModel tbModel;


};

#endif // RANKINGPAGE_H

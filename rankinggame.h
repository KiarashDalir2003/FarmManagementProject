#ifndef RANKINGGAME_H
#define RANKINGGAME_H

#include <QMainWindow>

namespace Ui {
class RankingGame;
}

class RankingGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit RankingGame(QWidget *parent = nullptr);
    ~RankingGame();

private:
    Ui::RankingGame *ui;
};

#endif // RANKINGGAME_H

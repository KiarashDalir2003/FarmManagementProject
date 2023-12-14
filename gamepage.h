#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QMainWindow>

namespace Ui {
class GamePage;
}

class GamePage : public QMainWindow
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);
    ~GamePage();

private:
    Ui::GamePage *ui;
};

#endif // GAMEPAGE_H

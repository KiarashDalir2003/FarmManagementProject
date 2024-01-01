#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlRecord>

namespace Ui {
class GamePage;
}

class GamePage : public QMainWindow
{
    Q_OBJECT

public:
    explicit GamePage(QWidget *parent = nullptr);
    ~GamePage();

    void ResetUi();
    void Resetdata();
    void SetWorkerNumber();

    bool updateCoinAmount(const QString user, int coinAm);

    QTimer *GameTimer = new QTimer(this);


private slots:
    void processNextRecord();
    void updateTime();
    void startProcessing();

    void on_Farm1btn_clicked();

    void on_Farm2btn_clicked();

    void on_Farm3btn_clicked();

    void on_Farm7btn_clicked();

    void on_Farm6btn_clicked();

    void on_Farm5btn_clicked();

    void on_Farm4btn_clicked();

    void on_Farm8btn_clicked();

    void on_addWorkerbtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::GamePage *ui;

    int availableWorkers = 1;
    int totalWorkers = 1;
    int remainingSeconds;

    QString username;
    int coinAmount;

    int coins;

    QSqlQuery q;

};

#endif // GAMEPAGE_H

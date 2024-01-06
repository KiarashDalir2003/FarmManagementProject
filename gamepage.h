#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlRecord>

#include <QPushButton>
#include <QLabel>

#include "ui_gamepage.h"

#include <QPropertyAnimation>
#include <QMediaPlayer>

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

    void managingFarm(QPushButton* farm, QPushButton* product, QLabel* coinLogo, QLabel* coinAmount, QLabel* totalCoins, QLabel* time, QTimer* breedTime, QTimer* penaltyTime);

    void manageProducts(QPushButton* product, QLabel* coinLogo, QLabel* coinAmount, QLabel* totalCoins, QLabel* time, QTimer* penaltyTime);

    void ShakeTotalCoinsLabel();
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

    void on_productBTN_1_clicked();

    void on_productBTN_2_clicked();

    void on_productBTN_3_clicked();

    void on_productBTN_4_clicked();

    void on_productBTN_5_clicked();

    void on_productBTN_6_clicked();

    void on_productBTN_7_clicked();

    void on_productBTN_8_clicked();



private:
    Ui::GamePage *ui;

    int availableWorkers = 1;
    int totalWorkers = 1;
    int remainingSeconds;

    QString username;
    int coinAmount;

    int coins;

    QSqlQuery q;



    QMediaPlayer *PositiveSound = new QMediaPlayer;

    QTimer* breedingTimer1 = nullptr;
    QTimer* penaltyTimer1 = nullptr;

    QTimer* breedingTimer2 = nullptr;
    QTimer* penaltyTimer2 = nullptr;

    QTimer* breedingTimer3 = nullptr;
    QTimer* penaltyTimer3 = nullptr;

    QTimer* breedingTimer4 = nullptr;
    QTimer* penaltyTimer4 = nullptr;

    QTimer* breedingTimer5 = nullptr;
    QTimer* penaltyTimer5 = nullptr;

    QTimer* breedingTimer6 = nullptr;
    QTimer* penaltyTimer6 = nullptr;

    QTimer* breedingTimer7 = nullptr;
    QTimer* penaltyTimer7 = nullptr;

    QTimer* breedingTimer8 = nullptr;
    QTimer* penaltyTimer8 = nullptr;

};

#endif // GAMEPAGE_H

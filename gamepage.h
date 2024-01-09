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

    void makeTimersNull();
    void makePenaltyTimerBooliansFalse();

    bool updateCoinAmount(const QString user, int coinAm);

    QTimer *GameTimer = new QTimer(this);

    void managingFarm(QPushButton* farm, QPushButton* product, QLabel* coinLogo, QLabel* coinAmount, QLabel* totalCoins, QLabel* time,
                      QTimer* breedTime, QTimer* penaltyTime,
                      bool* isPenalTimerActive);


    void ShakeTotalCoinsLabel();

    void KillingActionAndShakeTotalCoinsLabel();

    int checkFarmStatus(QPushButton* farm, QPushButton* product, QLabel* time);

    int showStoreMessage();


    void buyHen(QPushButton* farm, QLabel* time, QLabel* totalCoins);
    void buySheep(QPushButton* farm, QLabel* time, QLabel* totalCoins);
    void buyCow(QPushButton* farm, QLabel* time, QLabel* totalCoins);
    void buyWheat(QPushButton* farm, QLabel* time, QLabel* totalCoins);
    void buyBarlay(QPushButton* farm, QLabel* time, QLabel* totalCoins);

    void breedHen(QPushButton* farm, QPushButton* product,
                  QLabel* coinLogo, QLabel* coinAmount, QLabel* time,
                  QTimer* breedTime, QTimer* penaltyTime,
                  bool* isPenalTimerActive);

    void breedSheep(QPushButton* farm, QPushButton* product,
                    QLabel* coinLogo, QLabel* coinAmount, QLabel* time,
                    QTimer* breedTime, QTimer* penaltyTime,
                    bool* isPenalTimerActive);

    void breedCow(QPushButton* farm, QPushButton* product,
                  QLabel* coinLogo, QLabel* coinAmount, QLabel* time,
                  QTimer* breedTime, QTimer* penaltyTime,
                  bool* isPenalTimerActive);

    void breedWheat(QPushButton* farm, QPushButton* product,
                    QLabel* coinLogo, QLabel* coinAmount, QLabel* time,
                    QTimer* breedTime, QTimer* penaltyTime,
                    bool* isPenalTimerActive);

    void breedBralay(QPushButton* farm, QPushButton* product,
                     QLabel* coinLogo, QLabel* coinAmount, QLabel* time,
                     QTimer* breedTime, QTimer* penaltyTime,
                     bool* isPenalTimerActive);

    void killHen (QPushButton* farm, QPushButton* product, QLabel* totalCoins, QLabel* time);
    void killSheep (QPushButton* farm, QPushButton* product, QLabel* totalCoins, QLabel* time);
    void killCow (QPushButton* farm, QPushButton* product, QLabel* totalCoins, QLabel* time);

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
    QMediaPlayer *NegetiveSound = new QMediaPlayer;
    QMediaPlayer *TimeOverSound = new QMediaPlayer;
    QMediaPlayer *HenSound = new QMediaPlayer;
    QMediaPlayer *SheepSound = new QMediaPlayer;
    QMediaPlayer *CowSound = new QMediaPlayer;
    QMediaPlayer *PlantSound = new QMediaPlayer;
    QMediaPlayer *KillingSound = new QMediaPlayer;

    QTimer* breedingTimer1 ;
    QTimer* penaltyTimer1 ;

    QTimer* breedingTimer2 ;
    QTimer* penaltyTimer2 ;

    QTimer* breedingTimer3 ;
    QTimer* penaltyTimer3 ;

    QTimer* breedingTimer4 ;
    QTimer* penaltyTimer4 ;

    QTimer* breedingTimer5 ;
    QTimer* penaltyTimer5 ;

    QTimer* breedingTimer6 ;
    QTimer* penaltyTimer6 ;

    QTimer* breedingTimer7 ;
    QTimer* penaltyTimer7 ;

    QTimer* breedingTimer8 ;
    QTimer* penaltyTimer8 ;

    bool isPenaltyTimerActive1;
    bool isPenaltyTimerActive2;
    bool isPenaltyTimerActive3;
    bool isPenaltyTimerActive4;
    bool isPenaltyTimerActive5;
    bool isPenaltyTimerActive6;
    bool isPenaltyTimerActive7;
    bool isPenaltyTimerActive8;

    bool isUserActive;

};

#endif // GAMEPAGE_H

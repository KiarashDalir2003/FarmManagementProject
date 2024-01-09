#ifndef MYTIME_H
#define MYTIME_H

#include <QMainWindow>
#include<QTimer>
#include<QPushButton>
#include<QLabel>
#include<QWidget>
#include"ui_gamepage.h"

class myTime : public QWidget
{
    Q_OBJECT
public:
    explicit myTime(QWidget *parent = nullptr);

    void setBreedPenaltyTime(int b, int p);
    void SetWidget(int b, int p, QPushButton* f, QPushButton* prod, QLabel* timerLb);
signals:

private:
     QTimer* breedingTimer = new QTimer;
     QTimer* penaltyTimer = new QTimer;

     QLabel *timerLabel;

     QPushButton *farm;
     QPushButton *product;

     bool isBreedingTimeRunning = false;
     bool isPenaltyTimeRunning = false;

     int breedingTime ;
     int penaltyTime ;

     void startBreedingTimer();
     void stopBreedingTimer();

     void stopPenaltyTimer();
     void updateBreedingTimer();

     void updatePenaltyTimer();


};

#endif // MYTIME_H

#include "mytime.h"
#include <QMainWindow>
#include<QTimer>
#include<QPushButton>
#include<QLabel>
#include<QWidget>
#include"ui_gamepage.h"

myTime::myTime(QWidget *parent) : QWidget(parent)
{
    timerLabel = new QLabel;

    farm = new QPushButton;
    product = new QPushButton;

    connect(farm, &QPushButton::clicked, this, &myTime::startBreedingTimer);
    connect(product, &QPushButton::clicked, this, &myTime::stopPenaltyTimer);


    connect(breedingTimer, &QTimer::timeout, this, &myTime::updateBreedingTimer);
    connect(penaltyTimer, &QTimer::timeout, this , &myTime::updatePenaltyTimer);

}

void myTime::setBreedPenaltyTime(int b, int p)
{
    breedingTime = b;
    penaltyTime = p;
}

void myTime::SetWidget(int b, int p, QPushButton *f, QPushButton *prod, QLabel *timerLb)
{
    setBreedPenaltyTime(b, p);
    farm = f;
    product = prod;
    timerLabel = timerLb;
}

void myTime::startBreedingTimer()
{
    if (!isBreedingTimeRunning)
    {
        isBreedingTimeRunning = true;
        timerLabel->setText(QString::number(breedingTime));
        breedingTimer->start(1000);
    }
}

void myTime::stopBreedingTimer()
{
    if (isBreedingTimeRunning)
    {
        isBreedingTimeRunning = false;
        breedingTimer->stop();
        timerLabel->clear();
    }
}

void myTime::stopPenaltyTimer()
{
    if(isPenaltyTimeRunning)
    {
        isPenaltyTimeRunning = false;
        penaltyTimer->stop();
    }
}

void myTime::updateBreedingTimer()
{
    breedingTime--;
    if (breedingTime == 0)
    {
        stopBreedingTimer();
        penaltyTime = 5;
        if (!isPenaltyTimeRunning)
        {
            isPenaltyTimeRunning = true;

            timerLabel->setText(QString::number(penaltyTime));
            penaltyTimer->start(1000);
        }else{
            stopPenaltyTimer();
        }
    }
    else
    {
        timerLabel->setText(QString::number(breedingTime));
    }
}

void myTime::updatePenaltyTimer()
{
    penaltyTime--;
    if (penaltyTime == 0)
    {
        stopPenaltyTimer();
        startBreedingTimer();
    }
    else{
        timerLabel->setText(QString::number(penaltyTime));
    }
}




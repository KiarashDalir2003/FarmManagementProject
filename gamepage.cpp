#include "gamepage.h"
#include "ui_gamepage.h"

#include "loginpage.h"
#include "ui_loginpage.h"

#include "rankingpage.h"
#include "ui_rankingpage.h"

#include<QTime>
#include<QTimer>

#include<QtMath>

#include <QDebug>
#include <QMessageBox>
#include <QPushButton>

#include "hen.h"
#include "sheep.h"
#include "cow.h"
#include "wheat.h"
#include "barlay.h"

#include<QPropertyAnimation>
#include<QMediaPlayer>

GamePage::GamePage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GamePage)
{
    ui->setupUi(this);
    QPixmap worker("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\worker.png");
    QPixmap clock("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\clock.png");
    QPixmap coin ("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");
    QPixmap user("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\user.png");

    ui->worketIconLabel->setPixmap(worker);
    ui->clockIconLabel->setPixmap(clock);
    ui->coinIconLabel->setPixmap(coin);
    ui->addWorkerbtn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\plus.png"));
    ui->userIconLabel->setPixmap(user);

    ResetUi();

    startProcessing();

    makeTimersNull();

    makePenaltyTimerBooliansFalse();

    isUserActive = true;
}


GamePage::~GamePage()
{
    QSqlQuery q;
    if (!q.exec("UPDATE coins SET coins = 10"))
    {
        QMessageBox::warning(this, "Error", "Failed to reset coin values!");
        return;
    }

    delete ui;
}


void GamePage::ResetUi()
{
    ui->Farm1btn->setStyleSheet("background-color: rgb(0, 170, 0);");
    ui->Farm1btn->setIcon(QIcon(""));
    ui->Farm2btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm2btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm3btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm3btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm4btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm4btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm5btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm5btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm6btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm6btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm7btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm7btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm8btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm8btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm9btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm9btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm10btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm10btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm11btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm11btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm12btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm12btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));

    ui->Farm1btn->setEnabled(true);
    ui->Farm2btn->setEnabled(true);
    ui->Farm3btn->setEnabled(true);
    ui->Farm4btn->setEnabled(true);
    ui->Farm5btn->setEnabled(true);
    ui->Farm6btn->setEnabled(true);
    ui->Farm7btn->setEnabled(true);
    ui->Farm8btn->setEnabled(true);
    ui->Farm9btn->setEnabled(true);
    ui->Farm10btn->setEnabled(true);
    ui->Farm11btn->setEnabled(true);
    ui->Farm12btn->setEnabled(true);

    ui->coinAmountLabel_1->clear();
    ui->coinAmountLabel_2->clear();
    ui->coinAmountLabel_3->clear();
    ui->coinAmountLabel_4->clear();
    ui->coinAmountLabel_5->clear();
    ui->coinAmountLabel_6->clear();
    ui->coinAmountLabel_7->clear();
    ui->coinAmountLabel_8->clear();
    ui->coinAmountLabel_9->clear();
    ui->coinAmountLabel_10->clear();
    ui->coinAmountLabel_11->clear();
    ui->coinAmountLabel_12->clear();

    ui->coinLabel_1->clear();
    ui->coinLabel_2->clear();
    ui->coinLabel_3->clear();
    ui->coinLabel_4->clear();
    ui->coinLabel_5->clear();
    ui->coinLabel_6->clear();
    ui->coinLabel_7->clear();
    ui->coinLabel_8->clear();
    ui->coinLabel_9->clear();
    ui->coinLabel_10->clear();
    ui->coinLabel_11->clear();
    ui->coinLabel_12->clear();

    ui->timeLabel_1->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_3->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_4->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_5->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_6->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_7->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_8->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_9->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_10->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_11->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_12->setStyleSheet("background-color: rgb(255, 255, 255);");

    ui->productBTN_1->setIcon(QIcon(""));
    ui->productBTN_2->setIcon(QIcon(""));
    ui->productBTN_3->setIcon(QIcon(""));
    ui->productBTN_4->setIcon(QIcon(""));
    ui->productBTN_5->setIcon(QIcon(""));
    ui->productBTN_6->setIcon(QIcon(""));
    ui->productBTN_7->setIcon(QIcon(""));
    ui->productBTN_8->setIcon(QIcon(""));
    ui->productBTN_9->setIcon(QIcon(""));
    ui->productBTN_10->setIcon(QIcon(""));
    ui->productBTN_11->setIcon(QIcon(""));
    ui->productBTN_12->setIcon(QIcon(""));

    ui->productBTN_1->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_3->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_4->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_5->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_6->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_7->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_8->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_9->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_10->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_11->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_12->setStyleSheet("background-color: rgb(255, 255, 255);");

    SetWorkerNumber();
}


void GamePage::Resetdata()
{
    coins = 10;
    availableWorkers = 1;
    totalWorkers = 1;
    ResetUi();
}


void GamePage::SetWorkerNumber()
{
    QString labelTextWorkers = QString("%1/%2").arg(availableWorkers).arg(totalWorkers);
    ui->workerLabel->setText(labelTextWorkers);
}

void GamePage::makeTimersNull()
{
    breedingTimer1 = nullptr;
    penaltyTimer1 = nullptr;

    breedingTimer2 = nullptr;
    penaltyTimer2 = nullptr;

    breedingTimer3 = nullptr;
    penaltyTimer3 = nullptr;

    breedingTimer4 = nullptr;
    penaltyTimer4 = nullptr;

    breedingTimer5 = nullptr;
    penaltyTimer5 = nullptr;

    breedingTimer6 = nullptr;
    penaltyTimer6 = nullptr;

    breedingTimer7 = nullptr;
    penaltyTimer7 = nullptr;

    breedingTimer8 = nullptr;
    penaltyTimer8 = nullptr;

    breedingTimer9 = nullptr;
    penaltyTimer9 = nullptr;

    breedingTimer10 = nullptr;
    penaltyTimer10 = nullptr;

    breedingTimer11 = nullptr;
    penaltyTimer11 = nullptr;

    breedingTimer12 = nullptr;
    penaltyTimer12 = nullptr;
}

void GamePage::makePenaltyTimerBooliansFalse()
{
    isPenaltyTimerActive1 = false;
    isPenaltyTimerActive2 = false;
    isPenaltyTimerActive3 = false;
    isPenaltyTimerActive4 = false;
    isPenaltyTimerActive5 = false;
    isPenaltyTimerActive6 = false;
    isPenaltyTimerActive7 = false;
    isPenaltyTimerActive8 = false;
    isPenaltyTimerActive9 = false;
    isPenaltyTimerActive10 = false;
    isPenaltyTimerActive11 = false;
    isPenaltyTimerActive12 = false;
}


void GamePage::processNextRecord()
{
    if (q.next())
    {
        username = q.value(0).toString();
        coinAmount = q.value(1).toInt();

        ui->usernameLabel->setText(username);
        ui->coinsLabel->setText(QString::number(coinAmount));

        remainingSeconds = 180;
        QTimer::singleShot(1000, this, &GamePage::updateTime);
    }

    else
    {
        QMessageBox::information(this, "Game finished!", "All users completed the game!");
        RankingPage *R = new RankingPage;
        R->show();
        this->close();
    }
}


void GamePage::updateTime()
{
    if (remainingSeconds >= 0)
    {
        QString formattedTime = QString("%1:%2").arg(remainingSeconds / 60, 2, 10, QChar('0')).arg(remainingSeconds % 60, 2, 10, QChar('0'));
        ui->timerLabel->setText(formattedTime);
        remainingSeconds--;
        QTimer::singleShot(1000, this, &GamePage::updateTime);
    }

    else
    {
        TimeOverSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\timeoverSound.mp3"));
        TimeOverSound->play();
        QMessageBox::information(this, "Next turn", "Your time is over!");
        Resetdata();
        isUserActive = false;
        processNextRecord();
    }
}


void GamePage::startProcessing()
{
    QSqlDatabase coinsDB;
    coinsDB = QSqlDatabase::addDatabase("QSQLITE");
    coinsDB.setDatabaseName("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\ProjectDatabase.db");

    if (!coinsDB.open())
    {
        QMessageBox::warning(this, "Error", "Can not access to the database!");
        return;
    }

    q = QSqlQuery(coinsDB);

    if (!q.exec("SELECT username, coins FROM coins"))
    {
        QMessageBox::warning(this, "Error", "Error executing query");
        return;
    }

    processNextRecord();
}

//---------------------------------------------------------------------------------------------------------------------

/*
There is something that you have to consider. When you click the Farm button n, this program checks the styleSheet
of the time label n.
If it is rgb(255, 255, 255), this farm has nothing.
if it is rgb(255, 255, 254), this farm has hen.
if it is rgb(255, 255, 253), this farm has sheep.
if it is rgb(255, 255, 252), this farm has cow.
if it is rgb(255, 255, 251), this farm has wheat.
if it is rgb(255, 255, 250), this farm has barlay.
And Also checks the stylesheet of productBTN_n if it is rgb(255, 255, 254) it means that there is product
if not , there is nothing product.
*/

void GamePage::on_Farm1btn_clicked()
{
    isUserActive = true;
    managingFarm(ui->Farm1btn, ui->productBTN_1, ui->coinLabel_1, ui->coinAmountLabel_1, ui->coinsLabel, ui->timeLabel_1, breedingTimer1,  penaltyTimer1, &isPenaltyTimerActive1);

}


void GamePage::on_productBTN_1_clicked()
{
    isPenaltyTimerActive1 = false;
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm2btn_clicked()
{
    isUserActive = true;
    managingFarm(ui->Farm2btn, ui->productBTN_2, ui->coinLabel_2, ui->coinAmountLabel_2, ui->coinsLabel, ui->timeLabel_2, breedingTimer2, penaltyTimer2, &isPenaltyTimerActive2);
}


void GamePage::on_productBTN_2_clicked()
{
    isPenaltyTimerActive2 = false;
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm3btn_clicked()
{
    isUserActive = true;
    managingFarm(ui->Farm3btn, ui->productBTN_3, ui->coinLabel_3, ui->coinAmountLabel_3, ui->coinsLabel, ui->timeLabel_3, breedingTimer3, penaltyTimer3, &isPenaltyTimerActive3);
}


void GamePage::on_productBTN_3_clicked()
{
    isPenaltyTimerActive3 = false;
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm4btn_clicked()
{
    isUserActive = true;
    managingFarm(ui->Farm4btn, ui->productBTN_4, ui->coinLabel_4, ui->coinAmountLabel_4, ui->coinsLabel, ui->timeLabel_4, breedingTimer4, penaltyTimer4, &isPenaltyTimerActive4);
}


void GamePage::on_productBTN_4_clicked()
{
    isPenaltyTimerActive4 = false;
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm5btn_clicked()
{
    isUserActive = true;
    managingFarm(ui->Farm5btn, ui->productBTN_5, ui->coinLabel_5, ui->coinAmountLabel_5, ui->coinsLabel, ui->timeLabel_5, breedingTimer5, penaltyTimer5, &isPenaltyTimerActive5);
}


void GamePage::on_productBTN_5_clicked()
{
    isPenaltyTimerActive5 = false;
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm6btn_clicked()
{
    isUserActive = true;
    managingFarm(ui->Farm6btn, ui->productBTN_6, ui->coinLabel_6, ui->coinAmountLabel_6, ui->coinsLabel, ui->timeLabel_6, breedingTimer6, penaltyTimer6, &isPenaltyTimerActive6);
}


void GamePage::on_productBTN_6_clicked()
{
    isPenaltyTimerActive6 = false;
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm7btn_clicked()
{
    isUserActive = true;
    managingFarm(ui->Farm7btn, ui->productBTN_7, ui->coinLabel_7, ui->coinAmountLabel_7, ui->coinsLabel, ui->timeLabel_7, breedingTimer7, penaltyTimer7, &isPenaltyTimerActive7);
}

void GamePage::on_productBTN_7_clicked()
{
    isPenaltyTimerActive7 = false;
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm8btn_clicked()
{
    isUserActive = true;
    managingFarm(ui->Farm8btn, ui->productBTN_8, ui->coinLabel_8, ui->coinAmountLabel_8, ui->coinsLabel, ui->timeLabel_8, breedingTimer8, penaltyTimer8, &isPenaltyTimerActive8);
}

void GamePage::on_productBTN_8_clicked()
{
    isPenaltyTimerActive8 = false;
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm9btn_clicked()
{
    isUserActive = true;
    managingFarm(ui->Farm9btn, ui->productBTN_9, ui->coinLabel_9, ui->coinAmountLabel_9, ui->coinsLabel, ui->timeLabel_9, breedingTimer9,  penaltyTimer9, &isPenaltyTimerActive9);

}


void GamePage::on_productBTN_9_clicked()
{
    isPenaltyTimerActive9 = false;
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm10btn_clicked()
{
    isUserActive = true;
    managingFarm(ui->Farm10btn, ui->productBTN_10, ui->coinLabel_10, ui->coinAmountLabel_10, ui->coinsLabel, ui->timeLabel_10, breedingTimer10,  penaltyTimer10, &isPenaltyTimerActive10);

}


void GamePage::on_productBTN_10_clicked()
{
    isPenaltyTimerActive10 = false;
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm11btn_clicked()
{
    isUserActive = true;
    managingFarm(ui->Farm11btn, ui->productBTN_11, ui->coinLabel_11, ui->coinAmountLabel_11, ui->coinsLabel, ui->timeLabel_11, breedingTimer11,  penaltyTimer11, &isPenaltyTimerActive11);

}


void GamePage::on_productBTN_11_clicked()
{
    isPenaltyTimerActive11 = false;
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm12btn_clicked()
{
    isUserActive = true;
    managingFarm(ui->Farm12btn, ui->productBTN_12, ui->coinLabel_12, ui->coinAmountLabel_12, ui->coinsLabel, ui->timeLabel_12, breedingTimer12,  penaltyTimer12, &isPenaltyTimerActive12);

}


void GamePage::on_productBTN_12_clicked()
{
    isPenaltyTimerActive12 = false;
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_addWorkerbtn_clicked()
{
    coins = ui->coinsLabel->text().toInt();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Confirm",
                                  "Are you really sure you want to purchase another worker?\nworker price = 5 coins", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        if(coins < 5)
        {
            NegetiveSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));
            NegetiveSound->play();
            QMessageBox::warning(this, "Error", "You don't have enough coin");
            return;
        }

        coins -= 5;
        ShakeTotalCoinsLabel();
        if(updateCoinAmount(username, coins))
        {
            ui->coinsLabel->setText(QString::number(coins));
            availableWorkers++;
            totalWorkers++;
            SetWorkerNumber();
        }
        return;
    }
}


void GamePage::on_pushButton_clicked()
{
    LoginPage *L = new LoginPage;

    L->show();
    this->close();
}


bool GamePage::updateCoinAmount(const QString user, int coinAm)
{
    QSqlQuery q;
    q.prepare("UPDATE coins SET coins = :coinAm WHERE username = :user");
    q.bindValue(":coinAm", coinAm);
    q.bindValue(":user", user);

    if (!q.exec())
    {
        return false;
    }

    return true;
}

void GamePage::managingFarm(QPushButton* farm, QPushButton* product, QLabel* coinLogo, QLabel* coinAmount, QLabel* totalCoins, QLabel* time, QTimer* breedTime, QTimer* penaltyTime, bool *isPenalTimerActive)
{
    if(checkFarmStatus(farm, product, time) == 1)
    {
        coins = totalCoins->text().toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Oh!, You don't have this farm",
                                      "Are you really sure you want to purchase this Farm?\nfarm price = 3 coins", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            if(coins < 3)  // farm buy price = 3
            {
                NegetiveSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));
                NegetiveSound->play();
                QMessageBox::warning(this, "Sorry!", "You don't have enough coin!");
                return;
            }

            coins -= 3;    // farm buy price = 3

            if(updateCoinAmount(username, coins))
            {
                ShakeTotalCoinsLabel();
                totalCoins->setText(QString::number(coins));
                farm->setStyleSheet("background-color: rgb(0, 170, 0);");
                farm->setIcon(QIcon(""));
            }
            return;
        }
    }


    else if (checkFarmStatus(farm, product, time) == 2 )
    {
        //rgb(255, 255, 255) means that this farm has no animals or plants.


        switch (showStoreMessage())
        {
        case 0:
            buyHen(farm, time, totalCoins);
            break;

        case 1:
            buySheep(farm, time, totalCoins);
            break;

        case 2:
            buyCow(farm, time, totalCoins);
            break;

        case 3:
            buyWheat(farm, time, totalCoins);
            break;

        case 4:
            buyBarlay(farm, time, totalCoins);
            break;

        case 5:
            return;

        }
    }

    else if (checkFarmStatus(farm, product, time) == 3 )
    {
        //this farm has hen

        HenSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\henSound.mp3"));
        HenSound->play();

        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Kill", QMessageBox::AcceptRole);
        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Back", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult)
        {
        case 0:
            killHen(farm, product, totalCoins, time);
            break;


        case 1:
            breedHen(farm, product, coinLogo, coinAmount, time, breedTime, penaltyTime, isPenalTimerActive);
            break;
        case 2:
            return;
        }
    }

    else if (checkFarmStatus(farm, product, time) == 4 )
    {
        //this farm has sheep

        SheepSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\sheepSound.mp3"));
        SheepSound->play();

        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Kill", QMessageBox::AcceptRole);
        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Back", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult)
        {
        case 0:
            killSheep(farm, product, totalCoins, time);
            break;

        case 1:
            breedSheep(farm, product, coinLogo, coinAmount, time, breedTime, penaltyTime, isPenalTimerActive);
            break;
        case 2:
            return;
        }
    }

   else if (checkFarmStatus(farm, product, time) == 5 )
    {
        //this farm has cow


        CowSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\cowSound.mp3"));
        CowSound->play();

        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Kill", QMessageBox::AcceptRole);
        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Back", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult)
        {
        case 0:
            killCow(farm, product, totalCoins, time);
            break;

        case 1:
             breedCow(farm, product, coinLogo, coinAmount, time, breedTime, penaltyTime, isPenalTimerActive);
             break;
        case 2:
            return;
        }
    }


    else if  (checkFarmStatus(farm, product, time) == 6 )
    {
        //this farm has wheat

        PlantSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\plantSound.mp3"));
        PlantSound->play();

        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Back", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult)
        {
        case 0:
            breedWheat(farm, product, coinLogo, coinAmount, time, breedTime, penaltyTime, isPenalTimerActive);
            break;

        case 1:
            return;
        }

    }


     else if (checkFarmStatus(farm, product, time) == 7 )
    {
        //this farm has barlay

        PlantSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\plantSound.mp3"));
        PlantSound->play();

        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Back", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult)
        {
        case 0:
            breedBralay(farm, product, coinLogo, coinAmount, time, breedTime, penaltyTime, isPenalTimerActive);
            break;

        case 1:
            return;

        }

    }
    else
    {
        QMessageBox::warning(this, "Error!", "Something went wrong!");
    }
}


void GamePage::ShakeTotalCoinsLabel()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->coinIconLabel, "geometry");

    animation->setDuration(200);
    animation->setLoopCount(3);

    animation->setKeyValueAt(0, ui->coinIconLabel->geometry());
    animation->setKeyValueAt(0.25, ui->coinIconLabel->geometry().translated(0, 3));
    animation->setKeyValueAt(0.75, ui->coinIconLabel->geometry().translated(1, 3));
    animation->setKeyValueAt(1, ui->coinIconLabel->geometry());

    animation->start();

    PositiveSound->setMedia(
                QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\PositiveSound.mp3"));

    PositiveSound->play();
}

void GamePage::KillingActionAndShakeTotalCoinsLabel()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->coinIconLabel, "geometry");

        animation->setDuration(200);
        animation->setLoopCount(3);

        animation->setKeyValueAt(0, ui->coinIconLabel->geometry());
        animation->setKeyValueAt(0.25, ui->coinIconLabel->geometry().translated(0, 3));
        animation->setKeyValueAt(0.75, ui->coinIconLabel->geometry().translated(1, 3));
        animation->setKeyValueAt(1, ui->coinIconLabel->geometry());

        animation->start();

        KillingSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\killingSound.mp3"));
        KillingSound->play();
}

int GamePage::checkFarmStatus(QPushButton* farm, QPushButton* product, QLabel* time)
{
    if(farm->styleSheet() == "background-color: rgb(157, 157, 157);")
    {
        //this farm hasn't been purchased.
        return 1;
    }

    else if (farm->styleSheet() == "background-color: rgb(0, 170, 0);" &&
            time->styleSheet() == "background-color: rgb(255, 255, 255);"
            && product->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has nothing.
        return 2;
    }

    else if(farm->styleSheet() == "background-color: rgb(0, 170, 0);" &&
            time->styleSheet() == "background-color: rgb(255, 255, 254);"
            && product->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has hen.
        return 3;
    }

    else if(farm->styleSheet() == "background-color: rgb(0, 170, 0);" &&
            time->styleSheet() == "background-color: rgb(255, 255, 253);"
            && product->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has sheep.
        return 4;
    }

    else if(farm->styleSheet() == "background-color: rgb(0, 170, 0);" &&
            time->styleSheet() == "background-color: rgb(255, 255, 252);"
            && product->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has cow.
        return 5;
    }

    else if(farm->styleSheet() == "background-color: rgb(0, 170, 0);" &&
            time->styleSheet() == "background-color: rgb(255, 255, 251);"
            && product->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has wheat.
        return 6;
    }

    else if(farm->styleSheet() == "background-color: rgb(0, 170, 0);" &&
            time->styleSheet() == "background-color: rgb(255, 255, 250);"
            && product->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has baraly.
        return 7;
    }

    return 0;
}

int GamePage::showStoreMessage()
{
    QMessageBox StoreMsgBox;
    StoreMsgBox.setWindowTitle("You have nothing in this Farm.");
    StoreMsgBox.setText("Choose one of the following:");

    StoreMsgBox.addButton("Hen = 3 coins", QMessageBox::AcceptRole);
    StoreMsgBox.addButton("Sheep = 5 coins", QMessageBox::AcceptRole);
    StoreMsgBox.addButton("Cow = 7 coins", QMessageBox::AcceptRole);
    StoreMsgBox.addButton("Wheat = 2 coins", QMessageBox::AcceptRole);
    StoreMsgBox.addButton("Barlay = 2 coins", QMessageBox::AcceptRole);
    StoreMsgBox.addButton("Back", QMessageBox::AcceptRole);

    int result = StoreMsgBox.exec();

    return result;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GamePage::buyHen(QPushButton *farm, QLabel *time, QLabel *totalCoins)
{
    hen* Hen = new hen;

    coins = totalCoins->text().toInt();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Hen",
                                  "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        if(coins < Hen->getBuyPrice())
        {
            NegetiveSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));
            NegetiveSound->play();
            QMessageBox::warning(this, "Sorry!", "You don't have enough coin!");
            return;
        }

        coins -= Hen->getBuyPrice();
        ShakeTotalCoinsLabel();
        if(updateCoinAmount(username, coins))
        {
            totalCoins->setText(QString::number(coins));
            time->setStyleSheet("background-color: rgb(255, 255, 254);");
            //rgb(255, 255, 254) means that this farm has hen.
            farm->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
        }
    }
    delete Hen;
}

void GamePage::buySheep(QPushButton *farm, QLabel *time, QLabel *totalCoins)
{
    sheep* Sheep = new sheep;

    coins = totalCoins->text().toInt();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Sheep",
                                  "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        if(coins < Sheep->getBuyPrice())
        {
            NegetiveSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));
            NegetiveSound->play();
            QMessageBox::warning(this, "Sorry!", "You don't have enough coin!");
            return;
        }

        coins -= Sheep->getBuyPrice();
        ShakeTotalCoinsLabel();
        if(updateCoinAmount(username, coins))
        {
            totalCoins->setText(QString::number(coins));
            time->setStyleSheet("background-color: rgb(255, 255, 253);");
            //rgb(255, 255, 253) means that this farm has sheep
            farm->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
        }
    }
    delete Sheep;
}

void GamePage::buyCow(QPushButton *farm, QLabel *time, QLabel *totalCoins)
{
    cow* Cow = new cow;

    coins = totalCoins->text().toInt();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Cow",
                                  "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        if(coins < Cow->getBuyPrice())
        {
            NegetiveSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));
            NegetiveSound->play();
            QMessageBox::warning(this, "Sorry!", "You don't have enough coin!");
            return;
        }
        coins -= Cow->getBuyPrice();
        ShakeTotalCoinsLabel();
        if(updateCoinAmount(username, coins))
        {
            totalCoins->setText(QString::number(coins));
            time->setStyleSheet("background-color: rgb(255, 255, 252);");
            //rgb(255, 255, 252) means that this farm has cow.
            farm->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
        }
    }
    delete Cow;
}

void GamePage::buyWheat(QPushButton *farm, QLabel *time, QLabel *totalCoins)
{
    wheat* Wheat = new wheat;

    coins = totalCoins->text().toInt();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Wheat",
                                  "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        if(coins < Wheat->getBuyPrice())
        {
            NegetiveSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));
            NegetiveSound->play();
            QMessageBox::warning(this, "Sorry!", "You don't have enough coin!");
            return;
        }
        coins -= Wheat->getBuyPrice();
        ShakeTotalCoinsLabel();
        if(updateCoinAmount(username, coins))
        {
            totalCoins->setText(QString::number(coins));
            time->setStyleSheet("background-color: rgb(255, 255, 251);");
            //rgb(255, 255, 251) means that this farm has wheat.
            farm->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
        }
    }
    delete Wheat;
}

void GamePage::buyBarlay(QPushButton *farm, QLabel *time, QLabel *totalCoins)
{
    barlay* Barlay = new barlay;

    coins = totalCoins->text().toInt();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Barley",
                                  "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        if(coins < Barlay->getBuyPrice())
        {
            NegetiveSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));
            NegetiveSound->play();
            QMessageBox::warning(this, "Sorry!", "You don't have enough coin!");
            return;
        }
        coins -= Barlay->getBuyPrice();
        ShakeTotalCoinsLabel();
        if(updateCoinAmount(username, coins))
        {
            totalCoins->setText(QString::number(coins));
            time->setStyleSheet("background-color: rgb(255, 255, 250);");
            farm->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
        }
    }
    delete Barlay;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GamePage::breedHen(QPushButton *farm, QPushButton *product, QLabel *coinLogo, QLabel *coinAmount,
                        QLabel *time, QTimer *breedTime, QTimer *penaltyTime, bool *isPenalTimerActive)
{
    hen* Hen = new hen;

    if(availableWorkers != 0)
    {
        availableWorkers--;
        SetWorkerNumber();

        farm->setEnabled(false);

        if (breedTime && breedTime->isActive())
        {
            breedTime->stop();
            delete breedTime;

        }

        if (penaltyTime && penaltyTime->isActive())
        {
            penaltyTime->stop();
            delete penaltyTime;

        }

        breedTime = new QTimer(this);

        connect(breedTime, &QTimer::timeout, [=]() mutable
        {
            if(isUserActive)
            {
                time->setText(QString::number(Hen->getBreedingTime()));
                Hen->decreaseBreedingTime();

                if (Hen->getBreedingTime() < 0)
                {
                    breedTime->stop();
                    delete breedTime;
                    breedTime = nullptr;
                    *isPenalTimerActive = true;
                    //farm->setEnabled(true);
                    product->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\egg.png"));
                    product->setStyleSheet("background-color: rgb(255, 255, 254);");
                    time->clear();
                    QPixmap coinsPix ("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");
                    coinLogo->setPixmap(coinsPix);
                    coinAmount->setText(QString::number(Hen->getEggPrice()));

                    availableWorkers++;
                    SetWorkerNumber();

                    penaltyTime = new QTimer(this);

                    connect(penaltyTime, &QTimer::timeout, [=]() mutable
                    {
                        if(isUserActive)
                        {

                            if (*isPenalTimerActive)
                            {
                                time->setText(QString::number(Hen->getPenaltyTime()));

                                Hen->decreasePenaltyTime();

                                if (Hen->getEggPrice() == 0)
                                {
                                    coins += coinAmount->text().toInt();
                                    penaltyTime->stop();
                                    penaltyTime->deleteLater();

                                    delete penaltyTime;
                                    penaltyTime = nullptr;

                                     if (updateCoinAmount(username, coins))
                                        {

                                           ui->coinsLabel->setText(QString::number(coins));
                                           product->setIcon(QIcon(""));
                                           coinAmount->clear();
                                           coinLogo->clear();
                                           time->clear();
                                           farm->setEnabled(true);

                                           product->setStyleSheet("background-color: rgb(255, 255, 255);");
                                        }
                                }
                                if (Hen->getPenaltyTime() < 0)
                                {
                                    penaltyTime->stop();

                                    Hen->decreaseEggPrice();

                                    coinAmount->setText(QString::number(Hen->getEggPrice()));

                                    Hen->resetPenaltyTime();
                                    penaltyTime->start(1000);
                                }
                            }
                            else
                            {
                                if (product->styleSheet() == "background-color: rgb(255, 255, 254);")
                                    {

                                        if (availableWorkers != 0)
                                        {
                                          ShakeTotalCoinsLabel();
                                          coins += coinAmount->text().toInt();
                                          penaltyTime->stop();
                                          penaltyTime->deleteLater();

                                          delete penaltyTime;
                                          penaltyTime = nullptr;

                                           if (updateCoinAmount(username, coins))
                                              {

                                                 ui->coinsLabel->setText(QString::number(coins));
                                                 product->setIcon(QIcon(""));
                                                 coinAmount->clear();
                                                 coinLogo->clear();
                                                 time->clear();
                                                 farm->setEnabled(true);

                                                 product->setStyleSheet("background-color: rgb(255, 255, 255);");
                                              }
                                        }
                                    }
                            }

                        }
                        else
                        {
                            penaltyTime->stop();
                            delete penaltyTime;
                            penaltyTime = nullptr;
                            time->clear();
                            coinAmount->clear();
                        }

                    });

                    penaltyTime->start(1000);
                }
            }
            else
            {
                breedTime->stop();
                delete breedTime;
                breedTime = nullptr;
                time->clear();
                coinAmount->clear();
            }
        });

        breedTime->start(1000);
    }

    else
    {
        NegetiveSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));
        NegetiveSound->play();
        QMessageBox::warning(this, "", "You don't have a worker available.");
        return;
    }

}

void GamePage::breedSheep(QPushButton *farm, QPushButton *product, QLabel *coinLogo, QLabel *coinAmount, QLabel *time, QTimer *breedTime, QTimer *penaltyTime, bool* isPenalTimerActive)
{

    sheep* Sheep = new sheep;

    if(availableWorkers != 0)
    {
        availableWorkers--;
        SetWorkerNumber();

        farm->setEnabled(false);

        if (breedTime && breedTime->isActive())
        {
            breedTime->stop();
            delete breedTime;
        }

        if (penaltyTime && penaltyTime->isActive())
        {
            penaltyTime->stop();
            delete penaltyTime;
        }

        breedTime = new QTimer(this);

        connect(breedTime, &QTimer::timeout, [=]() mutable
        {
            if(isUserActive)
            {
                time->setText(QString::number(Sheep->getBreedingTime()));
                Sheep->decreaseBreedingTime();

                if (Sheep->getBreedingTime() < 0)
                {
                    breedTime->stop();
                    delete breedTime;
                    breedTime = nullptr;
                    *isPenalTimerActive = true;
                    //farm->setEnabled(true);
                    product->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\milk.png"));
                    product->setStyleSheet("background-color: rgb(255, 255, 254);");
                    time->clear();
                    QPixmap coinsPix ("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");
                    coinLogo->setPixmap(coinsPix);
                    coinAmount->setText(QString::number(Sheep->getMilkPrice()));

                    availableWorkers++;
                    SetWorkerNumber();

                    penaltyTime = new QTimer(this);

                    connect(penaltyTime, &QTimer::timeout, [=]() mutable
                    {
                        if(isUserActive)
                        {

                            if (*isPenalTimerActive)
                            {
                                time->setText(QString::number(Sheep->getPenaltyTime()));

                                Sheep->decreasePenaltyTime();

                                if (Sheep->getMilkPrice() == 0)
                                {
                                    coins += coinAmount->text().toInt();
                                    penaltyTime->stop();
                                    penaltyTime->deleteLater();

                                    delete penaltyTime;
                                    penaltyTime = nullptr;

                                     if (updateCoinAmount(username, coins))
                                        {

                                           ui->coinsLabel->setText(QString::number(coins));
                                           product->setIcon(QIcon(""));
                                           coinAmount->clear();
                                           coinLogo->clear();
                                           time->clear();
                                           farm->setEnabled(true);

                                           product->setStyleSheet("background-color: rgb(255, 255, 255);");
                                        }
                                }

                                if (Sheep->getPenaltyTime() < 0)
                                {
                                    penaltyTime->stop();

                                    Sheep->decreaseMilkPrice();
                                    coinAmount->setText(QString::number(Sheep->getMilkPrice()));
                                    Sheep->resetPenaltyTime();
                                    penaltyTime->start(1000);
                                }
                            }
                            else
                            {
                                if (product->styleSheet() == "background-color: rgb(255, 255, 254);")
                                    {

                                        if (availableWorkers != 0)
                                        {
                                          ShakeTotalCoinsLabel();
                                          coins += coinAmount->text().toInt();
                                          penaltyTime->stop();
                                          penaltyTime->deleteLater();

                                          delete penaltyTime;
                                          penaltyTime = nullptr;

                                           if (updateCoinAmount(username, coins))
                                              {

                                                 ui->coinsLabel->setText(QString::number(coins));
                                                 product->setIcon(QIcon(""));
                                                 coinAmount->clear();
                                                 coinLogo->clear();
                                                 time->clear();
                                                 farm->setEnabled(true);

                                                 product->setStyleSheet("background-color: rgb(255, 255, 255);");
                                              }
                                        }
                                    }
                            }

                        }
                        else
                        {
                            penaltyTime->stop();
                            delete penaltyTime;
                            penaltyTime = nullptr;
                            time->clear();
                            coinAmount->clear();
                        }

                    });

                    penaltyTime->start(1000);
                }
            }
            else
            {
                breedTime->stop();
                delete breedTime;
                breedTime = nullptr;
                time->clear();
                coinAmount->clear();
            }
        });

        breedTime->start(1000);
    }

    else
    {
        NegetiveSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));
        NegetiveSound->play();
        QMessageBox::warning(this, "", "You don't have a worker available.");
        return;
    }
}

void GamePage::breedCow(QPushButton *farm, QPushButton *product, QLabel *coinLogo, QLabel *coinAmount, QLabel *time, QTimer *breedTime, QTimer *penaltyTime, bool* isPenalTimerActive)
{

    cow* Cow = new cow;

    if(availableWorkers != 0)
    {
        availableWorkers--;
        SetWorkerNumber();

        farm->setEnabled(false);

        if (breedTime && breedTime->isActive())
        {
            breedTime->stop();
            delete breedTime;
        }

        if (penaltyTime && penaltyTime->isActive())
        {
            penaltyTime->stop();
            delete penaltyTime;
        }

        breedTime = new QTimer(this);

        connect(breedTime, &QTimer::timeout, [=]() mutable
        {
            if(isUserActive)
            {
                time->setText(QString::number(Cow->getBreedingTime()));
                Cow->decreaseBreedingTime();

                if (Cow->getBreedingTime() < 0)
                {
                    breedTime->stop();
                    delete breedTime;
                    breedTime = nullptr;
                    *isPenalTimerActive = true;
                    //farm->setEnabled(true);
                    product->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\milk.png"));
                    product->setStyleSheet("background-color: rgb(255, 255, 254);");
                    time->clear();
                    QPixmap coinsPix ("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");
                    coinLogo->setPixmap(coinsPix);
                    coinAmount->setText(QString::number(Cow->getMilkPrice()));

                    availableWorkers++;
                    SetWorkerNumber();

                    penaltyTime = new QTimer(this);

                    connect(penaltyTime, &QTimer::timeout, [=]() mutable
                    {
                        if(isUserActive)
                        {

                            if (*isPenalTimerActive)
                            {
                                time->setText(QString::number(Cow->getPenaltyTime()));

                                Cow->decreasePenaltyTime();

                                if (Cow->getMilkPrice() == 0)
                                {
                                    coins += coinAmount->text().toInt();
                                    penaltyTime->stop();
                                    penaltyTime->deleteLater();

                                    delete penaltyTime;
                                    penaltyTime = nullptr;

                                     if (updateCoinAmount(username, coins))
                                        {

                                           ui->coinsLabel->setText(QString::number(coins));
                                           product->setIcon(QIcon(""));
                                           coinAmount->clear();
                                           coinLogo->clear();
                                           time->clear();
                                           farm->setEnabled(true);

                                           product->setStyleSheet("background-color: rgb(255, 255, 255);");
                                        }
                                }
                                if (Cow->getPenaltyTime() < 0)
                                {
                                    penaltyTime->stop();

                                    Cow->decreaseMilkPrice();
                                    coinAmount->setText(QString::number(Cow->getMilkPrice()));
                                    Cow->resetPenaltyTime();
                                    penaltyTime->start(1000);
                                }
                            }
                            else
                            {
                                if (product->styleSheet() == "background-color: rgb(255, 255, 254);")
                                    {

                                        if (availableWorkers != 0)
                                        {
                                          ShakeTotalCoinsLabel();
                                          coins += coinAmount->text().toInt();
                                          penaltyTime->stop();
                                          penaltyTime->deleteLater();

                                          delete penaltyTime;
                                          penaltyTime = nullptr;

                                           if (updateCoinAmount(username, coins))
                                              {

                                                 ui->coinsLabel->setText(QString::number(coins));
                                                 product->setIcon(QIcon(""));
                                                 coinAmount->clear();
                                                 coinLogo->clear();
                                                 time->clear();
                                                 farm->setEnabled(true);

                                                 product->setStyleSheet("background-color: rgb(255, 255, 255);");
                                              }
                                        }
                                    }
                            }

                        }
                        else
                        {
                            penaltyTime->stop();
                            delete penaltyTime;
                            penaltyTime = nullptr;
                            time->clear();
                            coinAmount->clear();
                        }

                    });

                    penaltyTime->start(1000);
                }
            }
            else
            {
                breedTime->stop();
                delete breedTime;
                breedTime = nullptr;
                time->clear();
                coinAmount->clear();
            }
        });

        breedTime->start(1000);
    }

    else
    {
        NegetiveSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));
        NegetiveSound->play();
        QMessageBox::warning(this, "", "You don't have a worker available.");
        return;
    }

}

void GamePage::breedWheat(QPushButton *farm, QPushButton *product, QLabel *coinLogo, QLabel *coinAmount, QLabel *time, QTimer *breedTime, QTimer *penaltyTime, bool* isPenalTimerActive)
{

    wheat* Wheat = new wheat;

    if(availableWorkers != 0)
    {
        availableWorkers--;
        SetWorkerNumber();

        farm->setEnabled(false);

        if (breedTime && breedTime->isActive())
        {
            breedTime->stop();
            delete breedTime;
        }

        if (penaltyTime && penaltyTime->isActive())
        {
            penaltyTime->stop();
            delete penaltyTime;
        }

        breedTime = new QTimer(this);

        connect(breedTime, &QTimer::timeout, [=]() mutable
        {
            if(isUserActive)
            {
                time->setText(QString::number(Wheat->getBreedingTime()));
                Wheat->decreaseBreedingTime();

                if (Wheat->getBreedingTime() < 0)
                {
                    breedTime->stop();
                    delete breedTime;
                    breedTime = nullptr;
                    *isPenalTimerActive = true;
                    //farm->setEnabled(true);
                    product->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                    product->setStyleSheet("background-color: rgb(255, 255, 254);");
                    time->clear();
                    QPixmap coinsPix ("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");
                    coinLogo->setPixmap(coinsPix);
                    coinAmount->setText(QString::number(Wheat->getWheatPrice()));

                    availableWorkers++;
                    SetWorkerNumber();

                    penaltyTime = new QTimer(this);

                    connect(penaltyTime, &QTimer::timeout, [=]() mutable
                    {
                        if(isUserActive)
                        {

                            if (*isPenalTimerActive)
                            {
                                time->setText(QString::number(Wheat->getPenaltyTime()));

                                Wheat->decreasePenaltyTime();

                                if (Wheat->getWheatPrice() == 0)
                                {
                                    coins += coinAmount->text().toInt();
                                    penaltyTime->stop();
                                    penaltyTime->deleteLater();

                                    delete penaltyTime;
                                    penaltyTime = nullptr;

                                     if (updateCoinAmount(username, coins))
                                        {

                                           ui->coinsLabel->setText(QString::number(coins));
                                           product->setIcon(QIcon(""));
                                           coinAmount->clear();
                                           coinLogo->clear();
                                           time->clear();
                                           farm->setEnabled(true);

                                           product->setStyleSheet("background-color: rgb(255, 255, 255);");
                                        }
                                }

                                if (Wheat->getPenaltyTime() < 0)
                                {
                                    penaltyTime->stop();

                                    Wheat->decreaseWheatPrice();
                                    coinAmount->setText(QString::number(Wheat->getWheatPrice()));
                                    Wheat->resetPenaltyTime();
                                    penaltyTime->start(1000);
                                }
                            }
                            else
                            {
                                if (product->styleSheet() == "background-color: rgb(255, 255, 254);")
                                    {

                                        if (availableWorkers != 0)
                                        {
                                          ShakeTotalCoinsLabel();
                                          coins += coinAmount->text().toInt();
                                          penaltyTime->stop();
                                          penaltyTime->deleteLater();

                                          delete penaltyTime;
                                          penaltyTime = nullptr;

                                           if (updateCoinAmount(username, coins))
                                              {

                                                 ui->coinsLabel->setText(QString::number(coins));
                                                 product->setIcon(QIcon(""));
                                                 coinAmount->clear();
                                                 coinLogo->clear();
                                                 time->clear();
                                                 farm->setEnabled(true);

                                                 product->setStyleSheet("background-color: rgb(255, 255, 255);");

                                                 time->setStyleSheet("background-color: rgb(255, 255, 255);");
                                                 farm->setIcon(QIcon(""));
                                              }
                                        }
                                    }
                            }

                        }
                        else
                        {
                            penaltyTime->stop();
                            delete penaltyTime;
                            penaltyTime = nullptr;
                            time->clear();
                            coinAmount->clear();
                        }

                    });

                    penaltyTime->start(1000);
                }
            }
            else
            {
                breedTime->stop();
                delete breedTime;
                breedTime = nullptr;
                time->clear();
                coinAmount->clear();
            }
        });

        breedTime->start(1000);
    }

    else
    {
        NegetiveSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));
        NegetiveSound->play();
        QMessageBox::warning(this, "", "You don't have a worker available.");
        return;
    }

}

void GamePage::breedBralay(QPushButton *farm, QPushButton *product, QLabel *coinLogo, QLabel *coinAmount, QLabel *time, QTimer *breedTime, QTimer *penaltyTime, bool* isPenalTimerActive)
{
    barlay* Barlay = new barlay;

    if(availableWorkers != 0)
    {
        availableWorkers--;
        SetWorkerNumber();

        farm->setEnabled(false);

        if (breedTime && breedTime->isActive())
        {
            breedTime->stop();
            delete breedTime;
        }

        if (penaltyTime && penaltyTime->isActive())
        {
            penaltyTime->stop();
            delete penaltyTime;
        }

        breedTime = new QTimer(this);

        connect(breedTime, &QTimer::timeout, [=]() mutable
        {
            if(isUserActive)
            {
                time->setText(QString::number(Barlay->getBreedingTime()));
                Barlay->decreaseBreedingTime();

                if (Barlay->getBreedingTime() < 0)
                {
                    breedTime->stop();
                    delete breedTime;
                    breedTime = nullptr;
                    *isPenalTimerActive = true;
                    //farm->setEnabled(true);
                    product->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
                    product->setStyleSheet("background-color: rgb(255, 255, 254);");
                    time->clear();
                    QPixmap coinsPix ("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");
                    coinLogo->setPixmap(coinsPix);
                    coinAmount->setText(QString::number(Barlay->getBarlayPrice()));

                    availableWorkers++;
                    SetWorkerNumber();

                    penaltyTime = new QTimer(this);

                    connect(penaltyTime, &QTimer::timeout, [=]() mutable
                    {
                        if(isUserActive)
                        {

                            if (*isPenalTimerActive)
                            {
                                time->setText(QString::number(Barlay->getPenaltyTime()));

                                Barlay->decreasePenaltyTime();

                                if (Barlay->getBarlayPrice() == 0)
                                {
                                    coins += coinAmount->text().toInt();
                                    penaltyTime->stop();
                                    penaltyTime->deleteLater();

                                    delete penaltyTime;
                                    penaltyTime = nullptr;

                                     if (updateCoinAmount(username, coins))
                                        {

                                           ui->coinsLabel->setText(QString::number(coins));
                                           product->setIcon(QIcon(""));
                                           coinAmount->clear();
                                           coinLogo->clear();
                                           time->clear();
                                           farm->setEnabled(true);

                                           product->setStyleSheet("background-color: rgb(255, 255, 255);");
                                        }
                                }
                                if (Barlay->getPenaltyTime() < 0)
                                {
                                    penaltyTime->stop();

                                    Barlay->decreaseBarlayPrice();
                                    coinAmount->setText(QString::number(Barlay->getBarlayPrice()));
                                    Barlay->resetPenaltyTime();
                                    penaltyTime->start(1000);
                                }
                            }
                            else
                            {
                                if (product->styleSheet() == "background-color: rgb(255, 255, 254);")
                                    {

                                        if (availableWorkers != 0)
                                        {
                                          ShakeTotalCoinsLabel();
                                          coins += coinAmount->text().toInt();
                                          penaltyTime->stop();
                                          penaltyTime->deleteLater();

                                          delete penaltyTime;
                                          penaltyTime = nullptr;

                                           if (updateCoinAmount(username, coins))
                                              {

                                                 ui->coinsLabel->setText(QString::number(coins));
                                                 product->setIcon(QIcon(""));
                                                 coinAmount->clear();
                                                 coinLogo->clear();
                                                 time->clear();
                                                 farm->setEnabled(true);

                                                 product->setStyleSheet("background-color: rgb(255, 255, 255);");
                                                 time->setStyleSheet("background-color: rgb(255, 255, 255);");
                                                 farm->setIcon(QIcon(""));
                                              }
                                        }
                                    }
                            }

                        }
                        else
                        {
                            penaltyTime->stop();
                            delete penaltyTime;
                            penaltyTime = nullptr;
                            time->clear();
                            coinAmount->clear();
                        }

                    });

                    penaltyTime->start(1000);
                }
            }
            else
            {
                breedTime->stop();
                delete breedTime;
                breedTime = nullptr;
                time->clear();
                coinAmount->clear();
            }
        });

        breedTime->start(1000);
    }

    else
    {
        NegetiveSound->setMedia(QUrl::fromLocalFile("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));
        NegetiveSound->play();
        QMessageBox::warning(this, "", "You don't have a worker available.");
        return;
    }
}

//--------------------------------------------------------------------------------------------------------------------

void GamePage::killHen(QPushButton *farm, QPushButton *product, QLabel *totalCoins, QLabel *time)
{
    hen* Hen = new hen;

    coins += Hen->getMeatPrice();
    KillingActionAndShakeTotalCoinsLabel();
    if(updateCoinAmount(username, coins))
    {
        totalCoins->setText(QString::number(coins));
        farm->setIcon(QIcon(""));
        product->setIcon(QIcon(""));
        time->setStyleSheet("background-color: rgb(255, 255, 255);");
    }

    delete Hen;
}

//--------------------------------------------------------------------------------------------------------------------

void GamePage::killSheep(QPushButton *farm, QPushButton *product, QLabel *totalCoins, QLabel *time)
{
    sheep* Sheep = new sheep;
    coins += Sheep->getMeatPrice();
    KillingActionAndShakeTotalCoinsLabel();
    if(updateCoinAmount(username, coins))
    {
        totalCoins->setText(QString::number(coins));
        farm->setIcon(QIcon(""));
        product->setIcon(QIcon(""));
        time->setStyleSheet("background-color: rgb(255, 255, 255);");

    }

    delete Sheep;
}

//--------------------------------------------------------------------------------------------------------------------

void GamePage::killCow(QPushButton *farm, QPushButton *product, QLabel *totalCoins, QLabel *time)
{
    cow* Cow = new cow;
    coins += Cow->getMeatPrice();
    KillingActionAndShakeTotalCoinsLabel();
    if(updateCoinAmount(username, coins))
    {
        totalCoins->setText(QString::number(coins));
        farm->setIcon(QIcon(""));
        product->setIcon(QIcon(""));
        time->setStyleSheet("background-color: rgb(255, 255, 255);");
    }

    delete Cow;
}


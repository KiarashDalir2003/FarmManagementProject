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

GamePage::GamePage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GamePage)
{
    ui->setupUi(this);
    QPixmap worker("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\worker.png");
    QPixmap clock("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\clock.png");
    QPixmap coin ("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");
    QPixmap user("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\user.png");

    ui->worketIconLabel->setPixmap(worker);
    ui->clockIconLabel->setPixmap(clock);
    ui->coinIconLabel->setPixmap(coin);
    ui->addWorkerbtn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\plus.png"));
    ui->userIconLabel->setPixmap(user);

    ResetUi();
    startProcessing();
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
    ui->Farm2btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm3btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm3btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm4btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm4btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm5btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm5btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm6btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm6btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm7btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm7btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));
    ui->Farm8btn->setStyleSheet("background-color: rgb(157, 157, 157);");
    ui->Farm8btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\padlock.png"));

    ui->coinAmountLabel_1->clear();
    ui->coinAmountLabel_2->clear();
    ui->coinAmountLabel_3->clear();
    ui->coinAmountLabel_4->clear();
    ui->coinAmountLabel_5->clear();
    ui->coinAmountLabel_6->clear();
    ui->coinAmountLabel_7->clear();
    ui->coinAmountLabel_8->clear();

    ui->coinLabel_1->clear();
    ui->coinLabel_2->clear();
    ui->coinLabel_3->clear();
    ui->coinLabel_4->clear();
    ui->coinLabel_5->clear();
    ui->coinLabel_6->clear();
    ui->coinLabel_7->clear();
    ui->coinLabel_8->clear();

    ui->timeLabel_1->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_3->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_4->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_5->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_6->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_7->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->timeLabel_8->setStyleSheet("background-color: rgb(255, 255, 255);");

    ui->productBTN_1->setIcon(QIcon(""));
    ui->productBTN_2->setIcon(QIcon(""));
    ui->productBTN_3->setIcon(QIcon(""));
    ui->productBTN_4->setIcon(QIcon(""));
    ui->productBTN_5->setIcon(QIcon(""));
    ui->productBTN_6->setIcon(QIcon(""));
    ui->productBTN_7->setIcon(QIcon(""));
    ui->productBTN_8->setIcon(QIcon(""));

    ui->productBTN_1->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_3->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_4->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_5->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_6->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_7->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->productBTN_8->setStyleSheet("background-color: rgb(255, 255, 255);");

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
        QMessageBox::information(this, "Next turn", "Your time is over!");
        Resetdata();
        processNextRecord();
    }
}


void GamePage::startProcessing()
{
    QSqlDatabase coinsDB;
    coinsDB = QSqlDatabase::addDatabase("QSQLITE");
    coinsDB.setDatabaseName("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\ProjectDatabase.db");

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
    hen Hen;
    sheep Sheep;
    cow Cow;
    wheat Wheat;
    barlay Barlay;


    if (ui->Farm1btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
            ui->timeLabel_1->styleSheet() == "background-color: rgb(255, 255, 255);"
            && ui->productBTN_1->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //rgb(255, 255, 255) means that this farm has no animals or plants.

        QMessageBox StoreMsgBox;
        StoreMsgBox.setWindowTitle("You have nothing in this Farm.");
        StoreMsgBox.setText("Choose one of the following:");

        StoreMsgBox.addButton("Chicken", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Sheep", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Cow", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Wheat", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Barlay", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Exit", QMessageBox::AcceptRole);

        int result = StoreMsgBox.exec();

        switch (result)
        {
        case 0:
            coins = ui->coinsLabel->text().toInt();
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Chicken",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Hen.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }

                coins -= Hen.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_1->setStyleSheet("background-color: rgb(255, 255, 254);");
                    //rgb(255, 255, 254) means that this farm has chichen.
                    ui->Farm1btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                }
            }
            return;

        case 1:
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Sheep.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }

                coins -= Sheep.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_1->setStyleSheet("background-color: rgb(255, 255, 253);");
                    //rgb(255, 255, 253) means that this farm has sheep
                    ui->Farm1btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                }
            }
            break;

        case 2:
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Cow.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Cow.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_1->setStyleSheet("background-color: rgb(255, 255, 252);");
                    //rgb(255, 255, 252) means that this farm has cow.
                    ui->Farm1btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                }
            }
            break;

        case 3:
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Wheat.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Wheat.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_1->setStyleSheet("background-color: rgb(255, 255, 251);");
                    //rgb(255, 255, 251) means that this farm has wheat.
                    ui->Farm1btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                }
            }
            break;

        case 4:
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Barlay.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Barlay.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_1->setStyleSheet("background-color: rgb(255, 255, 250);");
                    ui->Farm1btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
                }
            }
            break;

        case 5:
            return;

        }
    }

    else if (ui->Farm1btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_1->styleSheet() == "background-color: rgb(255, 255, 254);"
             && ui->productBTN_1->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has hen

        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Kill", QMessageBox::AcceptRole);
        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Exit", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult)
        {
        case 0:
            coins += Hen.getMeatPrice();
            if(updateCoinAmount(username, coins))
            {
                ui->coinsLabel->setText(QString::number(coins));
                ui->Farm1btn->setIcon(QIcon(""));
                ui->productBTN_1->setIcon(QIcon(""));
                ui->timeLabel_1->setStyleSheet("background-color: rgb(255, 255, 255);");
                availableWorkers++;
                SetWorkerNumber();
            }
            break;


        case 1:
            if(availableWorkers != 0)
            {
                availableWorkers--;
                SetWorkerNumber();

                ui->Farm1btn->setEnabled(false);

                if (breedingTimer1 && breedingTimer1->isActive())
                {
                    breedingTimer1->stop();
                    delete breedingTimer1;
                }

                if (penaltyTimer1 && penaltyTimer1->isActive())
                {
                    penaltyTimer1->stop();
                    delete penaltyTimer1;
                }

                breedingTimer1 = new QTimer(this);
                connect(breedingTimer1, &QTimer::timeout, [=]() mutable
                {
                    ui->timeLabel_1->setText(QString::number(Hen.getBreedingTime()));
                    Hen.decreaseBreedingTime();

                    if (Hen.getBreedingTime() < 0)
                    {
                        breedingTimer1->stop();
                        delete breedingTimer1;
                        breedingTimer1 = nullptr;
                        ui->Farm1btn->setEnabled(true);
                        ui->productBTN_1->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\egg.png"));
                        ui->productBTN_1->setStyleSheet("background-color: rgb(255, 255, 254);");
                        ui->timeLabel_1->clear();
                        QPixmap coinsPix ("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");
                        ui->coinLabel_1->setPixmap(coinsPix);
                        ui->coinAmountLabel_1->setText(QString::number(Hen.getEggPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTimer1 = new QTimer(this);
                        connect(penaltyTimer1, &QTimer::timeout, [=]() mutable
                        {

                            ui->timeLabel_1->setText(QString::number(Hen.getPenaltyTime()));

                            Hen.decreasePenaltyTime();
                            if (Hen.getPenaltyTime() < 0)
                            {
                                penaltyTimer1->stop();
                                // penaltyTimer1->deleteLater();

                                Hen.decreaseEggPrice();
                                ui->coinAmountLabel_1->setText(QString::number(Hen.getEggPrice()));
                                Hen.resetPenaltyTime();
                                penaltyTimer1->start(1000);
                            }
                        });

                        penaltyTimer1->start(1000);
                    }
                });

                breedingTimer1->start(1000);


                break;
            }

            else
            {
                QMessageBox::warning(this, "", "You don't have a worker available.");
                return;
            }
        case 2:
            return;
        }
    }

    else if (ui->Farm1btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_1->styleSheet() == "background-color: rgb(255, 255, 253);"
             && ui->productBTN_1->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has sheep

        sheep Sheep;
        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Kill", QMessageBox::AcceptRole);
        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Exit", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult)
        {
        case 0:
            coins += Sheep.getMeatPrice();
            if(updateCoinAmount(username, coins))
            {
                ui->coinsLabel->setText(QString::number(coins));
                ui->Farm1btn->setIcon(QIcon(""));
                ui->timeLabel_1->setStyleSheet("background-color: rgb(255, 255, 255);");
                availableWorkers++;
                SetWorkerNumber();
            }
            break;

        case 1:
            if(availableWorkers != 0)
            {
                availableWorkers--;
                SetWorkerNumber();

                ui->Farm1btn->setEnabled(false);

                if (breedingTimer1 && breedingTimer1->isActive())
                {
                    breedingTimer1->stop();
                    delete breedingTimer1;
                }

                if (penaltyTimer1 && penaltyTimer1->isActive())
                {
                    penaltyTimer1->stop();
                    delete penaltyTimer1;
                }
                breedingTimer1 = new QTimer(this);
                connect(breedingTimer1, &QTimer::timeout, [=]() mutable
                {
                    ui->timeLabel_1->setText(QString::number(Sheep.getBreedingTime()));
                    Sheep.decreaseBreedingTime();

                    if (Sheep.getBreedingTime() < 0)
                    {
                        breedingTimer1->stop();

                        delete breedingTimer1;
                        breedingTimer1 = nullptr;

                        ui->Farm1btn->setEnabled(true);

                        ui->productBTN_1->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\milk.png"));
                        ui->productBTN_1->setStyleSheet("background-color: rgb(255, 255, 254);");

                        ui->timeLabel_1->clear();

                        QPixmap coinsPix ("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

                        ui->coinLabel_1->setPixmap(coinsPix);
                        ui->coinAmountLabel_1->setText(QString::number(Sheep.getMilkPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTimer1 = new QTimer(this);
                        connect(penaltyTimer1, &QTimer::timeout, [=]() mutable{

                            ui->timeLabel_1->setText(QString::number(Sheep.getPenaltyTime()));

                            Sheep.decreasePenaltyTime();
                            if (Sheep.getPenaltyTime() < 0)
                            {
                                penaltyTimer1->stop();
                                //  penaltyTimer1->deleteLater();

                                Sheep.decreaseMilkPrice();
                                ui->coinAmountLabel_1->setText(QString::number(Sheep.getMilkPrice()));
                                Sheep.resetPenaltyTime();
                                penaltyTimer1->start(1000);

                            }
                        } );
                        penaltyTimer1->start(1000);


                    }
                });

                breedingTimer1->start(1000);
                break;
            }

            else
            {
                QMessageBox::warning(this, "", "You don't have a worker available.");
                return;
            }
        }
    }

    else if (ui->Farm1btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_1->styleSheet() == "background-color: rgb(255, 255, 252);"
             && ui->productBTN_1->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has cow

        cow Cow;
        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Kill", QMessageBox::AcceptRole);
        questionMsg.addButton("Breed", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult)
        {
        case 0:

            coins += Cow.getMeatPrice();
            if(updateCoinAmount(username, coins))
            {
                ui->coinsLabel->setText(QString::number(coins));
                ui->Farm1btn->setIcon(QIcon(""));
                ui->timeLabel_1->setStyleSheet("background-color: rgb(255, 255, 255);");
                availableWorkers++;
                SetWorkerNumber();
            }
            break;

        case 1:
            if (availableWorkers != 0)
            {
                availableWorkers--;
                SetWorkerNumber();

                ui->Farm1btn->setEnabled(false);

                if (breedingTimer1 && breedingTimer1->isActive())
                {
                    breedingTimer1->stop();
                    delete breedingTimer1;
                }

                if (penaltyTimer1 && penaltyTimer1->isActive())
                {
                    penaltyTimer1->stop();
                    delete penaltyTimer1;
                }
                breedingTimer1 = new QTimer(this);
                connect(breedingTimer1, &QTimer::timeout, [=]() mutable
                {
                    ui->timeLabel_1->setText(QString::number(Cow.getBreedingTime()));
                    Cow.decreaseBreedingTime();

                    if (Cow.getBreedingTime() < 0)
                    {
                        breedingTimer1->stop();

                        delete breedingTimer1;
                        breedingTimer1 = nullptr;

                        ui->Farm1btn->setEnabled(true);

                        ui->productBTN_1->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\milk.png"));
                        ui->productBTN_1->setStyleSheet("background-color: rgb(255, 255, 254);");

                        ui->timeLabel_1->clear();

                        QPixmap coinsPix ("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

                        ui->coinLabel_1->setPixmap(coinsPix);
                        ui->coinAmountLabel_1->setText(QString::number(Cow.getMilkPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTimer1 = new QTimer(this);
                        connect(penaltyTimer1, &QTimer::timeout, [=]() mutable{

                            ui->timeLabel_1->setText(QString::number(Cow.getPenaltyTime()));

                            Cow.decreasePenaltyTime();
                            if (Cow.getPenaltyTime() < 0)
                            {
                                penaltyTimer1->stop();
                                //  penaltyTimer1->deleteLater();

                                Cow.decreaseMilkPrice();
                                ui->coinAmountLabel_1->setText(QString::number(Cow.getMilkPrice()));
                                Cow.resetPenaltyTime();
                                penaltyTimer1->start(1000);

                            }
                        } );
                        penaltyTimer1->start(1000);

                    }
                });

                breedingTimer1->start(1000);


                break;
            }

            else {
                QMessageBox::warning(this, "", "You don't have a worker available.");
                return;
            }
        case 2:
            return;
        }
    }
    else if (ui->Farm1btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_1->styleSheet() == "background-color: rgb(255, 255, 251);"
             && ui->productBTN_1->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has wheat
        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Exit", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult) {
        case 0:

            if (availableWorkers != 0)
            {
                availableWorkers--;
                SetWorkerNumber();

                ui->Farm1btn->setEnabled(false);

                if (breedingTimer1 && breedingTimer1->isActive())
                {
                    breedingTimer1->stop();
                    delete breedingTimer1;
                }

                if (penaltyTimer1 && penaltyTimer1->isActive())
                {
                    penaltyTimer1->stop();
                    delete penaltyTimer1;
                }
                breedingTimer1 = new QTimer(this);
                connect(breedingTimer1, &QTimer::timeout, [=]() mutable
                {
                    ui->timeLabel_1->setText(QString::number(Wheat.getBreedingTime()));
                    Wheat.decreaseBreedingTime();

                    if (Wheat.getBreedingTime() < 0)
                    {
                        breedingTimer1->stop();

                        delete breedingTimer1;
                        breedingTimer1 = nullptr;

                        ui->Farm1btn->setEnabled(true);

                        ui->productBTN_1->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                        ui->productBTN_1->setStyleSheet("background-color: rgb(255, 255, 254);");

                        ui->timeLabel_1->clear();

                        QPixmap coinsPix ("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

                        ui->coinLabel_1->setPixmap(coinsPix);
                        ui->coinAmountLabel_1->setText(QString::number(Wheat.getWheatPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTimer1 = new QTimer(this);
                        connect(penaltyTimer1, &QTimer::timeout, [=]() mutable{

                            ui->timeLabel_1->setText(QString::number(Wheat.getPenaltyTime()));

                            Wheat.decreasePenaltyTime();
                            if (Wheat.getPenaltyTime() < 0)
                            {
                                penaltyTimer1->stop();
                                //  penaltyTimer1->deleteLater();

                                Wheat.decreaseWheatPrice();
                                ui->coinAmountLabel_1->setText(QString::number(Wheat.getWheatPrice()));
                                Wheat.resetPenaltyTime();
                                penaltyTimer1->start(1000);

                            }
                        } );
                        penaltyTimer1->start(1000);

                    }
                });

                breedingTimer1->start(1000);
                break;
            }

            else
            {
                QMessageBox::warning(this, "", "You don't have a worker available.");
                return;
            }

        case 2:
            return;
        }

    }
    else if (ui->Farm1btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_1->styleSheet() == "background-color: rgb(255, 255, 250);"
             && ui->productBTN_1->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has barlay
        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Exit", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult) {
        case 0:

            if (availableWorkers != 0)
            {
                availableWorkers--;
                SetWorkerNumber();

                ui->Farm1btn->setEnabled(false);
                if (breedingTimer1 && breedingTimer1->isActive())
                {
                    breedingTimer1->stop();
                    delete breedingTimer1;
                }

                if (penaltyTimer1 && penaltyTimer1->isActive())
                {
                    penaltyTimer1->stop();
                    delete penaltyTimer1;
                }
                breedingTimer1 = new QTimer(this);
                connect(breedingTimer1, &QTimer::timeout, [=]() mutable
                {
                    ui->timeLabel_1->setText(QString::number(Barlay.getBreedingTime()));
                    Barlay.decreaseBreedingTime();

                    if (Barlay.getBreedingTime() < 0)
                    {
                        breedingTimer1->stop();

                        delete breedingTimer1;
                        breedingTimer1 = nullptr;

                        ui->Farm1btn->setEnabled(true);

                        ui->productBTN_1->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
                        ui->productBTN_1->setStyleSheet("background-color: rgb(255, 255, 254);");

                        ui->timeLabel_1->clear();

                        QPixmap coinsPix ("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

                        ui->coinLabel_1->setPixmap(coinsPix);
                        ui->coinAmountLabel_1->setText(QString::number(Barlay.getBarlayPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTimer1 = new QTimer(this);
                        connect(penaltyTimer1, &QTimer::timeout, [=]() mutable{

                            ui->timeLabel_1->setText(QString::number(Barlay.getPenaltyTime()));

                            Barlay.decreasePenaltyTime();
                            if (Barlay.getPenaltyTime() < 0)
                            {
                                penaltyTimer1->stop();
                                //  penaltyTimer1->deleteLater();

                                Barlay.decreaseBarlayPrice();
                                ui->coinAmountLabel_1->setText(QString::number(Barlay.getBarlayPrice()));
                                Barlay.resetPenaltyTime();
                                penaltyTimer1->start(1000);

                            }
                        } );
                        penaltyTimer1->start(1000);

                    }
                });

                breedingTimer1->start(1000);


                break;
            }
            else
            {
                QMessageBox::warning(this, "", "You don't have a worker available.");
                return;
            }
        case 1:
            return;

        }

    }

}


void GamePage::on_productBTN_1_clicked()
{
    if (ui->productBTN_1->styleSheet() == "background-color: rgb(255, 255, 254);")
    {
        if(availableWorkers != 0)
        {
            coins += ui->coinAmountLabel_1->text().toInt();
            penaltyTimer1->stop();
            delete penaltyTimer1;
            penaltyTimer1 = nullptr;

            if (updateCoinAmount(username, coins))
            {

                ui->coinsLabel->setText(QString::number(coins));
                ui->productBTN_1->setIcon(QIcon(""));
                ui->coinAmountLabel_1->clear();
                ui->coinLabel_1->clear();
                ui->timeLabel_1->clear();

                ui->productBTN_1->setStyleSheet("background-color: rgb(255, 255, 255);");
            }
        }
    }
}


void GamePage::on_Farm2btn_clicked()
{
    hen Hen;
    sheep Sheep;
    cow Cow;
    wheat Wheat;
    barlay Barlay;

    if(ui->Farm2btn->styleSheet() == "background-color: rgb(157, 157, 157);")
    {
        coins = ui->coinsLabel->text().toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Oh!, You don't have this farm",
                                      "Are you really sure you want to purchase this Farm?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            if(coins < 3)  // farm buy price = 3
            {
                QMessageBox::warning(this, "Sorry!", "You dont have enough coin!");
                return;
            }

            coins -= 3;    // farm buy price = 3
            if(updateCoinAmount(username, coins))
            {
                ui->coinsLabel->setText(QString::number(coins));
                ui->Farm2btn->setStyleSheet("background-color: rgb(0, 170, 0);");
                ui->Farm2btn->setIcon(QIcon(""));
            }
            return;
        }
    }

    else if (ui->Farm2btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_2->styleSheet() == "background-color: rgb(255, 255, 255);"
             && ui->productBTN_2->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //rgb(255, 255, 255) means that this farm has nothing
        QMessageBox StoreMsgBox;
        StoreMsgBox.setWindowTitle("You have nothing in this Farm.");
        StoreMsgBox.setText("Choose one of the following:");

        StoreMsgBox.addButton("Chicken", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Sheep", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Cow", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Wheat", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Barlay", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Exit", QMessageBox::AcceptRole);

        int result = StoreMsgBox.exec();


        switch (result)
        {
        case 0 :
            coins = ui->coinsLabel->text().toInt();
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Chicken",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Hen.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Hen.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_2->setStyleSheet("background-color: rgb(255, 255, 254);");
                    ui->Farm2btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                }
            }
            break;

        case 1 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Sheep.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                if(updateCoinAmount(username, coins))
                {
                    coins -= Sheep.getBuyPrice();
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_2->setStyleSheet("background-color: rgb(255, 255, 253);");
                    ui->Farm2btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                }
            }
            break;

        case 2 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Cow.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Cow.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_2->setStyleSheet("background-color: rgb(255, 255, 252);");
                    ui->Farm2btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                }
            }
            break;

        case 3 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Wheat.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Wheat.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_2->setStyleSheet("background-color: rgb(255, 255, 251);");
                    ui->Farm2btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                }
            }
            break;

        case 4 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Barlay.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Barlay.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_2->setStyleSheet("background-color: rgb(255, 255, 250);");
                    ui->Farm2btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
                }
            }
            break;
        }
    }
    else if (ui->Farm2btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_2->styleSheet() == "background-color: rgb(255, 255, 254);"
             && ui->productBTN_2->styleSheet() == "background-color: rgb(255, 255, 255);")
    {


        //this  farm has hen

        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Kill", QMessageBox::AcceptRole);
        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Exit", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult)
        {
        case 0:

            coins += Hen.getMeatPrice();
            if(updateCoinAmount(username, coins))
            {
                ui->coinsLabel->setText(QString::number(coins));
                ui->Farm2btn->setIcon(QIcon(""));
                ui->productBTN_2->setIcon(QIcon(""));
                ui->timeLabel_2->setStyleSheet("background-color: rgb(255, 255, 255);");
                availableWorkers++;
                SetWorkerNumber();
            }

            break;

        case 1:

            if(availableWorkers != 0)
            {
                availableWorkers--;
                SetWorkerNumber();

                ui->Farm2btn->setEnabled(false);

                if (breedingTimer2 && breedingTimer2->isActive())
                {
                    breedingTimer2->stop();
                    delete breedingTimer2;
                }

                if (penaltyTimer2 && penaltyTimer2->isActive())
                {
                    penaltyTimer2->stop();
                    delete penaltyTimer2;
                }
                breedingTimer2 = new QTimer(this);
                connect(breedingTimer2, &QTimer::timeout, [=]() mutable
                {
                    ui->timeLabel_2->setText(QString::number(Hen.getBreedingTime()));
                    Hen.decreaseBreedingTime();

                    if (Hen.getBreedingTime() < 0)
                    {
                        breedingTimer2->stop();

                        delete breedingTimer2;
                        breedingTimer2 = nullptr;

                        ui->Farm2btn->setEnabled(true);

                        ui->productBTN_2->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\egg.png"));
                        ui->productBTN_2->setStyleSheet("background-color: rgb(255, 255, 254);");

                        ui->timeLabel_2->clear();

                        QPixmap coinsPix ("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

                        ui->coinLabel_2->setPixmap(coinsPix);
                        ui->coinAmountLabel_2->setText(QString::number(Hen.getEggPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTimer2 = new QTimer(this);
                        connect(penaltyTimer2, &QTimer::timeout, [=]() mutable{

                            ui->timeLabel_2->setText(QString::number(Hen.getPenaltyTime()));

                            Hen.decreasePenaltyTime();
                            if (Hen.getPenaltyTime() < 0)
                            {
                                penaltyTimer2->stop();
                                //  penaltyTimer1->deleteLater();

                                Hen.decreaseEggPrice();
                                ui->coinAmountLabel_2->setText(QString::number(Hen.getEggPrice()));
                                Hen.resetPenaltyTime();
                                penaltyTimer2->start(1000);

                            }
                        } );
                        penaltyTimer2->start(1000);

                    }
                });

                breedingTimer2->start(1000);
                break;
            }

            else
            {
                QMessageBox::warning(this, "", "You don't have a worker available.");
                return;
            }

        case 2:
            return;
        }
    }

    else if (ui->Farm2btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_2->styleSheet() == "background-color: rgb(255, 255, 253);"
             && ui->productBTN_2->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has sheep

        sheep Sheep;
        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Kill", QMessageBox::AcceptRole);
        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Exit", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult)
        {
        case 0:

            coins += Sheep.getMeatPrice();
            if(updateCoinAmount(username, coins))
            {
                ui->coinsLabel->setText(QString::number(coins));
                ui->Farm2btn->setIcon(QIcon(""));
                ui->timeLabel_2->setStyleSheet("background-color: rgb(255, 255, 255);");
                availableWorkers++;
                SetWorkerNumber();
            }
            break;

        case 1:

            if(availableWorkers != 0)
            {
                availableWorkers--;
                SetWorkerNumber();

                ui->Farm1btn->setEnabled(false);

                if (breedingTimer2 && breedingTimer2->isActive())
                {
                    breedingTimer2->stop();
                    delete breedingTimer2;
                }

                if (penaltyTimer2 && penaltyTimer2->isActive())
                {
                    penaltyTimer2->stop();
                    delete penaltyTimer2;
                }
                breedingTimer2 = new QTimer(this);
                connect(breedingTimer2, &QTimer::timeout, [=]() mutable
                {
                    ui->timeLabel_2->setText(QString::number(Sheep.getBreedingTime()));
                    Sheep.decreaseBreedingTime();

                    if (Sheep.getBreedingTime() < 0)
                    {
                        breedingTimer2->stop();

                        delete breedingTimer2;
                        breedingTimer2 = nullptr;

                        ui->Farm2btn->setEnabled(true);

                        ui->productBTN_2->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\milk.png"));
                        ui->productBTN_2->setStyleSheet("background-color: rgb(255, 255, 254);");

                        ui->timeLabel_2->clear();

                        QPixmap coinsPix ("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

                        ui->coinLabel_2->setPixmap(coinsPix);
                        ui->coinAmountLabel_2->setText(QString::number(Sheep.getMilkPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTimer2 = new QTimer(this);
                        connect(penaltyTimer2, &QTimer::timeout, [=]() mutable{

                            ui->timeLabel_2->setText(QString::number(Sheep.getPenaltyTime()));

                            Sheep.decreasePenaltyTime();
                            if (Sheep.getPenaltyTime() < 0)
                            {
                                penaltyTimer2->stop();
                                //  penaltyTimer1->deleteLater();

                                Sheep.decreaseMilkPrice();
                                ui->coinAmountLabel_2->setText(QString::number(Sheep.getMilkPrice()));
                                Sheep.resetPenaltyTime();
                                penaltyTimer2->start(1000);

                            }
                        } );
                        penaltyTimer2->start(1000);


                    }
                });

                breedingTimer2->start(1000);

                break;
            }
            else
            {
                QMessageBox::warning(this, "", "You don't have a worker available.");
                return;
            }
        case 2:
            return;
        }
    }
    else if (ui->Farm2btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_2->styleSheet() == "background-color: rgb(255, 255, 252);"
             && ui->productBTN_2->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has cow

        cow Cow;
        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Kill", QMessageBox::AcceptRole);
        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Exit", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult)
        {
        case 0:

            coins += Cow.getMeatPrice();
            if(updateCoinAmount(username, coins))
            {
                ui->coinsLabel->setText(QString::number(coins));
                ui->Farm2btn->setIcon(QIcon(""));
                ui->timeLabel_2->setStyleSheet("background-color: rgb(255, 255, 255);");
                availableWorkers++;
                SetWorkerNumber();
            }
            break;

        case 1:


            if (availableWorkers != 0)
            {
                availableWorkers--;
                SetWorkerNumber();
                ui->Farm1btn->setEnabled(false);

                if (breedingTimer2 && breedingTimer2->isActive())
                {
                    breedingTimer2->stop();
                    delete breedingTimer2;
                }

                if (penaltyTimer2 && penaltyTimer2->isActive())
                {
                    penaltyTimer2->stop();
                    delete penaltyTimer2;
                }
                breedingTimer2 = new QTimer(this);
                connect(breedingTimer2, &QTimer::timeout, [=]() mutable
                {
                    ui->timeLabel_2->setText(QString::number(Cow.getBreedingTime()));
                    Cow.decreaseBreedingTime();

                    if (Cow.getBreedingTime() < 0)
                    {
                        breedingTimer2->stop();

                        delete breedingTimer2;
                        breedingTimer2 = nullptr;

                        ui->Farm2btn->setEnabled(true);

                        ui->productBTN_2->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\milk.png"));
                        ui->productBTN_2->setStyleSheet("background-color: rgb(255, 255, 254);");

                        ui->timeLabel_2->clear();

                        QPixmap coinsPix ("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

                        ui->coinLabel_2->setPixmap(coinsPix);
                        ui->coinAmountLabel_2->setText(QString::number(Cow.getMilkPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTimer2 = new QTimer(this);
                        connect(penaltyTimer2, &QTimer::timeout, [=]() mutable{

                            ui->timeLabel_2->setText(QString::number(Cow.getPenaltyTime()));

                            Cow.decreasePenaltyTime();
                            if (Cow.getPenaltyTime() < 0)
                            {
                                penaltyTimer2->stop();
                                //  penaltyTimer1->deleteLater();

                                Cow.decreaseMilkPrice();
                                ui->coinAmountLabel_2->setText(QString::number(Cow.getMilkPrice()));
                                Cow.resetPenaltyTime();
                                penaltyTimer2->start(1000);

                            }
                        } );
                        penaltyTimer2->start(1000);


                    }
                });

                breedingTimer2->start(1000);


                break;
            }

            else {
                QMessageBox::warning(this, "", "You don't have a worker available.");
                return;
            }
        case 2 :
            return;
        }
    }
    else if (ui->Farm2btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_2->styleSheet() == "background-color: rgb(255, 255, 251);"
             && ui->productBTN_2->styleSheet() == "backgeound-color: rgb(255, 255, 255);")
    {
        //this farm has wheat

        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Exit", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult) {
        case 0:

            if (availableWorkers != 0)
            {
                availableWorkers--;
                SetWorkerNumber();

                ui->Farm2btn->setEnabled(false);
                if (breedingTimer2 && breedingTimer2->isActive())
                {
                    breedingTimer2->stop();
                    delete breedingTimer2;
                }

                if (penaltyTimer2 && penaltyTimer2->isActive())
                {
                    penaltyTimer2->stop();
                    delete penaltyTimer2;
                }
                breedingTimer2 = new QTimer(this);
                connect(breedingTimer2, &QTimer::timeout, [=]() mutable
                {
                    ui->timeLabel_2->setText(QString::number(Wheat.getBreedingTime()));
                    Wheat.decreaseBreedingTime();

                    if (Wheat.getBreedingTime() < 0)
                    {
                        breedingTimer2->stop();

                        delete breedingTimer2;
                        breedingTimer2 = nullptr;

                        ui->Farm2btn->setEnabled(true);

                        ui->productBTN_2->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                        ui->productBTN_2->setStyleSheet("background-color: rgb(255, 255, 254);");

                        ui->timeLabel_2->clear();

                        QPixmap coinsPix ("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

                        ui->coinLabel_2->setPixmap(coinsPix);
                        ui->coinAmountLabel_2->setText(QString::number(Wheat.getWheatPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTimer2 = new QTimer(this);
                        connect(penaltyTimer2, &QTimer::timeout, [=]() mutable{

                            ui->timeLabel_2->setText(QString::number(Wheat.getPenaltyTime()));

                            Wheat.decreasePenaltyTime();
                            if (Wheat.getPenaltyTime() < 0)
                            {
                                penaltyTimer2->stop();
                                // penaltyTimer1->deleteLater();

                                Wheat.decreaseWheatPrice();
                                ui->coinAmountLabel_2->setText(QString::number(Wheat.getWheatPrice()));
                                Wheat.resetPenaltyTime();
                                penaltyTimer2->start(1000);

                            }
                        } );
                        penaltyTimer2->start(1000);

                    }
                });

                breedingTimer2->start(1000);
                break;
            }

            else
            {
                QMessageBox::warning(this, "", "You don't have a worker available.");
                return;
            }

        case 1:
            return;
        }


    }
    else if (ui->Farm2btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_2->styleSheet() == "background-color: rgb(255, 255, 250);"
             && ui->productBTN_2->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has barlay
        QMessageBox questionMsg;

        questionMsg.setWindowTitle("Action!");
        questionMsg.setText("Choose one:");

        questionMsg.addButton("Breed", QMessageBox::AcceptRole);
        questionMsg.addButton("Exit", QMessageBox::AcceptRole);

        int questionMsgResult;
        questionMsgResult = questionMsg.exec();

        switch (questionMsgResult) {
        case 0:

            if (availableWorkers != 0)
            {
                availableWorkers--;
                SetWorkerNumber();

                ui->Farm2btn->setEnabled(false);
                if (breedingTimer2 && breedingTimer2->isActive())
                {
                    breedingTimer2->stop();
                    delete breedingTimer2;
                }

                if (penaltyTimer2 && penaltyTimer2->isActive())
                {
                    penaltyTimer2->stop();
                    delete penaltyTimer2;
                }
                breedingTimer2 = new QTimer(this);
                connect(breedingTimer2, &QTimer::timeout, [=]() mutable
                {
                    ui->timeLabel_2->setText(QString::number(Barlay.getBreedingTime()));
                    Barlay.decreaseBreedingTime();

                    if (Barlay.getBreedingTime() < 0)
                    {
                        breedingTimer2->stop();

                        delete breedingTimer2;
                        breedingTimer2 = nullptr;

                        ui->Farm2btn->setEnabled(true);

                        ui->productBTN_2->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
                        ui->productBTN_2->setStyleSheet("background-color: rgb(255, 255, 254);");

                        ui->timeLabel_2->clear();

                        QPixmap coinsPix ("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

                        ui->coinLabel_2->setPixmap(coinsPix);
                        ui->coinAmountLabel_2->setText(QString::number(Barlay.getBarlayPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTimer2 = new QTimer(this);
                        connect(penaltyTimer2, &QTimer::timeout, [=]() mutable{

                            ui->timeLabel_2->setText(QString::number(Barlay.getPenaltyTime()));

                            Barlay.decreasePenaltyTime();
                            if (Barlay.getPenaltyTime() < 0)
                            {
                                penaltyTimer2->stop();
                                //  penaltyTimer1->deleteLater();

                                Barlay.decreaseBarlayPrice();
                                ui->coinAmountLabel_2->setText(QString::number(Barlay.getBarlayPrice()));
                                Barlay.resetPenaltyTime();
                                penaltyTimer2->start(1000);

                            }
                        } );
                        penaltyTimer2->start(1000);

                    }
                });

                breedingTimer2->start(1000);


                break;
            }
            else
            {
                QMessageBox::warning(this, "", "You don't have a worker available.");
                return;
            }

        case 1:
            return;

        }
    }

}


void GamePage::on_productBTN_2_clicked()
{
    if (ui->productBTN_2->styleSheet() == "background-color: rgb(255, 255, 254);")
    {

        if (availableWorkers != 0)
        {
            coins += ui->coinAmountLabel_2->text().toInt();
            penaltyTimer2->stop();
            delete penaltyTimer2;
            penaltyTimer2 = nullptr;

            if (updateCoinAmount(username, coins))
            {

                ui->coinsLabel->setText(QString::number(coins));
                ui->productBTN_2->setIcon(QIcon(""));
                ui->coinAmountLabel_2->clear();
                ui->coinLabel_2->clear();
                ui->timeLabel_2->clear();

                ui->productBTN_2->setStyleSheet("background-color: rgb(255, 255, 255);");
            }
        }
    }
}


void GamePage::on_Farm3btn_clicked()
{
    if(ui->Farm3btn->styleSheet() == "background-color: rgb(157, 157, 157);")
    {
        coins = ui->coinsLabel->text().toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Oh!, You don't have this farm",
                                      "Are you really sure you want to purchase this Farm?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            if(coins < 3)
            {
                QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                return;
            }
            coins -= 3;
            if(updateCoinAmount(username, coins))
            {
                ui->coinsLabel->setText(QString::number(coins));
                ui->Farm3btn->setStyleSheet("background-color: rgb(0, 170, 0);");
                ui->Farm3btn->setIcon(QIcon(""));
            }
            return;
        }
    }

    else if (ui->Farm3btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_3->styleSheet() == "background-color: rgb(255, 255, 255);"
             && ui->productBTN_3->text().isEmpty())
    {
        QMessageBox StoreMsgBox;
        StoreMsgBox.setWindowTitle("You have nothing in this Farm.");
        StoreMsgBox.setText("Choose one of the following:");

        StoreMsgBox.addButton("Chicken", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Sheep", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Cow", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Wheat", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Barlay", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Exit", QMessageBox::AcceptRole);

        int result = StoreMsgBox.exec();

        hen Hen;
        sheep Sheep;
        cow Cow;
        wheat Wheat;
        barlay Barlay;

        switch (result) {
        case 0 :
            coins = ui->coinsLabel->text().toInt();
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Chicken",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Hen.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Hen.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_3->setStyleSheet("background-color: rgb(255, 255, 254);");
                    ui->Farm3btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                }
            }
            break;

        case 1 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Sheep.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Sheep.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_3->setStyleSheet("background-color: rgb(255, 255, 253);");
                    ui->Farm3btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                }
            }
            break;

        case 2 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Cow.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Cow.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_3->setStyleSheet("background-color: rgb(255, 255, 252);");
                    ui->Farm3btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                }
            }
            break;

        case 3 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Wheat.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Wheat.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_3->setStyleSheet("background-color: rgb(255, 255, 251);");
                    ui->Farm3btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                }
            }
            break;

        case 4 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Barlay.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Barlay.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_3->setStyleSheet("background-color: rgb(255, 255, 250);");
                    ui->Farm3btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
                }
            }
            break;

        }
    }
}


void GamePage::on_Farm4btn_clicked()
{
    if(ui->Farm4btn->styleSheet() == "background-color: rgb(157, 157, 157);")
    {
        coins = ui->coinsLabel->text().toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Oh!, You don't have this farm",
                                      "Are you really sure you want to purchase this Farm?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            if(coins < 3)
            {
                QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                return;
            }
            coins -= 3;
            if(updateCoinAmount(username, coins))
            {
                ui->coinsLabel->setText(QString::number(coins));
                ui->Farm4btn->setStyleSheet("background-color: rgb(0, 170, 0);");
                ui->Farm4btn->setIcon(QIcon(""));
            }
            return;
        }
    }
    else if (ui->Farm4btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_4->styleSheet() == "background-color: rgb(255, 255, 255);"
             && ui->productBTN_4->text().isEmpty()
             )
    {

        hen Hen;
        sheep Sheep;
        cow Cow;
        wheat Wheat;
        barlay Barlay;

        QMessageBox StoreMsgBox;
        StoreMsgBox.setWindowTitle("You have nothing in this Farm.");
        StoreMsgBox.setText("Choose one of the following:");

        StoreMsgBox.addButton("Chicken", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Sheep", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Cow", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Wheat", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Barlay", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Exit", QMessageBox::AcceptRole);

        int result = StoreMsgBox.exec();

        switch (result) {
        case 0 :
            coins = ui->coinsLabel->text().toInt();
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Chicken",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Hen.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Hen.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {

                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_4->setStyleSheet("background-color: rgb(255, 255, 254);");
                    ui->Farm4btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                }
            }
            break;

        case 1 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Sheep.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Sheep.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_4->setStyleSheet("background-color: rgb(255, 255, 253);");
                    ui->Farm4btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                }
            }
            break;

        case 2 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Cow.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Cow.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_4->setStyleSheet("background-color: rgb(255, 255, 252);");
                    ui->Farm4btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                }
            }
            break;

        case 3 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Wheat.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Wheat.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_4->setStyleSheet("background-color: rgb(255, 255, 251);");
                    ui->Farm4btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                }
            }
            break;

        case 4 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Barlay.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Barlay.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_4->setStyleSheet("background-color: rgb(255, 255, 250);");
                    ui->Farm4btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
                }
            }
            break;

        case 5:
            return;
        }
    }
}


void GamePage::on_Farm5btn_clicked()
{
    if(ui->Farm5btn->styleSheet() == "background-color: rgb(157, 157, 157);")
    {
        coins = ui->coinsLabel->text().toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Oh!, You don't have this farm",
                                      "Are you really sure you want to purchase this Farm?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            if(coins < 3)
            {
                QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                return;
            }
            coins -= 3;
            if(updateCoinAmount(username, coins))
            {
                ui->coinsLabel->setText(QString::number(coins));
                ui->Farm5btn->setStyleSheet("background-color: rgb(0, 170, 0);");
                ui->Farm5btn->setIcon(QIcon(""));
            }
            return;
        }
    }
    else if (ui->Farm5btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_5->styleSheet() == "background-color: rgb(255, 255, 255);"
             && ui->productBTN_5->text().isEmpty()
             )
    {
        hen Hen;
        sheep Sheep;
        cow Cow;
        wheat Wheat;
        barlay Barlay;

        QMessageBox StoreMsgBox;
        StoreMsgBox.setWindowTitle("You have nothing in this Farm.");
        StoreMsgBox.setText("Choose one of the following:");

        StoreMsgBox.addButton("Chicken", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Sheep", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Cow", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Wheat", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Barlay", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Exit", QMessageBox::AcceptRole);

        int result = StoreMsgBox.exec();

        switch (result) {
        case 0 :
            coins = ui->coinsLabel->text().toInt();
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Chicken",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Hen.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Hen.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_5->setStyleSheet("background-color: rgb(255, 255, 254);");
                    ui->Farm5btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                }
            }
            break;

        case 1 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Sheep.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Sheep.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_5->setStyleSheet("background-color: rgb(255, 255, 253);");
                    ui->Farm5btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                }
            }
            break;

        case 2 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Cow.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Cow.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_5->setStyleSheet("background-color: rgb(255, 255, 252);");
                    ui->Farm5btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                }
            }
            break;

        case 3 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Wheat.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Wheat.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_5->setStyleSheet("background-color: rgb(255, 255, 251);");
                    ui->Farm5btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                }
            }
            break;

        case 4 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Barlay.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Barlay.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_5->setStyleSheet("background-color: rgb(255, 255, 250);");
                    ui->Farm5btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
                }
            }
            break;

        case 5:
            return;
        }
    }
}


void GamePage::on_Farm6btn_clicked()
{
    if(ui->Farm6btn->styleSheet() == "background-color: rgb(157, 157, 157);")
    {
        coins = ui->coinsLabel->text().toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Oh!, You don't have this farm",
                                      "Are you really sure you want to purchase this Farm?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            if(coins < 3)
            {
                QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                return;
            }
            coins -= 3;
            if(updateCoinAmount(username, coins))
            {
                ui->coinsLabel->setText(QString::number(coins));
                ui->Farm6btn->setStyleSheet("background-color: rgb(0, 170, 0);");
                ui->Farm6btn->setIcon(QIcon(""));
            }
            return;
        }
    }

    else if (ui->Farm6btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_6->styleSheet() == "background-color: rgb(255, 255, 255);"
             && ui->productBTN_6->text().isEmpty())
    {
        hen Hen;
        sheep Sheep;
        cow Cow;
        wheat Wheat;
        barlay Barlay;

        QMessageBox StoreMsgBox;
        StoreMsgBox.setWindowTitle("You have nothing in this Farm.");
        StoreMsgBox.setText("Choose one of the following:");

        StoreMsgBox.addButton("Chicken", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Sheep", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Cow", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Wheat", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Barlay", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Exit", QMessageBox::AcceptRole);

        int result = StoreMsgBox.exec();

        switch (result)
        {
        case 0 :
            coins = ui->coinsLabel->text().toInt();
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Chicken",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Hen.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Hen.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_6->setStyleSheet("background-color: rgb(255, 255, 254);");
                    ui->Farm6btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                }
            }
            break;

        case 1 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Sheep.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Sheep.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_6->setStyleSheet("background-color: rgb(255, 255, 253);");
                    ui->Farm6btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                }
                break;

                case 2 :
                    coins = ui->coinsLabel->text().toInt();
                    reply = QMessageBox::question(nullptr, "Cow",
                                                  "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                    if (reply == QMessageBox::Yes)
                    {
                        if(coins < Cow.getBuyPrice())
                        {
                            QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                            return;
                        }
                        coins -= Cow.getBuyPrice();
                        if(updateCoinAmount(username, coins))
                        {
                            ui->coinsLabel->setText(QString::number(coins));
                            ui->timeLabel_6->setStyleSheet("background-color: rgb(255, 255, 252);");
                            ui->Farm6btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                        }
                    }
                    break;

                case 3 :
                    coins = ui->coinsLabel->text().toInt();
                    reply = QMessageBox::question(nullptr, "Wheat",
                                                  "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                    if (reply == QMessageBox::Yes)
                    {
                        if(coins < Wheat.getBuyPrice())
                        {
                            QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                            return;
                        }
                        coins -= Wheat.getBuyPrice();
                        if(updateCoinAmount(username, coins))
                        {
                            ui->coinsLabel->setText(QString::number(coins));
                            ui->timeLabel_6->setStyleSheet("background-color: rgb(255, 255, 251);");
                            ui->Farm6btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                        }
                    }
                    break;

                case 4 :
                    coins = ui->coinsLabel->text().toInt();
                    reply = QMessageBox::question(nullptr, "Barley",
                                                  "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                    if (reply == QMessageBox::Yes)
                    {
                        if(coins < Barlay.getBuyPrice())
                        {
                            QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                            return;
                        }
                        coins -= Barlay.getBuyPrice();
                        if(updateCoinAmount(username, coins))
                        {
                            ui->coinsLabel->setText(QString::number(coins));
                            ui->timeLabel_6->setStyleSheet("background-color: rgb(255, 255, 250);");
                            ui->Farm6btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
                        }
                    }
                    break;

                case 5:
                    return;
            }
        }
    }

}


void GamePage::on_Farm7btn_clicked()
{
    if(ui->Farm7btn->styleSheet() == "background-color: rgb(157, 157, 157);")
    {
        coins = ui->coinsLabel->text().toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Oh!, You don't have this farm",
                                      "Are you really sure you want to purchase this Farm?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            if(coins < 3)
            {
                QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                return;
            }
            coins -= 3;
            if(updateCoinAmount(username, coins))
            {
                ui->coinsLabel->setText(QString::number(coins));
                ui->Farm7btn->setStyleSheet("background-color: rgb(0, 170, 0);");
                ui->Farm7btn->setIcon(QIcon(""));
            }
            return;
        }
    }

    else if (ui->Farm7btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_7->styleSheet() == "background-color: rgb(255, 255, 255);"
             && ui->productBTN_7->text().isEmpty())
    {
        hen Hen;
        sheep Sheep;
        cow Cow;
        wheat Wheat;
        barlay Barlay;

        QMessageBox StoreMsgBox;
        StoreMsgBox.setWindowTitle("You have nothing in this Farm.");
        StoreMsgBox.setText("Choose one of the following:");

        StoreMsgBox.addButton("Chicken", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Sheep", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Cow", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Wheat", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Barlay", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Exit", QMessageBox::AcceptRole);

        int result = StoreMsgBox.exec();

        switch (result) {
        case 0 :
            coins = ui->coinsLabel->text().toInt();
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Chicken",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Hen.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Hen.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_7->setStyleSheet("background-color: rgb(255, 255, 254);");
                    ui->Farm7btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                }
            }
            break;

        case 1 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Sheep.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Sheep.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_7->setStyleSheet("background-color: rgb(255, 255, 253);");
                    ui->Farm7btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                }
            }
            break;

        case 2 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Cow.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Cow.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_7->setStyleSheet("background-color: rgb(255, 255, 252);");
                    ui->Farm7btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                }
            }
            break;

        case 3 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Wheat.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Wheat.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_7->setStyleSheet("background-color: rgb(255, 255, 251);");
                    ui->Farm7btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                }
            }
            break;

        case 4 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Barlay.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Barlay.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_7->setStyleSheet("background-color: rgb(255, 255, 250);");
                    ui->Farm7btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
                }
            }
            break;

        case 5:
            return;
        }
    }
}


void GamePage::on_Farm8btn_clicked()
{
    if(ui->Farm8btn->styleSheet() == "background-color: rgb(157, 157, 157);")
    {
        coins = ui->coinsLabel->text().toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Oh!, You don't have this farm",
                                      "Are you really sure you want to purchase this Farm?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            if(coins < 3)
            {
                QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                return;
            }
            coins -= 3;
            if(updateCoinAmount(username, coins))
            {
                ui->coinsLabel->setText(QString::number(coins));
                ui->Farm8btn->setStyleSheet("background-color: rgb(0, 170, 0);");
                ui->Farm8btn->setIcon(QIcon(""));
            }
            return;
        }
    }

    else if (ui->Farm8btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             ui->timeLabel_8->styleSheet() == "background-color: rgb(255, 255, 255);"
             && ui->productBTN_8->text().isEmpty())
    {
        hen Hen;
        sheep Sheep;
        cow Cow;
        wheat Wheat;
        barlay Barlay;

        QMessageBox StoreMsgBox;
        StoreMsgBox.setWindowTitle("You have nothing in this Farm.");
        StoreMsgBox.setText("Choose one of the following:");

        StoreMsgBox.addButton("Chicken", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Sheep", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Cow", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Wheat", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Barlay", QMessageBox::AcceptRole);
        StoreMsgBox.addButton("Exit", QMessageBox::AcceptRole);

        int result = StoreMsgBox.exec();

        switch (result)
        {
        case 0 :
            coins = ui->coinsLabel->text().toInt();
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Chicken",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Hen.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Hen.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_8->setStyleSheet("background-color: rgb(255, 255, 254);");
                    ui->Farm8btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                }
            }
            break;

        case 1 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Sheep.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Sheep.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_8->setStyleSheet("background-color: rgb(255, 255, 253);");
                    ui->Farm8btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                }
            }
            break;

        case 2 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Cow.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Cow.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_8->setStyleSheet("background-color: rgb(255, 255, 252);");
                    ui->Farm8btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                }
            }
            break;

        case 3 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Wheat.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Wheat.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_8->setStyleSheet("background-color: rgb(255, 255, 251);");
                    ui->Farm8btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                }
            }
            break;

        case 4 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Barlay.getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Barlay.getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    ui->coinsLabel->setText(QString::number(coins));
                    ui->timeLabel_8->setStyleSheet("background-color: rgb(255, 255, 250);");
                    ui->Farm8btn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
                }
            }
            break;

        case 5:
            return;
        }
    }
}


void GamePage::on_addWorkerbtn_clicked()
{
    coins = ui->coinsLabel->text().toInt();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Confirm",
                                  "Are you really sure you want to purchase another worker?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        if(coins < 5)
        {
            QMessageBox::warning(this, "Error", "You do not have enough coin");
            return;
        }

        coins -= 5;
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

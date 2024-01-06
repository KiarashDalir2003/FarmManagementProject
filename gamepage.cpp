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
    managingFarm(ui->Farm1btn, ui->productBTN_1, ui->coinLabel_1, ui->coinAmountLabel_1, ui->coinsLabel, ui->timeLabel_1, breedingTimer1, penaltyTimer1);
}


void GamePage::on_productBTN_1_clicked()
{
    manageProducts(ui->productBTN_1, ui->coinLabel_1, ui->coinAmountLabel_1, ui->coinsLabel, ui->timeLabel_1, penaltyTimer1);
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm2btn_clicked()
{
    managingFarm(ui->Farm2btn, ui->productBTN_2, ui->coinLabel_2, ui->coinAmountLabel_2, ui->coinsLabel, ui->timeLabel_2, breedingTimer2, penaltyTimer2);
}


void GamePage::on_productBTN_2_clicked()
{
    manageProducts(ui->productBTN_2, ui->coinLabel_2, ui->coinAmountLabel_2, ui->coinsLabel, ui->timeLabel_2, penaltyTimer2);
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm3btn_clicked()
{
    managingFarm(ui->Farm3btn, ui->productBTN_3, ui->coinLabel_3, ui->coinAmountLabel_3, ui->coinsLabel, ui->timeLabel_3, breedingTimer3, penaltyTimer3);
}


void GamePage::on_productBTN_3_clicked()
{
    manageProducts(ui->productBTN_3, ui->coinLabel_3, ui->coinAmountLabel_3, ui->coinsLabel, ui->timeLabel_3, penaltyTimer3);
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm4btn_clicked()
{
    managingFarm(ui->Farm4btn, ui->productBTN_4, ui->coinLabel_4, ui->coinAmountLabel_4, ui->coinsLabel, ui->timeLabel_4, breedingTimer4, penaltyTimer4);
}


void GamePage::on_productBTN_4_clicked()
{
    manageProducts(ui->productBTN_4, ui->coinLabel_4, ui->coinAmountLabel_4, ui->coinsLabel, ui->timeLabel_4, penaltyTimer4);
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm5btn_clicked()
{
    managingFarm(ui->Farm5btn, ui->productBTN_5, ui->coinLabel_5, ui->coinAmountLabel_5, ui->coinsLabel, ui->timeLabel_5, breedingTimer5, penaltyTimer5);
}


void GamePage::on_productBTN_5_clicked()
{
    manageProducts(ui->productBTN_5, ui->coinLabel_5, ui->coinAmountLabel_5, ui->coinsLabel, ui->timeLabel_5, penaltyTimer5);
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm6btn_clicked()
{
    managingFarm(ui->Farm6btn, ui->productBTN_6, ui->coinLabel_6, ui->coinAmountLabel_6, ui->coinsLabel, ui->timeLabel_6, breedingTimer6, penaltyTimer6);
}


void GamePage::on_productBTN_6_clicked()
{
    manageProducts(ui->productBTN_6, ui->coinLabel_6, ui->coinAmountLabel_6, ui->coinsLabel, ui->timeLabel_6, penaltyTimer6);
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm7btn_clicked()
{
    managingFarm(ui->Farm7btn, ui->productBTN_7, ui->coinLabel_7, ui->coinAmountLabel_7, ui->coinsLabel, ui->timeLabel_7, breedingTimer7, penaltyTimer7);
}

void GamePage::on_productBTN_7_clicked()
{
    manageProducts(ui->productBTN_7, ui->coinLabel_7, ui->coinAmountLabel_7, ui->coinsLabel, ui->timeLabel_7, penaltyTimer7);
}

//---------------------------------------------------------------------------------------------------------------------

void GamePage::on_Farm8btn_clicked()
{
    managingFarm(ui->Farm8btn, ui->productBTN_8, ui->coinLabel_8, ui->coinAmountLabel_8, ui->coinsLabel, ui->timeLabel_8, breedingTimer8, penaltyTimer8);
}

void GamePage::on_productBTN_8_clicked()
{
    manageProducts(ui->productBTN_8, ui->coinLabel_8, ui->coinAmountLabel_8, ui->coinsLabel, ui->timeLabel_8, penaltyTimer8);
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

void GamePage::managingFarm(QPushButton* farm, QPushButton* product, QLabel* coinLogo, QLabel* coinAmount, QLabel* totalCoins, QLabel* time, QTimer* breedTime, QTimer* penaltyTime)
{
    hen* Hen = new hen;
    sheep* Sheep = new sheep;
    cow* Cow = new cow;
    wheat* Wheat = new wheat;
    barlay* Barlay = new barlay;


    if(farm->styleSheet() == "background-color: rgb(157, 157, 157);")
    {
        coins = totalCoins->text().toInt();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Oh!, You don't have this farm",
                                      "Are you really sure you want to purchase this Farm?\nfarm price = 3 coins", QMessageBox::Yes | QMessageBox::No);
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
                totalCoins->setText(QString::number(coins));
                farm->setStyleSheet("background-color: rgb(0, 170, 0);");
                farm->setIcon(QIcon(""));
            }
            return;
        }
    }


    else if (farm->styleSheet() == "background-color: rgb(0, 170, 0);" &&
            time->styleSheet() == "background-color: rgb(255, 255, 255);"
            && product->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //rgb(255, 255, 255) means that this farm has no animals or plants.

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

        switch (result)
        {
        case 0:
            coins = totalCoins->text().toInt();
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "Hen",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Hen->getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You dont have enough coin!");
                    return;
                }

                coins -= Hen->getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    totalCoins->setText(QString::number(coins));
                    time->setStyleSheet("background-color: rgb(255, 255, 254);");
                    //rgb(255, 255, 254) means that this farm has hen.
                    farm->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                }
            }
            break;

        case 1:
            coins = totalCoins->text().toInt();
            reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Sheep->getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }

                coins -= Sheep->getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    totalCoins->setText(QString::number(coins));
                    time->setStyleSheet("background-color: rgb(255, 255, 253);");
                    //rgb(255, 255, 253) means that this farm has sheep
                    farm->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                }
            }
            break;

        case 2:
            coins = totalCoins->text().toInt();
            reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Cow->getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Cow->getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    totalCoins->setText(QString::number(coins));
                    time->setStyleSheet("background-color: rgb(255, 255, 252);");
                    //rgb(255, 255, 252) means that this farm has cow.
                    farm->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                }
            }
            break;

        case 3:
            coins = totalCoins->text().toInt();
            reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Wheat->getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Wheat->getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    totalCoins->setText(QString::number(coins));
                    time->setStyleSheet("background-color: rgb(255, 255, 251);");
                    //rgb(255, 255, 251) means that this farm has wheat.
                    farm->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                }
            }
            break;

        case 4:
            coins = totalCoins->text().toInt();
            reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < Barlay->getBuyPrice())
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= Barlay->getBuyPrice();
                if(updateCoinAmount(username, coins))
                {
                    totalCoins->setText(QString::number(coins));
                    time->setStyleSheet("background-color: rgb(255, 255, 250);");
                    farm->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
                }
            }
            break;

        case 5:
            return;

        }
    }

    else if (farm->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             time->styleSheet() == "background-color: rgb(255, 255, 254);"
             && product->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has hen

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
            coins += Hen->getMeatPrice();
            if(updateCoinAmount(username, coins))
            {
                totalCoins->setText(QString::number(coins));
                farm->setIcon(QIcon(""));
                product->setIcon(QIcon(""));
                time->setStyleSheet("background-color: rgb(255, 255, 255);");
                availableWorkers++;
                SetWorkerNumber();
            }
            break;


        case 1:
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
                    time->setText(QString::number(Hen->getBreedingTime()));
                    Hen->decreaseBreedingTime();

                    if (Hen->getBreedingTime() < 0)
                    {
                        breedTime->stop();
                        delete breedTime;
                        breedTime = nullptr;
                        farm->setEnabled(true);
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

                            time->setText(QString::number(Hen->getPenaltyTime()));

                            Hen->decreasePenaltyTime();
                            if (Hen->getPenaltyTime() < 0)
                            {
                                penaltyTime->stop();

                                Hen->decreaseEggPrice();
                                coinAmount->setText(QString::number(Hen->getEggPrice()));
                                Hen->resetPenaltyTime();
                                penaltyTime->start(1000);
                            }
                        });

                        penaltyTime->start(1000);
                    }
                });

                breedTime->start(1000);
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

    else if (farm->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             time->styleSheet() == "background-color: rgb(255, 255, 253);"
             && product->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has sheep


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
            coins += Sheep->getMeatPrice();
            if(updateCoinAmount(username, coins))
            {
                totalCoins->setText(QString::number(coins));
                farm->setIcon(QIcon(""));
                time->setStyleSheet("background-color: rgb(255, 255, 255);");
                availableWorkers++;
                SetWorkerNumber();
            }
            break;

        case 1:
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
                    time->setText(QString::number(Sheep->getBreedingTime()));
                    Sheep->decreaseBreedingTime();

                    if (Sheep->getBreedingTime() < 0)
                    {
                        breedTime->stop();

                        delete breedTime;
                        breedTime = nullptr;

                        farm->setEnabled(true);

                        product->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\milk.png"));
                        product->setStyleSheet("background-color: rgb(255, 255, 254);");

                        time->clear();

                        QPixmap coinsPix ("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

                        coinLogo->setPixmap(coinsPix);
                        coinAmount->setText(QString::number(Sheep->getMilkPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTime = new QTimer(this);
                        connect(penaltyTime, &QTimer::timeout, [=]() mutable{

                            time->setText(QString::number(Sheep->getPenaltyTime()));

                            Sheep->decreasePenaltyTime();
                            if (Sheep->getPenaltyTime() < 0)
                            {
                                penaltyTime->stop();
                               // penaltyTime->deleteLater();

                                Sheep->decreaseMilkPrice();
                                coinAmount->setText(QString::number(Sheep->getMilkPrice()));
                                Sheep->resetPenaltyTime();
                                penaltyTime->start(1000);

                            }
                        } );
                        penaltyTime->start(1000);


                    }
                });

                breedTime->start(1000);
                break;
            }

            else
            {
                QMessageBox::warning(this, "", "You don't have a worker available.");
                return;
            }
        }
    }

    else if (farm->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             time->styleSheet() == "background-color: rgb(255, 255, 252);"
             && product->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has cow


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

            coins += Cow->getMeatPrice();
            if(updateCoinAmount(username, coins))
            {
                totalCoins->setText(QString::number(coins));
                farm->setIcon(QIcon(""));
                time->setStyleSheet("background-color: rgb(255, 255, 255);");
                availableWorkers++;
                SetWorkerNumber();
            }
            break;

        case 1:
            if (availableWorkers != 0)
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
                    time->setText(QString::number(Cow->getBreedingTime()));
                    Cow->decreaseBreedingTime();

                    if (Cow->getBreedingTime() < 0)
                    {
                        breedTime->stop();

                        delete breedTime;
                        breedTime = nullptr;

                        farm->setEnabled(true);

                        product->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\milk.png"));
                        product->setStyleSheet("background-color: rgb(255, 255, 254);");

                        time->clear();

                        QPixmap coinsPix ("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

                        coinLogo->setPixmap(coinsPix);
                        coinAmount->setText(QString::number(Cow->getMilkPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTime = new QTimer(this);
                        connect(penaltyTime, &QTimer::timeout, [=]() mutable{

                            time->setText(QString::number(Cow->getPenaltyTime()));

                            Cow->decreasePenaltyTime();
                            if (Cow->getPenaltyTime() < 0)
                            {
                                penaltyTime->stop();
                               // penaltyTime->deleteLater();

                                Cow->decreaseMilkPrice();
                                coinAmount->setText(QString::number(Cow->getMilkPrice()));
                                Cow->resetPenaltyTime();
                                penaltyTime->start(1000);

                            }
                        } );
                        penaltyTime->start(1000);

                    }
                });

                breedTime->start(1000);
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


    else if (farm->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             time->styleSheet() == "background-color: rgb(255, 255, 251);"
             && product->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has wheat
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

            if (availableWorkers != 0)
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
                    time->setText(QString::number(Wheat->getBreedingTime()));
                    Wheat->decreaseBreedingTime();

                    if (Wheat->getBreedingTime() < 0)
                    {
                        breedTime->stop();

                        delete breedTime;
                        breedTime = nullptr;

                        farm->setEnabled(true);

                        product->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                        product->setStyleSheet("background-color: rgb(255, 255, 254);");

                        time->clear();

                        QPixmap coinsPix ("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

                        coinLogo->setPixmap(coinsPix);
                        coinAmount->setText(QString::number(Wheat->getWheatPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTime = new QTimer(this);
                        connect(penaltyTime, &QTimer::timeout, [=]() mutable{

                            time->setText(QString::number(Wheat->getPenaltyTime()));

                            Wheat->decreasePenaltyTime();
                            if (Wheat->getPenaltyTime() < 0)
                            {
                                penaltyTime->stop();
                                penaltyTime->deleteLater();

                                Wheat->decreaseWheatPrice();
                                coinAmount->setText(QString::number(Wheat->getWheatPrice()));
                                Wheat->resetPenaltyTime();
                                penaltyTime->start(1000);

                            }
                        } );
                        penaltyTime->start(1000);

                    }
                });

                breedTime->start(1000);
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


    else if (farm->styleSheet() == "background-color: rgb(0, 170, 0);" &&
             time->styleSheet() == "background-color: rgb(255, 255, 250);"
             && product->styleSheet() == "background-color: rgb(255, 255, 255);")
    {
        //this farm has barlay
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

            if (availableWorkers != 0)
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
                    time->setText(QString::number(Barlay->getBreedingTime()));
                    Barlay->decreaseBreedingTime();

                    if (Barlay->getBreedingTime() < 0)
                    {
                        breedTime->stop();

                        delete breedTime;
                        breedTime = nullptr;

                        farm->setEnabled(true);

                        product->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\barlay.png"));
                        product->setStyleSheet("background-color: rgb(255, 255, 254);");

                        time->clear();

                        QPixmap coinsPix ("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

                        coinLogo->setPixmap(coinsPix);
                        coinAmount->setText(QString::number(Barlay->getBarlayPrice()));

                        availableWorkers++;
                        SetWorkerNumber();

                        penaltyTime = new QTimer(this);
                        connect(penaltyTime, &QTimer::timeout, [=]() mutable{

                            time->setText(QString::number(Barlay->getPenaltyTime()));

                            Barlay->decreasePenaltyTime();
                            if (Barlay->getPenaltyTime() < 0)
                            {
                                penaltyTime->stop();
                          //      penaltyTime->deleteLater();

                                Barlay->decreaseBarlayPrice();
                                coinAmount->setText(QString::number(Barlay->getBarlayPrice()));
                                Barlay->resetPenaltyTime();
                                penaltyTime->start(1000);

                            }
                        } );
                        penaltyTime->start(1000);

                    }
                });

                breedTime->start(1000);
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

void GamePage::manageProducts(QPushButton *product, QLabel *coinLogo, QLabel *coinAmount, QLabel *totalCoins, QLabel *time, QTimer* penaltyTime)
{
    if (product->styleSheet() == "background-color: rgb(255, 255, 254);")
        {

            if (availableWorkers != 0)
            {
            coins += coinAmount->text().toInt();
            penaltyTime->stop();
            delete penaltyTime;
            penaltyTime = nullptr;

            if (updateCoinAmount(username, coins))
            {

                totalCoins->setText(QString::number(coins));
                product->setIcon(QIcon(""));
                coinAmount->clear();
                coinLogo->clear();
                time->clear();

                product->setStyleSheet("background-color: rgb(255, 255, 255);");
            }
           }
        }
}



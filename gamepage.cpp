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
   }else{
       QMessageBox::information(this, "Game finished!", "All users completed the game!");
       RankingPage *R = new RankingPage;
       R->show();
   }
}
void GamePage::updateTime()
{
           if (remainingSeconds >= 0)
              {
                QString formattedTime = QString("%1:%2").arg(remainingSeconds / 60, 2, 10, QChar('0'))
                  .arg(remainingSeconds % 60, 2, 10, QChar('0'));

                ui->timerLabel->setText(formattedTime);
                remainingSeconds--;
                QTimer::singleShot(1000, this, &GamePage::updateTime);
           }else
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GamePage::on_Farm1btn_clicked()
{
    if (ui->Farm1btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
            ui->label1->styleSheet() == "background-color: rgb(255, 255, 255);"
            && ui->prodLabel1->text().isEmpty()
            )
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

        switch (result) {
         case 0 :
             coins = ui->coinsLabel->text().toInt();
             QMessageBox::StandardButton reply;
             reply = QMessageBox::question(nullptr, "Chicken",
                                      "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
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
                 ui->label1->setStyleSheet("background-color: rgb(255, 255, 254);");
                 ui->Farm1btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                 }
             }
            break;
         case 1 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Sheep",
                                     "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < 5)
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= 5;
                if(updateCoinAmount(username, coins))
                {
                ui->coinsLabel->setText(QString::number(coins));
                ui->label1->setStyleSheet("background-color: rgb(255, 255, 253);");
                ui->Farm1btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
           }
                }
            break;
         case 2 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Cow",
                                     "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < 7)
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= 7;
                if(updateCoinAmount(username, coins))
                {
                ui->coinsLabel->setText(QString::number(coins));
                ui->label1->setStyleSheet("background-color: rgb(255, 255, 252);");

                ui->Farm1btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
            }
            break;
         case 3 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Wheat",
                                     "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < 2)
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= 2;
                if(updateCoinAmount(username, coins))
                {
                ui->coinsLabel->setText(QString::number(coins));
                ui->label1->setStyleSheet("background-color: rgb(255, 255, 251);");
                ui->Farm1btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
            }
            break;
         case 4 :
            coins = ui->coinsLabel->text().toInt();
            reply = QMessageBox::question(nullptr, "Barley",
                                     "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)
            {
                if(coins < 2)
                {
                    QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                    return;
                }
                coins -= 2;
                if(updateCoinAmount(username, coins))
                {
                ui->coinsLabel->setText(QString::number(coins));
                ui->label1->setStyleSheet("background-color: rgb(255, 255, 250);");

               ui->Farm1btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\barley.png"));
           }
                }
            break;
        case 5:
            return;
        }
    }
}
}
}
void GamePage::on_Farm2btn_clicked()
{
     if(ui->Farm2btn->styleSheet() == "background-color: rgb(157, 157, 157);")
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
             ui->Farm2btn->setStyleSheet("background-color: rgb(0, 170, 0);");
             ui->Farm2btn->setIcon(QIcon(""));
             }
             return;
         }
      }
    else if (ui->Farm2btn->styleSheet() == "background-color: rgb(0, 170, 0);" &&
                 ui->label2->styleSheet() == "background-color: rgb(255, 255, 255);"
                 && ui->prodLabel2->text().isEmpty()
                 )
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

             switch (result) {
              case 0 :
                  coins = ui->coinsLabel->text().toInt();
                  QMessageBox::StandardButton reply;
                  reply = QMessageBox::question(nullptr, "Chicken",
                                           "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
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
                      ui->label2->setStyleSheet("background-color: rgb(255, 255, 254);");
                      ui->Farm2btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                 }
                      }
                 break;
              case 1 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 5)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     if(updateCoinAmount(username, coins))
                     {
                     coins -= 5;
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label2->setStyleSheet("background-color: rgb(255, 255, 253);");
                     ui->Farm2btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
               }
                     }
                 break;
              case 2 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 7)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 7;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label2->setStyleSheet("background-color: rgb(255, 255, 252);");
                     ui->Farm2btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
               }
                     }
                 break;
              case 3 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label2->setStyleSheet("background-color: rgb(255, 255, 251);");
                     ui->Farm2btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                 }
                     }
                 break;
              case 4 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label2->setStyleSheet("background-color: rgb(255, 255, 250);");
                     ui->Farm2btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\barley.png"));
               }
                     }
                 break;
             case 5:
                 return;
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
                 ui->label3->styleSheet() == "background-color: rgb(255, 255, 255);"
                 && ui->prodLabel3->text().isEmpty()
                 )
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

             switch (result) {
              case 0 :
                  coins = ui->coinsLabel->text().toInt();
                  QMessageBox::StandardButton reply;
                  reply = QMessageBox::question(nullptr, "Chicken",
                                           "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
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
                      ui->label3->setStyleSheet("background-color: rgb(255, 255, 254);");
                      ui->Farm3btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                  }
                  }
                 break;
              case 1 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 5)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 5;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label3->setStyleSheet("background-color: rgb(255, 255, 253);");
                     ui->Farm3btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                 }
                 }
                 break;
              case 2 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 7)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 7;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label3->setStyleSheet("background-color: rgb(255, 255, 252);");
                     ui->Farm3btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                 }
                 }
                 break;
              case 3 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {

                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label3->setStyleSheet("background-color: rgb(255, 255, 251);");
                     ui->Farm3btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                 }
                 }
                 break;
              case 4 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label3->setStyleSheet("background-color: rgb(255, 255, 250);");
                     ui->Farm3btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\barley.png"));
                 }
                 }
                 break;
             case 5:
                 return;
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
                 ui->label4->styleSheet() == "background-color: rgb(255, 255, 255);"
                 && ui->prodLabel4->text().isEmpty()
                 )
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

             switch (result) {
              case 0 :
                  coins = ui->coinsLabel->text().toInt();
                  QMessageBox::StandardButton reply;
                  reply = QMessageBox::question(nullptr, "Chicken",
                                           "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
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
                      ui->label4->setStyleSheet("background-color: rgb(255, 255, 254);");
                      ui->Farm4btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                  }
                  }
                 break;
              case 1 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 5)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 5;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label4->setStyleSheet("background-color: rgb(255, 255, 253);");
                     ui->Farm4btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                 }
                 }
                 break;
              case 2 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 7)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 7;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label4->setStyleSheet("background-color: rgb(255, 255, 252);");
                     ui->Farm4btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                 }
                 }
                 break;
              case 3 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label4->setStyleSheet("background-color: rgb(255, 255, 251);");
                     ui->Farm4btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                 }
                 }
                 break;
              case 4 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label4->setStyleSheet("background-color: rgb(255, 255, 250);");
                     ui->Farm4btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\barley.png"));
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
                 ui->label5->styleSheet() == "background-color: rgb(255, 255, 255);"
                 && ui->prodLabel5->text().isEmpty()
                 )
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

             switch (result) {
              case 0 :
                  coins = ui->coinsLabel->text().toInt();
                  QMessageBox::StandardButton reply;
                  reply = QMessageBox::question(nullptr, "Chicken",
                                           "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
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
                      ui->label5->setStyleSheet("background-color: rgb(255, 255, 254);");
                      ui->Farm5btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                  }
                  }
                 break;
              case 1 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 5)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 5;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label5->setStyleSheet("background-color: rgb(255, 255, 253);");
                     ui->Farm5btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                 }
                 }
                 break;
              case 2 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 7)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 7;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label5->setStyleSheet("background-color: rgb(255, 255, 252);");
                     ui->Farm5btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                 }
                 }
                 break;
              case 3 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label5->setStyleSheet("background-color: rgb(255, 255, 251);");
                     ui->Farm5btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                 }
                 }
                 break;
              case 4 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label5->setStyleSheet("background-color: rgb(255, 255, 250);");
                     ui->Farm5btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\barley.png"));
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
                 ui->label6->styleSheet() == "background-color: rgb(255, 255, 255);"
                 && ui->prodLabel6->text().isEmpty()
                 )
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

             switch (result) {
              case 0 :
                  coins = ui->coinsLabel->text().toInt();
                  QMessageBox::StandardButton reply;
                  reply = QMessageBox::question(nullptr, "Chicken",
                                           "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
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
                      ui->label6->setStyleSheet("background-color: rgb(255, 255, 254);");
                      ui->Farm6btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                  }
                  }
                 break;
              case 1 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 5)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 5;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label6->setStyleSheet("background-color: rgb(255, 255, 253);");
                     ui->Farm6btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                 }
                 break;
              case 2 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 7)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 7;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label6->setStyleSheet("background-color: rgb(255, 255, 252);");
                     ui->Farm6btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                 }
                 }
                 break;
              case 3 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label6->setStyleSheet("background-color: rgb(255, 255, 251);");
                     ui->Farm6btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                 }
                 }
                 break;
              case 4 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label6->setStyleSheet("background-color: rgb(255, 255, 250);");
                     ui->Farm6btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\barley.png"));
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
                 ui->label7->styleSheet() == "background-color: rgb(255, 255, 255);"
                 && ui->prodLabel7->text().isEmpty()
                 )
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

             switch (result) {
              case 0 :
                  coins = ui->coinsLabel->text().toInt();
                  QMessageBox::StandardButton reply;
                  reply = QMessageBox::question(nullptr, "Chicken",
                                           "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
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
                      ui->label7->setStyleSheet("background-color: rgb(255, 255, 254);");
                      ui->Farm7btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                  }
                  }
                 break;
              case 1 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 5)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 5;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label7->setStyleSheet("background-color: rgb(255, 255, 253);");
                     ui->Farm7btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                 }
                 }
                 break;
              case 2 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 7)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 7;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label7->setStyleSheet("background-color: rgb(255, 255, 252);");
                     ui->Farm7btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                 }
                 }
                 break;
              case 3 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label7->setStyleSheet("background-color: rgb(255, 255, 251);");
                     ui->Farm7btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                 }
                 }
                 break;
              case 4 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label7->setStyleSheet("background-color: rgb(255, 255, 250);");
                     ui->Farm7btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\barley.png"));
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
                 ui->label8->styleSheet() == "background-color: rgb(255, 255, 255);"
                 && ui->prodLabel8->text().isEmpty()
                 )
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

             switch (result) {
              case 0 :
                  coins = ui->coinsLabel->text().toInt();
                  QMessageBox::StandardButton reply;
                  reply = QMessageBox::question(nullptr, "Chicken",
                                           "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
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
                      ui->label8->setStyleSheet("background-color: rgb(255, 255, 254);");
                      ui->Farm8btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\hen.png"));
                  }
                  }
                 break;
              case 1 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Sheep",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 5)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 5;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label8->setStyleSheet("background-color: rgb(255, 255, 253);");
                     ui->Farm8btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\sheep.png"));
                 }
                 }
                 break;
              case 2 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Cow",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 7)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 7;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label8->setStyleSheet("background-color: rgb(255, 255, 252);");
                     ui->Farm8btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\cow.png"));
                 }
                 }
                 break;
              case 3 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Wheat",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label8->setStyleSheet("background-color: rgb(255, 255, 251);");
                     ui->Farm8btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\wheat.png"));
                 }
                 }
                 break;
              case 4 :
                 coins = ui->coinsLabel->text().toInt();
                 reply = QMessageBox::question(nullptr, "Barley",
                                          "Are you really sure you want to purchase this?", QMessageBox::Yes | QMessageBox::No);
                 if (reply == QMessageBox::Yes)
                 {
                     if(coins < 2)
                     {
                         QMessageBox::warning(this, "Sorry!", "You do not have enough coin!");
                         return;
                     }
                     coins -= 2;
                     if(updateCoinAmount(username, coins))
                     {
                     ui->coinsLabel->setText(QString::number(coins));
                     ui->label8->setStyleSheet("background-color: rgb(255, 255, 250);");
                     ui->Farm8btn->setIcon(QIcon("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\barley.png"));
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
    }else
    {
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

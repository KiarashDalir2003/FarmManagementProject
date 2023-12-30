#include "gamepage.h"
#include "ui_gamepage.h"

#include<QTime>
#include<QTimer>

#include<QtMath>

#include <QDebug>
#include <QMessageBox>

#include <rankingpage.h>

GamePage::GamePage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GamePage)
{
    ui->setupUi(this);
    QPixmap worker("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\worker.png");
    QPixmap clock("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\clock.png");
    QPixmap coin ("C:\\Users\\Microsoft\\Documents\\GitHub\\FarmManegementProject\\images\\coin.png");

    ui->worketIconLabel->setPixmap(worker);
    ui->clockIconLabel->setPixmap(clock);
    ui->coinIconLabel->setPixmap(coin);

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

   QString labelTextWorkers = QString("%1/%2").arg(availableWorkers).arg(totalWorkers);
   ui->workerLabel->setText(labelTextWorkers);
   /* q.prepare("SELECT username, coins FROM coins");
    if (!q.exec())
    {
        qDebug() << "Query execution failed!";
    }
*/
}
void GamePage::processNextRecord()
{
   if (q.next())
   {
           QString username = q.value(0).toString();
           int coinAmount = q.value(1).toInt();

           ui->usernameLabel->setText(username);
           ui->coinsLabel->setText(QString::number(coinAmount));

           remainingSeconds = 10;
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
void GamePage::on_Farm1btn_clicked()
{
    QString background = this->styleSheet();
    QString icon = this->property("iconSource").toString();
    QString labelText = ui->label1->text();

}
void GamePage::on_Farm2btn_clicked()
{

}


void GamePage::on_Farm3btn_clicked()
{

}


void GamePage::on_Farm7btn_clicked()
{

}


void GamePage::on_Farm6btn_clicked()
{

}


void GamePage::on_Farm5btn_clicked()
{

}


void GamePage::on_Farm4btn_clicked()
{

}


void GamePage::on_Farm8btn_clicked()
{

}


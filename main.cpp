#include "loginpage.h"
#include "gamepage.h"

#include <QApplication>

#include <QMediaPlayer>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginPage w;
    GamePage G;

    QMediaPlayer *StartSound = new QMediaPlayer;

    StartSound->setMedia(
             QUrl::fromLocalFile("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\sounds\\StartSound.mp3"));


    QSqlQuery que;
    que.exec("SELECT COUNT(*) FROM principle");
    if(que.next())
    {
        int recordCount = que.value(0).toInt();

        if (recordCount == 0)
        {
            w.show();
        }
        else
        {
            G.show();
        }
    }

    else
    {
        qDebug() << "Error executing query.";
    }

    return a.exec();
}

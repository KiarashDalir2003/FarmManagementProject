#include "loginpage.h"
#include "gamepage.h"

#include <QApplication>
#include <QSettings>

#include <QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginPage w;
    GamePage G;

    QMediaPlayer *StartSound = new QMediaPlayer;

    StartSound->setMedia(
                QUrl::fromLocalFile("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject"
                                    "\\sounds\\StartSound.mp3"));


    QSettings settings("MyApp", "MyAppSettings");

    settings.setValue("firstRun", true);

    if (settings.value("firstRun", true).toBool())
    {
        w.show();
        StartSound->play();
        settings.setValue("firstRun", false);
    }
    else
    {
        G.show();
    }

    return a.exec();
}

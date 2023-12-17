#include "loginpage.h"
#include "ui_loginpage.h"

#include "gamepage.h"
#include "ui_gamepage.h"

#include "captcha.h"

#include <QSqlDatabase>
#include <QSqlDriver>
#include<QSqlQuery>

#include <QMessageBox>

#include <QRandomGenerator>
#include <QPainter>
#include <QImage>

#include <QMediaPlayer>

LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    ui->LoginPageGroupBox->hide();
    ui->countryCodeLBL->hide();


    ui->EyeBtn->setIcon(QIcon("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\eye-close.png"));
    ui->PasswordLineEdit->setEchoMode(QLineEdit::Password);
    ui->RefreshBtn->setIcon(QIcon("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\refresh.png"));

    QMediaPlayer *NagativeSound = new QMediaPlayer;
    NagativeSound->setMedia(
                QUrl::fromLocalFile("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\sounds\\NegativeSound.mp3"));



    QSqlDatabase mydatabase;
    mydatabase = QSqlDatabase :: addDatabase("QSQLITE");
    mydatabase.setDatabaseName("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\ProjectDatebase.db");
    mydatabase.open();
    if (!mydatabase.open())
    {
        NagativeSound->play();
        QMessageBox::warning(this, "Error", "Can not cennect to the database");
    }


    const QPixmap Afghanistan("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\CountryFlags\\afghanistan.png");
    const QPixmap Brazil("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\CountryFlags\\brazil.png");
    const QPixmap Canada("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\CountryFlags\\canada.png");
    const QPixmap China("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\CountryFlags\\china.png");
    const QPixmap Germany("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\CountryFlags\\germany.png");
    const QPixmap Iran("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\CountryFlags\\iran.png");
    const QPixmap Iraq("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\CountryFlags\\iraq.png");
    const QPixmap Spain("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\CountryFlags\\spain.png");
    const QPixmap Russia("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\CountryFlags\\russia.png");
    const QPixmap UnitedStates("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\CountryFlags\\united_states.png");

    QStringList countries = {"choose country", "Afghanistan", "Brazil", "Canada", "China", "Germany", "Iran", "Iraq", "Russia", "Spain", "United States"};
    ui->CountryComboBox->addItems(countries);

    ui->CountryComboBox->setItemIcon(1,QIcon(Afghanistan));
    ui->CountryComboBox->setItemIcon(2,QIcon(Brazil));
    ui->CountryComboBox->setItemIcon(3,QIcon(Canada));
    ui->CountryComboBox->setItemIcon(4,QIcon(China));
    ui->CountryComboBox->setItemIcon(5,QIcon(Germany));
    ui->CountryComboBox->setItemIcon(6,QIcon(Iran));
    ui->CountryComboBox->setItemIcon(7,QIcon(Iraq));
    ui->CountryComboBox->setItemIcon(8,QIcon(Russia));
    ui->CountryComboBox->setItemIcon(9,QIcon(Spain));
    ui->CountryComboBox->setItemIcon(10,QIcon(UnitedStates));
}

LoginPage::~LoginPage()
{
    delete ui;
}


void LoginPage::on_EyeBtn_clicked()
{
    if (ui->PasswordLineEdit->echoMode() == QLineEdit::Password)
    {
        ui->EyeBtn->setIcon(QIcon("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\eye.png"));
        ui->PasswordLineEdit->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->EyeBtn->setIcon(QIcon("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\images\\eye-close.png"));
        ui->PasswordLineEdit->setEchoMode(QLineEdit::Password);
    }
}



void LoginPage::on_ContinueBtn_clicked()
{
     QString username, password, email, phoneNumber, moneyAmount, captchatext;
     QMediaPlayer *NagativeSound = new QMediaPlayer;
     NagativeSound->setMedia(
                 QUrl::fromLocalFile("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\sounds\\NegativeSound.mp3"));

     QMediaPlayer *PositiveSound = new QMediaPlayer;
     PositiveSound->setMedia(
                 QUrl::fromLocalFile("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\sounds\\PositiveSound.mp3"));

     QMediaPlayer *CompletedSound = new QMediaPlayer;
     CompletedSound->setMedia(
                 QUrl::fromLocalFile("C:\\Users\\Microsoft\\Desktop\\FarmManegementProject\\sounds\\CompletedSound.mp3"));

     username = ui->UsernameLineEdit->text();
     password = ui->PasswordLineEdit->text();
     email = ui->EmailLineEdit->text();
     phoneNumber = ui->PhoneNumberLineEdit->text();
     moneyAmount = ui->MoneyLineEdit->text();
     captchatext = ui->captchaLineEdit->text();


     if (username.isEmpty() && password.isEmpty() && email.isEmpty() &&
             phoneNumber.isEmpty() && moneyAmount.isEmpty() && captchatext.isEmpty())
     {
         NagativeSound->play();
         QMessageBox::warning(this, "Error", "Please complete all informations.");
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
         return;
     }

     //this  is for checking password
          QRegularExpression regex("^(?=.*[0-9])(?=.*[a-zA-Z])[a-zA-Z0-9]{8,}$");
          QRegularExpressionMatch match = regex.match(password);
     if (password.isEmpty())
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();

         NagativeSound->play();

         QMessageBox::warning(this, "Error", "Please enter the password");
         return;
     }

     if (!match.hasMatch())
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();

         NagativeSound->play();

         QMessageBox::warning(this, "Error", "The password must contain only alphabets and digits and at least 8 characters.");
         return;
     }

     QRegularExpression pattern("^[a-zA-Z0-9._-]+@(gmail\\.com|email\\.com|mail\\.um\\.ac)$");
     QRegularExpressionMatch EmailMatch = pattern.match(email);

     if (email.isEmpty())
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();

         NagativeSound->play();
         QMessageBox::warning(this, "Error", "Please enter the email.");
     }
     if (!EmailMatch.hasMatch())
     {
             on_RefreshBtn_clicked();
             ui->captchaLineEdit->clear();

             NagativeSound->play();
             QMessageBox::warning(this, "Error", "Incorrect email!");
             return;
     }

     QRegularExpression NumberRegex("\\d+");
     QRegularExpressionMatch CheckNumber = NumberRegex.match(phoneNumber);

     if (!CheckNumber.hasMatch())
     {

         NagativeSound->play();
         QMessageBox::warning(this, "Error", "Wrong phone number!");

         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();

         return;
     }
     if (captchatext != captchaCode)
     {

         NagativeSound->play();
         QMessageBox::warning(this, "Error", "Wrong captcha code!");

         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
     }

     QString tempPhone;
     tempPhone = ui->countryCodeLBL->text() + ui->PhoneNumberLineEdit->text();

     QSqlQuery q; 
     q.prepare("SELECT username FROM account WHERE username=:username");
     q.bindValue(":username", username);
     q.exec();

     if (q.first())
     {
         NagativeSound->play();
         QMessageBox::warning(this, "Error", "This account has already existed.");

         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
     }
     else
     {
         q.prepare("INSERT INTO Principle(username, password, email, phone, moneyAmount) "
                   "VALUES(:username, :password, :email, :phone, :moneyAmount)");

         q.bindValue(":username",username);
         q.bindValue(":password",password);
         q.bindValue(":email",email);
         q.bindValue(":phone",tempPhone);
         q.bindValue(":moneyAmount", moneyAmount);

         q.exec();
         QMessageBox::information(this,"Welcome", "The manager has signed up successfully.");
         PositiveSound->play();

         ui->UsernameLineEdit->clear();
         ui->PasswordLineEdit->clear();
         ui->EmailLineEdit->clear();
         ui->PhoneNumberLineEdit->clear();
         ui->MoneyLineEdit->clear();

         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();

         count++;
     }

     if (count == numManager)
     {
         GamePage *G = new GamePage;
       //  CompletedSound->play();
         QMessageBox::information(this, "Completed!", "Adding managers completed!");

         G->show();
         this->close();

         return;
     }
}

void LoginPage::on_ConfirmBtn_clicked()
{

    numManager = ui->NumberOfMaganersSpinBox->value();
    if(numManager != 0)
    {
        ui->LoginPageGroupBox->show();
        ui->label->hide();
        ui->NumberOfMaganersSpinBox->hide();
        ui->ConfirmBtn->hide();
    }
    on_RefreshBtn_clicked();
}

QString LoginPage::generateRandomTxt(int len)
{
    QString randomTxt;
    for (int i = 0; i < len; i++)
        {
            int index = QRandomGenerator::global()->bounded(dictionary.length());
            randomTxt.append(dictionary.at(index));
        }
    return randomTxt;
}

QPixmap LoginPage::generateCaptchaImg(const QString &text)
{
    QPixmap pixmap(150, 50);
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    QFont font("Arial", 16);
    painter.setFont(font);
    painter.drawText(pixmap.rect(), Qt::AlignCenter, text);

    return pixmap;
}

void LoginPage::on_RefreshBtn_clicked()
{
    Captcha cp;
    cp.randomize();
    cp.setDifficulty(1);
    cp.generateText(4, true, false, true);
    captchaCode = cp.captchaText();
    ui->showCaptcha->setPixmap(QPixmap::fromImage(cp.captchaImage()));
}

void LoginPage::on_CountryComboBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        ui->countryCodeLBL->hide();
        break;

    case 1:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        ui->countryCodeLBL->setText("+93");
        break;

    case 2:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        ui->countryCodeLBL->setText("+55");
        break;

    case 3:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        ui->countryCodeLBL->setText("+1");
        break;

    case 4:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        ui->countryCodeLBL->setText("+86");
        break;

    case 5:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        ui->countryCodeLBL->setText("+49");
        break;

    case 6:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        ui->countryCodeLBL->setText("+98");
        break;
    case 7:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        ui->countryCodeLBL->setText("+964");
        break;
    case 8:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        ui->countryCodeLBL->setText("+7095");
        break;
    case 9:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        ui->countryCodeLBL->setText("+34");
        break;
    case 10:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        ui->countryCodeLBL->setText("+1");
        break;
    }
}

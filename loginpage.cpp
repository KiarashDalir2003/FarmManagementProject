#include "loginpage.h"
#include "ui_loginpage.h"

#include "gamepage.h"
#include "ui_gamepage.h"

#include "captcha.h"

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>

#include <QMessageBox>

#include <QMediaPlayer>

QRegularExpression username_regex, email_regex, password_regex, phoneNum_regex, money_regex;
QRegularExpressionValidator username_regex_val, email_regex_val, password_regex_val, phoneNum_regex_val, money_regex_val;


LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    username_regex.setPattern("\\w+");  // The username can contain alphabets, digits and underline character
    email_regex.setPattern("^[a-zA-Z0-9._-]+@(gmail\\.com|email\\.com|mail\\.um\\.ac)$");
    password_regex.setPattern("^(?=.*[0-9])(?=.*[a-zA-Z])[a-zA-Z0-9]{8,}$");    // The password must contain at least one alphabets and digits character. length >= 8
    phoneNum_regex.setPattern("\\d+");  // just numbers is valid
    money_regex.setPattern("\\d+");     // just numbers is valid
    username_regex_val.setRegularExpression(username_regex);
    email_regex_val.setRegularExpression(email_regex);
    password_regex_val.setRegularExpression(password_regex);
    phoneNum_regex_val.setRegularExpression(phoneNum_regex);
    money_regex_val.setRegularExpression(money_regex);

    ui->setupUi(this);
    ui->LoginPageGroupBox->hide();

    ui->EyeBtn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\eye-close.png"));
    ui->PasswordLineEdit->setEchoMode(QLineEdit::Password);
    ui->RefreshBtn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\refresh.png"));

    QMediaPlayer *StartSound = new QMediaPlayer;
    StartSound->setMedia(
                QUrl::fromLocalFile("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\sounds\\StartSound.mp3"));


    QMediaPlayer *NagativeSound = new QMediaPlayer;
    NagativeSound->setMedia(
                QUrl::fromLocalFile("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));



    QSqlDatabase mydatabase;
    mydatabase = QSqlDatabase :: addDatabase("QSQLITE");
    mydatabase.setDatabaseName("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\ProjectDatabase.db");

    if (!mydatabase.open())
    {
        NagativeSound->play();
        QMessageBox::warning(this, "Error", "Can not connect to the database");
    }


    const QPixmap Afghanistan("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\CountryFlags\\afghanistan.png");
    const QPixmap Brazil("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\CountryFlags\\brazil.png");
    const QPixmap Canada("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\CountryFlags\\canada.png");
    const QPixmap China("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\CountryFlags\\china.png");
    const QPixmap Germany("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\CountryFlags\\germany.png");
    const QPixmap Iran("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\CountryFlags\\iran.png");
    const QPixmap Iraq("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\CountryFlags\\iraq.png");
    const QPixmap Spain("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\CountryFlags\\spain.png");
    const QPixmap Russia("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\CountryFlags\\russia.png");
    const QPixmap UnitedStates("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\CountryFlags\\united_states.png");

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
        ui->EyeBtn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\eye.png"));
        ui->PasswordLineEdit->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->EyeBtn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\eye-close.png"));
        ui->PasswordLineEdit->setEchoMode(QLineEdit::Password);
    }
}


void LoginPage::on_ContinueBtn_clicked()
{
     QString username, password, email, phoneNumber, moneyAmount, captchatext;
     QMediaPlayer *NagativeSound = new QMediaPlayer;
     NagativeSound->setMedia(
                 QUrl::fromLocalFile("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\sounds\\NegativeSound.mp3"));

     QMediaPlayer *PositiveSound = new QMediaPlayer;
     PositiveSound->setMedia(
                 QUrl::fromLocalFile("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\sounds\\PositiveSound.mp3"));

     QMediaPlayer *CompletedSound = new QMediaPlayer;
     CompletedSound->setMedia(
                 QUrl::fromLocalFile("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\sounds\\CompletedSound.mp3"));

     username    =  ui->UsernameLineEdit->text();
     password    =  ui->PasswordLineEdit->text();
     email       =  ui->EmailLineEdit->text();
     phoneNumber =  ui->PhoneNumberLineEdit->text();
     moneyAmount =  ui->MoneyLineEdit->text();
     captchatext =  ui->captchaLineEdit->text();


     if (username.isEmpty() && password.isEmpty() && email.isEmpty() &&
             phoneNumber.isEmpty() && moneyAmount.isEmpty() && captchatext.isEmpty())
     {
         NagativeSound->play();
         QMessageBox::warning(this, "Error", "Please complete all informations.");
         on_RefreshBtn_clicked();
         return;
     }


     //this is for checking username

     if (username.isEmpty())
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
         NagativeSound->play();

         QMessageBox::warning(this, "Error", "Please enter the username");
         return;
     }

     if(!isUsernameValid(ui->UsernameLineEdit))
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
         NagativeSound->play();

         QMessageBox::warning(this, "Error", "The username can contain alphabets, digits and underline character");
         return;
     }


     //this is for checking email

      if (email.isEmpty())
      {
          on_RefreshBtn_clicked();
          ui->captchaLineEdit->clear();

          NagativeSound->play();
          QMessageBox::warning(this, "Error", "Please enter the email.");
      }

      if(!isEmailValid(ui->EmailLineEdit))
      {
          on_RefreshBtn_clicked();
          ui->captchaLineEdit->clear();
          NagativeSound->play();

          QMessageBox::warning(this, "Error", "Incorrect Email.\nThe correct email format is given below:\n"
                                              "-----@gmail.com\n"
                                              "-----@email.com\n"
                                              "-----@mail.um.ac");
          return;
      }


     //this is for checking password

     if (password.isEmpty())
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
         NagativeSound->play();

         QMessageBox::warning(this, "Error", "Please enter the password");
         return;
     }

     if(!isPasswordValid(ui->PasswordLineEdit))
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
         NagativeSound->play();

         QMessageBox::warning(this, "Error", "The password must contain at least one alphabets and digits character.\nlen >= 8");
         return;
     }


     //this is for checking phone number

     if(ui->CountryComboBox->currentIndex() == 0)
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
         NagativeSound->play();

         QMessageBox::warning(this, "Error", "Please choose your country");
         return;
     }

     if (phoneNumber.isEmpty())
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
         NagativeSound->play();

         QMessageBox::warning(this, "Error", "Please enter the phone number");
         return;
     }

     if(!isPhoneNumValid(ui->PhoneNumberLineEdit))
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
         NagativeSound->play();

         QMessageBox::warning(this, "Error", "Wrong phone number!");
         return;
     }


     //this is for checking money amount

     if (moneyAmount.isEmpty())
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
         NagativeSound->play();

         QMessageBox::warning(this, "Error", "Please enter the money amount of manager");
         return;
     }

     if(!isMoneyAmountValid(ui->MoneyLineEdit))
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
         NagativeSound->play();

         QMessageBox::warning(this, "Error", "please enter a non-zero number for money amount of manager!");
         return;
     }


     //this is for checking captcha

     if (captchatext.isEmpty())
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
         NagativeSound->play();

         QMessageBox::warning(this, "Error", "Please enter the captcha code");
         return;
     }

     if (captchatext != captchaCode)
     {
         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
         NagativeSound->play();

         QMessageBox::warning(this, "Error", "Wrong captcha code!\ntry again");
         return;
     }

     QString tempPhone;
     tempPhone = ui->countryCodeLBL->text() + ui->PhoneNumberLineEdit->text();

     QSqlQuery q, q2;
     q.prepare("SELECT * FROM Principle WHERE username=:username OR email=:email OR phone=:phone");

     q.bindValue(":username", username);
     q.bindValue(":email", email);
     q.bindValue(":phone", tempPhone);

     q.exec();

     if (q.first())
     {
         NagativeSound->play();
         QMessageBox::warning(this, "Duplicate Error", "This account has the same username , email or phone number.\n"
                                                        "please try again");

         ui->UsernameLineEdit->clear();
         ui->PasswordLineEdit->clear();
         ui->EmailLineEdit->clear();
         ui->PhoneNumberLineEdit->clear();
         ui->MoneyLineEdit->clear();
         ui->CountryComboBox->setCurrentIndex(0);
         ui->EyeBtn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\eye-close.png"));
         ui->PasswordLineEdit->setEchoMode(QLineEdit::Password);

         on_RefreshBtn_clicked();
         ui->captchaLineEdit->clear();
     }

     else
     {
         q.prepare("INSERT INTO Principle(username, password, email, phone, moneyAmount) "
                   "VALUES(:username, :password, :email, :phone, :moneyAmount)");

         q2.prepare("INSERT INTO coins(username, coins) VALUES(:username, :coins)");

         q.bindValue(":username", username);
         q.bindValue(":password", password);
         q.bindValue(":email", email);
         q.bindValue(":phone", tempPhone);
         q.bindValue(":moneyAmount", moneyAmount);

         q.exec();

         q2.bindValue(":username", username);
         q2.bindValue(":coins", 10);
         q2.exec();

         PositiveSound->play();
         QMessageBox::information(this,"Welcome", "The manager has signed up successfully.");

         ui->UsernameLineEdit->clear();
         ui->PasswordLineEdit->clear();
         ui->EmailLineEdit->clear();
         ui->PhoneNumberLineEdit->clear();
         ui->MoneyLineEdit->clear();
         ui->CountryComboBox->setCurrentIndex(0);
         ui->EyeBtn->setIcon(QIcon("C:\\Users\\Sajjad\\Documents\\GitHub\\FarmManegementProject\\images\\eye-close.png"));
         ui->PasswordLineEdit->setEchoMode(QLineEdit::Password);

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
         this->close(); // or calling destructor: this->~LoginPage();

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
        ui->isPhoneNumCorrect->hide();
        break;

    case 1:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        if(ui->isPhoneNumCorrect->isHidden())   ui->isPhoneNumCorrect->show();
        ui->countryCodeLBL->setText("+93");
        break;

    case 2:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        if(ui->isPhoneNumCorrect->isHidden())   ui->isPhoneNumCorrect->show();
        ui->countryCodeLBL->setText("+55");
        break;

    case 3:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        if(ui->isPhoneNumCorrect->isHidden())   ui->isPhoneNumCorrect->show();
        ui->countryCodeLBL->setText("+1");
        break;

    case 4:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        if(ui->isPhoneNumCorrect->isHidden())   ui->isPhoneNumCorrect->show();
        ui->countryCodeLBL->setText("+86");
        break;

    case 5:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        if(ui->isPhoneNumCorrect->isHidden())   ui->isPhoneNumCorrect->show();
        ui->countryCodeLBL->setText("+49");
        break;

    case 6:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        if(ui->isPhoneNumCorrect->isHidden())   ui->isPhoneNumCorrect->show();
        ui->countryCodeLBL->setText("+98");
        break;
    case 7:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        if(ui->isPhoneNumCorrect->isHidden())   ui->isPhoneNumCorrect->show();
        ui->countryCodeLBL->setText("+964");
        break;
    case 8:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        if(ui->isPhoneNumCorrect->isHidden())   ui->isPhoneNumCorrect->show();
        ui->countryCodeLBL->setText("+7095");
        break;
    case 9:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        if(ui->isPhoneNumCorrect->isHidden())   ui->isPhoneNumCorrect->show();
        ui->countryCodeLBL->setText("+34");
        break;
    case 10:
        if(ui->countryCodeLBL->isHidden())  ui->countryCodeLBL->show();
        if(ui->isPhoneNumCorrect->isHidden())   ui->isPhoneNumCorrect->show();
        ui->countryCodeLBL->setText("+1");
        break;
    }
}

//----------------------------------------------------------------------------------------

bool LoginPage::isUsernameValid(QLineEdit* usernameLineEdit)
{
    QString username = usernameLineEdit->text();
    int pos = 0;

    if( !(username_regex_val.validate(username, pos) == QValidator::Acceptable) )
        return false;

    else
        return true;
}

bool LoginPage::isEmailValid(QLineEdit* emailLineEdit)
{
    QString email = emailLineEdit->text();
    int pos = 0;

    if( !(email_regex_val.validate(email, pos) == QValidator::Acceptable) )
        return false;

    else
        return true;
}

bool LoginPage::isPasswordValid(QLineEdit* passwordLineEdit)
{
    QString password = passwordLineEdit->text();
    int pos = 0;

    if( !(password_regex_val.validate(password, pos) == QValidator::Acceptable) )
        return false;

    else
        return true;
}

bool LoginPage::isPhoneNumValid(QLineEdit* phoneNumLineEdit)
{
    QString password = phoneNumLineEdit->text();
    int pos = 0;

    if( !(phoneNum_regex_val.validate(password, pos) == QValidator::Acceptable) )
        return false;

    else
        return true;
}

bool LoginPage::isMoneyAmountValid(QLineEdit* moneyLineEdit)
{
    QString money = moneyLineEdit->text();
    int pos = 0;

    if( !(phoneNum_regex_val.validate(money, pos) == QValidator::Acceptable) || money.toInt() == 0)
        return false;

    else
        return true;
}

void LoginPage::on_UsernameLineEdit_textChanged(const QString &text)
{
    int pos = 0;
    QString text_tmp = text;

    if (username_regex_val.validate(text_tmp, pos) == QValidator::Acceptable)
        ui->isUsernameCorrect->setStyleSheet("background-color: rgb(0, 255, 127);");

    else if (text_tmp.isEmpty())
        ui->isUsernameCorrect->setStyleSheet("background-color: rgb(255, 255, 255);");

    else
        ui->isUsernameCorrect->setStyleSheet("background-color: rgb(255, 56, 56);");
}

void LoginPage::on_EmailLineEdit_textChanged(const QString &text)
{
    int pos = 0;
    QString text_tmp = text;

    if (email_regex_val.validate(text_tmp, pos) == QValidator::Acceptable)
        ui->isEmailCorrect->setStyleSheet("background-color: rgb(0, 255, 127);");

    else if (text_tmp.isEmpty())
        ui->isEmailCorrect->setStyleSheet("background-color: rgb(255, 255, 255);");

    else
        ui->isEmailCorrect->setStyleSheet("background-color: rgb(255, 56, 56);");
}


void LoginPage::on_PasswordLineEdit_textChanged(const QString &text)
{
    int pos = 0;
    QString text_tmp = text;

    if (password_regex_val.validate(text_tmp, pos) == QValidator::Acceptable)
        ui->isPassCorrect->setStyleSheet("background-color: rgb(0, 255, 127);");

    else if (text_tmp.isEmpty())
        ui->isPassCorrect->setStyleSheet("background-color: rgb(255, 255, 255);");

    else
        ui->isPassCorrect->setStyleSheet("background-color: rgb(255, 56, 56);");
}


void LoginPage::on_PhoneNumberLineEdit_textChanged(const QString &text)
{
    int pos = 0;
    QString text_tmp = text;

    if (phoneNum_regex_val.validate(text_tmp, pos) == QValidator::Acceptable && text.size() == 10)
        ui->isPhoneNumCorrect->setStyleSheet("background-color: rgb(0, 255, 127);");

    else if (text_tmp.isEmpty())
        ui->isPhoneNumCorrect->setStyleSheet("background-color: rgb(255, 255, 255);");

    else
        ui->isPhoneNumCorrect->setStyleSheet("background-color: rgb(255, 56, 56);");
}


void LoginPage::on_MoneyLineEdit_textChanged(const QString &text)
{
    int pos = 0;
    QString text_tmp = text;

    if (money_regex_val.validate(text_tmp, pos) == QValidator::Acceptable && text_tmp.toInt() != 0)
        ui->isMoneyCorrect->setStyleSheet("background-color: rgb(0, 255, 127);");

    else if (text_tmp.isEmpty())
        ui->isMoneyCorrect->setStyleSheet("background-color: rgb(255, 255, 255);");

    else
        ui->isMoneyCorrect->setStyleSheet("background-color: rgb(255, 56, 56);");
}

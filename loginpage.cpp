#include "loginpage.h"
#include "ui_loginpage.h"

#include <QSqlDatabase>
#include <QSqlDriver>
#include<QSqlQuery>

#include <QMessageBox>

QSqlQuery boolq;

LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    ui->LoginPageGroupBox->hide();

    ui->EyeBtn->setIcon(QIcon("d:\\eye-icons\\eye-close.png"));
    ui->PasswordLineEdit->setEchoMode(QLineEdit::Password);

    QSqlDatabase mydatabase;
    mydatabase = QSqlDatabase :: addDatabase("QSQLITE");
    mydatabase.setDatabaseName("C:\\Users\\Microsoft\\Desktop\\FarmManagement\\ProjectDatebase.db");
    mydatabase.open();
    if (!mydatabase.open())
    {
        QMessageBox::warning(this, "Error", "Can not cennect to the database");
    }
}

LoginPage::~LoginPage()
{
    delete ui;
}


void LoginPage::on_EyeBtn_clicked()
{
    if (ui->PasswordLineEdit->echoMode() == QLineEdit::Password)
    {
        ui->EyeBtn->setIcon(QIcon("d:\\eye-icons\\eye.png"));
        ui->PasswordLineEdit->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->EyeBtn->setIcon(QIcon("d:\\eye-icons\\eye-close.png"));
        ui->PasswordLineEdit->setEchoMode(QLineEdit::Password);
    }
}



void LoginPage::on_ContinueBtn_clicked()
{
     QString username, password, email, phoneNumber, moneyAmount;

     username = ui->UsernameLineEdit->text();
     password = ui->PasswordLineEdit->text();
     email = ui->EmailLineEdit->text();
     phoneNumber = ui->PhoneNumberLineEdit->text();
     moneyAmount = ui->MoneyLineEdit->text();


     if (username.isEmpty() && password.isEmpty() && email.isEmpty() && phoneNumber.isEmpty() && moneyAmount.isEmpty())
     {
         QMessageBox::warning(this, "Error", "Pleas complete all informations.");
       //  boolq.prepare("INSERT INTO boolean(bool) VALUES(:bool) ");
        // boolq.bindValue(":bool", 0);
         return;
     }

     //this  is for checking password
          QRegularExpression regex("^(?=.*[0-9])(?=.*[a-zA-Z])[a-zA-Z0-9]{8,}$");
          QRegularExpressionMatch match = regex.match(password);
     if (password.isEmpty())
     {
         QMessageBox::warning(this, "Error", "Please enter the password");
         return;
     }

     if (!match.hasMatch())
     {
       QMessageBox::warning(this, "Error", "The password must contain only alphabets and digits and at least 8 characters.");
       return;
     }

     QRegularExpression pattern("^[a-zA-Z0-9._-]+@(gmail\\.com|email\\.com|mail\\.um\\.ac)$");
     QRegularExpressionMatch EmailMatch = pattern.match(email);
     if (email.isEmpty())
     {
         QMessageBox::warning(this, "Error", "Please enter the email.");
     }
     if (!EmailMatch.hasMatch())
     {
             QMessageBox::warning(this, "Error", "Incorrect email!");
             return;
     }

     QRegularExpression NumberRegex("\\d+");
     QRegularExpressionMatch CheckNumber = NumberRegex.match(phoneNumber);

     if (!CheckNumber.hasMatch())
     {
         QMessageBox::warning(this, "Error", "Wrong phone number!");
     }


        if (count == numManager)
        {
            QMessageBox::warning(this, "Error", "Adding managers completed!");
            return;
        }

     QSqlQuery q;

     q.prepare("SELECT username FROM account WHERE username=:username");
     q.bindValue(":username", username);
     q.exec();

     if (q.first())
     {
         QMessageBox::warning(this, "Error", "This account has already existed.");
     }
     else
     {
         q.prepare("INSERT INTO Principle(username, password, email, phone, moneyAmount) "
                   "VALUES(:username, :password, :email, :phone, :moneyAmount)");

         q.bindValue(":username",username);
         q.bindValue(":password",password);
         q.bindValue(":email",email);
         q.bindValue(":phone",phoneNumber);
         q.bindValue(":moneyAmount", moneyAmount);

         q.exec();
         QMessageBox::information(this,"Welcome", "The manager has signed up successfully.");

         ui->UsernameLineEdit->clear();
         ui->PasswordLineEdit->clear();
         ui->EmailLineEdit->clear();
         ui->PhoneNumberLineEdit->clear();
         ui->MoneyLineEdit->clear();

         count++;
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
}

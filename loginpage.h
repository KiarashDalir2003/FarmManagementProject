#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginPage; }
QT_END_NAMESPACE

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

private slots:
    void on_EyeBtn_clicked();

    void on_ContinueBtn_clicked();

    void on_ConfirmBtn_clicked();

    void on_RefreshBtn_clicked();

    void on_CountryComboBox_currentIndexChanged(int index);

    void on_UsernameLineEdit_textChanged(const QString &);

    void on_EmailLineEdit_textChanged(const QString &);

    void on_PasswordLineEdit_textChanged(const QString &);

    void on_PhoneNumberLineEdit_textChanged(const QString &);

    void on_MoneyLineEdit_textChanged(const QString &);

private:
    Ui::LoginPage *ui;
    QString captchaCode;
    int count = 0;
    int numManager;
    bool isUsernameValid(QLineEdit*);
    bool isEmailValid(QLineEdit*);
    bool isPasswordValid(QLineEdit*);
    bool isPhoneNumValid(QLineEdit*);
    bool isMoneyAmountValid(QLineEdit*);
};
#endif // LOGINPAGE_H

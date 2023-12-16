#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include <QRandomGenerator>
#include <QPainter>
#include <QImage>

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

private:
    Ui::LoginPage *ui;
    QString generateRandomTxt(int);
    QPixmap generateCaptchaImg(const QString &);
    QString dictionary = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    QString captchaCode;
    int count = 0;
    int numManager ;
};
#endif // LOGINPAGE_H

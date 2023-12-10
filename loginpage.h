#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>

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

private:
    Ui::LoginPage *ui;
    int count = 0;
};
#endif // LOGINPAGE_H

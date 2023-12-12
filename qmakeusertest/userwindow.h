#ifndef USERWINDOW_H
#define USERWINDOW_H

#include "usertest.h"
#include <QMainWindow>
#include <qsqldatabase.h>

QT_BEGIN_NAMESPACE
namespace Ui { class userWindow; }
QT_END_NAMESPACE


class userWindow : public QMainWindow
{
    Q_OBJECT

public:
    userWindow(QWidget *parent = nullptr);
    ~userWindow();

    static bool loggedIn();
    static QString userName();
    static userTest::UserType type();

private:
    Ui::userWindow *ui;
    void initForm();
    void initDB();

    static bool    m_loggedIn;         // 登录状态
    static QString m_userName;         // 登录的用户名
    static userTest::UserType m_userType;             // 用户类型
    QSqlDatabase m_db;
private slots:
    bool isTableExists(const QString& table);
    void slot_login();
    void slot_create();
};
#endif // USERWINDOW_H

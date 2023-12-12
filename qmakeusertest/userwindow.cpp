#include "userwindow.h"
#include "./ui_userwindow.h"

#include <qmessagebox.h>
#include <QSqlQuery>
#include <QDebug>
#include "mainpage.h"

bool userWindow::m_loggedIn = false;                           // 登录状态
QString userWindow::m_userName;                                // 登录的用户名
userTest::UserType userWindow::m_userType;                // 用户类型

userWindow::userWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::userWindow)
{
    ui->setupUi(this);
    initForm();
}

userWindow::~userWindow()
{
    delete ui;
}

bool userWindow::loggedIn()
{
    return m_loggedIn;
}

QString userWindow::userName()
{
    return m_userName;
}

userTest::UserType userWindow::type()
{
    return m_userType;
}

void userWindow::initForm()
{
    this->setWindowTitle("login");
    QStringList strList;
    strList<<"用户"<<"管理员";
    ui->comboBox_role->addItems(strList);
    initDB();

    connect(ui->pushButton_login, &QPushButton::clicked, this, &userWindow::slot_login);
    connect(ui->pushButton_enroll, &QPushButton::clicked, this, &userWindow::slot_create);
}

void userWindow::initDB()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");  // 使用数据库驱动（Qsqlite）和默认连接名称（qt_sql_default_connection）添加一个数据库
    m_db.setDatabaseName("SignIn.db");        // 使用文件数据库（可生成数据库文件，数据一直有效）

    if(!m_db.open())             // 打开数据库
    {
        QMessageBox::critical(nullptr, "Error", "打开数据库失败！");
        return ;
    }
    // 创建一个用于保存用户信息的表
    if(!isTableExists("User"))
    {
        QSqlQuery query;

        // 创建一个表person，包含id、firstname、lastname三个字段
        bool ret = query.exec("create table User ("
                              "id         integer primary key,"    // 索引(自增key)
                              "userName   varchar(20),"            // 用户名
                              "password   varchar(20),"            // 密码
                              "type       int)");                  // 用户类型
        if(!ret)
        {
            QMessageBox::critical(nullptr, "Error", "创建表失败");
        }
        else
        {
            QSqlQuery query;
            query.prepare("insert into User(userName, password, type)"
                          "values (:userName, :password, :type)");
            query.bindValue(":userName", "root");
            query.bindValue(":password", "123456");
            query.bindValue(":type", int(userTest::Root));
            query.exec();
        }
    }
}

bool userWindow::isTableExists(const QString &table)
{
    QSqlQuery query;
    // sqlite_master是一个特殊表, 存储数据库的元信息, 如表(table), 索引(index), 视图(view), 触发器(trigger), 可通过select查询相关信息。
    QString sql = QString("select * from sqlite_master where name = '%1';").arg(table);  // 查询sqlite_master表中是否存在表名
    if(query.exec(sql))
    {
        return query.next();
    }
    return false;
}

void userWindow::slot_login()
{
    QString userName = ui->lineEdit_account->text().trimmed();
    QString password = ui->lineEdit_password->text().trimmed();
    if(userName.isEmpty())
    {
        QMessageBox::about(this, "注意！", "用户名不能为空");
        return;
    }
    if(password.isEmpty())
    {
        QMessageBox::about(this, "注意！", "用户密码不能为空");
        return;
    }

    // 从数据库中查询用户和密码，完成登录功能
    QSqlQuery query;
    QString sql = QString("select * from User where userName = '%1';").arg(userName);  // 查询用户
    if(query.exec(sql))
    {
        if(query.next())   // true则用户存在
        {
            if(password == query.value("password").toString())   // 密码相等
            {
                m_userName = userName;
                m_userType = userTest::UserType(query.value("type").toInt());
                m_loggedIn = true;

                MainPage *main = new MainPage();
                main->m_loginDialog = this;
                main->show();
                this->hide();// 隐藏登录，打开软件主界面mainPage

            }
            else
            {
                QMessageBox::about(this, "注意", "输入密码错误！");
            }
        }
        else
        {
            QMessageBox::about(this, "注意", "用户不存在！");
        }
    }
    else
    {
        QMessageBox::about(this, "注意", "sql指令执行失败！");
    }
}

void userWindow::slot_create()
{
    QString userName = ui->lineEdit_account->text().trimmed();
    QString password = ui->lineEdit_password->text().trimmed();
    QString userRole = ui->comboBox_role->currentText();
    userTest::UserType userType = userTest::Root;
    if("用户" == userRole){
    userType = userTest::User;
    }else if("管理员" == userRole){
    userType = userTest::Admin;
    }
    // qDebug()<<"userType: "<<userType;
    if(userName.isEmpty())
    {
        QMessageBox::about(this, "注意！", "用户名不能为空");
        return;
    }
    if(password.isEmpty())
    {
        QMessageBox::about(this, "注意！", "用户密码不能为空");
        return;
    }

    // 注册用户
    QSqlQuery query;
    // QString sql = QString("select * from User where userName = '%1' and type = '%2';").arg(userName).arg(userType);  // 查询用户
    QString sql = QString("select * from User where userName = '%1';").arg(userName);  // 查询用户
    if(query.exec(sql)){
        if(query.next())   // true则用户存在则提示
        {
            QMessageBox::about(this, "注意", "用户已存在！");
        }else {
            query.prepare("insert into User(userName, password, type)"
                          "values (:userName, :password, :type)");
            query.bindValue(":userName", userName);
            query.bindValue(":password", password);
            query.bindValue(":type", int(userType));
            query.exec();
        }
    }else
    {
        QMessageBox::about(this, "注意", "注册用户失败！");
    }




}


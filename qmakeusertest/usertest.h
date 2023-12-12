#ifndef USERTEST_H
#define USERTEST_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class userTest; }
QT_END_NAMESPACE

class userTest : public QWidget
{
    Q_OBJECT

public:
    userTest(QWidget *parent = nullptr);
    ~userTest();

    enum UserType {
        User,            // 普通用户0
        Admin,           // 普通管理员1
        Root
    };
private:
    Ui::userTest *ui;
};
#endif // USERTEST_H

#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>
#include "userwindow.h"
namespace Ui {
class MainPage;
}

class MainPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();
    userWindow *m_loginDialog;

private:
    Ui::MainPage *ui;
    void initTree();
};

#endif // MAINPAGE_H

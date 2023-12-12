#include "usertest.h"
#include "ui_usertest.h"


userTest::userTest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::userTest)
{
    //ui->setupUi(this);
}

userTest::~userTest()
{
    delete ui;
}


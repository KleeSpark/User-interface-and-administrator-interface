#include "mainpage.h"
#include "ui_mainpage.h"

#include <QStandardItem>
#include <QTreeWidgetItem>

MainPage::MainPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    initTree();
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::initTree()
{
    QStringList topTitle;

    QTreeWidgetItem* treeWidgetItem_1;
    QTreeWidgetItem* treeWidgetItem_2;
    QTreeWidgetItem* treeWidgetItem_3;
    QTreeWidgetItem* treeWidgetItem_4;

    QTreeWidgetItem* treeItem_1;
    QTreeWidgetItem* treeItem_2;
    QTreeWidgetItem* treeItem_3;

    QStringList sTreeList_1,sTreeList_2,sTreeList_3,sTreeList_4;
    QStringList sTreeItemList_1,sTreeItemList_2,sTreeItemList_3;

    sTreeList_1 << "工作界面" ;
    sTreeList_2 << "设备运行" ;
    sTreeList_3 << "最终结果" ;
    sTreeList_4 <<"账户管理";
    sTreeItemList_1 << "速度";
    sTreeItemList_2 << "温度";
    sTreeItemList_3 << "时间";

    //创建项目
    treeWidgetItem_1 = new QTreeWidgetItem(sTreeList_1);
    treeWidgetItem_2 = new QTreeWidgetItem(sTreeList_2);
    treeWidgetItem_3 = new QTreeWidgetItem(sTreeList_3);
    treeWidgetItem_4 = new QTreeWidgetItem(sTreeList_4);

    treeItem_1=new QTreeWidgetItem(sTreeItemList_1);
    treeItem_2=new QTreeWidgetItem(sTreeItemList_2);
    treeItem_3=new QTreeWidgetItem(sTreeItemList_3);

    //添加一个顶层项目
    ui->treeWidget->addTopLevelItem(treeWidgetItem_1);
    ui->treeWidget->addTopLevelItem(treeWidgetItem_2);
    ui->treeWidget->addTopLevelItem(treeWidgetItem_3);
    //插入顶层项目
    if(userWindow::type()){
        ui->treeWidget->insertTopLevelItem(0,treeWidgetItem_4);
    }

    //给项目添加子项
    treeWidgetItem_1->addChild(treeItem_1);
    treeWidgetItem_1->addChild(treeItem_2);
    treeWidgetItem_1->addChild(treeItem_3);
}

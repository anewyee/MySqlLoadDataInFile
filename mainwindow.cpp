#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>
#include <QTime>
#include <qdebug.h>
#include <qfiledialog.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit->setPlaceholderText("The path of import file");

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL3");
    db.setHostName("localhost");
    db.setDatabaseName("bigdata");
    db.setUserName("root");
    db.setPassword("123456");

    if (!db.open()) {
        qDebug() << "Failed to connect!";
    }

    QSqlQuery("SET NAMES 'UTF8'").exec();
    QSqlQuery("SET foreign_key_checks = 0").exec();

    products = new SqlTable(ui->tbvProducts, "products");
    connect(products, SIGNAL(queryExecuted()),
            this, SLOT(on_queryExecuted()));
    tables.append(products);
    qDebug()<<products;

    orders = new SqlRelatedTable(ui->tbvOrders, "orders",
                                 QSqlRelation("products", "id", "article"));
    connect(orders, SIGNAL(queryExecuted()),
            this, SLOT(on_queryExecuted()));
    tables.append(orders);

    chart = new SqlTable(ui->tbvChartList, "chartlist");
    connect(chart, SIGNAL(queryExecuted()),
            this, SLOT(on_queryExecuted()));
    tables.append(chart);

    //当前操作的table
    currentTable = tables.at(ui->tabWidget->currentIndex());

    ui->lbQueryMsg->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbnExecQuery_clicked()
{
    currentTable->setImportFilePath(ui->lineEdit->text());
    currentTable->start();
    QThread::msleep(10);
    showStatus();
}

void MainWindow::on_pbnTruncateTable_clicked()
{
    ui->lbQueryMsg->setVisible(false);
    QSqlQuery("TRUNCATE TABLE `" + currentTable->getTable() + "`").exec();
    currentTable->select();
}

void MainWindow::on_pbnChoosePath_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open file"),
                                              "/home", tr("Text (*.txt)"));
    if (!path.isEmpty()) {
        ui->lineEdit->setText(path);
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);
    currentTable = tables.at(ui->tabWidget->currentIndex());
    if (currentTable->getMessage().isEmpty()) {
        ui->lbQueryMsg->setVisible(false);
    } else {
        showStatus();
    }
}

void MainWindow::on_queryExecuted()
{
    currentTable->select();
    showStatus();
}

void MainWindow::showStatus()
{
    ui->lbQueryMsg->setText(currentTable->getMessage());
    ui->lbQueryMsg->setStyleSheet(currentTable->getStyle());
    ui->lbQueryMsg->setVisible(true);
}

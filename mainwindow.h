#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqldriver.h>
#include "tables/sqltable.h"
#include "tables/sqlrelatedtable.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_pbnExecQuery_clicked();
    void on_pbnTruncateTable_clicked();
    void on_pbnChoosePath_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_queryExecuted();
private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlRelationalTableModel *ordersModel;
    SqlAbstractTable *currentTable;
    QList<SqlAbstractTable*> tables;
    SqlTable *products;
    SqlRelatedTable *orders;
    SqlTable *chart;
    void showStatus();
};

#endif // MAINWINDOW_H

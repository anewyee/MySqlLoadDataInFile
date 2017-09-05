#include "sqlabstracttable.h"
#include <qsqlerror.h>
#include <qdatetime.h>
#include <qsqlquery.h>
#include <qdebug.h>

SqlAbstractTable::SqlAbstractTable(QTableView *tableView, const QString &table, QObject *parent) :
    QThread(parent)
{
    this->tableView = tableView;
    this->table = table;
}

QString SqlAbstractTable::getMessage() const
{
    return message;
}

void SqlAbstractTable::setImportFilePath(const QString &value)
{
    importFilePath = value;
}

QString SqlAbstractTable::getTable() const
{
    return table;
}

QSqlDatabase SqlAbstractTable::getConnection()
{
    QSqlDatabase conn = QSqlDatabase::addDatabase("QMYSQL3", QTime::currentTime().toString());
    conn.setHostName("localhost");
    conn.setDatabaseName("bigdata");
    conn.setUserName("root");
    conn.setPassword("123456");

    if (!conn.open()) {
        qDebug() << "Failed to connect!";
        return QSqlDatabase();
    }
    return conn;
}

void SqlAbstractTable::run()
{
    message = "In progress...";
    style = "background-color: #FAFE72; padding: 5px; color: #000";
    QSqlDatabase conn = getConnection();
    QSqlQuery query = QSqlQuery(conn);

    QTime t;
    t.start();
    if (!query.exec(getStatement())) {
        style = "background-color: #CD5C5C; padding: 5px; color: #FFF";
        message = query.lastError().text();
    } else {
        style = "background-color: #5CCD5C; padding: 5px; color: #FFF";
        double elapsed = t.elapsed();
        message = "Elapsed time:" + QString::number(elapsed/1000, 'f', 2)
                                  + "sec";
    }
    conn.close();
    emit queryExecuted();
}

QString SqlAbstractTable::getStyle() const
{
    return style;
}

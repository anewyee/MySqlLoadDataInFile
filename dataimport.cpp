#include "dataimport.h"

#include <qsqlquery.h>
#include <qsqlerror.h>
#include <qdatetime.h>
#include <qdebug.h>

DataImport::DataImport(const QString &statement, QObject *parent)
    : QThread(parent)
{
    this->statement = statement;
}

QSqlDatabase DataImport::getConnection()
{
    QSqlDatabase conn = QSqlDatabase::addDatabase("QMYSQL3", QTime::currentTime().toString());
    conn.setHostName("localhost");
    conn.setDatabaseName("bigdata");
    conn.setUserName("root");

    if (!conn.open()) {
        qDebug() << "Failed to connect!";
        return QSqlDatabase();
    }
    return conn;
}

void DataImport::run()
{
    QSqlDatabase conn = getConnection();
    QSqlQuery query = QSqlQuery(conn);

    QTime t;
    t.start();

    if (!query.exec(statement)) {
        emit queryExecuted(query.lastError().text());
    } else {
        double elapsed = t.elapsed();
        emit queryExecuted("Elapsed time:" +
                           QString::number(elapsed/1000, 'f', 2) + "sec");
    }
    conn.close();
}

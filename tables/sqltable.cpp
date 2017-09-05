#include "sqltable.h"
#include <qdatetime.h>
#include <qdebug.h>

#include <qsqlerror.h>

SqlTable::SqlTable(QTableView *tableView, const QString &table) :
    SqlAbstractTable(tableView, table)
{
    model = new QSqlTableModel();
    model->setTable(table);
    model->select();

    tableView->setModel(model);
}

QString SqlTable::getStatement()
{
    return "LOAD DATA INFILE '" + importFilePath
            + "' INTO TABLE `" + table + "`";
}

void SqlTable::select()
{
    model->select();
}

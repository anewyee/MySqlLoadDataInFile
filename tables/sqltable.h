#ifndef PRODUCTS_H
#define PRODUCTS_H

#include "tables/sqlabstracttable.h"
#include <QtSql/qsqltablemodel.h>

class SqlTable : public SqlAbstractTable
{
public:
    SqlTable(QTableView *tableView, const QString &table);
    void setImportFilePath(const QString &value);
    void select();
private:
    QSqlTableModel *model;
    QString getStatement();
};

#endif // PRODUCTS_H

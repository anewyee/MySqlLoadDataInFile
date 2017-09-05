#ifndef ORDERS_H
#define ORDERS_H

#include "tables/sqlabstracttable.h"
#include <qsqlrelationaltablemodel.h>

class SqlRelatedTable : public SqlAbstractTable
{
public:
    SqlRelatedTable(QTableView *tableView, const QString &table,
                    const QSqlRelation &relation);
    QString getStatement();
    void select();
private:
    QSqlRelationalTableModel *model;

};

#endif // ORDERS_H

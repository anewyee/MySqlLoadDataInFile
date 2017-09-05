#include "sqlrelatedtable.h"

SqlRelatedTable::SqlRelatedTable(QTableView *tableView, const QString &table,
                                 const QSqlRelation &relation) :
    SqlAbstractTable(tableView, table)
{
    model = new QSqlRelationalTableModel();
    model->setTable(table);
    model->setRelation(0, relation);
    model->select();
    tableView->setModel(model);
}

QString SqlRelatedTable::getStatement()
{
    //BUG IS HERE (STATIC TABLE AND COLUMNS):
    return "LOAD DATA INFILE '" + importFilePath
            + "' IGNORE INTO TABLE `orders`(@id, `date`, `count`)"
              "SET id = (SELECT `id` FROM `products` WHERE article = @id)";
}

void SqlRelatedTable::select()
{
    model->select();
}

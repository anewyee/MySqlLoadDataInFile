#ifndef TABLE_H
#define TABLE_H

#include <qstring.h>
#include <qtableview.h>
#include <qthread.h>
#include <qsqldatabase.h>

class SqlAbstractTable : public QThread
{
    Q_OBJECT
public:
    SqlAbstractTable(QTableView *tableView, const QString &table, QObject *parent = 0);
    QString getMessage() const;
    QString getTable() const;
    QString getStyle() const;
    void setImportFilePath(const QString &value);
    virtual void select() = 0;
    virtual QString getStatement() = 0;
signals:
    QString queryExecuted();
protected:
    QTableView *tableView;
    QString importFilePath;
    QString table;
    QSqlDatabase getConnection();
    void run();
private:
    QString message;
    QString style;
};

#endif // TABLE_H

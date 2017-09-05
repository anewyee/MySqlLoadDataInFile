#ifndef DATAIMPORT_H
#define DATAIMPORT_H

#include <QThread>
#include <qsqldatabase.h>
#include <qstring.h>

class DataImport : public QThread
{
    Q_OBJECT
public:
    explicit DataImport(const QString &statement, QObject *parent = 0);
    QSqlDatabase getConnection();
    // QThread interface
protected:
    void run();
private:
    QString statement;
signals:
    QString queryExecuted(QString);
};

#endif // DATAIMPORT_H

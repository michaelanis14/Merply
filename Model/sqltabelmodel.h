#ifndef SQLTABELMODEL_H
#define SQLTABELMODEL_H

#include <QObject>
#include <QSqlRelationalTableModel>




class SQLTabelModel : public  QSqlRelationalTableModel
{
	Q_OBJECT
public:
	explicit SQLTabelModel(QObject *parent = 0, const QString document_id = "", QSqlDatabase db = QSqlDatabase());
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
	QString document_id;

signals:

public slots:
};

#endif // SQLTABELMODEL_H

#ifndef SQLTABELMODEL_H
#define SQLTABELMODEL_H

#include <QObject>
#include <QSqlRelationalTableModel>




class SQLTabelModel : public  QSqlTableModel
{
	Q_OBJECT
public:
	explicit SQLTabelModel(QObject *parent = 0, const int document_id = -1, QSqlDatabase db = QSqlDatabase());
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
	int document_id;

signals:

public slots:
};

#endif // SQLTABELMODEL_H

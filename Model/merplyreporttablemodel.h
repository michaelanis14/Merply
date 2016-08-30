#ifndef MERPLYREPORTTABLEMODEL_H
#define MERPLYREPORTTABLEMODEL_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QVector>
#include <QStringList>

class TableCell{

public:
	TableCell(QString id = "",QString data = "");
	QString getData() const;
	void setData(const QString& value);
	QString getId() const;
	void setId(const QString& value);
private:
	QString id;
	QString data;
};

class MerplyReportTableModel : public QAbstractTableModel
{
public:
	MerplyReportTableModel(QJsonObject strct = QJsonObject());
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	void fill(QList<QJsonDocument> documents);

private:
	int rowsCount;
	int colmnsCount;
	TableCell* cells;
	QHash<QString, int> i;
	QHash<QString, int> rowPointer;
	QHash<QString, int> entityRowPointer;

	QJsonObject strct;
	QJsonArray clmns;
	QStringList clmnsHeader;
};

#endif // MERPLYREPORTTABLEMODEL_H

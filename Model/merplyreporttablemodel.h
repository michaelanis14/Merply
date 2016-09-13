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
	Q_OBJECT
public:
	MerplyReportTableModel(QJsonObject strct = QJsonObject());
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;


private:
	int rowsCount;
	int colmnsCount;
	TableCell* cells;
	QHash<QString, int> i;
	QHash<QString, int> rowPointer;
	QHash<QString, int> entityRowPointer;
	QHash<QString, QJsonArray> equationColumns;
	QJsonObject strct;
	QJsonArray clmns;
	QStringList clmnsHeader;
signals:
	void equationColumnsSignal();
public slots:
	void fillEquationColumns();
	  void setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage);
	void fill(QList<QJsonDocument> documents);
};

#endif // MERPLYREPORTTABLEMODEL_H

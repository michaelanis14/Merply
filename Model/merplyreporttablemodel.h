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
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
	Qt::ItemFlags flags(const QModelIndex & index) const;
	QVector<QJsonDocument> items;
	QString getRowKey(int row);
	QJsonArray getJsonData();
	void evalTotalRow();
	double getTotalClmn(QString clmn);
	int getRowsCount() const;
	QJsonArray getRemovedRows();
	int getColmnsCount() const;

private:
	int rowsCount;
	int colmnsCount;
	QVector<TableCell> cells;
	QVector<int>totalColmns;
	QHash<QString, int> i;
	QHash<QString, int> rowPointer;
	QHash<QString, int> entityRowPointer;
	QHash<QString, QJsonArray> equationColumns;
	QHash<QString,  QJsonObject> editableColumns;
	QHash<QString,QJsonObject> Textclmns;
	QHash<QString,QJsonObject> Refrenceclmns;
	QJsonObject strct;
	QJsonArray clmns;
	QStringList clmnsHeader;
	bool addedTotalRow;
	QJsonArray dataArray;
	QJsonArray removedRowsArray;
signals:
	void equationColumnsSignal();
	void done();
	void changed();
public slots:
	void fillEquationColumns();
	double evalEquationCondition(int condition,double col1,double col2);
	void setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage);
	void fill(QVector<QJsonDocument> documents);
	void fillQuery(QVector<QJsonDocument> documents);
	void fillText(QJsonArray data);
	void fillIndexTabel(QVector<QJsonDocument> items);
	void fillLocalSource(QVector<QJsonDocument> items);
	void fillAddtoTable(QVector<QJsonDocument> items);

};

#endif // MERPLYREPORTTABLEMODEL_H

#ifndef MERPLYREPORTTABLEMODEL_H
#define MERPLYREPORTTABLEMODEL_H

#include <QObject>
#include <QWidget>
#include <QtGui>

class MerplyReportTableModel : public QAbstractTableModel
{
public:
	MerplyReportTableModel(QList<QJsonDocument> documents = QList<QJsonDocument>());
	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	void fill(QList<QJsonDocument> documents);
private:
	int m_numRows;
	int m_numColumns;
	QVector<QString> jdata;
	QHash<QString, int> i;
	QHash<QString, int> j;

};

#endif // MERPLYREPORTTABLEMODEL_H

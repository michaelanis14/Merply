#include "merplyreporttablemodel.h"

MerplyReportTableModel::MerplyReportTableModel(QList<QJsonDocument> documents)
{

	fill(documents);
}

int MerplyReportTableModel::rowCount(const QModelIndex& parent) const
{
	return m_numRows;
}

int MerplyReportTableModel::columnCount(const QModelIndex& parent) const
{
	return m_numColumns;
}

QVariant MerplyReportTableModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	// Return the data to which index points.
	return jdata[index.row() * m_numColumns + index.column()];
}

void MerplyReportTableModel::fill(QList<QJsonDocument> documents)
{

}

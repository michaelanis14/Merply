#include "sqltabelmodel.h"
#include "controller.h"

SQLTabelModel::SQLTabelModel(QObject *parent, const int document_id,QSqlDatabase db) :  QSqlRelationalTableModel(parent,db)
{
	this->document_id = document_id;
	this->setTable("`"+QString::number(document_id)+"`");
	this->setEditStrategy(QSqlTableModel::OnManualSubmit);
	qDebug() << "TabelID" << QString::number(document_id) << this->select() << this->lastError() << this->query().lastQuery();
}



QVariant SQLTabelModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal) {
		if(section < Controller::Get()->getCachedViewStructureIndexFieldsNames(document_id).count()){
			return tr(QString(Controller::Get()->getCachedViewStructureIndexFieldsNames(document_id).at(section)).toStdString().c_str());
			}
		}
	return QString::number(section);
}


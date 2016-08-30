#include "merplyreporttablemodel.h"


MerplyReportTableModel::MerplyReportTableModel(QJsonObject strct) :QAbstractTableModel()
{
	rowsCount = 0;
	this->strct = strct;
	this->clmnsHeader = QStringList();
	//colmnsCount = 1;
	if(strct.value("Columns").isArray()){
		this->clmns = (strct.value("Columns").toArray());
		colmnsCount = this->clmns.count();
		foreach(QJsonValue clmn,strct.value("Columns").toArray()){
			clmnsHeader << clmn.toObject().value("Header").toString();
			}
		}
	//fill(documents);
}

int MerplyReportTableModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return rowsCount;
}

int MerplyReportTableModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return colmnsCount;
}

QVariant MerplyReportTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal) {
		if(section <= colmnsCount){

			return tr(QString(clmnsHeader.at(section)).toStdString().c_str());
			}
		}
	return QVariant();
}

QVariant MerplyReportTableModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	// Return the data to which index points.
	return cells[index.row() * colmnsCount + index.column()].getData();
}

void MerplyReportTableModel::fill(QList<QJsonDocument> documents)
{
	//qDebug() << clmnsHeader;
	rowsCount = 0;
	//this->rowsCount = ;
	cells = new TableCell[colmnsCount * documents.count()];
	foreach(QJsonDocument doc, documents){
		int row = -1;
		QString dataKey;
		QString indexedKey;
		QStringList joinKeys;
		QString jKey;
		QStringList keys = doc.object().keys();

		foreach(QString key,keys){
			if(key.toLower().contains("key"))
				if(key.toLower().contains("join")){
					keys.removeOne(key);
					jKey = key.replace("Join","");
					break;

					//qDebug() <<"REMOVED "<< keys << key << jKey;
					//	continue;
					}
			}
		if(keys.count() > 2)
			keys.removeOne(jKey);
		//joinKeys.append(jKey);
		foreach(QString key,keys){
			//jKValue =doc.object().value(key).toString();
			if(key.toLower().contains("key")){


				if(!rowPointer.contains(key)){
					rowPointer.insert(key,0);
					}

				if(!entityRowPointer.contains(doc.object().value(key).toString())){
					entityRowPointer.insert(doc.object().value(key).toString(),rowPointer.value(key));
					}


				if(entityRowPointer.value(doc.object().value(key).toString()) >= row){
					//qDebug() << doc.object().value(key).toString()<<entityRowPointer.value(doc.object().value(key).toString());
					row = entityRowPointer.value(doc.object().value(key).toString());
					indexedKey = key;
					}


				joinKeys.append(key);
				}
			else{
				dataKey = key;
				}

			}


		TableCell cell(dataKey,doc.object().value(dataKey).toString());
		entityRowPointer.insert(doc.object().value(indexedKey).toString(),row);

		//qDebug()<<joinKeys<<indexedKey << row << rowPointer.value(indexedKey)<< row * this->colmnsCount + clmnsHeader.indexOf(dataKey) <<clmnsHeader.indexOf(dataKey)<<dataKey << doc.object().value(dataKey).toString();
		cells[row * this->colmnsCount + clmnsHeader.indexOf(dataKey)] = cell;
		int oldRow = rowPointer.value(indexedKey);
		oldRow++;
		//qDebug() <<joinKeys.count() << joinKeys.first().compare(indexedKey) ;
		if(joinKeys.count() != 1 && joinKeys.first().compare(indexedKey) == 0){
			}
		else{
			foreach (QString k, joinKeys) {
				rowPointer.insert(k,oldRow);
				}
			}
		if(rowsCount < row)
			rowsCount = row;
		//rowPointer.insert(joinKey,oldRow);
		}


	//qDebug()<<"TableModel Fill" << documents;
}



QString TableCell::getId() const
{
	return id;
}

void TableCell::setId(const QString& value)
{
	id = value;
}

TableCell::TableCell(QString id, QString data)
{
	this->id  = id;
	this->data = data;
}

QString TableCell::getData() const
{
	return data;
}

void TableCell::setData(const QString& value)
{
	data = value;
}

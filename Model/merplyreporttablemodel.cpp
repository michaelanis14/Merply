#include "merplyreporttablemodel.h"


MerplyReportTableModel::MerplyReportTableModel(QJsonObject strct) :QAbstractTableModel()
{
	rowsCount = 0;
	this->strct = strct;
	this->clmnsHeader = QStringList();
	this->equationColumns.clear();
	//colmnsCount = 1;
	if(strct.value("Columns").isArray()){
		this->clmns = (strct.value("Columns").toArray());
		colmnsCount = this->clmns.count();
		foreach(QJsonValue clmn,strct.value("Columns").toArray()){
			clmnsHeader << clmn.toObject().value("Header").toString();
			if(clmn.toObject().value("Type").toString().compare("Equation") == 0)
				equationColumns.insert(clmn.toObject().value("Header").toString(),clmn.toObject().value("EquationTerms").toArray());
			}
		}
	QObject::connect(this,SIGNAL(equationColumnsSignal()),this,SLOT(fillEquationColumns()));

	qDebug() << this->strct;
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

	if(this->equationColumns.count() > 0)
		emit equationColumnsSignal();
	//qDebug()<<"TableModel Fill" << documents;
}

void MerplyReportTableModel::fillEquationColumns()
{
	QHashIterator<QString, QJsonArray> i(equationColumns);
	while (i.hasNext()) {
		i.next();
		for(int j = 0; j < rowsCount; j++){
			double total = 0;
			foreach(QJsonValue eq,i.value()){
				double subTotal = 0;
				bool ok = false;
				double firstTerm = 0;
				double secondTerm = 0;
				if(eq.toObject().value("FirstColumn").toInt() > 0)
					firstTerm = cells[j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt()].getData().toDouble(&ok);
				if(eq.toObject().value("SecondColmn") != QJsonValue::Undefined){
					if(eq.toObject().value("SecondColmn").toInt() > 0)
						secondTerm = cells[j * this->colmnsCount + eq.toObject().value("SecondColmn").toInt()].getData().toDouble(&ok);
					}
				else if(eq.toObject().value("Number") != QJsonValue::Undefined){
					secondTerm = eq.toObject().value("Number").toString().toDouble();
					//qDebug() << "NUMBERRRR" << secondTerm;
					}
				//qDebug() << ok << firstTerm << secondTerm;
				if(ok){
					if(eq.toObject().value("Operation").toInt() == 0){
						subTotal = firstTerm + secondTerm;
						}
					else if(eq.toObject().value("Operation").toInt() == 1){
						subTotal = firstTerm - secondTerm;
						}
					else if(eq.toObject().value("Operation").toInt() == 2){
						subTotal = firstTerm * secondTerm;
						}
					else if(eq.toObject().value("Operation").toInt() == 3){
						subTotal = firstTerm / secondTerm;
						}

					if(eq.toObject().value("FirstOperation") != QJsonValue::Undefined){
						if(eq.toObject().value("FirstOperation").toInt() == 0){
							total += subTotal;
							}
						else if(eq.toObject().value("FirstOperation").toInt() == 1){
							total -= subTotal;
							}
						else if(eq.toObject().value("FirstOperation").toInt() == 2){
							total *= subTotal;
							}
						else if(eq.toObject().value("FirstOperation").toInt() == 3){
							total /= subTotal;
							}
						//qDebug() << subTotal << total;
						}
					else total = subTotal;
					}
				}
			//cout << i.key() << ": " << i.value() << endl;
			//qDebug() << total;
			TableCell cell("",QString::number(total));
			cells[j * this->colmnsCount + clmnsHeader.indexOf(i.key())] =cell;
			}
		}

}

void MerplyReportTableModel::setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage)
{
	int  columnIndex = clmnsHeader.indexOf(paramName);
	if(columnIndex != -1){
		paramValue = cells[recNo * this->colmnsCount + columnIndex].getData();
	//	qDebug() << paramValue << paramName;
		}
	else return;

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



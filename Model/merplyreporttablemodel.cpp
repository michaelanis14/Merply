#include "merplyreporttablemodel.h"
#include "controller.h"

#include "mtabelcombobox.h"

MerplyReportTableModel::MerplyReportTableModel(QJsonObject strct) :QAbstractTableModel()
{
	rowsCount = 0;
	this->strct = strct;
	this->clmnsHeader = QStringList();
	this->equationColumns.clear();
	this->addedTotalRow = false;
	this->removedRowsArray = QJsonArray();
	//colmnsCount = 1;
	if(strct.value("Columns").isArray()){
		this->clmns = (strct.value("Columns").toArray());
		clmnsHeader << "ID.No.";
		foreach(QJsonValue clmn,strct.value("Columns").toArray()){
			//	if(clmn.toObject().value("ShowIndex") == QJsonValue::Undefined){
			//		continue;
			//		}

			clmnsHeader << clmn.toObject().value("Header").toString().split("$")[0];
			if(clmn.toObject().value("Type").toString().compare("Text") == 0)
				Textclmns.insert(clmn.toObject().value("Header").toString(),clmn.toObject());
			else if(clmn.toObject().value("Type").toString().compare("Refrence") == 0)
				Refrenceclmns.insert(clmn.toObject().value("Header").toString(),clmn.toObject());
			else if(clmn.toObject().value("Type").toString().compare("Equation") == 0){
				equationColumns.insert(clmn.toObject().value("Header").toString(),clmn.toObject().value("EquationTerms").toArray());
				}


			if(clmn.toObject().value("TotalRow") != QJsonValue::Undefined)
				totalColmns.append(clmnsHeader.count() - 1);
			if(clmn.toObject().value("Editable") == QJsonValue::Undefined ||
					clmn.toObject().value("Editable").toBool())
				editableColumns.insert(clmn.toObject().value("Header").toString(),QJsonObject());


			}
		}
	else{
		clmnsHeader << "ID.No.";
		clmnsHeader << strct.value("clmnsHeader").toVariant().toStringList();
		//qDebug() << __FILE__ << __LINE__  << clmnsHeader;
		}
	colmnsCount = clmnsHeader.count();
	QObject::connect(this,SIGNAL(equationColumnsSignal()),this,SLOT(fillEquationColumns()));

	//	qDebug() << __FILE__ << __LINE__  << this->strct;
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
	if(index.isValid() && role == Qt::EditRole)
		return cells[index.row() * colmnsCount + index.column()].getData();
	if (!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	//qDebug() << __FILE__ << __LINE__  <<"Edit"<< cells[index.row() * colmnsCount + index.column()].getData();

	return cells[index.row() * colmnsCount + index.column()].getData();
}

bool MerplyReportTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (index.isValid() && role == Qt::EditRole) {
		//qDebug() << __FILE__ << __LINE__  <<value.toString();
		if(Textclmns.contains(clmnsHeader.at(index.column()))){
			if(Textclmns.value(clmnsHeader.at(index.column())).value("inputData").toInt() == 1){
				bool ok = true;
				value.toDouble(&ok);
				if(!ok){
					return false;
					}
				}
			}

		cells[index.row() * colmnsCount + index.column()].setData(value.toString());
		if(equationColumns.count() > 0 )
			fillEquationColumns();
		//if(totalColmns.count() > 0)
		//	evalTotalRow();
		emit dataChanged(index, index);
		emit changed();
		return true;
		}
	return false;
}

bool MerplyReportTableModel::insertRows(int row, int count, const QModelIndex& parent)
{
	if(addedTotalRow){
		//qDebug() << __FILE__ << __LINE__  << "RemoveRowsTotal";
		this->removeRow(this->rowCount(QModelIndex())-1);
		addedTotalRow = false;
		}
	bool state = false;
	beginInsertRows(parent, row, row+count-1);
	dataArray.append(QJsonValue());
	rowsCount = row +count;
	cells.resize(colmnsCount * rowsCount);

	//cells[row * this->colmnsCount + 1].setData("dd");
	//qDebug() << __FILE__ << __LINE__  << cells.size();
	state = true;
	endInsertRows();

	return state;
}


bool MerplyReportTableModel::removeRows(int row, int count, const QModelIndex& parent)
{
	bool state = false;
	beginRemoveRows(parent, row, row+count-1);

	//	qDebug() << __FILE__ << __LINE__  << cells.size() << row << row * this->colmnsCount;
	for(int j = 0; j< colmnsCount; j++){
		cells.removeAt(row * this->colmnsCount );
		if(dataArray.at(row).toObject().value("documentID") != QJsonValue::Undefined)
			removedRowsArray.append(dataArray.at(row));
		dataArray.removeAt(row);
		}
	//qDebug() << __FILE__ << __LINE__  << cells.count();
	//cells.resize(colmnsCount * rowsCount);
	//cells[row * this->colmnsCount + 1].setData("dd");
	rowsCount = rowsCount -count;
	state = true;
	endRemoveRows();
	return state;
}

Qt::ItemFlags MerplyReportTableModel::flags(const QModelIndex& index) const
{
	if(index.isValid())
		if(!equationColumns.contains(clmnsHeader.at(index.column())))
			if((editableColumns.contains(clmnsHeader.at(index.column())) && Textclmns.contains(clmnsHeader.at(index.column())))
					|| (Refrenceclmns.contains(clmnsHeader.at(index.column())))){
				//		qDebug() << __FILE__ << __LINE__ << "EDitabel";
				return QAbstractTableModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsEnabled |Qt::ItemIsSelectable;
				}

	return QAbstractTableModel::flags(index) & ~Qt::ItemIsEditable ;
}

QString MerplyReportTableModel::getRowKey(int row)
{
	return cells[row * this->colmnsCount].getId();
}

QJsonArray MerplyReportTableModel::getJsonData()
{
	QJsonArray tabel;
	for(int i = 0;i < rowsCount; i++){
		QJsonObject row = dataArray.at(i).toObject();
		for(int j = 0; j< colmnsCount; j++){
			QString data = cells[i * this->colmnsCount + j].getData();
			if(!data.isEmpty()){
				//	qDebug() << data  << data.split("$").count() << data.split("$");
				if(data.split("$").count() > 1){

					row.insert("ID",QString(data.split("$")[1]));
					row.insert(clmnsHeader.at(j),QString(data.split("$")[0]));
					//	qDebug()<<"IFF" <<j<< tabel<<row ;
					}
				else{
					if(row.value("ID") == QJsonValue::Undefined)
						row.insert("ID",cells[i * this->colmnsCount + j].getId());
					row.insert(clmnsHeader.at(j),data);
					//	qDebug() <<"ELSEE"<<j<< tabel<<row ;
					}
				}
			}
		if(!row.isEmpty())
			tabel.append(row);
		}

	//qDebug() << tabel;
	return tabel;
}

void MerplyReportTableModel::evalTotalRow()
{
	if(addedTotalRow){
		qDebug() << __FILE__ << __LINE__  << "RemoveTotal";
		this->removeRow(this->rowCount(QModelIndex())-1);
		addedTotalRow = false;

		}
	QVector<double> totals= QVector<double>(totalColmns.size());
	for (int i = 0; i < totalColmns.size(); i++) {
		double total = 0;
		bool ok = false;
		for(int j = 0; j < rowsCount; j++){
			//qDebug() << __FILE__ << __LINE__  <<"Totalll"<< cells[j * this->colmnsCount + totalColmns.at(i)].getData().trimmed().toDouble(&ok);
			total += cells[j * this->colmnsCount + totalColmns.at(i)].getData().trimmed().toDouble(&ok);
			}
		//qDebug() << __FILE__ << __LINE__  << i <<
		totals.insert(i,total);
		}

	//qDebug() << __FILE__ << __LINE__  << total;
	if(!addedTotalRow){
		//qDebug() << __FILE__ << __LINE__  <<"addddd";
		this->insertRow(this->rowCount(QModelIndex()));
		this->addedTotalRow = true;
		for (int i = 0; i < totalColmns.size();i++) {
			//	qDebug() << __FILE__ << __LINE__  <<"THE TOTAL"<< totals.at(i) << totals ;
			cells[(rowsCount-1) * this->colmnsCount + totalColmns.at(i)].setData(QString::number(totals.at(i)));
			}
		}
}

double MerplyReportTableModel::getTotalClmn(QString clmn)
{


	int clmnIndx = clmnsHeader.indexOf(clmn);
	double total = 0;
	if(rowsCount > 0){
		double subTotal = 0;
		bool ok =  false;
		//qDebug() << __FILE__ << __LINE__  << clmnIndx << clmn << clmnsHeader << rowsCount;
		if(clmnIndx > -1){
			for(int j = 0; j < rowsCount; j++){
				//	qDebug() << __FILE__ << __LINE__  <<"Totalll"<< cells[j * this->colmnsCount + clmnIndx].getData().trimmed().toDouble(&ok) << ok;
				subTotal += cells[j * this->colmnsCount + clmnIndx].getData().trimmed().toDouble(&ok);

				}
			}
		if(ok)
			total = subTotal;
		}

	return total;

}

int MerplyReportTableModel::getRowsCount() const
{
	return rowsCount;
}

QJsonArray MerplyReportTableModel::getRemovedRows()
{
	return removedRowsArray;
}

int MerplyReportTableModel::getColmnsCount() const
{
	return colmnsCount;
}

void MerplyReportTableModel::fill(QVector<QJsonDocument> documents)
{

	//qDebug() << documents;
	rowsCount = 0;
	cells =  QVector<TableCell>(colmnsCount * documents.count());
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

					//qDebug() << __FILE__ << __LINE__  <<"REMOVED "<< keys << key << jKey;
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
					//qDebug() << __FILE__ << __LINE__  << doc.object().value(key).toString()<<entityRowPointer.value(doc.object().value(key).toString());
					row = entityRowPointer.value(doc.object().value(key).toString());
					indexedKey = key;
					}


				joinKeys.append(key);
				}
			else{
				dataKey = key;
				}

			}
		if(dataKey.isEmpty())
			continue;

		TableCell cell(dataKey,doc.object().value(dataKey).toString());
		if(doc.object().value(dataKey).isArray())
			qDebug() << __FILE__ << __LINE__  << "ISARRAAYYYY";
		entityRowPointer.insert(doc.object().value(indexedKey).toString(),row);

		//qDebug() << __FILE__ << __LINE__ <<joinKeys<<indexedKey << row << rowPointer.value(indexedKey)<< row * this->colmnsCount + clmnsHeader.indexOf(dataKey) <<clmnsHeader.indexOf(dataKey)<<dataKey << doc.object().value(dataKey).toString();
		//	qDebug() << __FILE__ << __LINE__  << row << this->colmnsCount << clmnsHeader.indexOf(dataKey) << dataKey;

		cells[row * this->colmnsCount + clmnsHeader.indexOf(dataKey)] = cell;
		int oldRow = rowPointer.value(indexedKey);
		oldRow++;
		//qDebug() << __FILE__ << __LINE__  <<joinKeys.count() << joinKeys.first().compare(indexedKey) ;
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
	else emit done();
	//qDebug() << __FILE__ << __LINE__ <<"TableModel Fill" << documents;


}

void MerplyReportTableModel::fillQuery(QVector<QJsonDocument> documents)
{
	beginResetModel();
	//qDebug() << __FILE__ << __LINE__  <<documents;
	cells =  QVector<TableCell>(colmnsCount * documents.count());
	QHash<QString,int> rowsKeyed;
	int rowIndex = 0;
	//rowsCount = 0;
	foreach(QJsonDocument row,documents){
		//qDebug() << __FILE__ << __LINE__  <<row;
		QStringList keys = row.object().keys();
		int i = 0;
		if(row.object().value("ID") != QJsonValue::Undefined){
			if(rowsKeyed.contains(row.object().value("ID").toString())){
				i = rowsKeyed.value(row.object().value("ID").toString());
				//qDebug() << __FILE__ << __LINE__  <<i;
				}
			else {
				rowsKeyed.insert(row.object().value("ID").toString(),rowIndex);
				i = rowIndex;
				//qDebug() << __FILE__ << __LINE__  <<i;
				rowIndex++;
				}
			foreach(QString key,keys){
				int j = clmnsHeader.indexOf(key);
				if(j > -1){
					//	qDebug() << __FILE__ << __LINE__  <<i * this->colmnsCount + j << Controller::Get()->toString(row.object().value(key)) ;
					cells[i * this->colmnsCount + j].setId(row.object().value("ID").toString());
					QString value;

					QString dtoCompare = QString::fromUtf8("تاريخ");
					//qDebug() << clmnsHeader.at(j) << clmnsHeader.at(j).trimmed().compare(dtoCompare);
					if(clmnsHeader.at(j).trimmed().compare(dtoCompare) == 0 || clmnsHeader.at(j).trimmed().contains("Date")){
						QDateTimeEdit *date = new QDateTimeEdit;
						date->setHidden(true);
						date->setDateTime(QDateTime::fromString(row.object().value(clmnsHeader.at(j)).toString(),Qt::ISODate));
						value  =  date->dateTime().toString("dd/MM/yyyy");
						}
					else value = Controller::Get()->toString(row.object().value(key));
					cells[i * this->colmnsCount + j].setData(value);
					}
				}
			}

		}



	rowsCount = rowIndex ;
	endResetModel();

	if(this->equationColumns.count() > 0)
		emit equationColumnsSignal();
	emit done();

}

void MerplyReportTableModel::fillText(QJsonArray data)
{
	this->dataArray = data;
	cells =  QVector<TableCell>(colmnsCount * data.count());
	rowsCount = data.count();
	//qDebug() << rowCount();
	for(int i = 0; i < data.count(); i++){
		QJsonObject row =  data.at(i).toObject();
		for(int j = 0; j <clmnsHeader.count(); j++){
			QString value;
/* // TO SET THE DATE STRING
			QString dtoCompare = QString::fromUtf8("تاريخ");
			qDebug() << clmnsHeader.at(j) << clmnsHeader.at(j).trimmed().compare(dtoCompare);
			if(clmnsHeader.at(j).trimmed().compare(dtoCompare) == 0 || clmnsHeader.at(j).trimmed().contains("Date")){
				QDateTimeEdit *date = new QDateTimeEdit;
				date->setHidden(true);
				date->setDateTime(QDateTime::fromString(row.value(clmnsHeader.at(j)).toString(),Qt::ISODate));
				value  =  date->dateTime().toString("dd/MM/yyyy");
				}

			else
*/
			value = Controller::Get()->toString(row.value(clmnsHeader.at(j)));
			//qDebug() << value;
			if(!value.isEmpty() && value.split("$").count() > 1){
				cells[i * this->colmnsCount + j].setId(QString(value.split("$")[1]));
				cells[i * this->colmnsCount + j].setData(QString(value.split("$")[0]));
				}
			else if(!value.isEmpty()){
				if(row.value("ID") != QJsonValue::Undefined)
					cells[i * this->colmnsCount + j].setId(row.value("ID").toString());

				cells[i * this->colmnsCount + j].setData(value);
				}
			}

		}
	if(this->equationColumns.count() > 0)
		emit equationColumnsSignal();
	else emit done();

}

void MerplyReportTableModel::fillIndexTabel( QVector<QJsonDocument> items)
{
	//qDebug() << items;
	int i = 0;

	cells = QVector<TableCell>(colmnsCount * items.count());
	beginResetModel();
	foreach(QJsonDocument item,items){
		QString  key = item.object().value("document_id").toString();
		int j = 0;
		//	qDebug() << cells.count() << QString::number((i * this->colmnsCount + j)-1) << (((i * this->colmnsCount + j)-1) <= cells.count());
		if(cells.count() > 0 && ((i * this->colmnsCount + j)-1) <= cells.count() )
			cells[i * this->colmnsCount + j].setId(key);

		foreach(QString keyData,item.object().keys()){
			//	qDebug() << __FILE__ << __LINE__  <<"Filllll"<< keyData << clmnsHeader.indexOf(keyData);
			int clmnIndex = clmnsHeader.indexOf(keyData);
			if(clmnIndex > -1){
				QString valueString;
				valueString = Controller::Get()->toString(item.object().value(keyData));
				//		qDebug() << __FILE__ << __LINE__  <<"valueString"<< valueString;

				cells[(i * this->colmnsCount) + clmnIndex].setId(key);
				QString dtoCompare = QString::fromUtf8("تاريخ");
				//qDebug()<< __FILE__ << __LINE__ << keyData << keyData.trimmed().compare(dtoCompare);
				if(keyData.trimmed().compare(dtoCompare) == 0 || keyData.trimmed().contains("Date")){
					QDateTimeEdit *date = new QDateTimeEdit;
					date->setHidden(true);
					date->setDateTime(QDateTime::fromString(valueString,Qt::ISODate));
					valueString  =  date->dateTime().toString("dd/MM/yyyy");
					}
				cells[(i * this->colmnsCount) + clmnIndex].setData(valueString);
				//	QModelIndex id=this->index(i,clmnIndex,QModelIndex());
				//emit dataChanged(id, id);

				}
			else if(item.object().value(keyData) != QJsonValue::Undefined){
				foreach(QJsonValue row, item.object().value(keyData).toObject().value("merplyTabel").toArray()){
					//	qDebug() << __FILE__ << __LINE__  <<"ROwww"<< row;
					foreach(QString keyDataRow,row.toObject().keys()){
						//		qDebug() << __FILE__ << __LINE__  <<"Filllll"<< keyData << clmnsHeader.indexOf(keyData);
						int clmnIndexRow = clmnsHeader.indexOf(keyDataRow);
						if(clmnIndexRow > -1){
							QString valueString;
							valueString = Controller::Get()->toString(row.toObject().value(keyDataRow));
							//	qDebug() << __FILE__ << __LINE__  <<"valueStringROWW"<< valueString;

							cells[(i * this->colmnsCount) + clmnIndexRow].setId(key);

							if(cells[(i * this->colmnsCount) + clmnIndexRow].getData().isEmpty())
								cells[(i * this->colmnsCount) + clmnIndexRow].setData(valueString);
							else cells[(i * this->colmnsCount) + clmnIndexRow].setData(cells[(i * this->colmnsCount) + clmnIndexRow].getData().append(" , ").append(valueString));
							}
						}
					}
				}
			}
		//qDebug() << __FILE__ << __LINE__  <<"ITEMM"<< item;
		i++;
		}
	rowsCount = i;
	endResetModel();
	//	if(this->rowsCount == 0)
	//		this->rowsCount = 1;

	int r=this->rowsCount-1;
	int c=this->colmnsCount-1;
	QModelIndex id=this->index(r,c,QModelIndex());
	QModelIndex id0=this->index(0,0,QModelIndex());

	emit dataChanged(id0,id);
	if(this->equationColumns.count() > 0)
		emit equationColumnsSignal();
	else emit done();
}

void MerplyReportTableModel::fillLocalSource(QVector<QJsonDocument> items)
{
	rowsCount = 0;
	cells =  QVector<TableCell>(colmnsCount * items.count());

	foreach(QJsonDocument item,items){
		int row = -1;
		QString dataKey;
		QStringList keys = item.object().keys();
		foreach(QString key,keys){
			if(key.isEmpty())
				continue;
			if(key.toLower().contains("key")){
				dataKey = item.object().value(key).toString();
				}

			else{
				if(item.object().value(key).isArray()){
					if(item.object().value(key).toArray().size() > rowsCount){
						rowsCount = item.object().value(key).toArray().size();
						cells.resize(colmnsCount * rowsCount);
						}
					foreach(QJsonValue value,item.object().value(key).toArray()){
						row++;
						TableCell cell(dataKey,value.toString());
						//<>>>>>>		//
						//	qDebug() << __FILE__ << __LINE__  << row * this->colmnsCount + clmnsHeader.indexOf(key) << clmnsHeader.indexOf(key) << row;
						if(clmnsHeader.indexOf(key) > -1)
							cells[row * this->colmnsCount + clmnsHeader.indexOf(key)] = cell;
						}
					}
				else{
					row++;
					TableCell cell(dataKey,item.object().value(key).toString());
					cells[row * this->colmnsCount + clmnsHeader.indexOf(key)] = cell;
					}
				}

			}
		if(row > rowsCount)
			rowsCount = row;
		//qDebug() << __FILE__ << __LINE__  << item;
		//qDebug() << __FILE__ << __LINE__  << clmnsHeader;

		}

	if(this->equationColumns.count() > 0)
		emit equationColumnsSignal();
	else emit done();
}

void MerplyReportTableModel::fillEquationColumns()
{
	//qDebug() << __FILE__ << __LINE__  << "fillEquationColumns";
	beginResetModel();
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
				//qDebug() << __FILE__ << __LINE__  << eq.toObject();
				if(eq.toObject().value("FirstColumn").toInt() >= 0){
					if(eq.toObject().value("ConditionColumnOne") != QJsonValue::Undefined && eq.toObject().value("ConditionColumnOne").toInt() > -1)
						firstTerm = evalEquationCondition(eq.toObject().value("ConditionOnOne").toInt(),cells[j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt()].getData().trimmed().toDouble(&ok),cells[j * this->colmnsCount + eq.toObject().value("ConditionColumnOne").toInt()].getData().trimmed().toDouble(&ok));

					//qDebug() << __FILE__ << __LINE__  << eq.toObject().value("FirstColumn").toInt() << j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt() << cells[j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt()].getData();
					else {
						if(cells[j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt()].getData().trimmed().isEmpty()){
							if(eq.toObject().value("Operation").toInt() == 0 || eq.toObject().value("Operation").toInt() == 1)
								firstTerm = 0;
							else 	firstTerm = 1;
							ok = true;
							}
						else firstTerm = cells[j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt()].getData().trimmed().toDouble(&ok);
						}
					}
				if(eq.toObject().value("SecondColmn") != QJsonValue::Undefined){
					if(eq.toObject().value("SecondColmn").toInt() >= 0){
						if(eq.toObject().value("ConditionColumnTwo") != QJsonValue::Undefined && eq.toObject().value("ConditionColumnTwo").toInt() > -1)
							secondTerm = evalEquationCondition(eq.toObject().value("ConditionOnTwo").toInt(),cells[j * this->colmnsCount + eq.toObject().value("SecondColmn").toInt()].getData().trimmed().toDouble(&ok),cells[j * this->colmnsCount + eq.toObject().value("ConditionColumnTwo").toInt()].getData().trimmed().toDouble(&ok));
						else{
							if(cells[j * this->colmnsCount + eq.toObject().value("SecondColmn").toInt()].getData().trimmed().isEmpty()){
								if(eq.toObject().value("Operation").toInt() == 0 || eq.toObject().value("Operation").toInt() == 1)
									secondTerm = 0;
								else 	secondTerm = 1;
								ok = true;
								}
							else secondTerm = cells[j * this->colmnsCount + eq.toObject().value("SecondColmn").toInt()].getData().trimmed().toDouble(&ok);
							}
						}
					}
				else if(eq.toObject().value("Number") != QJsonValue::Undefined){
					secondTerm = eq.toObject().value("Number").toString().toDouble();
					//qDebug() << __FILE__ << __LINE__  << "NUMBERRRR" << secondTerm;
					}
				//qDebug() << __FILE__ << __LINE__  << ok << firstTerm << secondTerm;
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
						//qDebug() << __FILE__ << __LINE__  << subTotal << total;
						}
					else total = subTotal;
					}
				}
			//cout << i.key() << ": " << i.value() << endl;
			//qDebug() << __FILE__ << __LINE__  << total;
			TableCell cell("",QString::number(total));
			if(clmnsHeader.indexOf(i.key()) != -1)
				cells[j * this->colmnsCount + clmnsHeader.indexOf(i.key())] =cell;
			}
		}
	endResetModel();
	if(totalColmns.count() > 0 && !addedTotalRow)
		evalTotalRow();

	//qDebug() << __FILE__ << __LINE__  << "ALMOST";
	emit done();

	//int r=this->rowsCount-1;
	//int c=this->colmnsCount-1;
	//QModelIndex id=this->index(r,c,QModelIndex());
	//QModelIndex id0=this->index(0,0,QModelIndex());

	//emit dataChanged(id0,id);

}

double MerplyReportTableModel::evalEquationCondition(int condition, double col1, double col2)
{
	if(condition == 1){
		if(col1 > col2)
			return col1;
		else return col2;
		}
	else if(condition ==2){
		if(col1 < col2)
			return col1;
		else return col2;
		}
	return 0;
}

void MerplyReportTableModel::setValue(const int recNo, const QString paramName, QVariant &paramValue, const int reportPage)
{
	int  columnIndex = clmnsHeader.indexOf(paramName);
	if(columnIndex != -1){
		paramValue = cells[recNo * this->colmnsCount + columnIndex].getData();
		qDebug() << __FILE__ << __LINE__<< paramValue << paramName << reportPage;
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



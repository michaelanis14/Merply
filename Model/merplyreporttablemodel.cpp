#include "merplyreporttablemodel.h"
#include "controller.h"

MerplyReportTableModel::MerplyReportTableModel(QJsonObject strct) :QAbstractTableModel()
{
	rowsCount = 0;
	this->strct = strct;
	this->clmnsHeader = QStringList();
	this->equationColumns.clear();
	this->addedTotalRow = false;
	//colmnsCount = 1;
	if(strct.value("Columns").isArray()){
		this->clmns = (strct.value("Columns").toArray());

		foreach(QJsonValue clmn,strct.value("Columns").toArray()){

			clmnsHeader << clmn.toObject().value("Header").toString();
			if(clmn.toObject().value("Type").toString().compare("Text") == 0)
				Textclmns.insert(clmn.toObject().value("Header").toString(),QJsonObject());
			if(clmn.toObject().value("Type").toString().compare("Equation") == 0){

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
		clmnsHeader = strct.value("clmnsHeader").toVariant().toStringList();
		//qDebug() << clmnsHeader;
		}
	colmnsCount = clmnsHeader.count();
	QObject::connect(this,SIGNAL(equationColumnsSignal()),this,SLOT(fillEquationColumns()));

	//	qDebug() << this->strct;
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

	//qDebug() <<"Edit";

	return cells[index.row() * colmnsCount + index.column()].getData();
}

bool MerplyReportTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (index.isValid() && role == Qt::EditRole) {
		//qDebug() <<value.toString();
		cells[index.row() * colmnsCount + index.column()].setData(value.toString());
		if(equationColumns.count() > 0 )
			fillEquationColumns();
		//if(totalColmns.count() > 0)
		//	evalTotalRow();
		emit dataChanged(index, index);
		return true;
		}
	return false;
}

bool MerplyReportTableModel::insertRows(int row, int count, const QModelIndex& parent)
{
	if(addedTotalRow){
		//qDebug() << "RemoveRowsTotal";
		this->removeRow(this->rowCount(QModelIndex())-1);
		addedTotalRow = false;
		}
	bool state = false;
	beginInsertRows(parent, row, row+count-1);
	rowsCount = row +count;
	cells.resize(colmnsCount * rowsCount);
	//cells[row * this->colmnsCount + 1].setData("dd");
	//qDebug() << cells.size();
	state = true;
	endInsertRows();

	return state;
}


bool MerplyReportTableModel::removeRows(int row, int count, const QModelIndex& parent)
{
	bool state = false;
	beginRemoveRows(parent, row, row+count-1);

	//	qDebug() << cells.size() << row << row * this->colmnsCount;
	for(int j = 0; j< colmnsCount; j++){
		cells.removeAt(row * this->colmnsCount );
		}
	//qDebug() << cells.count();
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
			if(editableColumns.contains(clmnsHeader.at(index.column())) || Textclmns.contains(clmnsHeader.at(index.column())))
				return QAbstractTableModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsEnabled |Qt::ItemIsSelectable;

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
		QJsonObject row;
		for(int j = 0; j< colmnsCount; j++){
			QString data = cells[i * this->colmnsCount + j].getData();
			if(!data.isEmpty())
				row.insert(clmnsHeader.at(j),data);
			}
		if(!row.isEmpty())
			tabel.append(row);
		}
	return tabel;
}

void MerplyReportTableModel::evalTotalRow()
{
	if(addedTotalRow){
		qDebug() << "RemoveTotal";
		this->removeRow(this->rowCount(QModelIndex())-1);
		addedTotalRow = false;

		}
	QVector<double> totals= QVector<double>(totalColmns.size());
	for (int i = 0; i < totalColmns.size(); i++) {
		double total = 0;
		bool ok = false;
		for(int j = 0; j < rowsCount; j++){
			//qDebug() <<"Totalll"<< cells[j * this->colmnsCount + totalColmns.at(i)].getData().trimmed().toDouble(&ok);
			total += cells[j * this->colmnsCount + totalColmns.at(i)].getData().trimmed().toDouble(&ok);
			}
		//qDebug() << i <<
		totals.insert(i,total);
		}

	//qDebug() << total;
	if(!addedTotalRow){
		//qDebug() <<"addddd";
		this->insertRow(this->rowCount(QModelIndex()));
		this->addedTotalRow = true;
		for (int i = 0; i < totalColmns.size();i++) {
			//	qDebug() <<"THE TOTAL"<< totals.at(i) << totals ;
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
		//qDebug() << clmnIndx << clmn << clmnsHeader << rowsCount;
		if(clmnIndx > -1){
			for(int j = 0; j < rowsCount; j++){
			//	qDebug() <<"Totalll"<< cells[j * this->colmnsCount + clmnIndx].getData().trimmed().toDouble(&ok) << ok;
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

void MerplyReportTableModel::fill(QList<QJsonDocument> documents)
{
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
		if(dataKey.isEmpty())
			continue;

		TableCell cell(dataKey,doc.object().value(dataKey).toString());
		if(doc.object().value(dataKey).isArray())
			qDebug() << "ISARRAAYYYY";
		entityRowPointer.insert(doc.object().value(indexedKey).toString(),row);

		//qDebug()<<joinKeys<<indexedKey << row << rowPointer.value(indexedKey)<< row * this->colmnsCount + clmnsHeader.indexOf(dataKey) <<clmnsHeader.indexOf(dataKey)<<dataKey << doc.object().value(dataKey).toString();
		//	qDebug() << row << this->colmnsCount << clmnsHeader.indexOf(dataKey) << dataKey;

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
	else emit done();
	//qDebug()<<"TableModel Fill" << documents;


}

void MerplyReportTableModel::fillText(QJsonArray data)
{

	cells =  QVector<TableCell>(colmnsCount * data.count());
	rowsCount = data.count();
	for(int i = 0; i < data.count(); i++){
		QJsonObject row =  data.at(i).toObject();
		for(int j = 0; j <clmnsHeader.count(); j++){
			QString value = row.value(clmnsHeader.at(j)).toString();
			if(!value.isEmpty()){
				cells[i * this->colmnsCount + j].setData(value);
				}
			}

		}
	if(this->equationColumns.count() > 0)
		emit equationColumnsSignal();
	else emit done();
}

void MerplyReportTableModel::fillIndexTabel( QList<QJsonDocument> items)
{

	int i = 0;
	cells = QVector<TableCell>(colmnsCount * items.count());
	foreach(QJsonDocument item,items){
		QString  key = item.object().value("document_id").toString();
		int j = 0;
		cells[i * this->colmnsCount + j].setId(key);
		foreach(QJsonValue value, item.object().value("Fields").toArray()){
			foreach(QJsonValue viewGroup, value.toArray()){
				QString valueString;
				if(clmnsHeader.count()  > j)
					valueString = Controller::Get()->toString(viewGroup.toObject().value(clmnsHeader.at(j)).toArray());

				cells[i * this->colmnsCount + j].setId(key);
				cells[i * this->colmnsCount + j].setData(valueString);
				j++;
				}
			}
		i++;
		}
	rowsCount = i;

	if(this->equationColumns.count() > 0)
		emit equationColumnsSignal();
	else emit done();
}

void MerplyReportTableModel::fillLocalSource(QList<QJsonDocument> items)
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
					//	qDebug() << row * this->colmnsCount + clmnsHeader.indexOf(key) << clmnsHeader.indexOf(key) << row;
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
		//qDebug() << item;
		//qDebug() << clmnsHeader;

		}

	if(this->equationColumns.count() > 0)
		emit equationColumnsSignal();
	else emit done();
}

void MerplyReportTableModel::fillEquationColumns()
{
	//qDebug() << "fillEquationColumns";
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
			//	qDebug() << eq.toObject();
				if(eq.toObject().value("FirstColumn").toInt() >= 0){
					if(eq.toObject().value("ConditionColumnOne") != QJsonValue::Undefined)
						firstTerm = evalEquationCondition(eq.toObject().value("ConditionOnOne").toInt(),cells[j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt()].getData().trimmed().toDouble(&ok),cells[j * this->colmnsCount + eq.toObject().value("ConditionColumnOne").toInt()].getData().trimmed().toDouble(&ok));

					//qDebug() << eq.toObject().value("FirstColumn").toInt() << j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt() << cells[j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt()].getData();
					else firstTerm = cells[j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt()].getData().trimmed().toDouble(&ok);
					}
				if(eq.toObject().value("SecondColmn") != QJsonValue::Undefined){
					if(eq.toObject().value("SecondColmn").toInt() >= 0){
						if(eq.toObject().value("ConditionColumnTwo") != QJsonValue::Undefined)
							secondTerm = evalEquationCondition(eq.toObject().value("ConditionOnTwo").toInt(),cells[j * this->colmnsCount + eq.toObject().value("SecondColmn").toInt()].getData().trimmed().toDouble(&ok),cells[j * this->colmnsCount + eq.toObject().value("ConditionColumnTwo").toInt()].getData().trimmed().toDouble(&ok));
						else secondTerm = cells[j * this->colmnsCount + eq.toObject().value("SecondColmn").toInt()].getData().trimmed().toDouble(&ok);
						}
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
			if(clmnsHeader.indexOf(i.key()) != -1)
				cells[j * this->colmnsCount + clmnsHeader.indexOf(i.key())] =cell;
			}
		}

	if(totalColmns.count() > 0 && !addedTotalRow)
		evalTotalRow();
	emit done();
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
		qDebug() << paramValue << paramName << reportPage;
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



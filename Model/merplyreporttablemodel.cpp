#include "merplyreporttablemodel.h"
#include "controller.h"

MerplyReportTableModel::MerplyReportTableModel(QJsonObject strct) :QAbstractTableModel()
{
	rowsCount = 0;
	this->strct = strct;
	this->clmnsHeader = QStringList();
	this->equationColumns.clear();
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
	if (!index.isValid() || role != Qt::DisplayRole)
		return QVariant();

	return cells[index.row() * colmnsCount + index.column()].getData();
}

bool MerplyReportTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (index.isValid() && role == Qt::EditRole) {

		cells[index.row() * colmnsCount + index.column()].setData(value.toString());
		if(equationColumns.count() > 0 )
			fillEquationColumns();
		emit dataChanged(index, index);
		return true;
		}
	return false;
}

bool MerplyReportTableModel::insertRows(int row, int count, const QModelIndex& parent)
{
	bool state = false;
	beginInsertRows(parent, row, row+count-1);
	rowsCount = row +count;
	cells.resize(colmnsCount * rowsCount);
	cells[row * this->colmnsCount + 1].setData("dd");

	state = true;
	endInsertRows();

	return state;
}


bool MerplyReportTableModel::removeRows(int row, int count, const QModelIndex& parent)
{
	bool state = false;
	beginRemoveRows(parent, row, row+count-1);

	qDebug() << cells.count() << row << row * this->colmnsCount;
	for(int j = 0; j< colmnsCount; j++){
		cells.removeAt(row * this->colmnsCount );
		}
	qDebug() << cells.count();
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
		if(!equationColumns.contains(clmnsHeader.at(index.column())) && Textclmns.contains(clmnsHeader.at(index.column())))
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
	emit equationColumnsSignal();
}

void MerplyReportTableModel::fillIndexTabel( QList<QJsonDocument> items)
{

	int i = 0;
	cells = QVector<TableCell>(colmnsCount * items.count());
	foreach(QJsonDocument item,items){
		QString  key = item.object().value("document_id").toString();
		int j = 0;
		foreach(QJsonValue value, item.object().value("Fields").toArray()){
			foreach(QJsonValue viewGroup, value.toArray()){
				QString valueString;
				if(clmnsHeader.count()  > j)
					valueString = Controller::Get()->toString(viewGroup.toObject().value(clmnsHeader.at(j)).toArray());
				TableCell cell(key,valueString);
				cells[i * this->colmnsCount + j] = cell;
				j++;
				}
			}
		i++;
		}
	rowsCount = i;
	emit done();
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
				//qDebug() << eq.toObject();
				if(eq.toObject().value("FirstColumn").toInt() >= 0){
					//qDebug() << eq.toObject().value("FirstColumn").toInt() << j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt() << cells[j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt()].getData();
					firstTerm = cells[j * this->colmnsCount + eq.toObject().value("FirstColumn").toInt()].getData().trimmed().toDouble(&ok);
				}if(eq.toObject().value("SecondColmn") != QJsonValue::Undefined){
					if(eq.toObject().value("SecondColmn").toInt() >= 0)
						secondTerm = cells[j * this->colmnsCount + eq.toObject().value("SecondColmn").toInt()].getData().trimmed().toDouble(&ok);
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

	emit done();
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



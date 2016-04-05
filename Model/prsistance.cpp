#include "prsistance.h"




Prsistance::Prsistance(QObject *parent) : QObject(parent)
{

}



bool Prsistance::write(QString table, QList<QString> lines, bool update){
	QJsonObject json = QJsonObject();
	foreach(QString line,lines){
		int splitCount = line.split("->").count();
		if(splitCount > 0){
			if(splitCount == 2){
				json[line.split("->")[0]] = line.split("->")[1];

				}
			else{
				QJsonArray array;

				QJsonArray table = Prsistance::table(line);
				if(!table.isEmpty()){
					//	qDebug() << "table";
					array = table;
					}

				else{
					QJsonArray inArray;
					for(int i = 1;splitCount > i;i++){
						inArray << line.split("->").at(i);
						//qDebug()<<line.split("->")[0]<<line << line.split("->").at(i);
						}
					array << inArray;

					//	qDebug() << line.split("->")[0] <<json.value(line.split("->")[0]);
					if(json.value(line.split("->")[0]) == QJsonValue::Undefined){
						json.insert(line.split("->")[0],array);
						}
					else{
						QJsonArray tempArray;
						if(json.value(line.split("->")[0]).isArray())
							tempArray = json.value(line.split("->")[0]).toArray();

						else {
							{
							QJsonArray temp;
							temp << json.value(line.split("->")[0]).toString();
							tempArray <<temp;
							}
							}
						tempArray << inArray;
						json.insert(line.split("->")[0],tempArray);
						}



					}

				}
			}

		/*		else{
					//qDebug() << "NOT Array"<< line;
					QJsonArray tempArray;
					QJsonArray table = Prsistance::table(line);

					if(!table.isEmpty()){
						tempArray <<table;
						qDebug() << table;
						}

					*/
		}


	//qDebug() << line;


	QJsonDocument doc(json);

	//QString strJson(doc.toJson(QJsonDocument::Indented));
	//qDebug() << strJson;
	if(update)
		return	Database::Get()->updateDoc(doc);
	else return Database::Get()->storeDoc(table,doc);


}

void Prsistance::write(QString table, QString line)
{
	QList<QString> lines;
	lines.append(line);
	Prsistance::write(table,lines,false);
}



QJsonArray Prsistance::table(QString line)
{
	QJsonArray array;
	QString key = line.split("->")[0];
	line.replace(0,QString(line.split("->")[0]).count(),"");
	//qDebug() << line;
	QString s =  QString("->")+QString(key) + QString("->");
	int splitCount = line.split(s).count();
	//qDebug() << s << line.split(s);
	if(line.split(s).count() > 1){
		//array
		for(int i = 0; i < splitCount; i++){
			QJsonArray row;
			//	qDebug() << "QString(line.split(s)[i]).split()" << QString(line.split(s)[i]).split("->");
			for(int j = 0; j < QString(line.split(s)[i]).split("->").count(); j++){
				QString rowString = QString(line.split(s)[i]).split("->")[j];
				if(!(rowString.trimmed().isEmpty())){
					//		qDebug() << rowString.trimmed();
					row <<  rowString.trimmed();
					//	qDebug() << row << array;
					}
				}
			if(!row.isEmpty())
				array << row;
			}

		}
	return array;


}

bool Prsistance::init()
{
	if(Count("ContactType") == -1){
		write("ContactType",QString("Name->Customer"));
		write("ContactType",QString("Name->Supplier"));
		write("ContactType",QString("Name->Customer and Supplier"));
		write("ContactType",QString("Name->Employee"));
		write("ContactType",QString("Name->Other"));
		}

	if(Count("Country") == -1){
		QList<QString> countries;
		countries <<"Afghanistan"<<"Albania"<<"Algeria"<<"American Samoa"<<"Andorra"<<"Angola"<<"Anguilla"<<"Antigua"<<"Argentina"<<"Armenia"<<"Aruba"<<"Australia"<<"Austria"<<"Azerbaijan"<<"Bahamas"<<"Bahrain"<<"Bangladesh"<<"Barbados"<<"Belarus"<<"Belgium"<<"Belize"<<"Benin"<<"Bermuda"<<"Bhutan"<<"Bolivia"<<"Bosnia-Herzegovina"<<"Botswana"<<"Bouvet Island"<<"Brazil"<<"Brunei"<<"Bulgaria"<<"Burkina Faso"<<"Burundi"<<"Cambodia"<<"Cameroon"<<"Canada"<<"Cape Verde"<<"Cayman Islands"<<"Central African Republic"<<"Chad"<<"Chile"<<"China"<<"Christmas Island"<<"Cocos Islands"<<"Colombia"<<"Comoros"<<"Congo"<< "Democratic Republic of the (Zaire)"<<"Congo<< Republic of"<<"Cook Islands"<<"Costa Rica"<<"Croatia"<<"Cuba"<<"Cyprus"<<"Czech Republic"<<"Denmark"<<"Djibouti"<<"Dominica"<<"Dominican Republic"<<"Ecuador"<<"Egypt"<<"El Salvador"<<"Equatorial Guinea"<<"Eritrea"<<"Estonia"<<"Ethiopia"<<"Falkland Islands"<<"Faroe Islands"<<"Fiji"<<"Finland"<<"France"<<"French Guiana"<<"Gabon"<<"Gambia"<<"Georgia"<<"Germany"<<"Ghana"<<"Gibraltar"<<"Greece"<<"Greenland"<<"Grenada"<<"Guadeloupe (French)"<<"Guam (USA)"<<"Guatemala"<<"Guinea"<<"Guinea Bissau"<<"Guyana"<<"Haiti"<<"Holy See"<<"Honduras"<<"Hong Kong"<<"Hungary"<<"Iceland"<<"India"<<"Indonesia"<<"Iran"<<"Iraq"<<"Ireland"<<"Israel"<<"Italy"<<"Ivory Coast (Cote D`Ivoire)"<<"Jamaica"<<"Japan"<<"Jordan"<<"Kazakhstan"<<"Kenya"<<"Kiribati"<<"Kuwait"<<"Kyrgyzstan"<<"Laos"<<"Latvia"<<"Lebanon"<<"Lesotho"<<"Liberia"<<"Libya"<<"Liechtenstein"<<"Lithuania"<<"Luxembourg"<<"Macau"<<"Macedonia"<<"Madagascar"<<"Malawi"<<"Malaysia"<<"Maldives"<<"Mali"<<"Malta"<<"Marshall Islands"<<"Martinique (French)"<<"Mauritania"<<"Mauritius"<<"Mayotte"<<"Mexico"<<"Micronesia"<<"Moldova"<<"Monaco"<<"Mongolia"<<"Montenegro"<<"Montserrat"<<"Morocco"<<"Mozambique"<<"Myanmar"<<"Namibia"<<"Nauru"<<"Nepal"<<"Netherlands"<<"Netherlands Antilles"<<"New Caledonia (French)"<<"New Zealand"<<"Nicaragua"<<"Niger"<<"Nigeria"<<"Niue"<<"Norfolk Island"<<"North Korea"<<"Northern Mariana Islands"<<"Norway"<<"Oman"<<"Pakistan"<<"Palau"<<"Palestine"<<"Panama"<<"Papua New Guinea"<<"Paraguay"<<"Peru"<<"Philippines"<<"Pitcairn Island"<<"Poland"<<"Polynesia (French)"<<"Portugal"<<"Puerto Rico"<<"Qatar"<<"Reunion"<<"Romania"<<"Russia"<<"Rwanda"<<"Saint Helena"<<"Saint Kitts and Nevis"<<"Saint Lucia"<<"Saint Pierre and Miquelon"<<"Saint Vincent and Grenadines"<<"Samoa"<<"San Marino"<<"Sao Tome and Principe"<<"Saudi Arabia"<<"Senegal"<<"Serbia"<<"Seychelles"<<"Sierra Leone"<<"Singapore"<<"Slovakia"<<"Slovenia"<<"Solomon Islands"<<"Somalia"<<"South Africa"<<"South Georgia and South Sandwich Islands"<<"South Korea"<<"South Sudan"<<"Spain"<<"Sri Lanka"<<"Sudan"<<"Suriname"<<"Svalbard and Jan Mayen Islands"<<"Swaziland"<<"Sweden"<<"Switzerland"<<"Syria"<<"Taiwan"<<"Tajikistan"<<"Tanzania"<<"Thailand"<<"Timor-Leste (East Timor)"<<"Togo"<<"Tokelau"<<"Tonga"<<"Trinidad and Tobago"<<"Tunisia"<<"Turkey"<<"Turkmenistan"<<"Turks and Caicos Islands"<<"Tuvalu"<<"Uganda"<<"Ukraine"<<"United Arab Emirates"<<"United Kingdom"<<"United States"<<"Uruguay"<<"Uzbekistan"<<"Vanuatu"<<"Venezuela"<<"Vietnam"<<"Virgin Islands"<<"Wallis and Futuna Islands"<<"Yemen"<<"Zambia"<<"Zimbabwe";
		for(int i = 0;i < countries.count(); i++){
			write("Country",QString("Name:"+countries.at(i).trimmed()));
			}
		}
	//if()
	return true;
}



QList<QString> Prsistance::ComboxList(QString table, QString select,QString condition)
{

	QList<QString> list;

	QString where;
	if(!condition.isEmpty())
		where = QString("AND "+condition);
	QString query = "SELECT "+select.trimmed()+" AS `"+select.trimmed()+"`  FROM  `"+QString(DATABASE)+"` WHERE META( `"+QString(DATABASE)+"`).id LIKE \""+table+"::%\" "+where;
	//qDebug() << query;
	Database::Get()->query(query);
	foreach (const QJsonDocument & value, Database::Get()->getArray()){
		//qDebug() << select.trimmed() << value.object().keys();
		QString valueString = value.object().value(select.trimmed()).toString();
		if(!valueString.isEmpty())
			list.append( value.object().value(select.trimmed()).toString());
		}
	QStringList Stringlist (list);
	Stringlist.sort();

	return Stringlist;
}

int Prsistance::Count(const QString table)
{

	if(Database::Get()->query("SELECT COUNT(*) AS count  FROM  "+QString(DATABASE)+" WHERE META( "+QString(DATABASE)+").id LIKE \""+table+"::%\"")){
		//qDebug() << Database::Get()->getArray().first().object().value("count").toInt();
		if(!Database::Get()->getArray().isEmpty() && Database::Get()->getArray().count() > 0){
			return Database::Get()->getArray().first().object().value("count").toInt();
			}
		else{
		//	qDebug() <<"-1";
			return -1;
			}
		}
	return -1;
}

QList<QJsonDocument> Prsistance::GetALL(const QString entity, const QString condition)
{
	QString where;
	if(!condition.isEmpty())
		where = QString("AND "+condition);
	QString query = QString("SELECT `"+QString(DATABASE)+"`.*,meta("+QString(DATABASE)+").id AS `document_id` FROM `"+QString(DATABASE)+"` WHERE META( `"+QString(DATABASE)+"`).id LIKE '"+entity+"::%' "+where);
	//	qDebug() << query <<"===";
	if(Database::Get()->query(query))
		//qDebug() << Database::Get()->getArray().first().object().value("count").toInt();
		return Database::Get()->getArray();
	return QList<QJsonDocument>();
}



bool Prsistance::Select(const QString query)
{
	QStringList tableColumn =  query.split(".");
	if(tableColumn.count() > 0){
		if(Database::Get()->query("S"))
			return true;
		}

	return false;
}

QString Prsistance::GetDatabaseName()
{
	return QString(DATABASE);
}

#include "CGBSpielListModel.h"


int CGBSpielListModel::rowCount(const QModelIndex& parent) const {
	return this->Spieleliste.count();
}


int CGBSpielListModel::columnCount(const QModelIndex& parent) const {
	/* Tabelle immer 2 Spalten */
	return 3;
}


QVariant CGBSpielListModel::data(const QModelIndex& index, int role) const {
	if(index.isValid()==false) return QVariant();
	if(index.row()>=Spieleliste.count()) return QVariant();
	if(index.column()>=3) return QVariant();
	//if(role==Qt::DecorationRole && index.column()==STATUS) return QIcon(":/img/gnuboy.png");
	//if(role!=Qt::DisplayRole && index.column()!=STATUS) return QVariant();
	
	/* Zeile ist klar. Spalte ist wie folgt definiert:
		0 - Name	(String)
		1 - ROM-File	(String)
	*/
	switch(index.column()) {
		case STATUS:
			if(role==Qt::DecorationRole) {
				if(this->Spieleliste[index.row()].ROMExists()==false) {
					return QIcon(":/img/x.png");
				}
				else if(this->Spieleliste[index.row()].getType()==CGBSpiel::GAMEBOY) {
					return QIcon(":/img/gb.png");
				}
				else if(this->Spieleliste[index.row()].getType()==CGBSpiel::GAMEBOYCOLOR) {
					return QIcon(":/img/gbc.png");
				}
				else 	if(this->Spieleliste[index.row()].getType()==CGBSpiel::GAMEBOYADVANCE) {
					return QIcon(":/img/gba.png");
				}
				else return QIcon(":/img/x.png");
			}
			else if(role==Qt::ToolTipRole) {
				if(this->Spieleliste[index.row()].ROMExists()==false) {
					return trUtf8("ROM-Datei nicht gefunden");
				}
				else if(this->Spieleliste[index.row()].getType()==CGBSpiel::GAMEBOY) {
					return trUtf8("GameBoy-ROM");
				}
				else if(this->Spieleliste[index.row()].getType()==CGBSpiel::GAMEBOYCOLOR) {
					return trUtf8("Gamboy Color-ROM");
				}
				else 	if(this->Spieleliste[index.row()].getType()==CGBSpiel::GAMEBOYADVANCE) {
					return trUtf8("Gameboy Advance-ROM");
				}
				else return trUtf8("Ungültige ROM-Datei");
			}
			break;
		case NAME: // Name
			if(role==Qt::DisplayRole) {
				return this->Spieleliste[index.row()].getName();
			}
			break;
		case ROMFILE: // ROM-File
			if(role==Qt::DisplayRole) {
				return this->Spieleliste[index.row()].getFilename().replace(QDir::homePath(), "~");
			}
			break;
	}
	return QVariant();
}


QVariant CGBSpielListModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if(role!=Qt::DisplayRole) return QVariant();
	if(orientation==Qt::Horizontal)
		switch(section) {
			case STATUS:
				return "";
				break;
			case NAME: // Name
				return trUtf8("Spiel");
				break;
			case ROMFILE: // Dateiname
				return trUtf8("ROM-Datei");
				break;
		}
	else
		return "";
}


bool CGBSpielListModel::removeRows(int position, int rows, const QModelIndex &parent) {
	int row;
	
	beginRemoveRows(QModelIndex(), position, position+rows-1);
	for (row=0;row<rows;++row) {
		Spieleliste.removeAt(position);
	}
	endRemoveRows();
	
	return true;
}


void CGBSpielListModel::addItem(const CGBSpiel& Spiel) {
	beginInsertRows(QModelIndex(), Spieleliste.count(), Spieleliste.count());
	Spieleliste.append(Spiel);
	endInsertRows();
	
	emit dataChanged(QModelIndex(), QModelIndex());
}


CGBSpiel& CGBSpielListModel::getItem(const QModelIndex& Index) {
	return Spieleliste[Index.row()]; // return non-constant reference to item in list
}


bool CGBSpielListModel::toXml(const QString& Filename) {
	QList<CGBSpiel>::const_iterator Iter;
	QFile *XmlFile=new QFile(Filename);
	
	if(XmlFile->open(QIODevice::WriteOnly)==true) {
		QXmlStreamWriter XmlWriter(XmlFile);
		XmlWriter.setAutoFormatting(true);
		XmlWriter.setAutoFormattingIndent(6);
		XmlWriter.writeStartDocument("1.0");
		// Spieleliste serialisieren
		XmlWriter.writeStartElement("gamelist");
		for(Iter=Spieleliste.begin();Iter!=Spieleliste.end();++Iter) {
			
			XmlWriter.writeStartElement("game");
			XmlWriter.writeAttribute("name", (*Iter).getName());
			XmlWriter.writeAttribute("romfile", (*Iter).getFilename());
			(*Iter).toXml(XmlWriter);
			XmlWriter.writeEndElement();
		}
		XmlWriter.writeEndElement();
		XmlWriter.writeEndDocument();
		XmlFile->close();
	}
	else return false;
	
	return true;
}


bool CGBSpielListModel::fromXml(const QString& Filename) {
	CGBSpiel *Spiel=0;
	
	if(!QFile::exists(Filename)) return false;
	QFile *XmlFile=new QFile(Filename);
	if(!XmlFile->open(QIODevice::ReadOnly)) return false;
	
	QXmlStreamReader XmlReader(XmlFile);
	Spieleliste.clear();
	
	// Dokument muss mit dem Dokumente-Starttag beginnen ^^
	XmlReader.readNext();
	if(!XmlReader.isStartDocument()) {
		XmlFile->close();
		return false;
	}
	// Danach beginnt die Spieleliste
	XmlReader.readNext();
	if(!XmlReader.isStartElement() || XmlReader.qualifiedName().toString()!="gamelist") {
		XmlFile->close();
		return false;
	}
	
	// Alle Listenelemente einlesen
	// Dieser kleine Miniparser liest so viele Daten wie möglich ein, ungeachtet, ob sie valide sind.
	while(!XmlReader.atEnd()) {
		XmlReader.readNext();
		
		if(XmlReader.isStartElement() && XmlReader.qualifiedName().toString()=="game") { // Start eines <game />
			Spiel=new CGBSpiel(XmlReader.attributes().value("romfile").toString());
			Spiel->setName(XmlReader.attributes().value("name").toString());
			Spiel->fromXml(XmlReader);
		}
		else if((XmlReader.isEndElement() && XmlReader.qualifiedName().toString()=="game")) {
			this->Spieleliste.append(*Spiel);
			delete Spiel;
		}
		else if((XmlReader.isEndElement() && XmlReader.qualifiedName().toString()=="gamelist") || XmlReader.isEndDocument()) { // Dokumentende
			break;
		}
	}

	XmlFile->close();
	return true;
}

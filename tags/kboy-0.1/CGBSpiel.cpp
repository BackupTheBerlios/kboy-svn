#include "CGBSpiel.h"

CGBSpiel::CGBSpiel(QString Filename) {
	this->setFilename(Filename);
	prOptions=0;
	
	// Standardmäßig GnuBoy-Optionen vergeben
	changeEmulator(CAbstraktOptions::GNUBOY);
}


CGBSpiel::CGBSpiel(QString Filename, CAbstraktOptions::E_Emulator EmuType) {
	this->setFilename(Filename);
	prOptions=0;
	changeEmulator(EmuType);
}


CGBSpiel::CGBSpiel(const CGBSpiel& Other) {
	this->prFilename=Other.prFilename;
	this->prName=Other.prName;

	// Optionen kopieren
	switch(Other.prOptions->getEmulator()) {
		case CAbstraktOptions::GNUBOY:
			prOptions=new CGnuboyOptions();
			*(CGnuboyOptions*)prOptions=*((CGnuboyOptions*)Other.prOptions);
			break;
		case CAbstraktOptions::VBA:
			prOptions=new CVBAOptions();
			*(CVBAOptions*)prOptions=*((CVBAOptions*)Other.prOptions);
			break;
	}
	
}


CGBSpiel::~CGBSpiel() {
	if(prOptions!=0) {
		if(prOptions->getEmulator()==CAbstraktOptions::GNUBOY) {
			delete (CGnuboyOptions*)prOptions;
		}
		else {
			delete (CVBAOptions*)prOptions;
		}
	}
}


QString CGBSpiel::getName()  const {
	return prName;
}

void CGBSpiel::setName(const QString& Val) {
	prName=Val;
}

QString CGBSpiel::getFilename()  const {
	return prFilename;
}

void CGBSpiel::setFilename(const QString& Val) {
	prFilename=Val;
	prName=this->getIdentifier();
}

QString CGBSpiel::getIdentifier() const {
	char buffer[16+1];
	QFile BinFile(prFilename);
	QString FailedString("[InvalidROM]"); // Wird zurückgegeben, wenn die Datei nicht ausgewertet werden kann
	
	if(getType()==GAMEBOYADVANCE) return "GBA - NYI"; // TODO
	
	if(!this->ROMExists()) return FailedString;
	if(!BinFile.open(QIODevice::ReadOnly)) return FailedString;
	// Zum Beginn des Namens gehen (erstes Zeichen bei 0x134)
	if(!BinFile.seek(0x134)) {
		BinFile.close();
		return FailedString;
	}
	// Der Name ist maximal 16 Byte lang, falls kürzer, wird mit 0 aufgefüllt
	buffer[16]='\0';
	if(BinFile.read(buffer, 16)==-1) {
		BinFile.close();
		return FailedString;
	}
	BinFile.close();
	return QString(buffer);
}

enum CGBSpiel::EGBTYPE CGBSpiel::getType() const {
	QFileInfo fi(prFilename);
	if(fi.suffix()=="gb") return GAMEBOY;
	else if(fi.suffix()=="gbc") return GAMEBOYCOLOR;
	else if(fi.suffix()=="gba") return GAMEBOYADVANCE;
	else return INVALID;
}

bool CGBSpiel::ROMExists() const {
	return QFile::exists(prFilename);
}


int CGBSpiel::fromXml(QXmlStreamReader& XmlReader) {
	/* Auslesen der Optionen starten */
	while(!XmlReader.atEnd()) {
		XmlReader.readNext();
			
		if(XmlReader.isStartElement() && XmlReader.qualifiedName().toString()=="options") {
			// Emulatortyp herausfinden
			if(XmlReader.attributes().value("emutype").toString()=="gnuboy") {
				this->changeEmulator(CAbstraktOptions::GNUBOY);
				((CGnuboyOptions*)this->prOptions)->fromXml(XmlReader); // Optionen einlesen
			}
			else if(XmlReader.attributes().value("emutype").toString()=="vba") {
				this->changeEmulator(CAbstraktOptions::VBA);
				((CVBAOptions*)this->prOptions)->fromXml(XmlReader); // Optionen einlesen
			}
			else return 1; // Abbruch
			break;
		}
	}
	return 0;
}



void CGBSpiel::toXml(QXmlStreamWriter& XmlWriter) const {
	// Optionen schreiben
	XmlWriter.writeStartElement("options");
	// Attribut "emutype"
	switch(prOptions->getEmulator()) {
		case CAbstraktOptions::GNUBOY:
			XmlWriter.writeAttribute("emutype", "gnuboy");
			// Alle Optionen schreiben
			((CGnuboyOptions*)prOptions)->toXml(XmlWriter);
			break;
		case CAbstraktOptions::VBA:
			XmlWriter.writeAttribute("emutype", "vba");
			// Alle Optionen schreiben
			((CVBAOptions*)prOptions)->toXml(XmlWriter);
			break;
	}
	
	XmlWriter.writeEndElement(); // options
}



void CGBSpiel::changeEmulator(CAbstraktOptions::E_Emulator EmuType) {
	if(prOptions!=0) {
		if(prOptions->getEmulator()==CAbstraktOptions::GNUBOY) {
			delete (CGnuboyOptions*)prOptions;
		}
		else {
			delete (CVBAOptions*)prOptions;
		}
	}
	
	switch(EmuType) {
		case CAbstraktOptions::GNUBOY:
			prOptions=new CGnuboyOptions();
			break;
		case CAbstraktOptions::VBA:
			prOptions=new CVBAOptions();
			break;
	}
}


CAbstraktOptions* CGBSpiel::getOptions() {
	return prOptions;
}


QString CGBSpiel::getEmuCommand() const {
	return prOptions->getEmuCommand();
}

QStringList CGBSpiel::getCommandLine() const {
	// Kommandozeile ermitteln
	if(prOptions->getEmulator()==CAbstraktOptions::GNUBOY) {
		return ((CGnuboyOptions*)prOptions)->getCommandArgs();
		
	}
	else {
		return ((CVBAOptions*)prOptions)->getCommandArgs();
	}
}

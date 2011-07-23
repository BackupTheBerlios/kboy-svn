#include "CVBAOptions.h"


CVBAOptions::CVBAOptions() {
	// Standardwerte
	setEmulator(CAbstraktOptions::VBA);
	setEmuCommand("visualboyadvance");
	setScale(1);
	setFullscreen(true);
}

void CVBAOptions::setScale(const unsigned short Val) {
	if(Val>4) prScale=4;
	else prScale=Val;
}

unsigned short CVBAOptions::getScale() const {
	return prScale;
}



int CVBAOptions::fromXml(QXmlStreamReader& XmlReader) {
	/* Emulator-spezifische Optionen einlesen */
	while(!XmlReader.atEnd()) {
		XmlReader.readNext();
		
		if(XmlReader.isStartElement()) {
			if(XmlReader.qualifiedName().toString()=="commandline") {
				// Befehlszeile
				this->setEmuCommand(XmlReader.readElementText());
			}
			else if(XmlReader.qualifiedName().toString()=="fullscreen") {
				//Vollbildmodus
				if(XmlReader.readElementText()=="true") this->setFullscreen(true);
				else this->setFullscreen(false);
			}
			else if(XmlReader.qualifiedName().toString()=="scale") {
				//Fenstervergrößerung
				this->setScale(XmlReader.readElementText().toShort());
			}
		}
		else if(XmlReader.isEndElement() && XmlReader.qualifiedName().toString()=="options") {
			/* Abbruch, wenn Optionen zu Ende sind */
			break; // Ende der Optionenliste erreicht
		}
	}
	return 0;
}


void CVBAOptions::toXml(QXmlStreamWriter& XmlWriter) {
	// Kommandozeile
	XmlWriter.writeTextElement("commandline", getEmuCommand());
	// Vollbildmodus
	if(true==this->getFullscreen()) {
		XmlWriter.writeTextElement("fullscreen", "true");
	}
	else {
		XmlWriter.writeTextElement("fullscreen", "false");
	}
	// Fenster-Scaling
	XmlWriter.writeTextElement("scale", QString::number(this->getScale()));
}



QStringList CVBAOptions::getCommandArgs() {
	QStringList Args;
	
	if(getFullscreen()==true) Args.append("-F");
	if(getScale()>1) Args.append("-"+QString::number(getScale()));
	
	return Args;
}

#include "CGnuboyOptions.h"

CGnuboyOptions::CGnuboyOptions() {
	// Standardwerte festlegen
	setEmulator(CAbstraktOptions::GNUBOY);
	setEmuCommand("sdlgnuboy");
	setSound(false);
	setFullscreen(true);
	setHardwareAccl(true);
	setScale(1);
}


void CGnuboyOptions::setSound(const bool Val) {
	prSound=Val;
}

bool CGnuboyOptions::getSound() const {
	return prSound;
}


void CGnuboyOptions::setHardwareAccl(const bool Val) {
	prHardwareAccl=Val;
}

bool CGnuboyOptions::getHardwareAccl() const {
	return prHardwareAccl;
}


void CGnuboyOptions::setScale(const unsigned short Val) {
	prScale=Val;
}

unsigned short CGnuboyOptions::getScale() const {
	return prScale;
}


int CGnuboyOptions::fromXml(QXmlStreamReader& XmlReader) {
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
			else if(XmlReader.qualifiedName().toString()=="sound") {
				//Sound
				if(XmlReader.readElementText()=="true") this->setSound(true);
				else this->setSound(false);
			}
			else if(XmlReader.qualifiedName().toString()=="hardwareaccl") {
				//Hardwarebeschleunigung
				if(XmlReader.readElementText()=="true") this->setHardwareAccl(true);
				else this->setHardwareAccl(false);
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


void CGnuboyOptions::toXml(QXmlStreamWriter& XmlWriter) {
	// Kommandozeile
	XmlWriter.writeTextElement("commandline", getEmuCommand());
	// Vollbildmodus
	if(true==this->getFullscreen()) {
		XmlWriter.writeTextElement("fullscreen", "true");
	}
	else {
		XmlWriter.writeTextElement("fullscreen", "false");
	}
	// Sound
	if(true==this->getSound()) {
		XmlWriter.writeTextElement("sound", "true");
	}
	else {
		XmlWriter.writeTextElement("sound", "false");
	}
	// Hardware-Beschleunigung
	if(true==this->getHardwareAccl()) {
		XmlWriter.writeTextElement("hardwareaccl", "true");
	}
	else {
		XmlWriter.writeTextElement("hardwareaccl", "false");
	}
	// Fenster-Scaling
	XmlWriter.writeTextElement("scale", QString::number(this->getScale()));
}



QStringList CGnuboyOptions::getCommandArgs() {
	QStringList Args;
	
	if(getFullscreen()==false) Args.append("--no-fullscreen");
	if(getSound()==false) Args.append("--no-sound");
	if(getHardwareAccl()==false) {
		Args.append("--no-yuv");
		if(getScale()>1) Args.append("--density="+QString::number(getScale()));
	}
	if(getScale()>1) Args.append("--scale="+QString::number(getScale()));
	
	return Args;
}

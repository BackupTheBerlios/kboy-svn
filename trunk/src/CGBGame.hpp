#ifndef H_CGBSPIEL
#define H_CGBSPIEL

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QXmlStreamReader>

#include "CGnuboyOptions.h"
#include "CVBAOptions.h"

/** Repräsentiert ein zu emulierendes Gameboy-Spiel. */
class CGBSpiel {
 public:
	enum EGBTYPE { INVALID, GAMEBOY, GAMEBOYCOLOR, GAMEBOYADVANCE };
	
	CGBSpiel(QString Filename);
	CGBSpiel(QString Filename, CAbstraktOptions::E_Emulator EmuType);
	
	CGBSpiel(const CGBSpiel& Other);
	
	~CGBSpiel();
	
	QString getName() const;
	void setName(const QString& Val);
	
	QString getIdentifier() const;
	
	QString getFilename() const;
	void setFilename(const QString& Val);
	
	enum CGBSpiel::EGBTYPE getType() const;
	
	bool ROMExists() const;
	
	QStringList getCommandLine() const;
	QString getEmuCommand() const;
	
	void changeEmulator(CAbstraktOptions::E_Emulator EmuType);
	
	CAbstraktOptions* getOptions();
	
	int fromXml(QXmlStreamReader& XmlReader);
	void toXml(QXmlStreamWriter& XmlWriter) const;


 private:
	QString prFilename;
	QString prName;
	
	CAbstraktOptions *prOptions;
};

#endif

#ifndef H_ACBSTRAKTOPTIONS
#define H_ACBSTRAKTOPTIONS

#include <QXmlStreamReader>
#include <QStringList>


class CAbstraktOptions {
 public:
 	CAbstraktOptions();
 
	enum E_Emulator { GNUBOY=0, VBA=1 };
	
	enum CAbstraktOptions::E_Emulator getEmulator();
	void setEmulator(enum CAbstraktOptions::E_Emulator);
	
	bool getFullscreen() const;
	void setFullscreen(const bool Val);
	
	QString getEmuCommand();
	void setEmuCommand(const QString& Val);
	
	virtual int fromXml(QXmlStreamReader& XmlReader)=0;
	virtual void toXml(QXmlStreamWriter& XmlWriter)=0;
	
	virtual QStringList getCommandArgs()=0;


 private:
	bool prFullscreen;
	enum E_Emulator prEmuType;
	QString prEmuCommand;
};

#endif

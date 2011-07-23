#ifndef H_CGNUBOYOPTIONS
#define H_CGNUBOYOPTIONS

#include <QStringList>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include "CAbstraktOptions.h"

class CGnuboyOptions : public CAbstraktOptions {
 private:
	bool prSound;
	bool prHardwareAccl;
	unsigned short prScale;
	
 public:
	CGnuboyOptions();
	
	void setSound(const bool Val);
	bool getSound() const;
	
	void setHardwareAccl(const bool Val);
	bool getHardwareAccl() const;
	
	void setScale(const unsigned short Val);
	unsigned short getScale() const;
	
	virtual int fromXml(QXmlStreamReader& XmlReader);
	virtual void toXml(QXmlStreamWriter& XmlWriter);
	
	virtual QStringList getCommandArgs();
};

#endif

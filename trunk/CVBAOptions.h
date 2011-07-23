#ifndef H_CVBAOPTIONS
#define H_CVBAOPTIONS

#include <QStringList>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include "CAbstraktOptions.h"

class CVBAOptions : public CAbstraktOptions {
 private:
	unsigned short prScale;
	
 public:
	CVBAOptions();
	
	void setScale(const unsigned short Val);
	unsigned short getScale() const;
	
	virtual int fromXml(QXmlStreamReader& XmlReader);
	virtual void toXml(QXmlStreamWriter& XmlWriter);
	
	virtual QStringList getCommandArgs();
};

#endif

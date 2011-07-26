#ifndef H_CVBAOPTIONS
#define H_CVBAOPTIONS

#include <QStringList>
#include <QXmlStreamWriter>


#include "emulators/CAbstractEmulatorOptions.hpp"

class CVBAOptions : public CAbstractEmulatorOptions {
private:
   unsigned short m_Scale;
   QString m_EmuCommand;
   bool m_Fullscreen;


public:
   CVBAOptions();

   void setScale(const unsigned short Val);
   unsigned short getScale() const;

   void setFullscreen(bool Val);
   bool getFullscreen() const;

   QStringList getCommandArgs() const;


   const QString& getEmuCommand() const;
   void setEmuCommand(const QString& command);


   bool isRomSupported(const QString& Filename) const;

   std::auto_ptr<CAbstractEmulatorOptions> clone() const;


   virtual QWidget* getOptionsWidget();

};

#endif



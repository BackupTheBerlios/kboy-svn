#ifndef H_CGNUBOYOPTIONS
#define H_CGNUBOYOPTIONS


#include <QString>
#include <QStringList>
#include <QXmlStreamWriter>


#include "emulators/CAbstractEmulatorOptions.hpp"

class CGnuboyOptions : public CAbstractEmulatorOptions {
private:
   bool m_Fullscreen;
   bool m_Sound;
   bool m_HardwareAccl;
   unsigned short m_Scale;
   QString m_EmuCommand;

public:
   CGnuboyOptions();

   bool getFullscreen() const;
   void setFullscreen(const bool fullscreen);

   void setSound(const bool sound);
   bool getSound() const;

   void setHardwareAccl(const bool accl);
   bool getHardwareAccl() const;

   void setScale(const unsigned short scaleVal);
   unsigned short getScale() const;

   const QString& getEmuCommand() const;
   void setEmuCommand(const QString& command);

   bool isRomSupported(const QString& Filename) const;

   std::auto_ptr<CAbstractEmulatorOptions> clone() const;

   virtual QStringList getCommandArgs() const;
};

#endif


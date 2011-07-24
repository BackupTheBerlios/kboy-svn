#ifndef H_CABSTRACTEMULATOROPTIONS
#define H_CABSTRACTEMULATOROPTIONS

#include <memory>

#include <QXmlStreamReader>
#include <QStringList>


class CAbstractEmulatorOptions {
public:

   enum E_Emulator { GNUBOY=0, VBA=1 };

   CAbstractEmulatorOptions();

   virtual ~CAbstractEmulatorOptions() {}


   virtual enum CAbstractEmulatorOptions::E_Emulator getEmulator() const;
   virtual void setEmulator(enum CAbstractEmulatorOptions::E_Emulator);

   virtual const QString& getEmuCommand() const = 0;
   virtual void setEmuCommand(const QString& command) = 0;



   virtual QStringList getCommandArgs() const = 0;

   virtual bool isRomSupported(const QString& Filename) const = 0;

   virtual std::auto_ptr<CAbstractEmulatorOptions> clone() const = 0;

private:
   CAbstractEmulatorOptions::E_Emulator m_Emulator;
};

#endif

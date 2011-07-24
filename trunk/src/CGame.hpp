#ifndef H_CGAME
#define H_CGAME

#include <memory>

#include <QString>
#include <QFile>
#include <QFileInfo>

#include "emulators/CAbstractEmulatorOptions.hpp"

/** Repräsentiert ein zu emulierendes Gameboy-Spiel.
 * \todo Use auto-pointer for "obtions" pointer?
 */
class CGame {
public:
   enum E_GBType { INVALID, GAMEBOY, GAMEBOYCOLOR, GAMEBOYADVANCE };

   CGame(QString Filename);
   CGame(QString Filename, CAbstractEmulatorOptions::E_Emulator emulator);

   CGame(const CGame& other);

   ~CGame();

   const QString& getName() const;
   void setName(const QString& name);

   QString getIdentifier() const;

   const QString& getFilename() const;
   void setFilename(const QString& filename);

   enum CGame::E_GBType getType() const;

   bool ROMExists() const;

#if 0
   QStringList getCommandLine() const;
   QString getEmuCommand() const;
#endif
   void changeEmulator(CAbstractEmulatorOptions::E_Emulator EmuType);

   const CAbstractEmulatorOptions& getOptions() const;
   void setOptions(std::auto_ptr<CAbstractEmulatorOptions> options);

   CGame& operator=(const CGame& other);

private:
   QString m_Filename;
   QString m_GameTitle;
   std::auto_ptr<CAbstractEmulatorOptions> m_Options;
};

#endif

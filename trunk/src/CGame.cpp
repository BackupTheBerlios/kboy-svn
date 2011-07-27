#include "CGame.hpp"


CGame::CGame(QString filename) {
   this->setFilename(filename);

   // Set Gnuboy to be the standard
   changeEmulator(CAbstractEmulatorOptions::GNUBOY);
}


CGame::CGame(QString filename, CAbstractEmulatorOptions::E_Emulator emulator) {
   this->setFilename(filename);
   changeEmulator(emulator);
}


CGame::CGame(const CGame& other) {
   this->m_Filename=other.m_Filename;
   this->m_GameTitle=other.m_GameTitle;

   // clone the options object
   m_Options=other.m_Options->clone();
}


const QString& CGame::getName() const {
   return m_GameTitle;
}

void CGame::setName(const QString& name) {
   m_GameTitle=name;
}

const QString& CGame::getFilename()  const {
   return m_Filename;
}

void CGame::setFilename(const QString& filename) {
   m_Filename=filename;
   m_GameTitle=this->getIdentifier();
}

QString CGame::getIdentifier() const {
   // Try too get the game title from the ROM file...
   char buffer[16+1];
   QFile BinFile(m_Filename);
   QString FailedString("[InvalidROM]"); // Will be returned when we cannot obtain the game title form the file

   if (getType()==GAMEBOYADVANCE) return "GBA - NYI"; // TODO: Add support for GBA

   if (!this->romExists()) return FailedString;
   if (!BinFile.open(QIODevice::ReadOnly)) return FailedString;
   // Seek to the begin of the name string (first character is at 0x134)
   if (!BinFile.seek(0x134)) {
      BinFile.close();
      return FailedString;
   }
   // The maximum name length is 16 byte. If it's shorter it is filled with \0.
   buffer[16]='\0';
   if (BinFile.read(buffer, 16)==-1) {
      BinFile.close();
      return FailedString;
   }
   BinFile.close();
   return QString(buffer);
}

enum CGame::E_GBType CGame::getType() const {
   QFileInfo fi(m_Filename);
   if (fi.suffix()=="gb") return GAMEBOY;
   else if (fi.suffix()=="gbc") return GAMEBOYCOLOR;
   else if (fi.suffix()=="gba") return GAMEBOYADVANCE;
   else return INVALID;
}

bool CGame::romExists() const {
   return QFile::exists(m_Filename);
}



void CGame::changeEmulator(CAbstractEmulatorOptions::E_Emulator emulator) {
      m_Options=CAbstractEmulatorOptions::createEmulatorOptions(emulator);
}


CAbstractEmulatorOptions& CGame::getOptions() {
   return *m_Options;
}

const CAbstractEmulatorOptions& CGame::getOptions() const {
   return *m_Options;
}

void CGame::setOptions(std::auto_ptr<CAbstractEmulatorOptions> options) {
   m_Options=options;
}


CGame& CGame::operator=(const CGame& other) {
   this->m_Filename=other.m_Filename;
   this->m_GameTitle=other.m_GameTitle;

   // clone the options object
   m_Options=other.m_Options->clone();
}


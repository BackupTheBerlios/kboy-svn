/*
 * KBoy is a graphical user interface for managing a collection of Gameboy
 * ROM files and assigning emulator configuration information to them.
 *
 * Copyright (C) 2011  Thomas Wesenigk <thomas_aus_dresden@web.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef H_CGAME
#define H_CGAME

#include <memory>

#include <QString>
#include <QFile>
#include <QFileInfo>

#include "emulators/CAbstractEmulatorOptions.hpp"

/** This class describes a GameBoy game that can be emulated.
 */
class CGame {
public:
   enum E_GBType { INVALID, GAMEBOY, GAMEBOYCOLOR, GAMEBOYADVANCE };

   CGame(QString filename);
   CGame(QString filename, CAbstractEmulatorOptions::E_Emulator emulator);

   CGame(const CGame& other);

   const QString& getName() const;
   void setName(const QString& name);

   QString getIdentifier() const;

   const QString& getFilename() const;
   void setFilename(const QString& filename);

   enum CGame::E_GBType getType() const;

   bool romExists() const;

   void changeEmulator(CAbstractEmulatorOptions::E_Emulator emulator);

   CAbstractEmulatorOptions& getOptions();
   const CAbstractEmulatorOptions& getOptions() const;

   void setOptions(std::auto_ptr<CAbstractEmulatorOptions> options);

   CGame& operator=(const CGame& other);

private:
   QString m_Filename;
   QString m_GameTitle;
   std::auto_ptr<CAbstractEmulatorOptions> m_Options;
};

#endif

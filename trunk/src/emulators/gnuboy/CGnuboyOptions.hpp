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

   virtual QWidget* getOptionsWidget();

   virtual QStringList getCommandArgs() const;
};

#endif


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



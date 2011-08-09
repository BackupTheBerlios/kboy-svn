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

#ifndef H_CABSTRACTEMULATOROPTIONS
#define H_CABSTRACTEMULATOROPTIONS

#include <memory>

#include <QWidget>
#include <QXmlStreamReader>
#include <QStringList>


class CAbstractEmulatorOptions {
public:

   enum E_Emulator { GNUBOY=0, VBA=1 };

   CAbstractEmulatorOptions();

   virtual ~CAbstractEmulatorOptions() {}


   virtual CAbstractEmulatorOptions::E_Emulator getEmulator() const;
   virtual void setEmulator(enum CAbstractEmulatorOptions::E_Emulator);

   virtual const QString& getEmuCommand() const = 0;
   virtual void setEmuCommand(const QString& command) = 0;



   virtual QStringList getCommandArgs() const = 0;

   virtual bool isRomSupported(const QString& Filename) const = 0;

   virtual std::auto_ptr<CAbstractEmulatorOptions> clone() const = 0;

   virtual QWidget* getOptionsWidget() = 0;


   static std::auto_ptr<CAbstractEmulatorOptions> createEmulatorOptions(CAbstractEmulatorOptions::E_Emulator emulator);

private:
   CAbstractEmulatorOptions::E_Emulator m_Emulator;
};

#endif

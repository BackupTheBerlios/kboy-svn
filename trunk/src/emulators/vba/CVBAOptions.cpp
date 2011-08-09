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

#include "emulators/vba/CVBAOptionsWidget.hpp"

#include "emulators/vba/CVBAOptions.hpp"


CVBAOptions::CVBAOptions() {
	// define some standard values
	setEmulator(CAbstractEmulatorOptions::VBA);
	setEmuCommand("visualboyadvance");
	setScale(1);
	setFullscreen(true);
}

void CVBAOptions::setScale(const unsigned short scaleVal) {
	if(scaleVal>4) m_Scale=4;
	else m_Scale=scaleVal;
}

unsigned short CVBAOptions::getScale() const {
	return m_Scale;
}

void CVBAOptions::setFullscreen(bool fullscreen) {
   m_Fullscreen=fullscreen;
}

bool CVBAOptions::getFullscreen() const {
   return m_Fullscreen;
}

const QString& CVBAOptions::getEmuCommand() const {
   return m_EmuCommand;
}

void CVBAOptions::setEmuCommand(const QString& command) {
   m_EmuCommand=command;
}



bool CVBAOptions::isRomSupported(const QString& Filename) const {
   // TODO: Check if VBA supports this ROM file (file extension check etc.)
   return true;
}


std::auto_ptr<CAbstractEmulatorOptions> CVBAOptions::clone() const {
   // Make a deep copy of THIS
   return std::auto_ptr<CAbstractEmulatorOptions>(new CVBAOptions(*this));
}


QStringList CVBAOptions::getCommandArgs() const {
	QStringList Args;

	if(getFullscreen()==true) Args.append("-F");
	if(getScale()>1) Args.append("-"+QString::number(getScale()));

	return Args;
}


QWidget* CVBAOptions::getOptionsWidget() {
   return new CVBAOptionsWidget(*this, (QWidget*)0);
}

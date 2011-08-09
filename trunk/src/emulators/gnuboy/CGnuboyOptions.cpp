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

#include "emulators/gnuboy/CGnuboyOptionsWidget.hpp"

#include "emulators/gnuboy/CGnuboyOptions.hpp"

CGnuboyOptions::CGnuboyOptions() {
	// Standardwerte festlegen
	setEmulator(CAbstractEmulatorOptions::GNUBOY);
	setEmuCommand("sdlgnuboy");
	setSound(false);
	setFullscreen(true);
	setHardwareAccl(true);
	setScale(1);
}


void CGnuboyOptions::setFullscreen(bool fullscreen) {
   m_Fullscreen=fullscreen;
}

bool CGnuboyOptions::getFullscreen() const {
   return m_Fullscreen;
}

void CGnuboyOptions::setSound(const bool sound) {
	m_Sound=sound;
}

bool CGnuboyOptions::getSound() const {
	return m_Sound;
}


void CGnuboyOptions::setHardwareAccl(const bool accl) {
	m_HardwareAccl=accl;
}

bool CGnuboyOptions::getHardwareAccl() const {
	return m_HardwareAccl;
}


void CGnuboyOptions::setScale(const unsigned short scaleVal) {
	m_Scale=scaleVal;
}

unsigned short CGnuboyOptions::getScale() const {
	return m_Scale;
}


const QString& CGnuboyOptions::getEmuCommand() const {
   return m_EmuCommand;
}

void CGnuboyOptions::setEmuCommand(const QString& command) {
   m_EmuCommand=command;
}

bool CGnuboyOptions::isRomSupported(const QString& filename) const {
   // TODO
   return true;
}


std::auto_ptr<CAbstractEmulatorOptions> CGnuboyOptions::clone() const {
   // Make a deep copy of THIS
   return std::auto_ptr<CAbstractEmulatorOptions>(new CGnuboyOptions(*this));
}


QStringList CGnuboyOptions::getCommandArgs() const {
	QStringList Args;

	if(getFullscreen()==false) Args.append("--no-fullscreen");
	if(getSound()==false) Args.append("--no-sound");
	if(getHardwareAccl()==false) {
		Args.append("--no-yuv");
		if(getScale()>1) Args.append("--density="+QString::number(getScale()));
	}
	if(getScale()>1) Args.append("--scale="+QString::number(getScale()));

	return Args;
}


QWidget* CGnuboyOptions::getOptionsWidget() {
   return new CGnuboyOptionsWidget(*this, 0);
}

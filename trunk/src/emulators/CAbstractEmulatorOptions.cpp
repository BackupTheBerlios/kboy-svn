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

#include "emulators/CAbstractEmulatorOptions.hpp"

// The following two includes are needed for the "factory method" that creates new option objects
#include "emulators/gnuboy/CGnuboyOptions.hpp"
#include "emulators/vba/CVBAOptions.hpp"


CAbstractEmulatorOptions::CAbstractEmulatorOptions() {
   // Use gnuboy as standard
   setEmulator(GNUBOY);
}

enum CAbstractEmulatorOptions::E_Emulator CAbstractEmulatorOptions::getEmulator() const {
   return m_Emulator;
}

void CAbstractEmulatorOptions::setEmulator(enum CAbstractEmulatorOptions::E_Emulator emulator) {
   m_Emulator = emulator;
}



std::auto_ptr<CAbstractEmulatorOptions> CAbstractEmulatorOptions::createEmulatorOptions(CAbstractEmulatorOptions::E_Emulator emulator) {
   switch(emulator) {
      case GNUBOY:
         return std::auto_ptr<CAbstractEmulatorOptions>(new CGnuboyOptions());
         break;
      case VBA:
         return std::auto_ptr<CAbstractEmulatorOptions>(new CVBAOptions());
         break;
         // TODO: Error output on "default"?
   }
}

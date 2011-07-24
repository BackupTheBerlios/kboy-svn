/* TODO
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  thw <thomas@fomori.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#ifndef IABSTRACTGAMELISTLOADER_HPP
#define IABSTRACTGAMELISTLOADER_HPP

#include "CGameListModel.hpp"

/** Abstract interface for the game list loader.
 * A game list loader loads the game list (only the list including stored emulator options, not the ROM files itself!) from a data source
 * like a file.
 * \note The current program design relies in each ROM file being a real files. reading them directly from a database is currently not
 * supported and will need further redesign and restructuring.
 */
class IAbstractGameListLoader {

public:
   virtual ~IAbstractGameListLoader() {}

   virtual unsigned int readGameList(CGameListModel* gamelist) = 0;
};

#endif // IABSTRACTGAMELISTLOADER_HPP

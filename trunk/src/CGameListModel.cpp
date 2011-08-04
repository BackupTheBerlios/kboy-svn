#include "CGameListModel.hpp"


int CGameListModel::rowCount(const QModelIndex& parent) const {
   return this->m_GameList.count();
}


int CGameListModel::columnCount(const QModelIndex& parent) const {
   /* The table model has three columns */
   return 3;
}


QVariant CGameListModel::data(const QModelIndex& index, int role) const {
   if (index.isValid() ==false) return QVariant();
   if (index.row() >=m_GameList.count()) return QVariant();
   if (index.column() >=3) return QVariant();

   /* Row is the row (surprise! :) ; the column is defined as follows:
      * 0 (STATUS) - Icon (QIcon)
      * 1 (NAME) - Name (String)
      * 2 (ROMFILE)) - ROM-File (String)
    */
   switch (index.column()) {
      case STATUS: // Icon column
         if (role==Qt::DecorationRole) {
            // The view wants the content of the icon column
            if (this->m_GameList[index.row()].romExists() ==false) {
               return QIcon(":/img/x.png");
            }
            else if (this->m_GameList[index.row()].getType() == CGame::GAMEBOY) {
               return QIcon(":/img/gb.png");
            }
            else if (this->m_GameList[index.row()].getType() == CGame::GAMEBOYCOLOR) {
               return QIcon(":/img/gbc.png");
            }
            else  if (this->m_GameList[index.row()].getType() == CGame::GAMEBOYADVANCE) {
               return QIcon(":/img/gba.png");
            }
            else return QIcon(":/img/x.png");
         }
         else if (role==Qt::ToolTipRole) {
            // The view wants the tooltip text for the icon column
            if (this->m_GameList[index.row()].romExists() == false) {
               return trUtf8("ROM file not found");
            }
            else if (this->m_GameList[index.row()].getType() == CGame::GAMEBOY) {
               return trUtf8("GameBoy ROM");
            }
            else if (this->m_GameList[index.row()].getType() == CGame::GAMEBOYCOLOR) {
               return trUtf8("Gameboy Color ROM");
            }
            else  if (this->m_GameList[index.row()].getType() == CGame::GAMEBOYADVANCE) {
               return trUtf8("Gameboy Advance ROM");
            }
            else return trUtf8("Invalid ROM file");
         }
         break;

      case NAME: // Name
         if (role==Qt::DisplayRole) {
            return this->m_GameList[index.row()].getName();
         }
         break;

      case ROMFILE: // ROM-File
         if (role==Qt::DisplayRole) {
            QString filename(this->m_GameList[index.row()].getFilename());
            return filename.replace(QDir::homePath(), "~");
         }
         break;
   }

   // In other cases (=invalid input) return an uninitialized QVariant according to Qt doc.
   return QVariant();
}


QVariant CGameListModel::headerData(int section, Qt::Orientation orientation, int role) const {
   if (role!=Qt::DisplayRole) return QVariant();
   if (orientation==Qt::Horizontal) {
      switch (section) {
         case STATUS:
            return "";
            break;
         case NAME: // Name
            return trUtf8("game title");
            break;
         case ROMFILE: // ROM file name
            return trUtf8("ROM file");
            break;
      }
   }
   else {
      return "";
   }
}


bool CGameListModel::removeRows(int position, int rows, const QModelIndex &parent) {
   int row;

   beginRemoveRows(QModelIndex(), position, position+rows-1);
   for (row=0;row<rows;++row) {
      m_GameList.removeAt(position);
   }
   endRemoveRows();

   return true;
}


void CGameListModel::addItem(const CGame& Spiel) {
   beginInsertRows(QModelIndex(), m_GameList.count(), m_GameList.count());
   m_GameList.append(Spiel);
   endInsertRows();

   emit dataChanged(QModelIndex(), QModelIndex());
}


CGame& CGameListModel::getItem(const QModelIndex& Index) {
   return m_GameList[Index.row()];  // return non-constant reference to item in list
}

// This method is needed for the gamelistwriter classes to be able to iterate through all game item :)
const QList<CGame>& CGameListModel::getInternalGameList() const {
   return m_GameList;
}
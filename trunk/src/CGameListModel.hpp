#ifndef H_CGBSPIELLISTMODEL
#define H_CGBSPIELLISTMODEL

#include <QAbstractTableModel>
#include <QList>
#include <QFile>
#include <QDir>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QIcon>

#include "CGame.hpp"

/** Modelklasse zur Speicherung der Spielliste.
  Diese Klasse verwaltet eine Liste mit Zutaten sowie pro Zutat eine Mengenangabe. Die Liste wird in Form eines TableModels bereitgestellt, so dass jede View-Komponente, die mit einem TableModel umgehen kann, die Liste anzeigen und bearbeiten kann.

  Die verwaltete Liste ist einfach eine Liste (QList) von Objekten der Klasse CGBSpiel. Die modellierte Tabelle hate drei Spalten:
  Name, ROM-File und Identifier (bisher noch leer)
*/
class CGameListModel : public QAbstractTableModel {
    Q_OBJECT

public:

   virtual ~CGameListModel() {}

    enum EMODELSPALTEN { STATUS=0, NAME, ROMFILE };

    CGameListModel(QObject *parent=0) : QAbstractTableModel(parent) {};

    int rowCount(const QModelIndex& parent=QModelIndex()) const;
    int columnCount(const QModelIndex& parent=QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const;

    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());

    /** Maybe we could also omit this method implement the "addItem" according to MVC */
    void addItem(const CGame& Spiel);
    CGame& getItem(const QModelIndex& Index);

    // The game list writer could be designed as "view" (according to the Qt MVC architecture)
    /** \deprecated Replace this method.
     */
    const QList<CGame>& getInternalGameList() const;

private:


    QList<CGame> m_GameList;	/**< Die Spieleliste, die angezeigt/modifiziert werden soll. */

};

#endif

#ifndef H_CGBSPIELLISTMODEL
#define H_CGBSPIELLISTMODEL

#include <QAbstractTableModel>
#include <QList>
#include <QFile>
#include <QDir>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QIcon>
#include "CGBSpiel.h"

/** Modelklasse zur Speicherung der Spielliste.
  Diese Klasse verwaltet eine Liste mit Zutaten sowie pro Zutat eine Mengenangabe. Die Liste wird in Form eines TableModels bereitgestellt, so dass jede View-Komponente, die mit einem TableModel umgehen kann, die Liste anzeigen und bearbeiten kann.

  Die verwaltete Liste ist einfach eine Liste (QList) von Objekten der Klasse CGBSpiel. Die modellierte Tabelle hate drei Spalten:
  Name, ROM-File und Identifier (bisher noch leer)
*/
class CGBSpielListModel : public QAbstractTableModel {
  Q_OBJECT

  public:
	enum EMODELSPALTEN { STATUS=0, NAME, ROMFILE };
	
	CGBSpielListModel(QObject *parent=0):QAbstractTableModel(parent) {};

	int rowCount(const QModelIndex& parent=QModelIndex()) const;
	int columnCount(const QModelIndex& parent=QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role=Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role=Qt::DisplayRole) const;
	
	bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());

	void addItem(const CGBSpiel& Spiel);
	CGBSpiel& getItem(const QModelIndex& Index);
	
	bool toXml(const QString& Filename);
	bool fromXml(const QString& Filename);

  private:
	QList<CGBSpiel> Spieleliste;	/**< Die Spieleliste, die angezeigt/modifiziert werden soll. */

};

#endif

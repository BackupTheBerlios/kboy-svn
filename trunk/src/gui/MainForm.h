#ifndef H_MAINFORM
#define H_MAINFORM

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTableView>
#include <QGroupBox>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include <QInputDialog>
#include <QIcon>
#include <QTranslator>
#include <QComboBox>

#include "CGBSpiel.h"
#include "CGBSpielListModel.h"
#include "CGnuboyOptionsWidget.h"
#include "CVBAOptionsWidget.h"
#include "CGnuboyOptions.h"
#include "CVBAOptions.h"


class MainForm:public QWidget {
 Q_OBJECT

 private:
 	/* Private Member für GUI */
	// Layouts
	QHBoxLayout *MainHBox, *SpieleButtonHBox;
	QVBoxLayout *RechtsVBox, *SpieleFrameBox, *OptionenVBox;
	
	// Container
	QGroupBox *FrameListe, *FrameOptionen;
	QWidget *SpieleFrameButtonBox, *BoxRechts;
	CGnuboyOptionsWidget *GnuboyOptionenBox;
	CVBAOptionsWidget *VBAOptionenBox;
	
	// Steuerelemente
	QPushButton *ButtonAdd, *ButtonDel, *ButtonStart, *ButtonEnde;
	QTableView *ListViewSpiele;
	QComboBox *ComboEmulator;
	
	/* Sonstige Member */
	QProcess *Gnuboy;
	CGBSpielListModel *Spieleliste;
	
	// Methoden
	void buildGUI();
	void initWidgets();
	void configureWidgets();
	void connectObjects();
	
 private slots:
	void btnStartClicked();
	void btnAddClicked();
	void btnDelClicked();
	void gameStatusChanged(QProcess::ProcessState newState);
	void selectedGameChanged(const QItemSelection & selected, const QItemSelection & deselected);
	void emulatorChanged(int index);
	
 public:
	MainForm(QWidget *parent=0);
	~MainForm();
};

#endif

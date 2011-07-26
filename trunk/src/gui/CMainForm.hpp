#ifndef H_CMAINFORM
#define H_CMAINFORM

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

#include "CGame.hpp"
#include "CGameListModel.hpp"


class CMainForm : public QWidget {
 Q_OBJECT

 private:
 	/* Private Member für GUI */
	// Layouts
	QHBoxLayout *MainHBox, *SpieleButtonHBox;
	QVBoxLayout *RechtsVBox, *SpieleFrameBox, *OptionenVBox;

	// Container
	QGroupBox *FrameListe, *FrameOptionen;
	QWidget *SpieleFrameButtonBox, *BoxRechts;

	// Steuerelemente
	QPushButton *ButtonAdd, *ButtonDel, *ButtonStart, *ButtonEnde;
	QTableView *ListViewSpiele;
	QComboBox *ComboEmulator;

   QWidget *OptionsWidget; // Bleibt uninitialisiert bis ein Spiel ausgewählt wird

	/* Sonstige Member */
	QProcess *Gnuboy;
	CGameListModel *Spieleliste;

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
	CMainForm(QWidget *parent=0);
	virtual ~CMainForm();
};

#endif

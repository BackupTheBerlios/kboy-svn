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
   /* Private member for GUI */
   // layouts
   QHBoxLayout *m_MainHBox;
   QHBoxLayout *m_GamesButtonHBox;
   QVBoxLayout *m_RechtsVBox;
   QVBoxLayout *m_GamesFrameBox;
   QVBoxLayout *m_OptionsVBox;

   // container
   QGroupBox *m_FrameGamesList;
   QGroupBox *m_FrameOptions;
   QWidget *m_GamesFrameButtonBox;
   QWidget *m_BoxRight;

   // control widgets
   QPushButton *m_ButtonAdd;
   QPushButton *m_ButtonDel;
   QPushButton *m_ButtonStart;
   QPushButton *m_ButtonEnde;
   QTableView *m_ListViewGames;
   QComboBox *m_ComboEmulator;

   QWidget *m_OptionsWidget; // Stay uninitialized until a game was selected

   /* other member */
   QProcess *m_EmuProcess;
   CGameListModel *m_GameList;

   // methods
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
   CMainForm(QWidget *parent = 0);
   virtual ~CMainForm();
};

#endif

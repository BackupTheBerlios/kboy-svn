#ifndef CVBAOPTIONSWIDGET
#define CVBAOPTIONSWIDGET

#include <QWidget>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>

#include "emulators/vba/CVBAOptions.hpp"

class CVBAOptionsWidget : public QWidget {
   Q_OBJECT

public:
   CVBAOptionsWidget(CVBAOptions& emulatorOptions, QWidget *parent = 0);

private:
   QVBoxLayout *OptionenVBox;
   QFormLayout *ScaleHBox, *CmdLineHBox;
   QCheckBox *CheckFullscreen;
   QSpinBox *SpinScale;
   QWidget *ScaleBox, *CmdLineBox;
   QLineEdit *EditCmdLine;

   CVBAOptions& m_Options;


private slots:
   void fullscreenChanged(int state);
   void scaleChanged(int scale);
   void cmdlineChanged(const QString& text);
};

#endif

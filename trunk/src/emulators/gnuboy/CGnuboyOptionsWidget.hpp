#ifndef CGNUBOYOPTIONSWIDGET
#define CGNUBOYOPTIONSWIDGET

#include <QWidget>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>

#include "emulators/gnuboy/CGnuboyOptions.hpp"

class CGnuboyOptionsWidget : public QWidget {
   Q_OBJECT

public:
   CGnuboyOptionsWidget(CGnuboyOptions& emulatorOptions, QWidget *parent = 0);

private:
   QVBoxLayout *OptionenVBox;
   QFormLayout *ScaleHBox, *CmdLineHBox;
   QCheckBox *CheckFullscreen;
   QSpinBox *SpinScale;
   QWidget *ScaleBox, *CmdLineBox;
   QLineEdit *EditCmdLine;
   QCheckBox *CheckSound, *CheckHardwareAccl;

   CGnuboyOptions& m_Options;


private slots:
   void fullscreenChanged(int state);
   void soundChanged(int state);
   void hardwareAcclChanged(int state);
   void scaleChanged(int scale);
   void cmdlineChanged(const QString& text);
};

#endif

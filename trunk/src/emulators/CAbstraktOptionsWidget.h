#ifndef CABSTRAKTOPTIONSWIDGET_H
#define CABSTRAKTOPTIONSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>

class CAbstraktOptionsWidget : public QWidget {
 Q_OBJECT
 
 public:
	CAbstraktOptionsWidget(QWidget *parent=0);
 
 protected:
	QVBoxLayout *OptionenVBox;
	QFormLayout *ScaleHBox, *CmdLineHBox;
	QCheckBox *CheckFullscreen;
	QSpinBox *SpinScale;
	QWidget *ScaleBox, *CmdLineBox;
	QLineEdit *EditCmdLine;
};

#endif

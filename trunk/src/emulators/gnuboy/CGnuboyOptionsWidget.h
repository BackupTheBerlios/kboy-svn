#ifndef CGNUBOYOPTIONSWIDGET
#define CGNUBOYOPTIONSWIDGET

#include <QWidget>
#include <QCheckBox>

#include "CAbstraktOptionsWidget.h"
#include "CGnuboyOptions.h"

class CGnuboyOptionsWidget : public CAbstraktOptionsWidget {
 Q_OBJECT

 public:
	CGnuboyOptionsWidget(QWidget *parent=0);
	
	void setOptionsPtr(CGnuboyOptions* Options);

 private:
	
	QCheckBox *CheckSound, *CheckHardwareAccl;
	CGnuboyOptions *prOptions;
	
	
 private slots:
	void FullscreenChanged(int State);
	void SoundChanged(int State);
	void HardwareAcclChanged(int State);
	void ScaleChanged(int Scale);
	void CmdlineChanged(const QString& text);
};

#endif

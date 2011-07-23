#ifndef CVBAOPTIONSWIDGET
#define CVBAOPTIONSWIDGET

#include <QWidget>

#include "CAbstraktOptionsWidget.h"
#include "CVBAOptions.h"

class CVBAOptionsWidget : public CAbstraktOptionsWidget {
 Q_OBJECT

 public:
	CVBAOptionsWidget(QWidget *parent=0);
	
	void setOptionsPtr(CVBAOptions* Options);

 private:
	CVBAOptions *prOptions;
	
	
 private slots:
	void FullscreenChanged(int State);
	void ScaleChanged(int Scale);
	void CmdlineChanged(const QString& text);
};

#endif

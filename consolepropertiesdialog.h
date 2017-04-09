#ifndef H_CONSOLE_PROPERTIES_DIALOG
#define H_CONSOLE_PROPERTIES_DIALOG

// Console Headers
#include "consolesettings.h"

// DAZ Studio SDK Headers
#include "dzbasicdialog.h"

// Qt SDK Headers
#include "QtCore\qstring.h"
#include "QtGui\qlabel.h"
#include "QtGui\qlineedit.h"

// Constants
static const float defaultFontPointSize = 10.0;

class ConsolePropertiesDialog : public DzBasicDialog {

  Q_OBJECT

public:
  ConsolePropertiesDialog(QWidget *parent, ConsoleSettings *settings);
  virtual ~ConsolePropertiesDialog();

  QString getNewFontSize();

private:
  QLabel *fontSizeLabel;
  QLineEdit *fontSizeEdit;

};

#endif

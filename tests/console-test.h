#ifndef H_CONSOLE_TEST
#define H_CONSOLE_TEST

#include <QtTest/QtTest>
#include <console.h>

class ConsoleTest : public QObject {

  Q_OBJECT
  
public:
  ConsoleTest(const QString logPath);

private slots:
  void init();
  void cleanup();

  void testConsole();

private:
  Console* console;
  QString logPath;
};
#endif
#ifndef H_STATISTICS_TEST_MACROS
#define H_STATISTICS_TEST_MACROS

#include "statistics-test-constants.h"
#include <typeinfo>

#define STATISTICS_GET_SLEEP_SECONDS() \
  ((static_cast<double>(TEST_SLEEP_MILLISECONDS) / 1000.0))

#define STATISTICS_GET_STRING_REPRESENTATION() \
  QString("Engine: %1, Nodes: %2, Duration [s]: %3") \
    .arg((TEST_ENGINE), QString::number((TEST_NODES)), QString::number((STATISTICS_GET_SLEEP_SECONDS())))

#define STATISTICS_STOP_CLOCK(duration) \
  QTest::qSleep((duration)); \
  statistics->stopClock();

#define STATISTICS_BUILD_CURRENT_DATETIME(varname, facet) \
  ptime startDateTime = second_clock::local_time(); \
  stringstream stringStream; \
  stringStream.imbue(locale(locale::classic(), (facet))); \
  const type_info &typeInfo = typeid(facet); \
  const QString facetTypeName = QString::fromStdString(typeInfo.name()); \
  if (facetTypeName.contains("date_facet")) { \
    stringStream << startDateTime.date(); \
  } else if (facetTypeName.contains("time_facet")) { \
    stringStream << startDateTime; \
  } else { \
    QFAIL("Failed to identify passed facet into STATISTICS_GET_CURRENT_DATETIME macro, aborting unit test."); \
    stringStream.flush(); \
    stringStream.clear(); \
  } \
  stringStream.flush(); \
  const QString varname = QString::fromStdString(stringStream.str()); \
  stringStream.clear();

#endif


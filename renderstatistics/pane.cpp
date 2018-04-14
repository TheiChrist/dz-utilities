// Render Statistics Headers
#include "logger.h"
#include "pane.h"
#include "statistics.h"
#include "version.h"

// Qt SDK Headers
#include "QtCore\qobject.h"
#include "QtCore\qstring.h"
#include "QtGui\qboxlayout.h"
#include "QtGui\qimage.h"
#include "QtGui\qlabel.h"
#include "QtGui\qmessagebox.h"

// DAZ Studio SDK Headers
#include "dzapp.h"
#include "dzrenderer.h"
#include "dzrendermgr.h"
#include "dzscene.h"
#include "dzstyle.h"

RenderStatisticsPane::RenderStatisticsPane() : DzPane("Render Statistics") {
  logger = new RenderStatisticsLogger();
  renderManager = dzApp->getRenderMgr();
  connectSignals();
  setupPaneLayout();
  renderingCounter = 0;
}

RenderStatisticsPane::~RenderStatisticsPane() {
  logger->log("Destructing render statistics pane.");

  delete(logger);
  logger = NULL;

  clear();
}

void RenderStatisticsPane::clear() {
  if (statistics.size() > 0) {
    statistics.clear();
    statistics.shrink_to_fit();
  }

  if (statisticsLayout->rowCount() > HEADING_ROWS) {
    // todo: remove all widgets inside one QGridLayouts row
  }
}

void RenderStatisticsPane::connectSignals() {
  connect(renderManager, SIGNAL(renderStarting()), this, SLOT(processStartRendering()));
  connect(renderManager, SIGNAL(renderFinished(bool)), this, SLOT(processFinishRendering()));
}

void RenderStatisticsPane::buildOptionsMenu(DzActionMenu *menu) const {
  menu->insertAction("RenderStatisticsClearAction");
}

void RenderStatisticsPane::processStartRendering() {
  logger->log("Rendering started.");

  DzRenderer* renderer = renderManager->getActiveRenderer();
  statistics.push_back(RenderStatistics(renderer->getName().toStdString(), dzScene->getNumNodes()));
}

void RenderStatisticsPane::processFinishRendering() {
  logger->log("Rendering finished.");

  RenderStatistics* currentStatistics = &statistics.back();
  currentStatistics->stopClock();
  currentStatistics->setCounter(++renderingCounter);
  currentStatistics->setRenderImage(saveLastRenderImage(renderingCounter).toStdString());

  logger->log(*currentStatistics);
  statisticsLayout->update();
}

void RenderStatisticsPane::setupPaneLayout() {
  int margin = style()->pixelMetric(DZ_PM_GeneralMargin);

  paneLayout = new QVBoxLayout(this);
  paneLayout->setMargin(margin);
  paneLayout->setSpacing(margin);

  statisticsLayout = new QStatisticsLayout(&statistics);
  paneLayout->addLayout(statisticsLayout);
  paneLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));

  setLayout(paneLayout);
}

QString RenderStatisticsPane::saveLastRenderImage(int renderingCounter) {
  QString renderStoragePath = dzApp->getTempPath();
  QString filename = QString(RENDER_FILE_NAME_TEMPLATE).arg(QString::number(renderingCounter));
  QString filePath = QString("%1/%2").arg(renderStoragePath, filename);
  QImage lastRenderImage(renderManager->getLastSavedRenderPath());

  if (! lastRenderImage.save(filePath, 0, -1)) {
    logger->log(QString("Failed storing render image at %1.").arg(filePath));

    return NOTHING;
  }

  return filename;
}
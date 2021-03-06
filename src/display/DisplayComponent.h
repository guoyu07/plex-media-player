#ifndef DISPLAYCOMPONENT_H
#define DISPLAYCOMPONENT_H

#include "DisplayManager.h"
#include "ComponentManager.h"
#include <QScreen>
#include <QTimer>

class DisplayComponent : public ComponentBase
{
  Q_OBJECT
  DEFINE_SINGLETON(DisplayComponent);

public:
  ~DisplayComponent();

  virtual const char* componentName() { return "display"; }
  virtual bool componentExport() { return true; }
  virtual bool componentInitialize();

  inline DisplayManager* getDisplayManager() { return m_displayManager; }
  int getApplicationDisplay();

  // Switch to the best video mode for the given video framerate. Return true only if the actual
  // mode was switched. If a good match was found, but the current video mode didn't have to be
  // changed, return false. Return false on failure too.
  bool switchToBestVideoMode(float frameRate);

  // Switch to best overall video mode. This will also switch the resolution.
  bool switchToBestOverallVideoMode(int display);

  double currentRefreshRate();

private:
  DisplayComponent(QObject *parent = 0);

  DisplayManager  *m_displayManager;
  int m_lastVideoMode;
  int m_lastDisplay;
  QTimer m_initTimer;

public Q_SLOTS:
  void  monitorChange();
  bool  initializeDisplayManager();
  bool  restorePreviousVideoMode();

Q_SIGNALS:
  void refreshRateChanged();

};

#endif // DISPLAYCOMPONENT_H

#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <QMainWindow>
#include "gamecontrol.h"
QT_BEGIN_NAMESPACE
namespace Ui {
  class GamePanel;
}
QT_END_NAMESPACE

class GamePanel : public QMainWindow {
  Q_OBJECT

public:
  GamePanel(QWidget *parent = nullptr);
  ~GamePanel();
protected:
  void paintEvent(QPaintEvent *ev)override;
private:
  Ui::GamePanel *ui;
  QPixmap m_bkImage;
  GameControl *m_gameCtl;
};
#endif // GAMEPANEL_H

#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include "gamecontrol.h"
#include "card.h"
#include "cardpanel.h"
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
  void gameControlInit();
  void updatePlayerScore();
  void initCardMap();
  void cropImage(QPixmap &pix, int x, int y, Card &card);
  void initButtonsGroup();
  void initPlayerContext();
  void initGameScene();
protected:
  void paintEvent(QPaintEvent *ev)override;
private:
  enum CardAlign {Horizontal, Vertical};
  struct PlayerContext {
    QRect cardRect;
    QRect playHandRect;
    CardAlign align;
    bool isFrontSide;
    QLabel *info;
    QLabel *roleImg;
    Cards lastCards;
  };
  Ui::GamePanel *ui;
  QPixmap m_bkImage;
  GameControl *m_gameCtl;
  QVector<Player *>m_playerList;
  QMap<Card, CardPanel *>m_cardMap;
  QSize m_cardSize;
  QPixmap m_cardBackImg;
  QMap<Player *, PlayerContext>m_contextMap;
  CardPanel *m_baseCard;
  CardPanel *m_moveCard;
  QVector<CardPanel *>m_last3Card;
  QPoint m_baseCardPos;
};
#endif // GAMEPANEL_H

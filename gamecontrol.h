#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include "robot.h"
#include "userplayer.h"

class GameControl : public QObject {
  Q_OBJECT
public:
  enum GameStatus {
    DispatchCard,
    CallingLord,
    PlayingHand
  };
  enum PlayerStatus {
    ThinkingForCallLord,
    ThinkingForPlayHand,
    Winning
  };

public:
  explicit GameControl(QObject *parent = nullptr);
  void PlayerInit();
  Robot *getLeftRobot();
  Robot *getRightRobot();
  UserPlayer *getUserPlayer();
  void setCurrentPlayer(Player *player);
  Player *getCurrentPlayer();
  Player *getPendPlayer();
  Cards getPendCards();
  void initAllCards();
  Card takeOneCard();
  Cards getSurplusCards();
  void resetCardData();
  void startLordCard();
  void becomeLord(Player *player);
  void clearPlayerScore();
signals:
private:
  Robot *m_robotLeft;
  Robot *m_robotRight;
  UserPlayer *m_user;
  Player *m_currPlayer;
  Player *m_pendPlayer;
  Cards m_pendCards;
  Cards m_allCards;
};

#endif // GAMECONTROL_H

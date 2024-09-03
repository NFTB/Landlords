#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "cards.h"

class Player : public QObject {
  Q_OBJECT
public:
  enum Role {Lord, Farmer};
  enum Sex {Man, Woman};
  enum Direction {Left, Right};
  enum Type {Robot, User, UnKnow};
public:
  explicit Player(QObject *parent = nullptr);
  explicit Player(QString name, QObject *parent = nullptr);
  void setScore(const int &score);
  int getScore();
  void setName(const QString &name);
  QString getName();
  void setRole(const Role &role);
  Role getRole();
  void setSex(const Sex &sex);
  Sex getSex();
  void setDirection(const Direction &direction);
  Direction getDirection();
  void setType(const Type &type);
  Type getType();
  void setWin(const bool &isWin);
  bool isWin();
  void setPrevPlayer(Player *player);
  Player *getPrevPlayer();
  void setNextPlayer(Player *player);
  Player *getNextPlayer();
  void grabLordBet(int point);
  void storeDispatchCard(Card &card);
  void storeDispatchCard(Cards &cards);
  Cards getCards();
  void clearCards();
  void playHand(Cards &cards);
  void setPendingInfo(Player *player, Cards &cards);
  Player *getPendPlayer();
  Cards getPendCards();

  virtual void prepareCallLord();
  virtual void preparePlayHand();
protected:
  int m_score;
  QString m_name;
  Role m_role;
  Sex m_sex;
  Direction m_direction;
  Type m_type;
  bool m_isWin;
  Player *m_prev;
  Player *m_next;
  Cards m_cards;
  Cards m_pendCards;
  Player *m_pendPlayer;
signals:
};

#endif // PLAYER_H

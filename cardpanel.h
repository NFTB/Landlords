#ifndef CARDPANEL_H
#define CARDPANEL_H

#include <QWidget>
#include "card.h"
#include "player.h"

class CardPanel : public QWidget {
  Q_OBJECT
public:
  explicit CardPanel(QWidget *parent = nullptr);
  void setImage(QPixmap &front, QPixmap &back);
  QPixmap getImage();

  void setFrontSide(bool flag);
  bool isFrontSide();

  void setSelected(bool flag);
  bool isSelected();

  void setCard(Card &card);
  Card getCard();

  void setOwner(Player *player);
  Player *getOwner();
protected:
  void paintEvent(QPaintEvent *event)override;
  void mousePressEvent(QMouseEvent *event)override;

signals:

private:
  QPixmap m_front;
  QPixmap m_back;
  bool m_isfront;
  bool m_isSelect;
  Card m_card;
  Player *m_owner;
};

#endif // CARDPANEL_H

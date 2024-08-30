#ifndef CARDS_H
#define CARDS_H

#include "card.h"

#include <QSet>
class Cards {
public:
  enum class SortType {Asc, Desc, NoSort};
  Cards();
  void add(const Card &card);
  void add(const Cards &cards);

  Cards &operator<<(const Card &card);
  Cards &operator<<(const Cards &cards);

  void remove(const Card &card);
  void remove(const Cards &cards);

  int cardCount();
  bool isEmpty();
  void clear();

  Card::CardPoint maxPoint();
  Card::CardPoint minPoint();
  int pointCount(const Card::CardPoint &point);
  bool contains(const Card &card);
  bool contains(const Cards &cards);

  Card takeRandCard();
  CardList toCardList(const SortType &type = Cards::SortType::Desc);
private:
  QSet<Card>m_cards;
};

#endif // CARDS_H

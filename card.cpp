#include "card.h"

Card::Card() {
}

void Card::setSuit(CardSuit suit) {
  m_suit = suit;
}

void Card::setPoint(CardPoint point) {
  m_point = point;
}

Card::CardSuit Card::suit() const {
  return m_suit;
}

Card::CardPoint Card::point() const {
  return m_point;
}

bool lessSort(const Card &c1, const Card &c2) {
  if(c1.point() == c2.point()) {
    return c1.suit() < c2.suit();
  }
  return c1.point() < c2.point();
}

bool greaterSort(const Card &c1, const Card &c2) {
  if(c1.point() == c2.point()) {
    return c1.suit() > c2.suit();
  }
  return c1.point() > c2.point();
}

bool operator==(const Card &leaf, const Card &right) {
  return leaf.point() == right.point() && leaf.suit() == right.suit();
}

uint qHash(const Card &card) {
  return card.point() * 100 + card.suit();
}

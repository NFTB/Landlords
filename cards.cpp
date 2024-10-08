#include "cards.h"
#include <QRandomGenerator>


Cards::Cards() {}

Cards::Cards(const Card &card) {
  add(card);
}

void Cards::add(const Card &card) {
  m_cards.insert(card);
}

void Cards::add(const Cards &cards) {
  m_cards.unite(cards.m_cards);
}

Cards &Cards::operator<<(const Card &card) {
  add(card);
  return *this;
}

Cards &Cards::operator<<(const Cards &cards) {
  add(cards);
  return *this;
}

void Cards::remove(const Card &card) {
  m_cards.remove(card);
}

void Cards::remove(const Cards &cards) {
  m_cards.subtract(cards.m_cards);
}

int Cards::cardCount() {
  return m_cards.size();
}

bool Cards::isEmpty() {
  return m_cards.isEmpty();
}

void Cards::clear() {
  m_cards.clear();
}

Card::CardPoint Cards::maxPoint() {
  Card::CardPoint max = Card::CardPoint::Card_Begin;
  for(auto &card : m_cards) {
    if(card.point() > max) {
      max = card.point();
    }
  }
  return max;
}

Card::CardPoint Cards::minPoint() {
  Card::CardPoint min = Card::CardPoint::Card_End;
  for(auto &card : m_cards) {
    if(card.point() < min) {
      min = card.point();
    }
  }
  return min;
}

int Cards::pointCount(const Card::CardPoint &point) {
  int cnt = 0;
  for(auto &card : m_cards) {
    if(point == card.point()) {
      ++cnt;
    }
  }
  return cnt;
}

bool Cards::contains(const Card &card) {
  return m_cards.contains(card);
}

bool Cards::contains(const Cards &cards) {
  return m_cards.contains(cards.m_cards);
}

Card Cards::takeRandomCard() {
  int num = QRandomGenerator::global()->bounded(m_cards.size());
  auto it = m_cards.cbegin();
  for(int i = 0; i < num; ++i, ++it);
  Card card = *it;
  m_cards.erase(it);
  return card;
}

CardList Cards::toCardList(const SortType &type) {
  CardList list{m_cards.begin(), m_cards.end()};
  if(type == SortType::Asc) {
    std::sort(list.begin(), list.end(), lessSort);
  } else if(type == SortType::Desc) {
    std::sort(list.begin(), list.end(), greaterSort);
  }
  return list;
}

#include "player.h"

Player::Player(QObject *parent)
  : QObject{parent} {
  m_score = 0;
  m_isWin = false;
}

Player::Player(QString name, QObject *parent)
  : Player(parent) {
  m_name = name;
}

void Player::setScore(const int &score) {
  m_score = score;
}

int Player::getScore() {
  return m_score;
}

void Player::setName(const QString &name) {
  m_name = name;
}

QString Player::getName() {
  return m_name;
}

void Player::setRole(const Role &role) {
  m_role = role;
}

Player::Role Player::getRole() {
  return m_role;
}

void Player::setSex(const Sex &sex) {
  m_sex = sex;
}

Player::Sex Player::getSex() {
  return m_sex;
}

void Player::setDirection(const Direction &direction) {
  m_direction = direction;
}

Player::Direction Player::getDirection() {
  return m_direction;
}

void Player::setType(const Type &type) {
  m_type = type;
}

Player::Type Player::getType() {
  return m_type;
}

void Player::setWin(const bool &isWin) {
  m_isWin = isWin;
}

bool Player::isWin() {
  return m_isWin;
}

void Player::setPrevPlayer(Player *player) {
  m_prev = player;
}

Player *Player::getPrevPlayer() {
  return m_prev;
}

void Player::setNextPlayer(Player *player) {
  m_next = player;
}

Player *Player::getNextPlayer() {
  return m_next;
}

void Player::storeDispatchCard(Card &card) {
  m_cards.add(card);
}

void Player::storeDispatchCard(Cards &cards) {
  m_cards.add(cards);
}

Cards Player::getCards() {
  return m_cards;
}

void Player::clearCards() {
  m_cards.clear();
}

void Player::playHand(Cards &cards) {
  m_cards.remove(cards);
}

void Player::setPendingInfo(Player *player, Cards &cards) {
  m_pendPlayer = player;
  m_pendCards = cards;
}

Player *Player::getPendPlayer() {
  return m_pendPlayer;
}

Cards Player::getPendCards() {
  return m_pendCards;
}

void Player::prepareCallLord() {
}

void Player::preparePlayHand() {
}

#include "gamecontrol.h"
#include <QRandomGenerator>

GameControl::GameControl(QObject *parent)
  : QObject{parent}
{}

void GameControl::PlayerInit() {
  m_robotLeft = new Robot("机器人A", this);
  m_robotRight = new Robot("机器人B", this);
  m_user = new UserPlayer("玩家", this);
  m_robotLeft->setDirection(Player::Left);
  m_robotRight->setDirection(Player::Right);
  m_user->setDirection(Player::Right);
  Player::Sex sex;
  sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
  m_robotLeft->setSex(sex);
  sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
  m_robotRight->setSex(sex);
  sex = (Player::Sex)QRandomGenerator::global()->bounded(2);
  m_user->setSex(sex);
  m_user->setPrevPlayer(m_robotLeft);
  m_user->setNextPlayer(m_robotRight);
  m_robotLeft->setPrevPlayer(m_robotRight);
  m_robotLeft->setNextPlayer(m_user);
  m_robotRight->setPrevPlayer(m_user);
  m_robotRight->setNextPlayer(m_robotLeft);
  m_currPlayer = m_user;
}

Robot *GameControl::getLeftRobot() {
  return m_robotLeft;
}

Robot *GameControl::getRightRobot() {
  return m_robotRight;
}

UserPlayer *GameControl::getUserPlayer() {
  return m_user;
}

void GameControl::setCurrentPlayer(Player *player) {
  m_currPlayer = player;
}

Player *GameControl::getCurrentPlayer() {
  return m_currPlayer;
}

Player *GameControl::getPendPlayer() {
  return m_pendPlayer;
}

Cards GameControl::getPendCards() {
  return m_pendCards;
}

void GameControl::initAllCards() {
  m_allCards.clear();
  for(int p = Card::Card_Begin + 1; p < Card::Card_SJ; ++p) {
    for(int s = Card::Suit_Begin + 1; s < Card::Suit_End; ++s) {
      m_allCards.add(Card{(Card::CardPoint)p, (Card::CardSuit )s});
    }
  }
  m_allCards.add(Card{Card::Card_SJ, Card::Suit_Begin});
  m_allCards.add(Card{Card::Card_BJ, Card::Suit_Begin});
}

Card GameControl::takeOneCard() {
  return m_allCards.takeRandomCard();
}

Cards GameControl::getSurplusCards() {
  return m_allCards;
}

void GameControl::resetCardData() {
  initAllCards();
  m_robotLeft->clearCards();
  m_robotRight->clearCards();
  m_user->clearCards();
  m_pendPlayer = nullptr;
  m_pendCards.clear();
}

void GameControl::startLordCard() {
  m_currPlayer->prepareCallLord();
  emit playerStatusChanged(m_currPlayer, ThinkingForCallLord);
}

void GameControl::becomeLord(Player *player) {
  player->setRole(Player::Lord);
  player->getPrevPlayer()->setRole(Player::Farmer);
  player->getNextPlayer()->setRole(Player::Farmer);
  m_currPlayer = player;
  player->storeDispatchCard(m_allCards);
  m_currPlayer->preparePlayHand();
}

void GameControl::clearPlayerScore() {
  m_robotLeft->setScore(0);
  m_robotRight->setScore(0);
  m_user->setScore(0);
}

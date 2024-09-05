#include "gamepanel.h"
#include "ui_gamepanel.h"
#include "buttongroup.h"
#include "gamecontrol.h"
#include <QDebug>
#include <QPainter>
#include <QRandomGenerator>

GamePanel::GamePanel(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::GamePanel) {
  ui->setupUi(this);
  int num = QRandomGenerator::global()->bounded(10) + 1;
  QString path = QString(":/images/background-%1.png").arg(num);
  m_bkImage.load(path);
  this->setWindowTitle("欢乐斗地主");
  this->setFixedSize(1000, 650);
  gameControlInit();
  updatePlayerScore();
  initCardMap();
  initButtonsGroup();
  initPlayerContext();
  initGameScene();
}

GamePanel::~GamePanel() {
  delete ui;
}

void GamePanel::gameControlInit() {
  m_gameCtl = new GameControl(this);
  m_gameCtl->PlayerInit();
  Robot *leftRobot = m_gameCtl->getLeftRobot();
  Robot *rightRobot = m_gameCtl->getRightRobot();
  UserPlayer *user = m_gameCtl->getUserPlayer();
  m_playerList << leftRobot << rightRobot << user;
}

void GamePanel::updatePlayerScore() {
  ui->scorePanel->SetSocre(m_playerList[0]->getScore(),
                           m_playerList[1]->getScore(),
                           m_playerList[2]->getScore());
}

void GamePanel::initCardMap() {
  QPixmap pixmap(":/images/card.png");
  m_cardSize.setWidth(pixmap.width() / 13);
  m_cardSize.setHeight(pixmap.height() / 5);
  m_cardBackImg = pixmap.copy(2 * m_cardSize.width(), 4 * m_cardSize.height(),
                              m_cardSize.width(), m_cardSize.height());
  for(int i = 0, suit = Card::Suit_Begin + 1; i < Card::Suit_End; ++suit, ++i) {
    for(int j = 0, point = Card::Card_Begin + 1; point < Card::Card_SJ; ++point, ++i) {
      Card card{(Card::CardPoint)point, (Card::CardSuit)suit};
      cropImage(pixmap, j *m_cardSize.width(), i *m_cardSize.height(), card);
    }
  }
  Card card;
  card.setPoint(Card::Card_SJ);
  card.setSuit(Card::Suit_Begin);
  cropImage(pixmap, 0, 4 * m_cardSize.height(), card);
  card.setPoint(Card::Card_BJ);
  cropImage(pixmap, m_cardSize.width(), 4 * m_cardSize.height(), card);
}

void GamePanel::cropImage(QPixmap &pix, int x, int y, Card &card) {
  QPixmap sub = pix.copy(x, y, m_cardSize.width(), m_cardSize.height());
  CardPanel* panel = new CardPanel(this);
  panel->setImage(sub, m_cardBackImg);
  panel->setCard(card);
  panel->hide();
  m_cardMap.insert(card, panel);
}

void GamePanel::initButtonsGroup() {
  ui->btnGroup->initButtons();
  ui->btnGroup->selectPanel(ButtonGroup::Start);
  connect(ui->btnGroup, &ButtonGroup::startGame, this, [ = ]() {});
  connect(ui->btnGroup, &ButtonGroup::playHand, this, [ = ]() {});
  connect(ui->btnGroup, &ButtonGroup::pass, this, [ = ]() {});
  connect(ui->btnGroup, &ButtonGroup::betPoint, this, [ = ]() {});
}

void GamePanel::initPlayerContext() {
  const QRect cardsRect[] = {
    QRect(90, 130, 100, height() - 200),                    // 左侧机器人
    QRect(rect().right() - 190, 130, 100, height() - 200),  // 右侧机器人
    QRect(250, rect().bottom() - 120, width() - 500, 100)   // 当前玩家
  };
  const QRect playHandRect[] = {
    QRect(260, 150, 100, 100),                              // 左侧机器人
    QRect(rect().right() - 360, 150, 100, 100),             // 右侧机器人
    QRect(150, rect().bottom() - 290, width() - 300, 105)   // 当前玩家
  };
  const QPoint roleImgPos[] = {
    QPoint(cardsRect[0].left() - 80, cardsRect[0].height() / 2 + 20),   // 左侧机器人
    QPoint(cardsRect[1].right() + 10, cardsRect[1].height() / 2 + 20),  // 右侧机器人
    QPoint(cardsRect[2].right() - 10, cardsRect[2].top() - 10)          // 当前玩家
  };
  int index = m_playerList.indexOf(m_gameCtl->getUserPlayer());
  for(int i = 0; i < m_playerList.size(); ++i) {
    PlayerContext context;
    context.align = i == index ? Horizontal : Vertical;
    context.isFrontSide = i == index ? true : false;
    context.cardRect = cardsRect[i];
    context.playHandRect = playHandRect[i];
    context.info = new QLabel(this);
    context.info->resize(160, 98);
    context.info->hide();
    QRect rect = playHandRect[i];
    QPoint pt(rect.left() + (rect.width() - context.info->width()) / 2,
              rect.top() + (rect.height() - context.info->height()) / 2);
    context.info->move(pt);
    context.roleImg = new QLabel(this);
    context.roleImg->resize(84, 120);
    context.roleImg->hide();
    context.roleImg->move(roleImgPos[i]);
    context.lastCards.clear();
    m_contextMap.insert(m_playerList[i], context);
  }
}

void GamePanel::initGameScene() {
  m_baseCard = new CardPanel(this);
  m_baseCard->setImage(m_cardBackImg, m_cardBackImg);
  m_moveCard = new CardPanel(this);
  m_moveCard->setImage(m_cardBackImg, m_cardBackImg);
  for(int i = 0; i < 3; ++i) {
    CardPanel* panel = new CardPanel(this);
    panel->setImage(m_cardBackImg, m_cardBackImg);
    m_last3Card.push_back(panel);
    panel->hide();
  }
  m_baseCardPos = QPoint((width() - m_cardSize.width()) / 2,
                         (height() - m_cardSize.height()) / 2 - 100);
  m_baseCard->move(m_baseCardPos);
  m_moveCard->move(m_baseCardPos);
  int base = (width() - m_cardSize.width() * 3 - 2 * 10) / 2;
  for(int i = 0; i < 3; ++i) {
    m_last3Card[i]->move(base + (m_baseCard->width() + 10)*i, 20);
  }
}

void GamePanel::paintEvent(QPaintEvent *ev) {
  QPainter p(this);
  p.drawPixmap(rect(), m_bkImage);
}

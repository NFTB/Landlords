#include "gamepanel.h"
#include "ui_gamepanel.h"
#include <QDebug>
#include <QPainter>
#include <QRandomGenerator>

GamePanel::GamePanel(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::GamePanel) {
  ui->setupUi(this);
  ui->btnGroup->initButtons();
  ui->btnGroup->selectPanel(ButtonGroup::Start);
  int num = QRandomGenerator::global()->bounded(10) + 1;
  QString path = QString(":/images/background-%1.png").arg(num);
  m_bkImage.load(path);
  this->setWindowTitle("欢乐斗地主");
  this->setFixedSize(1000, 650);
  m_gameCtl = new GameControl(this);
}

GamePanel::~GamePanel() {
  delete ui;
}

void GamePanel::paintEvent(QPaintEvent *ev) {
  QPainter p(this);
  p.drawPixmap(rect(), m_bkImage);
}

#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton {
  Q_OBJECT
public:
  explicit MyButton(QWidget *parent = nullptr);
  void setImage(QString normal, QString hover, QString pressed);
protected:
  void mousePressEvent(QMouseEvent *ev)override;
  void mouseReleaseEvent(QMouseEvent *ev)override;
  void enterEvent(QEvent *ev)override;
  void leaveEvent(QEvent *ev)override;
  void paintEvent(QPaintEvent *ev)override;
signals:

private:
  QString m_normal;
  QString m_hover;
  QString m_pressed;
  QPixmap m_pixmap;
};

#endif // MYBUTTON_H

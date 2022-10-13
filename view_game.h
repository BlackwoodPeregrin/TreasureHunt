#ifndef VIEW_GAME_H
#define VIEW_GAME_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>
#include <QButtonGroup>
#include "controller_game.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Nightmare {

enum CoordsPlayingField {
  k00,
  k01,
  k02,
  k03,
  k04,
  k10,
  k11,
  k12,
  k13,
  k14,
  k20,
  k21,
  k22,
  k23,
  k24,
  k30,
  k31,
  k32,
  k33,
  k34,
  k40,
  k41,
  k42,
  k43,
  k44
};

class ViewGame : public QWidget
{
    Q_OBJECT

public:
    ViewGame(QWidget *parent = nullptr);
    ~ViewGame();

protected:
    void addGameButtonToGroup();
    void clearAllIcons();
    void setInterfaceStyle();
    void setAllIcons();
    void setIconToButton(QPushButton *button, QPixmap const &icon, QSize const &icon_size);
    void paintEvent(QPaintEvent *event);

private slots:
    void on_button_about_game_clicked();
    void on_button_back_clicked();
    void on_button_start_game_clicked();

private:
    Ui::Widget *ui;
    bool m_is_game_start{false};
    Controller &m_controller{Controller::getInstance()};
    QButtonGroup m_group;

};
}
QT_END_NAMESPACE
#endif // VIEW_GAME_H

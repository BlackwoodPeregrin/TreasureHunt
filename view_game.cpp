#include <QStyleOption>
#include <QTabBar>

#include "style_helper.h"
#include "ui_widget.h"
#include "view_game.h"

QT_BEGIN_NAMESPACE
namespace Nightmare {

ViewGame::ViewGame(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  // скрыл лэйбл с сообщением о победе
  ui->label->hide();
  // скрыл вкладки выбора и устанвил первую страницу таб бара
  ui->tabWidget->tabBar()->hide();
  ui->tabWidget->setCurrentIndex(0);
  // установка дэфольтных стилей
  setInterfaceStyle();
  // установка дэфольтных иконок игровым кнопкам
  setAllIcons();
}

ViewGame::~ViewGame() { delete ui; }


auto ViewGame::addGameButtonToGroup() -> void {
    // первый ряд игрового поля
    m_group.addButton(ui->cell_0_0, CoordsPlayingField::k00);
    m_group.addButton(ui->cell_0_1, CoordsPlayingField::k01);
    m_group.addButton(ui->cell_0_2, CoordsPlayingField::k02);
    m_group.addButton(ui->cell_0_3, CoordsPlayingField::k03);
    m_group.addButton(ui->cell_0_4, CoordsPlayingField::k04);
    // второй ряд игрового поля
    m_group.addButton(ui->cell_1_0, CoordsPlayingField::k10);
    m_group.addButton(ui->cell_1_1, CoordsPlayingField::k11);
    m_group.addButton(ui->cell_1_2, CoordsPlayingField::k12);
    m_group.addButton(ui->cell_1_3, CoordsPlayingField::k13);
    m_group.addButton(ui->cell_1_4, CoordsPlayingField::k14);
    // третий ряд игрового поля
    m_group.addButton(ui->cell_2_0, CoordsPlayingField::k20);
    m_group.addButton(ui->cell_2_1, CoordsPlayingField::k21);
    m_group.addButton(ui->cell_2_2, CoordsPlayingField::k22);
    m_group.addButton(ui->cell_2_3, CoordsPlayingField::k23);
    m_group.addButton(ui->cell_2_4, CoordsPlayingField::k24);
    // четвертый ряд игрового поля
    m_group.addButton(ui->cell_2_0, CoordsPlayingField::k30);
    m_group.addButton(ui->cell_2_1, CoordsPlayingField::k31);
    m_group.addButton(ui->cell_2_2, CoordsPlayingField::k32);
    m_group.addButton(ui->cell_2_3, CoordsPlayingField::k33);
    m_group.addButton(ui->cell_2_4, CoordsPlayingField::k34);
    // пятый ряд игрового поля
    m_group.addButton(ui->cell_2_0, CoordsPlayingField::k40);
    m_group.addButton(ui->cell_2_1, CoordsPlayingField::k41);
    m_group.addButton(ui->cell_2_2, CoordsPlayingField::k42);
    m_group.addButton(ui->cell_2_3, CoordsPlayingField::k43);
    m_group.addButton(ui->cell_2_4, CoordsPlayingField::k44);
}

void ViewGame::clearAllIcons() {
    for (int i = CoordsPlayingField::k00; i <= CoordsPlayingField::k44; ++i) {
       m_group.button(i)->setIcon(QIcon());
    }
}

void ViewGame::setInterfaceStyle() {
  this->setStyleSheet(StyleHelper::getMainWidgetsStyle());

  ui->button_start_game->setStyleSheet(
      StyleHelper::getStartGameAboutGameButtonStyle());
  ui->button_about_game->setStyleSheet(
      StyleHelper::getStartGameAboutGameButtonStyle());
  setIconToButton(ui->button_start_game, QPixmap(":/img/play.png"),
                  QSize(40, 40));
  setIconToButton(ui->button_about_game, QPixmap(":/img/info.png"),
                  QSize(40, 40));

  ui->cell_0_0->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_0_1->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_0_2->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_0_3->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_0_4->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  //
  ui->cell_1_0->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_1_1->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_1_2->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_1_3->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_1_4->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  //
  ui->cell_2_0->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_2_1->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_2_2->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_2_3->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_2_4->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  //
  ui->cell_3_0->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_3_1->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_3_2->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_3_3->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_3_4->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  //
  ui->cell_4_0->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_4_1->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_4_2->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_4_3->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  ui->cell_4_4->setStyleSheet(StyleHelper::getReleasedButtonStyle());
  //
  ui->cell_upper_left->setStyleSheet(
      StyleHelper::getGamePushButtonResultStyle());
  ui->cell_upper_medium->setStyleSheet(
      StyleHelper::getGamePushButtonResultStyle());
  ui->cell_upper_right->setStyleSheet(
      StyleHelper::getGamePushButtonResultStyle());
}

void ViewGame::setAllIcons() {
  QSize icon_size(55, 55);
  // добавляю текстуры красных камней
  QPixmap texture_ruby(StyleHelper::getPathToRubyTexture());
  setIconToButton(ui->cell_upper_left, texture_ruby, icon_size);
  setIconToButton(ui->cell_0_0, texture_ruby, icon_size);
  setIconToButton(ui->cell_1_0, texture_ruby, icon_size);
  setIconToButton(ui->cell_2_0, texture_ruby, icon_size);
  setIconToButton(ui->cell_3_0, texture_ruby, icon_size);
  setIconToButton(ui->cell_4_0, texture_ruby, icon_size);
  // добавляю текстуры зеленых камней
  QPixmap texture_emeralds(StyleHelper::getPathToEmeraldTexture());
  setIconToButton(ui->cell_upper_medium, texture_emeralds, icon_size);
  setIconToButton(ui->cell_0_2, texture_emeralds, icon_size);
  setIconToButton(ui->cell_1_2, texture_emeralds, icon_size);
  setIconToButton(ui->cell_2_2, texture_emeralds, icon_size);
  setIconToButton(ui->cell_3_2, texture_emeralds, icon_size);
  setIconToButton(ui->cell_4_2, texture_emeralds, icon_size);
  // добавляю текстуры синих камней
  QPixmap texture_saphfire(StyleHelper::getPathToSaphfireTexture());
  setIconToButton(ui->cell_upper_right, texture_saphfire, icon_size);
  setIconToButton(ui->cell_0_4, texture_saphfire, icon_size);
  setIconToButton(ui->cell_1_4, texture_saphfire, icon_size);
  setIconToButton(ui->cell_2_4, texture_saphfire, icon_size);
  setIconToButton(ui->cell_3_4, texture_saphfire, icon_size);
  setIconToButton(ui->cell_4_4, texture_saphfire, icon_size);
  // добавляю текстуры сундука
  QPixmap texture_box(":/img/box.png");
  setIconToButton(ui->cell_0_1, texture_box, icon_size);
  setIconToButton(ui->cell_0_3, texture_box, icon_size);
  setIconToButton(ui->cell_2_1, texture_box, icon_size);
  setIconToButton(ui->cell_2_3, texture_box, icon_size);
  setIconToButton(ui->cell_4_1, texture_box, icon_size);
  setIconToButton(ui->cell_4_3, texture_box, icon_size);
}

void ViewGame::setIconToButton(QPushButton *button, QPixmap const &icon,
                               QSize const &icon_size) {
  button->setIcon(icon);
  button->setIconSize(icon_size);
}

void ViewGame::paintEvent(QPaintEvent *event) {
  QStyleOption opt;
  opt.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  QWidget::paintEvent(event);
}

void ViewGame::on_button_about_game_clicked() {
  if (ui->tabWidget->currentIndex() == 0) {
    ui->tabWidget->setCurrentIndex(1);
  }
}

void ViewGame::on_button_back_clicked() { ui->tabWidget->setCurrentIndex(0); }

void ViewGame::on_button_start_game_clicked() {
  if (m_is_game_start == false) {
    //
  } else {
    //       m_controller.ClearField();
    setIconToButton(ui->cell_0_0, QPixmap(""), QSize());
  }
}

}  // namespace Nightmare
QT_END_NAMESPACE

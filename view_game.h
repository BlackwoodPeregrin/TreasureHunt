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
  k00, // 0
  k01, // 1
  k02, // 2
  k03, // 3
  k04, // 4
  k10, // 5
  k11, // 6
  k12, // 7
  k13, // 8
  k14, // 9
  k20, // 10
  k21, // 11
  k22, // 12
  k23, // 13
  k24, // 14
  k30, // 15
  k31, // 16
  k32, // 17
  k33, // 18
  k34, // 19
  k40, // 20
  k41, // 21
  k42, // 22
  k43, // 23
  k44 // 24
};

class ViewGame : public QWidget
{
    Q_OBJECT

public:
    ViewGame(QWidget *parent = nullptr);
    ~ViewGame();

public:
    // функция устанавливает задний фон
    auto installBackgroundImage(QString const &background_image) -> void;

protected:
    auto paintEvent(QPaintEvent *event) -> void;

    // функция добавляет все кнопки находящиеся на игровом поле в группу
    auto addButtonsPlayingFieldToGroup_() -> void;

    // функция устанавливает стили для кнопок игрвого поле
    auto installStyleButtonsPlayingField_() -> void;

    // функция устанавливает иконки кнопок игрового поля перед стартом игры
    auto installDefaultIconsButtonsPlayingField_() -> void;

    // функция устанавливает стили и иконки для кнопок: start_game && about_game
    auto installStyleButtonsStartGameAboutGame_() -> void;

    // функция очищает все иконки находящиеся на игровом поле
    auto clearAllIcons_() -> void;

    // функция присваивает иконку поступающецй кнопки размера icon_size
    auto setIconToButton_(QAbstractButton *button, QIcon const &icon, QSize const &icon_size) -> void;

    // функция перерисовки иконок игрового поля
    auto installGenerateIconsPlayingFiled_() -> void;

    // функция устанавливает иконки для строки над игровым поедм
    auto installIconToCellInRowOverPlayingField_(int index_in_row, QString const &path_to_icon) -> void;

    // функция по id кнопки возвращает координаты на игровом поле (строка, столбец)
    auto getCoordButtonInPlayingField_(int id_button) -> std::pair<int, int>;
    auto getIdButtonInPlayingField_(int row, int column) -> int;

private slots:
    void on_button_about_game_clicked();
    void on_button_back_clicked();
    void on_button_start_game_clicked();
    void on_button_in_playing_field_clicked(int id_button);

private:
    Ui::Widget *ui;
    bool m_is_game_start{false};
    ControllerGame &m_controller{ControllerGame::getInstance()};
    QButtonGroup m_group;

};
}
QT_END_NAMESPACE
#endif // VIEW_GAME_H

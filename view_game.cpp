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

  // установка заднего фона
  installBackgroundImage(StyleHelper::getMainWidgetsStyle());

  // добавления кнопок в группу
  addButtonsPlayingFieldToGroup_();

  // устанавка стилей для кнопок игрвого поле
  installStyleButtonsPlayingField_();

  // устанавка иконок кнопок игрового поля перед стартом игры
  installDefaultIconsButtonsPlayingField_();

  // устанавка стилей и иконок для кнопок: start_game && about_game
  installStyleButtonsStartGameAboutGame_();

  connect(&m_group, SIGNAL(idClicked(int)), this, SLOT(on_button_in_playing_field_clicked(int)));

}

ViewGame::~ViewGame() { delete ui; }

void ViewGame::installBackgroundImage(QString const &background_image) {
    this->setStyleSheet(background_image);
}

auto ViewGame::paintEvent(QPaintEvent *event) -> void {
  QStyleOption opt;
  opt.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  QWidget::paintEvent(event);
}

auto ViewGame::addButtonsPlayingFieldToGroup_() -> void {
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
    m_group.addButton(ui->cell_3_0, CoordsPlayingField::k30);
    m_group.addButton(ui->cell_3_1, CoordsPlayingField::k31);
    m_group.addButton(ui->cell_3_2, CoordsPlayingField::k32);
    m_group.addButton(ui->cell_3_3, CoordsPlayingField::k33);
    m_group.addButton(ui->cell_3_4, CoordsPlayingField::k34);
    // пятый ряд игрового поля
    m_group.addButton(ui->cell_4_0, CoordsPlayingField::k40);
    m_group.addButton(ui->cell_4_1, CoordsPlayingField::k41);
    m_group.addButton(ui->cell_4_2, CoordsPlayingField::k42);
    m_group.addButton(ui->cell_4_3, CoordsPlayingField::k43);
    m_group.addButton(ui->cell_4_4, CoordsPlayingField::k44);
}

void ViewGame::installStyleButtonsPlayingField_() {
    // установка стилей кнопок на игровом поле
    for (int cell = CoordsPlayingField::k00; cell <= CoordsPlayingField::k44; ++cell) {
        m_group.button(cell)->setStyleSheet(StyleHelper::getReleasedButtonStyle());
    }

    // установка стилей кнопок над игровым поле
    ui->cell_upper_left->setStyleSheet(
        StyleHelper::getButtonStyleUnderGameField());
    ui->cell_upper_medium->setStyleSheet(
        StyleHelper::getButtonStyleUnderGameField());
    ui->cell_upper_right->setStyleSheet(
        StyleHelper::getButtonStyleUnderGameField());
}


void ViewGame::installDefaultIconsButtonsPlayingField_() {
    int pos_ruby = 0;
    int pos_emerald = 2;
    int pos_saphfire = 4;
    // размер иконки
    QSize size_icon(55, 55);


    for (int cell = CoordsPlayingField::k00; cell <= CoordsPlayingField::k44; ++cell) {
        auto button = m_group.button(cell);
        // установка иконок красных камней клеток
        if (cell == pos_ruby) {
            setIconToButton_(button, QIcon(StyleHelper::getPathToRubyIcon()), size_icon);
            pos_ruby += 5;
        // установка иконок зеленых камней клеток
        } else if (cell == pos_emerald) {
            setIconToButton_(button, QIcon(StyleHelper::getPathToEmeraldIcon()), size_icon);
            pos_emerald += 5;
            // установка иконок синих камней клеток
        } else if (cell == pos_saphfire) {
            setIconToButton_(button, QIcon(StyleHelper::getPathToSaphfireIcon()), size_icon);
            pos_saphfire += 5;
            // установка иконок неактивыных клеток
        } else if (cell == CoordsPlayingField::k01 || cell == CoordsPlayingField::k03 ||
                   cell == CoordsPlayingField::k21 || cell == CoordsPlayingField::k23 ||
                   cell == CoordsPlayingField::k41 || cell == CoordsPlayingField::k43) {
            setIconToButton_(button, QIcon(StyleHelper::getPathToBoxIcon()), size_icon);
        }
    }

    // установка иконок для кнопок над игровым полем по умолчанию
    setIconToButton_(ui->cell_upper_left, QIcon(StyleHelper::getPathToRubyIcon()), size_icon);
    setIconToButton_(ui->cell_upper_medium, QIcon(StyleHelper::getPathToEmeraldIcon()), size_icon);
    setIconToButton_(ui->cell_upper_right, QIcon(StyleHelper::getPathToSaphfireIcon()), size_icon);

}

auto ViewGame::installStyleButtonsStartGameAboutGame_() -> void {
    // установка стиля кнопок
    ui->button_start_game->setStyleSheet(
        StyleHelper::getStartGameAboutGameButtonStyle());
    ui->button_about_game->setStyleSheet(
        StyleHelper::getStartGameAboutGameButtonStyle());

    // установка иконок для кнопок
    setIconToButton_(ui->button_start_game, QIcon(StyleHelper::getStartGameButtonIcon()),
                    QSize(40, 40));
    setIconToButton_(ui->button_about_game, QIcon(StyleHelper::getAboutGameButtonIcon()),
                    QSize(40, 40));
}



auto ViewGame::clearAllIcons_() -> void {
    // очистка иконок кнопок игрово поля
    for (int i = CoordsPlayingField::k00; i <= CoordsPlayingField::k44; ++i) {
       m_group.button(i)->setIcon(QIcon());
    }

    // очистка иконок кнопок над игровым полем
    ui->cell_upper_left->setIcon(QIcon());
    ui->cell_upper_medium->setIcon(QIcon());
    ui->cell_upper_right->setIcon(QIcon());
}

auto ViewGame::setIconToButton_(QAbstractButton *button, QIcon const &icon,
                               QSize const &icon_size) -> void {
  button->setIcon(icon);
  button->setIconSize(icon_size);
}

auto ViewGame::installGenerateIconsPlayingFiled_() -> void {
    for (int id = CoordsPlayingField::k00; id <= CoordsPlayingField::k44; ++id) {
       auto cur_button = m_group.button(id);
       auto coord_on_field = getCoordButtonInPlayingField_(id);
       auto color_cell = m_controller.GetColorCell(coord_on_field.first, coord_on_field.second);

       // если цвет клетки красный, ставим иконку красного камня
       if (color_cell == Color::kRed) {
           setIconToButton_(cur_button, QIcon(StyleHelper::getPathToRubyIcon()), QSize(55, 55));
       // если цвет клетки зеленый, ставим иконку зеленого камня
       } else if (color_cell == Color::kGreen) {
           setIconToButton_(cur_button, QIcon(StyleHelper::getPathToEmeraldIcon()), QSize(55, 55));
       // если цвет клетки синий, ставим иконку синиго камня
       } else if (color_cell == Color::kBlue) {
           setIconToButton_(cur_button, QIcon(StyleHelper::getPathToSaphfireIcon()), QSize(55, 55));
       } else {
           // если клетка является неактивной, ставим иконку сундука
           if (m_controller.IsSelectedBlockCell(coord_on_field.first, coord_on_field.second)) {
               setIconToButton_(cur_button, QIcon(StyleHelper::getPathToBoxIcon()), QSize(55, 55));
           }
       }
    }

    // установка иконок кнопок над игровым полем
    installIconToCellInRowOverPlayingField_(m_controller.GetPosRedChipInExpectedRow(),
                                                    StyleHelper::getPathToRubyIcon());

    installIconToCellInRowOverPlayingField_(m_controller.GetPosGreenChipInExpectedRow(),
                                            StyleHelper::getPathToEmeraldIcon());

    installIconToCellInRowOverPlayingField_(m_controller.GetPosBlueChipInExpectedRow(),
                                            StyleHelper::getPathToSaphfireIcon());
}

auto ViewGame::installIconToCellInRowOverPlayingField_(int index_in_row, QString const &path_to_icon) -> void {
    if (index_in_row == 0) {
        setIconToButton_(ui->cell_upper_left,
                         QIcon(path_to_icon), QSize(55, 55));
    } else if (index_in_row == 2) {
        setIconToButton_(ui->cell_upper_medium,
                         QIcon(path_to_icon), QSize(55, 55));
    } else {
        setIconToButton_(ui->cell_upper_right,
                         QIcon(path_to_icon), QSize(55, 55));
    }
}

int ViewGame::getIdButtonInPlayingField_(int row, int column) {
    int id_button = row * 5 + column;
    return id_button;
}

auto ViewGame::getCoordButtonInPlayingField_(int id_button) -> std::pair<int, int> {
    int index_row = id_button / 5;
    int index_column = id_button % 5;
    return {index_row, index_column};
}

void ViewGame::on_button_about_game_clicked() {
    ui->tabWidget->setCurrentIndex(1);
}

void ViewGame::on_button_back_clicked() { ui->tabWidget->setCurrentIndex(0); }

void ViewGame::on_button_start_game_clicked() {
  if (m_is_game_start == false) {
    // замена иконки кнопки start_game
    setIconToButton_(ui->button_start_game,
                     QIcon(StyleHelper::getStopGameButtonIcon()), QSize(40, 40));
    m_is_game_start = true;
    // генерируем игрвоое поле
    clearAllIcons_();
    m_controller.GenerateField();
    installGenerateIconsPlayingFiled_();
  } else {
    // очистка всех иконок игрового поля
    clearAllIcons_();
    // установка иконок игрового поля по умолчанию
    installDefaultIconsButtonsPlayingField_();

    // замена иконки кнопки start_game
    setIconToButton_(ui->button_start_game,
                   QIcon(StyleHelper::getStartGameButtonIcon()), QSize(40, 40));
    m_is_game_start = false;
  }
}

void ViewGame::on_button_in_playing_field_clicked(int id_button) {
    std::pair<int, int> coord = getCoordButtonInPlayingField_(id_button);
    if (m_controller.IsSelectedFreeCell(coord.first, coord.second) == true
            && m_controller.IsCellPossibleStep(coord.first, coord.second) == true) {
        //  сохраняем координаты предидущего клика
        std::pair<int, int> prev_coord = m_controller.GetCurrentCoord();
        //  меняем местами клетки в модели
        m_controller.SwapCells(coord.first, coord.second);
        // меняем иконки местами
        auto prev_button = m_group.button(getIdButtonInPlayingField_(prev_coord.first, prev_coord.second));
        m_group.button(id_button)->setIcon(prev_button->icon());
        prev_button->setIcon(QIcon());
        //
    } else {
        m_controller.SwitchCurrentFocusOnFiled(coord.first, coord.second);
    }
}

}  // namespace Nightmare
QT_END_NAMESPACE

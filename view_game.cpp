#include <QStyleOption>
#include <QTabBar>
#include <QMessageBox>

#include "style_helper.h"
#include "ui_widget.h"
#include "view_game.h"

QT_BEGIN_NAMESPACE
namespace Nightmare {

constexpr QSize icon_size = {55, 55};

ViewGame::ViewGame(QWidget *parent) : QWidget(parent), ui(new Ui::Widget), m_victory_dialog(nullptr) {
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
  m_victory_dialog = new VictoryDialog;
  connect(m_victory_dialog, SIGNAL(restart()), this, SLOT(on_dialog_button_start_clecked()));

}

ViewGame::~ViewGame() {
    delete ui;
    delete m_victory_dialog;
}

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
        // установка размера иконки
        m_group.button(cell)->setIconSize(icon_size);
        // установка стиля для кнопок без нажатия
        m_group.button(cell)->setStyleSheet(StyleHelper::getReleasedButtonStyle());
    }

    // установка стилей кнопок над игровым поле
    ui->cell_upper_left->setIconSize(icon_size);
    ui->cell_upper_left->setStyleSheet(
        StyleHelper::getButtonStyleUnderGameField());

    ui->cell_upper_medium->setIconSize(icon_size);
    ui->cell_upper_medium->setStyleSheet(
        StyleHelper::getButtonStyleUnderGameField());

    ui->cell_upper_right->setIconSize(icon_size);
    ui->cell_upper_right->setStyleSheet(
        StyleHelper::getButtonStyleUnderGameField());
}


void ViewGame::installDefaultIconsButtonsPlayingField_() {
    int pos_ruby = 0; // стартовая позиция красного камня на поле
    int pos_emerald = 2; // стартовая позиция зеленого камня на поле
    int pos_saphfire = 4; // стартовая позиция синиго камня на поле

    for (int cell = CoordsPlayingField::k00; cell <= CoordsPlayingField::k44; ++cell) {
        auto button = m_group.button(cell);
        // установка иконок красных камней клеток
        if (cell == pos_ruby) {
            button->setIcon(QIcon(StyleHelper::getPathToRubyIcon()));
            pos_ruby += 5;
        // установка иконок зеленых камней клеток
        } else if (cell == pos_emerald) {
            button->setIcon(QIcon(StyleHelper::getPathToEmeraldIcon()));
            pos_emerald += 5;
            // установка иконок синих камней клеток
        } else if (cell == pos_saphfire) {
            button->setIcon(QIcon(StyleHelper::getPathToSaphfireIcon()));
            pos_saphfire += 5;
            // установка иконок неактивыных клеток
        } else if (cell == CoordsPlayingField::k01 || cell == CoordsPlayingField::k03 ||
                   cell == CoordsPlayingField::k21 || cell == CoordsPlayingField::k23 ||
                   cell == CoordsPlayingField::k41 || cell == CoordsPlayingField::k43) {
            button->setIcon(QIcon(StyleHelper::getPathToBoxIcon()));
        }
    }

    // установка иконок для кнопок над игровым полем по умолчанию
    ui->cell_upper_left->setIcon(QIcon(StyleHelper::getPathToRubyIcon()));
    ui->cell_upper_medium->setIcon(QIcon(StyleHelper::getPathToEmeraldIcon()));
    ui->cell_upper_right->setIcon(QIcon(StyleHelper::getPathToSaphfireIcon()));
}

auto ViewGame::installStyleButtonsStartGameAboutGame_() -> void {
    // установка стиля кнопок
    ui->button_start_game->setStyleSheet(
        StyleHelper::getStartGameAboutGameButtonStyle());
    ui->button_about_game->setStyleSheet(
        StyleHelper::getStartGameAboutGameButtonStyle());

    // установка иконок для кнопок
    ui->button_start_game->setIcon(QIcon(StyleHelper::getStartGameButtonIcon()));
    ui->button_start_game->setIconSize(QSize(40, 40));

    ui->button_about_game->setIcon(QIcon(StyleHelper::getAboutGameButtonIcon()));
    ui->button_about_game->setIconSize(QSize(40, 40));
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

auto ViewGame::installGenerateIconsPlayingFiled_() -> void {
    for (int id_button = CoordsPlayingField::k00; id_button <= CoordsPlayingField::k44; ++id_button) {

       int color_cell = m_controller.GetColorCell(id_button);

       // если цвет клетки красный, ставим иконку красного камня
       if (color_cell == Color::kRed) {
           m_group.button(id_button)->setIcon(QIcon(StyleHelper::getPathToRubyIcon()));
       // если цвет клетки зеленый, ставим иконку зеленого камня
       } else if (color_cell == Color::kGreen) {
           m_group.button(id_button)->setIcon(QIcon(StyleHelper::getPathToEmeraldIcon()));
       // если цвет клетки синий, ставим иконку синиго камня
       } else if (color_cell == Color::kBlue) {
           m_group.button(id_button)->setIcon(QIcon(StyleHelper::getPathToSaphfireIcon()));
       // если клетка является неактивной, ставим иконку сундука
       } else if (color_cell == Color::kNoColor
                  && m_controller.IsSelectedBlockCell(id_button)) {
           m_group.button(id_button)->setIcon(QIcon(StyleHelper::getPathToBoxIcon()));
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
        ui->cell_upper_left->setIcon(QIcon(path_to_icon));
        ui->cell_upper_left->setIconSize(icon_size);
    } else if (index_in_row == 2) {
        ui->cell_upper_medium->setIcon(QIcon(path_to_icon));
        ui->cell_upper_medium->setIconSize(icon_size);
    } else {
        ui->cell_upper_right->setIcon(QIcon(path_to_icon));
        ui->cell_upper_right->setIconSize(icon_size);
    }
}


void ViewGame::on_button_about_game_clicked() {
    ui->tabWidget->setCurrentIndex(1);
}

void ViewGame::on_button_back_clicked() { ui->tabWidget->setCurrentIndex(0); }

void ViewGame::on_button_start_game_clicked() {
  if (m_is_game_start == false) {
    // замена иконки кнопки start_game
    ui->button_start_game->setIcon(QIcon(StyleHelper::getStopGameButtonIcon()));
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
    ui->button_start_game->setIcon(QIcon(StyleHelper::getStartGameButtonIcon()));
    m_is_game_start = false;
  }
}

void ViewGame::on_button_in_playing_field_clicked(int id_button) {
    if (m_is_game_start == true) {
        // если ячейка является возможным шагом
        if (m_controller.IsCellPossibleStep(id_button) == true) {
            //  сохраняем координаты предидущего клика
            int id_button_prev = m_controller.GetCurrentCoord();
            // меняю стиль подсвеченных кнопок на стандартный
            m_group.button(id_button_prev)->setStyleSheet(StyleHelper::getReleasedButtonStyle());
            changeStyleReleasedButtons_();

            //  меняем местами клетки в модели
            m_controller.SwapCells(id_button);

            // меняем иконки местами
            m_group.button(id_button)->setIcon(m_group.button(id_button_prev)->icon());
            m_group.button(id_button_prev)->setIcon(QIcon());

            // проверяем наступила ли победа в игре
            if (m_controller.IsVictoryGame()) {
                // диалоговое окно с ифнормацией о завершении игры
                m_victory_dialog = new VictoryDialog;
                m_victory_dialog->show();
                // замена иконки кнопки start_game
                ui->button_start_game->setIcon(QIcon(StyleHelper::getStartGameButtonIcon()));
                m_is_game_start = false;
            }
        } else {
            // меняем текущую выбранную ячейку и пересчитываем возможные шаги
            if (m_controller.IsSelectedChipCell(id_button)) {

                int id_button_prev = m_controller.GetCurrentCoord();
                // если ячейка былы выбрана, то меняем ей стили на стандартный
                if (id_button_prev != -1) {
                    m_group.button(id_button_prev)->setStyleSheet(StyleHelper::getReleasedButtonStyle());
                }
                // меняю стиль до этого выбранных кнопок на стандартный
                changeStyleReleasedButtons_();

                // меняем стиль новой выбранной кнопки
                m_group.button(id_button)->setStyleSheet(StyleHelper::getPressedButtonChooseStyle());
                // рассчитываем новые возможные шаги
                m_controller.ChangePossibleStepsChipInPlayingField_(id_button);
                // меняем их стиль отобрадения на поле
                changeStylePressedButtons_();
            }

        }
    }
}

void ViewGame::on_dialog_button_start_clecked() {
    delete m_victory_dialog;
    m_victory_dialog = nullptr;
}

void ViewGame::changeStylePressedButtons_() {
    std::vector<int> id_buttons = m_controller.GetVectorPossibleSteps();
    for (int &id : id_buttons) {
      m_group.button(id)->setStyleSheet(StyleHelper::getPressedButtonStyle());
    }
}

void ViewGame::changeStyleReleasedButtons_() {
    std::vector<int> id_buttons = m_controller.GetVectorPossibleSteps();
    for (int &id : id_buttons) {
      m_group.button(id)->setStyleSheet(StyleHelper::getReleasedButtonStyle());
    }
}

}  // namespace Nightmare
QT_END_NAMESPACE

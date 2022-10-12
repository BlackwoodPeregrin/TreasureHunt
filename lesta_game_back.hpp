#include <iostream>
#include <random>
#include <vector>

namespace Nightmare {

enum Color { kNoColor, kYellow, kOrange, kRed };  // цвет фишки

enum TypeCell { kChip, kBlock, kFree };  // тип клетки

constexpr u_int8_t kColumnsField = 5;  // ширина игрового поля

constexpr u_int8_t kRowsField = 5;  // высота игрового поля

constexpr u_int8_t kBlockCellsInField = 6;  // кол-во неактивных клеток на поле

constexpr u_int8_t kFreeCellsInField = 4;  // кол-во свободных клеток на поле

constexpr u_int8_t kYellowChipCellInField = 5;  // кол-во желтых клеток на поле

constexpr u_int8_t kOrangeChipCellInField =
    5;  // кол-во оранжевых клеток на поле

constexpr u_int8_t kRedChipCellInField = 5;  // кол-во красных клеток на поле

constexpr std::pair<int, int> kCoordBlockCells[kBlockCellsInField] = {
    {0, 1}, {0, 3}, {2, 1},
    {2, 3}, {4, 1}, {4, 3}};  // координаты всех неактивных клеток на поле

constexpr std::pair<int, int> kCoordFreeCells[kFreeCellsInField] = {
    {1, 1}, {1, 3}, {3, 1}, {3, 3}};  // координаты всех свободных клеток на
                                      // поле при старте игры

//
class AbstractCell {
 public:
  AbstractCell(int type_cell) : m_type_cell(type_cell) {}
  ~AbstractCell() = default;

  auto TypeCell() { return m_type_cell; }
  virtual auto GetColor() -> int = 0;

 private:
  int m_type_cell;
};

class ChipCell : public AbstractCell {
 public:
  ChipCell(int color_chip, int type_cell = TypeCell::kChip)
      : AbstractCell(type_cell), m_color_chip(color_chip) {}
  auto GetColor() -> int override { return m_color_chip; }

 private:
  int m_color_chip;
};

class BlockCell : public AbstractCell {
 public:
  BlockCell(int type_cell = TypeCell::kBlock) : AbstractCell(type_cell) {}
  auto GetColor() -> int override { return Color::kNoColor; }
};

class FreeCell : public AbstractCell {
 public:
  FreeCell(int type_cell = TypeCell::kFree) : AbstractCell(type_cell) {}
  auto GetColor() -> int override { return Color::kNoColor; }
};

//

// игрвое поле 5х5
class PlayingField {
 public:
  PlayingField() { InizialiseField_(); }
  PlayingField(PlayingField const &other) = delete;
  PlayingField(PlayingField &&other) = delete;
  ~PlayingField() { ClearField_(); }

  auto operator=(PlayingField const &other) -> PlayingField & = delete;
  auto operator=(PlayingField &&other) -> PlayingField & = delete;

  auto operator[](int index_row) -> std::vector<AbstractCell *> & {
    if (index_row >= kRowsField && index_row < 0) {
      throw std::out_of_range("operator[]:");
    }
    return m_cell[index_row];
  }

 protected:
  auto InizialiseField_() -> void {
    for (int row = 0; row < kRowsField; ++row) {
      m_cell.push_back(std::vector<AbstractCell *>(kColumnsField));
      for (int column = 0; column < kColumnsField; ++column) {
        m_cell[row][column] = nullptr;
      }
    }
  }

  auto ClearField_() -> void {
    for (auto &row_cells : m_cell) {
      for (auto &cell : row_cells) {
        delete cell;
      }
    }
  }

 private:
  std::vector<std::vector<AbstractCell *>> m_cell;
};

class GameMechanics {
 public:
  GameMechanics() : m_current(nullptr), m_field(nullptr) { srand(time(0)); }
  GameMechanics(GameMechanics const &other) = delete;
  GameMechanics(GameMechanics &&other) = delete;
  ~GameMechanics() { delete m_field; }

  auto operator=(GameMechanics const &other) -> GameMechanics & = delete;
  auto operator=(GameMechanics &&other) -> GameMechanics & = delete;

  auto GenerateField() -> void {
    // очищаем поле если ранее было сгенерировано
    delete m_field;
    m_field = new PlayingField;
    //
    std::vector<std::pair<int, u_int8_t>> possible_colors(
        {{Color::kYellow, kYellowChipCellInField},
         {Color::kOrange, kOrangeChipCellInField},
         {Color::kRed, kRedChipCellInField}});
    //
    for (int row = 0; row < kRowsField; ++row) {
      for (int column = 0; column < kColumnsField; ++column) {
        // заносим на поле неактивные клетки
        if (IsBlockCell_(row, column)) {
          m_field->operator[](row)[column] = new BlockCell;
          // заносим на поле свободные клетки
        } else if (IsFreeCell_(row, column)) {
          m_field->operator[](row)[column] = new FreeCell;
          // генерируем на поле цветные фишки
        } else {
          u_int8_t color = rand() % possible_colors.size();
          m_field->operator[](row)[column] =
              new ChipCell(GenerateColorChip_(possible_colors));
        }
      }
    }
  }

  auto PrintField() -> void {
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        if (m_field->operator[](i)[j]->TypeCell() == TypeCell::kBlock) {
          std::cout << " o ";
        } else if (m_field->operator[](i)[j]->TypeCell() == TypeCell::kFree) {
          std::cout << "   ";
        } else {
          std::string color_print{};
          if (m_field->operator[](i)[j]->GetColor() == Color::kYellow) {
            color_print = "\033[38;2;255;255;0m";
          } else if (m_field->operator[](i)[j]->GetColor() == Color::kOrange) {
            color_print = "\033[38;2;201;100;59m";
          } else {
            color_print = "\033[38;2;255;0;0m";
          }
          std::cout << color_print << " # "
                    << "\033[0m";
        }
      }
      std::cout << std::endl;
    }
  }

 protected:
  auto GenerateColorChip_(
      std::vector<std::pair<int, u_int8_t>> &possible_colors) -> int {
    u_int8_t index_color = rand() % possible_colors.size();
    int color = possible_colors[index_color].first;
    if (--possible_colors[index_color].second == 0) {
      auto iter = possible_colors.begin();
      while (*iter != possible_colors[index_color]) {
        ++iter;
      }
      possible_colors.erase(iter);
    }
    return color;
  }

  auto IsBlockCell_(int row, int column) -> bool {
    for (auto coord : kCoordBlockCells) {
      if (coord.first == row && coord.second == column) {
        return true;
      }
    }
    return false;
  }

  auto IsFreeCell_(int row, int column) -> bool {
    for (auto coord : kCoordFreeCells) {
      if (coord.first == row && coord.second == column) {
        return true;
      }
    }
    return false;
  }

 private:
  AbstractCell *m_current;
  PlayingField *m_field;
};

}  // namespace Nightmare

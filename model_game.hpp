#include <iostream>
#include <random>
#include <vector>

namespace Nightmare {

enum Color { kNoColor, kBlue, kGreen, kRed };  // цвет фишки

enum TypeCell { kChip, kBlock, kFree };  // тип клетки

constexpr u_int8_t kColumnsField = 5;  // ширина игрового поля

constexpr u_int8_t kRowsField = 5;  // высота игрового поля

constexpr u_int8_t kBlockCellsInField = 6;  // кол-во неактивных клеток на поле

constexpr u_int8_t kFreeCellsInField = 4;  // кол-во свободных клеток на поле

constexpr u_int8_t kBlueChipCellInField = 5;  // кол-во желтых клеток на поле

constexpr u_int8_t kGreenChipCellInField =
    5;  // кол-во оранжевых клеток на поле

constexpr u_int8_t kRedChipCellInField = 5;  // кол-во красных клеток на поле

constexpr std::pair<int, int> kCoordBlockCells[kBlockCellsInField] = {
    {0, 1}, {0, 3}, {2, 1},
    {2, 3}, {4, 1}, {4, 3}};  // координаты всех неактивных клеток на поле

constexpr std::pair<int, int> kCoordFreeCells[kFreeCellsInField] = {
    {1, 1}, {1, 3}, {3, 1}, {3, 3}};  // координаты всех свободных клеток на
                                      // поле при старте игры

/*=== Абстрактный класс клетки игрового поля ===*/
class AbstractCell {
 public:
  AbstractCell(int type_cell) : m_type_cell(type_cell) {}
  virtual ~AbstractCell() = default;

  auto TypeCell() -> int { return m_type_cell; }
  virtual auto GetColor() -> int = 0;

 private:
  int m_type_cell;
};

/*=== Класс Фишек Игрового Поля ===*/
class ChipCell : public AbstractCell {
 public:
  ChipCell(int color_chip, int type_cell = TypeCell::kChip)
      : AbstractCell(type_cell), m_color_chip(color_chip) {}
  auto GetColor() -> int override { return m_color_chip; }
  ~ChipCell() = default;

 private:
  int m_color_chip;
};

/*=== Класс Неактивных Клеток Игрового Поля ===*/
class BlockCell : public AbstractCell {
 public:
  BlockCell(int type_cell = TypeCell::kBlock) : AbstractCell(type_cell) {}
  auto GetColor() -> int override { return Color::kNoColor; }
  ~BlockCell() = default;
};

/*=== Класс Свободных Клеток Игрового Поля ===*/
class FreeCell : public AbstractCell {
 public:
  FreeCell(int type_cell = TypeCell::kFree) : AbstractCell(type_cell) {}
  auto GetColor() -> int override { return Color::kNoColor; }
  ~FreeCell() = default;
};

/*=== Класс Игрового Поля ===*/
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
  // клетки на игровом поле
  std::vector<std::vector<AbstractCell *>> m_cell;
};

/*=== Класс Механики Игры ===*/
class GameMechanics {
 public:
  GameMechanics()
      : m_current(nullptr), m_field(nullptr), m_field_generate(false) {
    srand(time(0));
  }
  GameMechanics(GameMechanics const &other) = delete;
  GameMechanics(GameMechanics &&other) = delete;
  ~GameMechanics() { delete m_field; }

  auto operator=(GameMechanics const &other) -> GameMechanics & = delete;
  auto operator=(GameMechanics &&other) -> GameMechanics & = delete;

  // генерация игрового поля
  auto GenerateField() -> void {
    // очищаем поле если ранее было сгенерировано
    if (IsGenerateField_()) {
      delete m_field;
    }
    m_field = new PlayingField;
    //
    std::vector<std::pair<int, u_int8_t>> possible_colors(
        {{Color::kBlue, kBlueChipCellInField},
         {Color::kGreen, kGreenChipCellInField},
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
          m_field->operator[](row)[column] =
              new ChipCell(GenerateColorChip_(possible_colors));
        }
      }
    }
    m_field_generate = true;
  }

  auto ClearField() -> void {
    delete m_field;
    m_field = nullptr;
    m_field_generate = false;
  }

  auto SwitchCurrentFocusOnFiled(int row, int column) -> void {
    if (!IsGenerateField_()) {
      throw std::out_of_range("Field is not generate");
    }
    if (m_current->TypeCell() == TypeCell::kChip &&
        IsSelectedFreeCell(row, column)) {
      // std::swap(m_current, m_field->operator[](row)[column]);
      //
    } else {
      m_current = m_field->operator[](row)[column];
    }
  }

  auto IsSelectedBlockCell(int row, int column) const -> bool {
    if (!IsGenerateField_()) {
      throw std::out_of_range("Field is not generate");
    }
    return m_field->operator[](row)[column]->TypeCell() == TypeCell::kBlock;
  }

  auto IsSelectedFreeCell(int row, int column) const -> bool {
    if (!IsGenerateField_()) {
      throw std::out_of_range("Field is not generate");
    }
    return m_field->operator[](row)[column]->TypeCell() == TypeCell::kFree;
  }

  auto IsSelectedChipCell(int row, int column) const -> bool {
    if (!IsGenerateField_()) {
      throw std::out_of_range("Field is not generate");
    }
    return m_field->operator[](row)[column]->TypeCell() == TypeCell::kChip;
  }

  auto GetPossibleSwapChipInField(int row, int column) const
      -> std::vector<std::pair<int, int>> {
    std::vector<std::pair<int, int>> possible_swap;
    //
    if (IsSelectedChipCell(row, column)) {
      if (row != 0 && IsSelectedFreeCell(row - 1, column)) {
        possible_swap.push_back({row - 1, column});
      }
      if (row < kRowsField && IsSelectedFreeCell(row + 1, column)) {
        possible_swap.push_back({row + 1, column});
      }
      if (column != 0 && IsSelectedFreeCell(row, column - 1)) {
        possible_swap.push_back({row, column - 1});
      }
      if (column < kColumnsField && IsSelectedFreeCell(row, column + 1)) {
        possible_swap.push_back({row, column + 1});
      }
    }
    //
    return possible_swap;
  }

  auto PrintField() const -> void {
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        if (m_field->operator[](i)[j]->TypeCell() == TypeCell::kBlock) {
          std::cout << " o ";
        } else if (m_field->operator[](i)[j]->TypeCell() == TypeCell::kFree) {
          std::cout << "   ";
        } else {
          std::string color_print{};
          if (m_field->operator[](i)[j]->GetColor() == Color::kBlue) {
            color_print = "\033[38;2;255;255;0m";
          } else if (m_field->operator[](i)[j]->GetColor() == Color::kGreen) {
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

  auto IsBlockCell_(int row, int column) const -> bool {
    for (auto coord : kCoordBlockCells) {
      if (coord.first == row && coord.second == column) {
        return true;
      }
    }
    return false;
  }

  auto IsFreeCell_(int row, int column) const -> bool {
    for (auto coord : kCoordFreeCells) {
      if (coord.first == row && coord.second == column) {
        return true;
      }
    }
    return false;
  }

  auto IsGenerateField_() const -> bool { return m_field_generate; }

 private:
  AbstractCell *m_current;
  PlayingField *m_field;
  bool m_field_generate;
};

}  // namespace Nightmare

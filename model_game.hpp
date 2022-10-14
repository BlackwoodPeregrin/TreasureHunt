#include <iostream>
#include <random>
#include <vector>
#include <array>

namespace Nightmare {

constexpr u_int8_t kColumnsField = 5;  // ширина игрового поля
constexpr u_int8_t kRowsField = 5;  // высота игрового поля

enum TypeCell { kChip, kBlock, kFree };  // тип клетки
constexpr u_int8_t kBlockCellsInField = 6;  // кол-во неактивных клеток на поле
constexpr u_int8_t kFreeCellsInField = 4;  // кол-во свободных клеток на поле

constexpr std::pair<int, int> kCoordBlockCells[kBlockCellsInField] = {
    {0, 1}, {0, 3}, {2, 1},
    {2, 3}, {4, 1}, {4, 3}};  // координаты всех неактивных клеток на поле

constexpr std::pair<int, int> kCoordFreeCells[kFreeCellsInField] = {
    {1, 1}, {1, 3}, {3, 1}, {3, 3}};  // координаты всех свободных клеток на
                                      // поле при старте игры

enum Color { kNoColor, kBlue, kGreen, kRed };  // цвет фишки
constexpr u_int8_t kGreenChipCellInField =
    5;  // кол-во зеленых фишек на поле
constexpr u_int8_t kRedChipCellInField = 5;  // кол-во красных фишек на поле
constexpr u_int8_t kBlueChipCellInField = 5;  // кол-во синих фишек на поле


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

  auto operator==(ChipCell const &other) const -> bool {
      return m_color_chip == other.m_color_chip;
  }

  auto operator!=(ChipCell const &other) const -> bool {
      return !operator==(other);
  }

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


///*=== Класс Ожидаемого Ряда Находящегося Над Полем Игры ===*/
//class RowOverPlayingField {
//public:
// RowOverPlayingField() = default;
// RowOverPlayingField(PlayingField const &other) = delete;
// RowOverPlayingField(PlayingField &&other) = delete;
// ~RowOverPlayingField() = default;

// auto operator=(RowOverPlayingField const &other) -> PlayingField & = delete;
// auto operator=(RowOverPlayingField &&other) -> PlayingField & = delete;

// auto GenerateRow() {
//     //
// }

//protected:


//private:
// // клетки на игровом поле
// int index_row[Color::kRed];
// std::vector<ChipCell> m_cell;
//};

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
    // генерация игрового поля
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
    GenerateExpectedRow_();
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
    // если клетка является фишкой, меняю текущий указатель на фишку
    // и перезаполняю вектор возможных перемещений относительно данной клетки
    if (IsSelectedChipCell(row, column)) {
        m_current = m_field->operator[](row)[column];
        m_current_coord = {row, column};
        InstallPossibleSwapChipInField_(row, column);
    }
  }

  auto SwapCells(int row, int column) -> void {
      std::swap(m_current, m_field->operator[](row)[column]);
      // очищаем предидущие возможные перемещения
      m_possible_steps.clear();
  }

 auto GetCurrentCoord() const -> std::pair<int, int> {
    return m_current_coord;
 }

  auto IsCurrentCellIsChip() const -> bool {
      if (m_current != nullptr) {
          return m_current->TypeCell() == TypeCell::kChip;
      }
      return false;
  }

  auto IsCellPossibleStep(int row, int column) const -> bool {
      for (auto &coord : m_possible_steps) {
          if (coord.first == row && coord.second == column) {
              return true;
          }
      }
      return false;
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

  auto GetColorCell(int row, int column) const -> int {
      if (!IsGenerateField_()) {
        throw std::out_of_range("Field is not generate");
      }
      return m_field->operator[](row)[column]->GetColor();
  }

  auto GetPosRedChipInExpectedRow() const -> int {
    return m_expected_row[Color::kRed - 1].second;
  }

  auto GetPosGreenChipInExpectedRow() const -> int {
    return m_expected_row[Color::kGreen - 1].second;
  }

  auto GetPosBlueChipInExpectedRow() const -> int {
    return m_expected_row[Color::kBlue - 1].second;
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

  auto InstallPossibleSwapChipInField_(int row, int column) -> void {
    //
    if (IsSelectedChipCell(row, column)) {
      // очищаем предидущие возможные перемещения
      m_possible_steps.clear();

      if (row != 0 && IsSelectedFreeCell(row - 1, column)) {
        m_possible_steps.push_back({row - 1, column});
      }
      if (row < kRowsField && IsSelectedFreeCell(row + 1, column)) {
        m_possible_steps.push_back({row + 1, column});
      }
      if (column != 0 && IsSelectedFreeCell(row, column - 1)) {
        m_possible_steps.push_back({row, column - 1});
      }
      if (column < kColumnsField && IsSelectedFreeCell(row, column + 1)) {
        m_possible_steps.push_back({row, column + 1});
      }
    }
  }

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

  auto GenerateExpectedRow_() -> void {
      // если была сгенерирвоана, то очищаем предидущую генерацию
      if (!m_expected_row.empty()) {
          m_expected_row.clear();
      }
      //

      std::vector<ChipCell> chips({ChipCell(Color::kBlue), ChipCell(Color::kGreen), ChipCell(Color::kRed)});
      int index_chip = 0;
      std::vector<int> pos_chip_in_row({0, 2, 5});

      for (int i = 0; i < chips.size(); ++i) {
          auto random_chip_index = pos_chip_in_row[rand() % pos_chip_in_row.size()];
          m_expected_row.push_back({chips[index_chip++], random_chip_index});
          // удаление элемента из списка генерации
          for (auto it = pos_chip_in_row.begin(); it != pos_chip_in_row.end(); ++it) {
              if (*it == random_chip_index) {
                  pos_chip_in_row.erase(it);
                  break;
              }
          }
          //
      }
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
  std::pair<int, int> m_current_coord;
  AbstractCell *m_current;
  std::vector<std::pair<int, int>> m_possible_steps;
  PlayingField *m_field;
  std::vector<std::pair<ChipCell, int>> m_expected_row;
  bool m_field_generate;
};

}  // namespace Nightmare

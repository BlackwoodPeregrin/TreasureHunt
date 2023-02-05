#include <iostream>
#include <map>
#include <random>
#include <set>
#include <vector>

namespace InSearchOfTreasure {

constexpr int kColumnsField = 5;  // ширина игрового поля
constexpr int kRowsField = 5;     // высота игрового поля

enum TypeCell { kChip, kBlock, kFree };  // тип клетки
constexpr int kBlockCellsInField = 6;  // кол-во неактивных клеток на поле
constexpr int kFreeCellsInField = 4;  // кол-во свободных клеток на поле

constexpr std::pair<int, int> kCoordBlockCells[kBlockCellsInField] = {
    {0, 1}, {0, 3}, {2, 1},
    {2, 3}, {4, 1}, {4, 3}};  // координаты всех неактивных клеток на поле

constexpr std::pair<int, int> kCoordFreeCells[kFreeCellsInField] = {
    {1, 1}, {1, 3}, {3, 1}, {3, 3}};  // координаты всех свободных клеток на
                                      // поле при старте игры

enum Color { kNoColor, kBlue, kGreen, kRed };  // цвет фишки
constexpr int kGreenChipCellInField = 5;  // кол-во зеленых фишек на поле
constexpr int kRedChipCellInField = 5;  // кол-во красных фишек на поле
constexpr int kBlueChipCellInField = 5;  // кол-во синих фишек на поле

/*=== Абстрактный класс клетки игрового поля ===*/
class AbstractCell {
 public:
  AbstractCell(int type_cell) : m_type_cell(type_cell) {}
  virtual ~AbstractCell() = default;

  auto TypeCell() -> int { return m_type_cell; }
  virtual auto GetColor() const -> int = 0;

 private:
  int m_type_cell;
};

/*=== Класс Фишек Игрового Поля ===*/
class ChipCell : public AbstractCell {
 public:
  ChipCell(int color_chip)
      : AbstractCell(TypeCell::kChip), m_color_chip(color_chip) {}
  auto GetColor() const -> int override { return m_color_chip; }
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
  BlockCell() : AbstractCell(TypeCell::kBlock) {}
  auto GetColor() const -> int override { return Color::kNoColor; }
  ~BlockCell() = default;
};

/*=== Класс Свободных Клеток Игрового Поля ===*/
class FreeCell : public AbstractCell {
 public:
  FreeCell() : AbstractCell(TypeCell::kFree) {}
  auto GetColor() const -> int override { return Color::kNoColor; }
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
  GameMechanics() : m_field(nullptr), m_field_generate(false) {
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
    std::vector<std::pair<int, int>> possible_colors(
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

    // генерация финальной строки над полем
    GenerateExpectedRow_();

    m_field_generate = true;
  }

  auto ClearField() -> void {
    delete m_field;
    m_field = nullptr;
    m_field_generate = false;
  }

  // поменять местами ячейки игрвого поля
  auto SwapCells(int row, int column) -> void {
    if (IsSelectedFreeCell(row, column)) {
      std::swap(
          m_field->operator[](m_current_coord.first)[m_current_coord.second],
          m_field->operator[](row)[column]);
      // очищаем предидущие возможные перемещения
      m_possible_steps.clear();
      m_current_coord = {-1, -1};
    }
  }

  // сохранить в вектор возможные перемещения фишки на игровом поле
  auto ChangePossibleStepsChipInPlayingField(int row, int column) -> void {
    //
    if (IsSelectedChipCell(row, column)) {
      //  сохраняем текущие координаты
      m_current_coord = {row, column};
      // очищаем предидущие возможные перемещения
      m_possible_steps.clear();

      if ((row > 0) && IsSelectedFreeCell(row - 1, column)) {
        m_possible_steps.push_back({row - 1, column});
      }

      if ((row < kRowsField - 1) && IsSelectedFreeCell(row + 1, column)) {
        m_possible_steps.push_back({row + 1, column});
      }

      if ((column > 0) && IsSelectedFreeCell(row, column - 1)) {
        m_possible_steps.push_back({row, column - 1});
      }

      if ((column < kColumnsField - 1) && IsSelectedFreeCell(row, column + 1)) {
        m_possible_steps.push_back({row, column + 1});
      }
    }
  }

  auto GetVectorPossibleSteps() const -> std::vector<std::pair<int, int>> {
    return m_possible_steps;
  }

  // получить координаты выбранной игровой фишки на поле
  auto GetCurrentCoord() const -> std::pair<int, int> {
    return m_current_coord;
  }

  // является ли ячейка возможным перемещением
  auto IsCellPossibleStep(int row, int column) const -> bool {
    for (auto &coord : m_possible_steps) {
      if (coord.first == row && coord.second == column) {
        return true;
      }
    }
    return false;
  }

  // является ли выбранная ячейка неактивной
  auto IsSelectedBlockCell(int row, int column) const -> bool {
    if (!IsGenerateField_()) {
      throw std::out_of_range("Field is not generate");
    }
    return m_field->operator[](row)[column]->TypeCell() == TypeCell::kBlock;
  }

  // является ли выбранная ячейка свободной
  auto IsSelectedFreeCell(int row, int column) const -> bool {
    if (!IsGenerateField_()) {
      throw std::out_of_range("Field is not generate");
    }
    return m_field->operator[](row)[column]->TypeCell() == TypeCell::kFree;
  }

  // является ли выбранная ячейка игровой фишкой
  auto IsSelectedChipCell(int row, int column) const -> bool {
    if (!IsGenerateField_()) {
      throw std::out_of_range("Field is not generate");
    }
    return m_field->operator[](row)[column]->TypeCell() == TypeCell::kChip;
  }

  // получить цвет выбранной ячейки
  auto GetColorCell(int row, int column) const -> int {
    if (!IsGenerateField_()) {
      throw std::out_of_range("Field is not generate");
    }
    return m_field->operator[](row)[column]->GetColor();
  }

  auto GetPosRedChipInExpectedRow() const -> int {
    auto iter = m_expected_row.find(Color::kRed);
    return (*iter).second;
  }

  auto GetPosGreenChipInExpectedRow() const -> int {
    auto iter = m_expected_row.find(Color::kGreen);
    return (*iter).second;
  }

  auto GetPosBlueChipInExpectedRow() const -> int {
    auto iter = m_expected_row.find(Color::kBlue);
    return (*iter).second;
  }

  // проверка на победу в игре
  auto IsGameVictory() const -> bool {
    for (auto [color, index_column] : m_expected_row) {
      for (int row = 0; row < kRowsField; ++row) {
        if (color != m_field->operator[](row)[index_column]->GetColor()) {
          return false;
        }
      }
    }
    return true;
  }

 protected:
  auto GenerateColorChip_(std::vector<std::pair<int, int>> &possible_colors)
      -> int {
    //
    int index_color = rand() % possible_colors.size();
    int color = possible_colors[index_color].first;
    if (--possible_colors[index_color].second == 0) {
      auto iter = possible_colors.begin();
      for (int i = 0; i < index_color; ++i) {
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

    int colors[Color::kRed]{Color::kBlue, Color::kGreen, Color::kRed};
    std::set<int> pos_chip_in_row({0, 2, 4});

    for (int i = 0; i < Color::kRed; ++i) {
      int r_index = rand() % pos_chip_in_row.size();
      auto iter = pos_chip_in_row.begin();
      for (int j = 0; j < r_index; ++j) {
        ++iter;
      }
      m_expected_row.insert({colors[i], *iter});
      // удаление элемента из списка генерации
      pos_chip_in_row.erase(iter);
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
  std::pair<int, int> m_current_coord{-1, -1};
  std::vector<std::pair<int, int>> m_possible_steps;
  PlayingField *m_field;
  std::map<int, int> m_expected_row;
  bool m_field_generate;
};

}  // namespace InSearchOfTreasure

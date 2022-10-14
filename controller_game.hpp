#ifndef ControllerGame_GAME_HPP
#define ControllerGame_GAME_HPP

#include "model_game.hpp"

namespace Nightmare {
// контроллер реализован в паттерне Singletone
class ControllerGame {
private:
    ControllerGame() = default;
    ControllerGame(ControllerGame const &other) = delete;
    ControllerGame(ControllerGame &&other) = delete;
    ~ControllerGame() = default;

    ControllerGame &operator=(ControllerGame const &other) = delete;
    ControllerGame &operator=(ControllerGame &&other) = delete;
public:
    //
    static auto getInstance() -> ControllerGame& {
        static ControllerGame controller{};
        return controller;
    }
    //

    auto GenerateField() -> void {
        // генерация игрового поля
        m_model.GenerateField();
    }

    auto ClearField() -> void {
        // очистка игрового поля
        m_model.ClearField();
    }

    auto IsSelectedBlockCell(int row, int column) const -> bool {
        try {
            return m_model.IsSelectedBlockCell(row, column);
        } catch (std::exception const &e) {
            // игровое поле не инициализированно
            return false;
        }
    }

    auto IsSelectedFreeCell(int row, int column) const -> bool {
        try {
            return m_model.IsSelectedFreeCell(row, column);
        } catch (std::exception const &e) {
            // игровое поле не инициализированно
            return false;
        }

    }

    auto IsSelectedChipCell(int row, int column) const -> bool {
        try {
            return m_model.IsSelectedChipCell(row, column);
        } catch (std::exception const &e) {
            // игровое поле не инициализированно
            return false;
        }
    }

    auto GetColorCell(int row, int column) const -> int {
        try {
            return m_model.GetColorCell(row, column);
        } catch (std::exception const &e) {
            // игровое поле не инициализированно
            return -1;
        }
    }

    auto GetPosRedChipInExpectedRow() const -> int {
        return m_model.GetPosRedChipInExpectedRow();
    }

    auto GetPosGreenChipInExpectedRow() const -> int {
        return m_model.GetPosGreenChipInExpectedRow();
    }

    auto GetPosBlueChipInExpectedRow() const -> int {
        return m_model.GetPosBlueChipInExpectedRow();
    }

//    auto GetPossibleSwapChipInField(int row, int column) const
//    -> std::vector<std::pair<int, int>> {
//        return m_model.GetPossibleSwapChipInField(row, column);
//    }

    auto SwitchCurrentFocusOnFiled(int row, int column) -> void {
        m_model.SwitchCurrentFocusOnFiled(row, column);
    }

    auto IsCellPossibleStep(int row, int column) const -> bool {
        return m_model.IsCellPossibleStep(row, column);
    }

    auto GetCurrentCoord() const -> std::pair<int, int> {
        return m_model.GetCurrentCoord();
    }

    auto SwapCells(int row, int column) -> void {
        m_model.SwapCells(row, column);
    }


private:
    GameMechanics m_model;
};

}
#endif // ControllerGame_GAME_HPP

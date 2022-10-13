#ifndef CONTROLLER_GAME_HPP
#define CONTROLLER_GAME_HPP

#include "model_game.hpp"

namespace Nightmare {
// контроллер реализован в паттерне Singletone
class Controller {
private:
    Controller() = default;
    Controller(Controller const &other) = delete;
    Controller(Controller &&other) = delete;
    ~Controller() = default;

    Controller &operator=(Controller const &other) = delete;
    Controller &operator=(Controller &&other) = delete;
public:
    //
    static auto getInstance() -> Controller& {
        static Controller controller{};
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

    auto GetPossibleSwapChipInField(int row, int column) const
    -> std::vector<std::pair<int, int>> {
        return m_model.GetPossibleSwapChipInField(row, column);
    }


private:
    GameMechanics m_model;
};

}
#endif // CONTROLLER_GAME_HPP

#ifndef STYLE_HELPER_H
#define STYLE_HELPER_H

#include <QString>

class StyleHelper
{
public:
    StyleHelper() = default;
    ~StyleHelper() = default;

    static auto getMainWidgetsStyle() -> QString {
        return "QWidget {"
               "   background-image: url(:/img/background.jpg);"
               "};";
    }

    static auto getDialogWindowStyle() -> QString {
        return "QDialog {"
               "   background-image: url(:/img/deck.jpg);"
               "};";
    }

    static auto getStyleLabel() -> QString {
        return "QLabel {"
               "   font-size: 15px;"
               "};";
    }

    static auto getStartGameAboutGameButtonStyle() -> QString {
        return "QPushButton {"
               "   background: none;"
               "   background-color: rgb(170, 118, 92);"
               "   border: none;"
               "   border-style: solid;"
               "   border-width: 2px;"
               "   border-radius: 15px;"
               "   border-color: gray;"
               "   font-size: 15px;"
               "}\n"
               "QPushButton:hover {"
                "   border-style: solid;"
                "   border-width: 2px;"
                "   border-color: black;"
               "};";
    }

    static auto getStartGameButtonIcon() -> QString {
        return ":/img/play.png";
    }

    static auto getStopGameButtonIcon() -> QString {
        return ":/img/pause.png";
    }

    static auto getAboutGameButtonIcon() -> QString {
        return ":/img/info.png";
    }

    static auto getReleasedButtonStyle() -> QString {
        return "QPushButton {"
               "   background: none;"
               "   background-image: url(:/img/deck.jpg);"
               "   border-radius: 15px;"
               "}\n"
               "QPushButton:hover {"
                "   border-style: solid;"
                "   border-width: 3px;"
                "   border-color: black;"
               "};";
    }

     static auto getPressedButtonStyle() -> QString {
        return "QPushButton {"
               "   background: none;"
               "   background-image: url(:/img/deck.jpg);"
               "   border-style: solid;"
               "   border-width: 3px;"
               "   border-color: rgb(0, 214, 120);"
               "   border-radius: 15px;"
               "};";
    }

     static auto getPressedButtonChooseStyle() -> QString {
        return "QPushButton {"
               "   background: none;"
               "   background-image: url(:/img/deck.jpg);"
               "   border-style: solid;"
               "   border-width: 3px;"
               "   border-color: #ffba00;"
               "   border-radius: 15px;"
               "};";
    }

     static auto getButtonStyleUnderGameField() -> QString {
        return "QPushButton {"
               "   background: none;"
               "   border: none;"
               "   border-radius: 15px;"
               "};";
    }

    static auto getPathToRubyIcon() -> QString {
        return ":/img/ruby.png";
    }

    static auto getPathToEmeraldIcon() -> QString {
        return ":/img/emeralds.png";
    }

    static auto getPathToSaphfireIcon() -> QString {
        return ":/img/saphfire.png";
    }

    static auto getPathToBoxIcon() -> QString {
        return ":/img/box.png";
    }

};

#endif // STYLE_HELPER_H

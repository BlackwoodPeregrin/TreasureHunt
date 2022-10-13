#ifndef STYLE_HELPER_H
#define STYLE_HELPER_H

#include <QString>

class StyleHelper
{
public:
    StyleHelper() = default;
    ~StyleHelper() = default;

    inline static QString getMainWidgetsStyle() {
        return "QWidget {"
               "   background-image: url(:/img/background.jpg);"
               "};";
    }

    inline static QString getStartGameAboutGameButtonStyle() {
        return "QPushButton {"
               "   background: none;"
               "   background-color: rgb(170, 118, 92);"
               "   border: none;"
               "   border-radius: 15px;"
               "   border-color: gray;"
               "}\n"
               "QPushButton:hover {"
                "   border-style: solid;"
                "   border-width: 2px;"
                "   border-color: black;"
               "};";
    }

    inline static QString getReleasedButtonStyle() {
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

    inline static QString getPressedButtonStyle() {
        return "QPushButton {"
               "   background: none;"
               "   background-image: url(:/img/deck.jpg);"
               "   border-style: solid;"
               "   border-width: 3px;"
               "   border-color: rgb(170, 118, 92);"
               "   border-radius: 15px;"
               "};";
    }

    inline static QString getGamePushButtonResultStyle() {
        return "QPushButton {"
               "   background: none;"
               "   border: none;"
               "   border-radius: 15px;"
               "};";
    }

    inline static QString getPathToRubyTexture() {
        return ":/img/ruby.png";
    }

    inline static QString getPathToEmeraldTexture() {
        return ":/img/emeralds.png";
    }

    inline static QString getPathToSaphfireTexture() {
        return ":/img/saphfire.png";
    }

    inline static QString getPathToBoxTexture() {
        return ":/img/box.png";
    }

};

#endif // STYLE_HELPER_H

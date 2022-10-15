#ifndef VICTORY_DIALOG_H
#define VICTORY_DIALOG_H

#include <QDialog>
#include "ui_victory_dialog.h"
#include "style_helper.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class VictoryDialog;
}
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Nightmare {

class VictoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VictoryDialog(QWidget *parent = nullptr)
        : QDialog(parent),
          ui(new Ui::VictoryDialog) {
        ui->setupUi(this);
        this->setStyleSheet(StyleHelper::getDialogWindowStyle());
        ui->pushButton_restart->setStyleSheet(StyleHelper::getStartGameAboutGameButtonStyle());
        ui->pushButton_end->setStyleSheet(StyleHelper::getStartGameAboutGameButtonStyle());
        ui->label->setStyleSheet(StyleHelper::getStyleLabel());
    }
    ~VictoryDialog() { delete ui; }

signals:
    void restart();
    void end();

private slots:
    void on_pushButton_end_clicked() {
        emit end();
    }
    void on_pushButton_start_clicked() {
        emit restart();
    }
private:
    Ui::VictoryDialog *ui;
};
}
#endif // VICTORY_DIALOG_H

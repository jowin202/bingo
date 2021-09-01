#ifndef MANAGEGAMEWIDGET_H
#define MANAGEGAMEWIDGET_H

#include <QList>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QTimer>

#include "protocol.h"
#include "game.h"

namespace Ui {
class ManageGameWidget;
}

class ManageGameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManageGameWidget(QWidget *parent = nullptr);
    ~ManageGameWidget();
    void set_game_id(int game_id);
    void reset_buttons(int start);
    void lock_game();
    void setProtocol( Protocol *protocol);

private slots:
    void reset();
    void num_button_pressed();
    void draw_num_button_pressed();
    void on_btn_create_instance_clicked();
    void on_button_rand_instance_clicked();
    void show_drawn_nums(QVariantList nums);



    void on_btn_refresh_boards_clicked();

    void on_refresh_drawn_nums_button_clicked();

    void on_draw_random_button_clicked();

private:
    Ui::ManageGameWidget *ui;
    QList <QLabel*> label_list;
    QList <QPushButton*> button_list;
    QList <QPushButton*> draw_button_list;
    int state;
    int game_id;
    Protocol *protocol;
};

#endif // MANAGEGAMEWIDGET_H

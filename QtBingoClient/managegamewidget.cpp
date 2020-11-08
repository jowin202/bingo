#include "managegamewidget.h"
#include "ui_managegamewidget.h"

ManageGameWidget::ManageGameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageGameWidget)
{
    ui->setupUi(this);

    connect(this->ui->btn_reset, SIGNAL(pressed()), this, SLOT(reset()));
    this->label_list.append(this->ui->label_b1);
    this->label_list.append(this->ui->label_b2);
    this->label_list.append(this->ui->label_b3);
    this->label_list.append(this->ui->label_b4);
    this->label_list.append(this->ui->label_b5);

    this->label_list.append(this->ui->label_i1);
    this->label_list.append(this->ui->label_i2);
    this->label_list.append(this->ui->label_i3);
    this->label_list.append(this->ui->label_i4);
    this->label_list.append(this->ui->label_i5);

    this->label_list.append(this->ui->label_n1);
    this->label_list.append(this->ui->label_n2);
    this->label_list.append(this->ui->label_n3);
    this->label_list.append(this->ui->label_n4);
    this->label_list.append(this->ui->label_n5);

    this->label_list.append(this->ui->label_g1);
    this->label_list.append(this->ui->label_g2);
    this->label_list.append(this->ui->label_g3);
    this->label_list.append(this->ui->label_g4);
    this->label_list.append(this->ui->label_g5);

    this->label_list.append(this->ui->label_o1);
    this->label_list.append(this->ui->label_o2);
    this->label_list.append(this->ui->label_o3);
    this->label_list.append(this->ui->label_o4);
    this->label_list.append(this->ui->label_o5);


    this->button_list.append(this->ui->btn1);
    this->button_list.append(this->ui->btn2);
    this->button_list.append(this->ui->btn3);
    this->button_list.append(this->ui->btn4);
    this->button_list.append(this->ui->btn5);
    this->button_list.append(this->ui->btn6);
    this->button_list.append(this->ui->btn7);
    this->button_list.append(this->ui->btn8);
    this->button_list.append(this->ui->btn9);
    this->button_list.append(this->ui->btn10);
    this->button_list.append(this->ui->btn11);
    this->button_list.append(this->ui->btn12);
    this->button_list.append(this->ui->btn13);
    this->button_list.append(this->ui->btn14);
    this->button_list.append(this->ui->btn15);

    for (int i = 0; i < this->button_list.length(); i++)
    {
        connect(this->button_list.at(i), SIGNAL(pressed()), this, SLOT(num_button_pressed()));
    }

    this->reset();



    this->draw_button_list.append(this->ui->draw_button_1);
    this->draw_button_list.append(this->ui->draw_button_2);
    this->draw_button_list.append(this->ui->draw_button_3);
    this->draw_button_list.append(this->ui->draw_button_4);
    this->draw_button_list.append(this->ui->draw_button_5);
    this->draw_button_list.append(this->ui->draw_button_6);
    this->draw_button_list.append(this->ui->draw_button_7);
    this->draw_button_list.append(this->ui->draw_button_8);
    this->draw_button_list.append(this->ui->draw_button_9);
    this->draw_button_list.append(this->ui->draw_button_10);
    this->draw_button_list.append(this->ui->draw_button_11);
    this->draw_button_list.append(this->ui->draw_button_12);
    this->draw_button_list.append(this->ui->draw_button_13);
    this->draw_button_list.append(this->ui->draw_button_14);
    this->draw_button_list.append(this->ui->draw_button_15);
    this->draw_button_list.append(this->ui->draw_button_16);
    this->draw_button_list.append(this->ui->draw_button_17);
    this->draw_button_list.append(this->ui->draw_button_18);
    this->draw_button_list.append(this->ui->draw_button_19);
    this->draw_button_list.append(this->ui->draw_button_20);
    this->draw_button_list.append(this->ui->draw_button_21);
    this->draw_button_list.append(this->ui->draw_button_22);
    this->draw_button_list.append(this->ui->draw_button_23);
    this->draw_button_list.append(this->ui->draw_button_24);
    this->draw_button_list.append(this->ui->draw_button_25);
    this->draw_button_list.append(this->ui->draw_button_26);
    this->draw_button_list.append(this->ui->draw_button_27);
    this->draw_button_list.append(this->ui->draw_button_28);
    this->draw_button_list.append(this->ui->draw_button_29);
    this->draw_button_list.append(this->ui->draw_button_30);
    this->draw_button_list.append(this->ui->draw_button_31);
    this->draw_button_list.append(this->ui->draw_button_32);
    this->draw_button_list.append(this->ui->draw_button_33);
    this->draw_button_list.append(this->ui->draw_button_34);
    this->draw_button_list.append(this->ui->draw_button_35);
    this->draw_button_list.append(this->ui->draw_button_36);
    this->draw_button_list.append(this->ui->draw_button_37);
    this->draw_button_list.append(this->ui->draw_button_38);
    this->draw_button_list.append(this->ui->draw_button_39);
    this->draw_button_list.append(this->ui->draw_button_40);
    this->draw_button_list.append(this->ui->draw_button_41);
    this->draw_button_list.append(this->ui->draw_button_42);
    this->draw_button_list.append(this->ui->draw_button_43);
    this->draw_button_list.append(this->ui->draw_button_44);
    this->draw_button_list.append(this->ui->draw_button_45);
    this->draw_button_list.append(this->ui->draw_button_46);
    this->draw_button_list.append(this->ui->draw_button_47);
    this->draw_button_list.append(this->ui->draw_button_48);
    this->draw_button_list.append(this->ui->draw_button_49);
    this->draw_button_list.append(this->ui->draw_button_50);
    this->draw_button_list.append(this->ui->draw_button_51);
    this->draw_button_list.append(this->ui->draw_button_52);
    this->draw_button_list.append(this->ui->draw_button_53);
    this->draw_button_list.append(this->ui->draw_button_54);
    this->draw_button_list.append(this->ui->draw_button_55);
    this->draw_button_list.append(this->ui->draw_button_56);
    this->draw_button_list.append(this->ui->draw_button_57);
    this->draw_button_list.append(this->ui->draw_button_58);
    this->draw_button_list.append(this->ui->draw_button_59);
    this->draw_button_list.append(this->ui->draw_button_60);
    this->draw_button_list.append(this->ui->draw_button_61);
    this->draw_button_list.append(this->ui->draw_button_62);
    this->draw_button_list.append(this->ui->draw_button_63);
    this->draw_button_list.append(this->ui->draw_button_64);
    this->draw_button_list.append(this->ui->draw_button_65);
    this->draw_button_list.append(this->ui->draw_button_66);
    this->draw_button_list.append(this->ui->draw_button_67);
    this->draw_button_list.append(this->ui->draw_button_68);
    this->draw_button_list.append(this->ui->draw_button_69);
    this->draw_button_list.append(this->ui->draw_button_70);
    this->draw_button_list.append(this->ui->draw_button_71);
    this->draw_button_list.append(this->ui->draw_button_72);
    this->draw_button_list.append(this->ui->draw_button_73);
    this->draw_button_list.append(this->ui->draw_button_74);
    this->draw_button_list.append(this->ui->draw_button_75);

    for (int i = 0; i < this->draw_button_list.length(); i++)
    {
        this->draw_button_list.at(i)->setText(QString::number(i+1));
        connect(this->draw_button_list.at(i), SIGNAL(pressed()), this, SLOT(draw_num_button_pressed()));
    }
}

ManageGameWidget::~ManageGameWidget()
{
    delete ui;
}

void ManageGameWidget::set_game_id(int game_id)
{
    this->game_id = game_id;
}

void ManageGameWidget::reset()
{
    this->state = 0;
    this->reset_buttons(1);
    for (int i = 0; i < this->label_list.length(); i++)
    {
        this->label_list.at(i)->setText("");
    }
    this->ui->btn_create_instance->setEnabled(false);
}

void ManageGameWidget::reset_buttons(int start)
{
    for (int i = 0; i < this->button_list.length(); i++)
    {
        this->button_list.at(i)->setText(QString::number(start+i));
        this->button_list.at(i)->setEnabled(true);
    }
}

void ManageGameWidget::lock_game()
{
    for (int i = 0; i < this->button_list.length(); i++)
    {
        this->button_list.at(i)->setEnabled(false);
    }
    this->ui->btn_create_instance->setEnabled(true);
}

void ManageGameWidget::setProtocol(Protocol *protocol)
{
    this->protocol = protocol;
}

void ManageGameWidget::num_button_pressed()
{
    QPushButton *btn = (QPushButton*) sender();

    if (btn != 0)
    {
        btn->setEnabled(false);
        this->label_list.at(this->state)->setText(btn->text());
        this->state++;
        if (state == 5)
            this->reset_buttons(16);
        else if (state == 10)
            this->reset_buttons(31);
        else if (state == 15)
            this->reset_buttons(46);
        else if (state == 20)
            this->reset_buttons(61);
        else if (state == 25)
            this->lock_game();

    }
}

void ManageGameWidget::draw_num_button_pressed()
{
    QPushButton *btn = (QPushButton*) sender();
    if (btn != 0)
    {
        int value = btn->text().toInt();

    }
}

void ManageGameWidget::on_btn_create_instance_clicked()
{
    QList<int> numbers;
    for (int i = 0; i < this->label_list.length(); i++)
    {
        numbers.append(this->label_list.at(i)->text().toInt());
    }
    this->protocol->create_instance(this->game_id, this->ui->input_user->text(),numbers);
}

void ManageGameWidget::on_button_rand_instance_clicked()
{
    this->protocol->create_instance(this->game_id, this->ui->input_rand_inst_name->text(),QList<int>());
    this->ui->input_rand_inst_name->setText("");
}

#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QWidget>

class CustomButton : public QPushButton
{
public:
    CustomButton();
    void set_id(int id);
    int get_id();

    void set_name(QString name);
    QString get_name();

private:
    int id;
    QString name;
};

#endif // CUSTOMBUTTON_H

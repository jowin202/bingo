#include "custombutton.h"

CustomButton::CustomButton()
{
}

void CustomButton::set_id(int id)
{
    this->id = id;
}

int CustomButton::get_id()
{
    return this->id;
}

void CustomButton::set_name(QString name)
{
    this->name = name;
}

QString CustomButton::get_name()
{
    return this->name;
}

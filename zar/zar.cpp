#include "zar.h"

zar::Zar::Zar()
{
}

zar::Zar::Zar(std::string name_class)
{
    this->name_class = name_class;
    this->show_class();
}

std::string zar::Zar::get_name() const
{
    return name_class;
}

void zar::Zar::show_class() const
{
    spdlog::info("core: {}", get_name());
}

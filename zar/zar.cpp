#include "zar.h"

#include <utility>

zar::Zar::Zar()
{
}

zar::Zar::Zar(std::string name_class)
{
    this->name_class = std::move(name_class);
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

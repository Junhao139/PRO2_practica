#include "ship.hh"

Ship::Ship() {
    
}

Ship::~Ship() {

}

void Ship::wanted_products(int32_t& wanted, int& wanted_number) const {
    wanted          = this->wanted;
    wanted_number   = this->wanted_quantity;
}

void Ship::for_sell_products(int32_t& for_sell, int& for_sell_number) const {
    for_sell        = this->for_sell;
    for_sell_number = this->for_sell_quantity;
}

void Ship::set_all(int32_t wanted, int wanted_number, int32_t for_sell, int for_sell_number) {
    this->wanted            = wanted;
    this->wanted_quantity   = wanted_number;
    this->for_sell          = for_sell;
    this->for_sell_quantity = for_sell_number;
}

void Ship::add_destination(string const& city_id) {
    visited_cities.push_back(city_id);
}
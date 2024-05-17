#include "ship.hh"

Ship::Ship() {
    
}

Ship::~Ship() {

}

uint32_t Ship::wanted_product() const {
    return this->wanted;
}

int Ship::wanted_number() const {
    return this->wanted_quantity;
}

uint32_t Ship::for_sell_product() const {
    return this->for_sell;
}

int Ship::for_sell_number() const {
    return this->for_sell_quantity;
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

void Ship::write_all_destinations() const {
    for (int i = 0; i < this->visited_cities.size(); ++i) {
        cout << this->visited_cities[i] << endl;
    }
}

void Ship::clear_all_destinations() {
    this->visited_cities.clear();
}
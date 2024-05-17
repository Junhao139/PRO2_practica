#include "city.hh"

City::City() {
    this->inventory_disposition = false;
    this->total_mass = 0;
    this->total_volume = 0;
}

City::~City() {

}

void City::clear_inventory() {
    this->inventory.clear();
    this->inventory_disposition = false;
    this->total_mass = 0;
    this->total_volume = 0;
}

void City::add_product_to_inventory(uint32_t identifier, ProductData const& pd, int in_demand, int available) {
    this->inventory_disposition = true;
    ProductDemand pdm = {
        .in_demand = in_demand,
        .available = available
    };
    this->inventory.insert(pair<uint32_t,ProductDemand>(identifier, pdm));

    // declare a "nothing" product
    Product product(0, 0);
    pd.consult_product(product, identifier);
    this->total_mass    += product.get_mass() * available;
    this->total_volume  += product.get_volume() * available;
}

void City::set_product_in_inventory(uint32_t identifier, ProductData const& pd, int in_demand, int available) {
    this->inventory_disposition = true;
    ProductDemand pdm = {
        .in_demand = in_demand,
        .available = available
    };

    map<uint32_t, ProductDemand>::iterator it = this->inventory.find(identifier);
    ProductDemand previous_demand = it->second;

    // declare a "nothing" product
    Product product(0, 0);
    pd.consult_product(product, identifier);
    this->total_mass    += product.get_mass() * (available - previous_demand.available);
    this->total_volume  += product.get_volume() * (available - previous_demand.available);

    it->second = pdm;
}

bool City::exist_in_inventory(uint32_t product) const {
    if (not this->has_inventory()) {
        return false;
    }
    auto it = this->inventory.find(product);
    return it != this->inventory.end();
}

void City::consult_product(uint32_t identifier, int& in_demand, int& available) const {
    auto it = this->inventory.find(identifier);
    in_demand = it->second.in_demand;
    available = it->second.available;
}

void City::delete_product(uint32_t identifier, ProductData const& pd) {
    auto it = this->inventory.find(identifier);

    // declare a "nothing" product
    Product product(0, 0);
    pd.consult_product(product, identifier);

    this->total_mass    -= product.get_mass() * it->second.available;
    this->total_volume  -= product.get_volume() * it->second.available;

    this->inventory.erase(it);
}

void City::total_mass_and_volume(int& mass, int& volume) const {
    mass = this->total_mass;
    volume = this->total_volume;
}

bool City::has_inventory() const {
    return this->inventory_disposition;
}

void City::commercialize_with(City& foreign, ProductData const& pd) {
    // if one doesn't have inventory then nothing to commmercialize
    if (this->has_inventory() and foreign.has_inventory()) {
        auto map_city_1_it  = this->inventory.begin();
        auto map_city_1_end = this->inventory.end();
        auto map_city_2_it  = foreign.inventory.begin();
        auto map_city_2_end = foreign.inventory.end();

        City& city_1 = *this;
        City& city_2 = foreign;

        // while both have not reached the end
        while (map_city_1_it != map_city_1_end and map_city_2_it != map_city_2_end) {

            // compare the product tag (a uint32_t integer)
            if (map_city_1_it->first < map_city_2_it->first) {
                ++map_city_1_it;
            }
            else if (map_city_1_it->first > map_city_2_it->first) {
                ++map_city_2_it;
            }
            else { 
                // they have got the same product!
                ProductDemand& city1_demand = map_city_1_it->second;
                ProductDemand& city2_demand = map_city_2_it->second;

                Product product_info(0, 0);
                pd.consult_product(product_info, map_city_1_it->first);

                // if city_1 has more than it needs of what city_2 needs
                if (city1_demand.available > city1_demand.in_demand and city2_demand.available < city2_demand.in_demand) {
                    int city1_can_sell = city1_demand.available - city1_demand.in_demand;
                    int city2_needs_to_buy = city2_demand.in_demand - city2_demand.available;
                    // city_1 can fully satisfy city_2's needs
                    if (city1_can_sell >= city2_needs_to_buy) {
                        city1_demand.available -= city2_needs_to_buy;
                        city_1.total_mass   -= city2_needs_to_buy * product_info.get_mass();
                        city_1.total_volume -= city2_needs_to_buy * product_info.get_volume();

                        city2_demand.available += city2_needs_to_buy;
                        city_2.total_mass   += city2_needs_to_buy * product_info.get_mass();
                        city_2.total_volume += city2_needs_to_buy * product_info.get_volume();
                    } else {
                        city1_demand.available -= city1_can_sell;
                        city_1.total_mass   -= city1_can_sell * product_info.get_mass();
                        city_1.total_volume -= city1_can_sell * product_info.get_volume();

                        city2_demand.available += city1_can_sell;
                        city_2.total_mass   += city1_can_sell * product_info.get_mass();
                        city_2.total_volume += city1_can_sell * product_info.get_volume();
                    }
                }
                // if city_1 needs what in city_2 exceeded
                else if (city2_demand.available > city2_demand.in_demand and city1_demand.available < city1_demand.in_demand) {
                    int city2_can_sell = city2_demand.available - city2_demand.in_demand;
                    int city1_needs_to_buy = city1_demand.in_demand - city1_demand.available;
                    // city_2 can fully satisfy city_1's needs
                    if (city2_can_sell >= city1_needs_to_buy) {
                        city2_demand.available -= city1_needs_to_buy;
                        city_2.total_mass   -= city1_needs_to_buy * product_info.get_mass();
                        city_2.total_volume -= city1_needs_to_buy * product_info.get_volume();

                        city1_demand.available += city1_needs_to_buy;
                        city_1.total_mass   += city1_needs_to_buy * product_info.get_mass();
                        city_1.total_volume += city1_needs_to_buy * product_info.get_volume();
                    } else {
                        city2_demand.available -= city2_can_sell;
                        city_2.total_mass   -= city2_can_sell * product_info.get_mass();
                        city_2.total_volume -= city2_can_sell * product_info.get_volume();

                        city1_demand.available += city2_can_sell;
                        city_1.total_mass   += city2_can_sell * product_info.get_mass();
                        city_1.total_volume += city2_can_sell * product_info.get_volume();
                    }
                }

                ++map_city_1_it;
                ++map_city_2_it;
            }            
        }
    }
}

void City::write_inventory() const {
    if (this->has_inventory()) {
        auto it = this->inventory.begin();
        auto end = this->inventory.end();

        while (it != end) {
            cout << it->first << ' '
                 << it->second.available << ' ' << it->second.in_demand
                 << endl;
            ++it;
        }   
    }
}
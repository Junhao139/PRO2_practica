#include "river.hh"

BinTree<string> River::read_input_bin_tree() {
    string input;
    cin >> input;
    if (input == "#") {
        return BinTree<string>();
    }

    // to make this city exist in inventory
    this->inventory_database.insert(pair<string, City>(input, City()));

    auto left = read_input_bin_tree();
    auto right = read_input_bin_tree();
    return BinTree<string>(input, left, right);
}

void River::ship_seek_all_routes(
    list<pair<int, pair<string, SalesStatus>>>& all_destinations,
    Ship const& ship,
    int steps,
    SalesStatus accumulated_sale,
    BinTree<string> this_city
) {
    if (this_city.empty()) {
        // force to do nothing
        return;
    }

    // ship "simulates" a commercialization with this city
    auto it = this->inventory_database.find(this_city.value());
    
    // only commercializes if the city has more than it needs
    int ship_wanted_in_demand_in_city,      ship_wanted_available_in_city,
        ship_for_sell_in_demand_in_city,    ship_for_sell_available_in_city;
    
    // if the city has the wanted product
    if (it->second.exist_in_inventory(ship.wanted_product())) {
        it->second.consult_product(ship.wanted_product(), ship_wanted_in_demand_in_city, ship_wanted_available_in_city);

        // city has more than it needs of what the ship wanted 
        if (ship_wanted_available_in_city > ship_wanted_in_demand_in_city) {
            // buy them
            accumulated_sale.bought_units +=
                ship_wanted_available_in_city - ship_wanted_in_demand_in_city;
        }
    }

    // if the city has the selling product
    if (it->second.exist_in_inventory(ship.for_sell_product())) {
        it->second.consult_product(ship.for_sell_product(), ship_for_sell_in_demand_in_city, ship_for_sell_available_in_city);

        // city has less than it needs of what the ship is selling
        if (ship_for_sell_available_in_city < ship_for_sell_in_demand_in_city) {
            // sell them
            accumulated_sale.sold_units +=
                ship_for_sell_in_demand_in_city - ship_for_sell_available_in_city;
        }
    }

    // if this is a leaf
    if (this_city.left().empty() and this_city.right().empty()) {
        pair<string, SalesStatus> city_info(this_city.value(), accumulated_sale);
        pair<int, pair<string, SalesStatus>> node_info(steps, city_info);
        all_destinations.push_back(node_info);
    } else {
        // proceeds to continue with the recursion
        // if this branch has only one sub-branch, nothing will be affected.
        ship_seek_all_routes(all_destinations, ship, steps + 1, accumulated_sale, this_city.left());
        ship_seek_all_routes(all_destinations, ship, steps + 1, accumulated_sale, this_city.right());
    }
}

bool River::ship_get_route(
    list<string>& route,
    pair<int, string>& verifier,
    int steps,
    BinTree<string> this_city
) {
    // if this is empty, this is not on the right path
    // if this does not verify the depth, neither is on the right path
    if (this_city.empty() or steps > verifier.first) {
        return false;
    }

    // if more depth is needed, then proceed to get in
    if (steps < verifier.first) {
        route.push_back(this_city.value());
        bool is_on_the_left = ship_get_route(route, verifier, steps + 1, this_city.left());
        if (not is_on_the_left) {
            // the route does not come from the left
            bool is_on_the_right = ship_get_route(route, verifier, steps + 1, this_city.right());
            if (not is_on_the_right) {
                // the route does not contain this node
                route.pop_back();
                return false;
            } else {
                // the route is found on the right side!
                return is_on_the_right;
            }
        } else {
            // the route is found on the left side!
            return true;
        }
    }
    
    // now, steps == verifier.first
    if (this_city.value() == verifier.second) {
        // this is the right route!
        route.push_back(this_city.value());
        return true;
    } else {
        return false;
    }
}

void River::ship_transact(string const& city_name, Ship& ship, ProductData const& pddata) {
    auto city_it = this->inventory_database.find(city_name);

    int ship_wanted_product_count   = ship.wanted_number();
    int ship_for_sell_product_count = ship.for_sell_number();

    if (city_it->second.exist_in_inventory(ship.wanted_product())) {
        int ship_wanted_in_demand, ship_wanted_available;
        city_it->second.consult_product(ship.wanted_product(), ship_wanted_in_demand, ship_wanted_available);
        // only transact if the city has more than it needs
        if (ship_wanted_available > ship_wanted_in_demand) {
            int available_for_purchase = ship_wanted_available - ship_wanted_in_demand;
            if (ship.wanted_number() <= available_for_purchase) {
                city_it->second.set_product_in_inventory(ship.wanted_product(), pddata, ship_wanted_in_demand, ship_wanted_available - ship.wanted_number());
                // now the ship dows not need this product anymore
                ship_wanted_product_count = 0;
            } else {
                // now the ship bought some, the inventory of the city reduced to exactly how many it needs
                ship_wanted_product_count -= available_for_purchase;
                city_it->second.set_product_in_inventory(ship.wanted_product(), pddata, ship_wanted_in_demand, ship_wanted_in_demand);
            }
        }
    }

    if (city_it->second.exist_in_inventory(ship.for_sell_product())) {
        int ship_for_sell_in_demand, ship_for_sell_available;
        city_it->second.consult_product(ship.for_sell_product(), ship_for_sell_in_demand, ship_for_sell_available);
        // only transact if the city needs more
        if (ship_for_sell_in_demand > ship_for_sell_available) {
            int available_for_sell = ship_for_sell_in_demand - ship_for_sell_available;
            if (ship.for_sell_number() <= available_for_sell) {
                city_it->second.set_product_in_inventory(ship.for_sell_product(), pddata, ship_for_sell_in_demand, ship_for_sell_available + ship.for_sell_number());
                // now the ship sold all of what it has
                ship_for_sell_product_count = 0;
            } else {
                // now the ship sold some, the inventory of the city augmented to exactly how many it needs
                ship_for_sell_product_count -= available_for_sell;
                city_it->second.set_product_in_inventory(ship.for_sell_product(), pddata, ship_for_sell_in_demand, ship_for_sell_in_demand);
            }
        }
    }

    // update the ship's info after crossing with this city
    ship.set_all(ship.wanted_product(), ship_wanted_product_count, ship.for_sell_product(), ship_for_sell_product_count);
}

int River::ship_for_sell_wanted_sum(Ship const& ship, int wanted, int for_sell) const {
    return min(wanted, ship.wanted_number()) + min(for_sell, ship.for_sell_number());
}

void River::redistribute_REC(BinTree<string> this_city, ProductData const& pddata) {
    if (this_city.empty()) return;

    BinTree<string> left = this_city.left();
    BinTree<string> right = this_city.right();

    if (not left.empty()) {
        this->commercialize(this_city.value(), left.value(), pddata);
    }

    if (not right.empty()) {
        this->commercialize(this_city.value(), right.value(), pddata);
    }

    redistribute_REC(left, pddata);
    redistribute_REC(right, pddata);
}

River::River() {

}

River::~River() {

}

void River::input_river_structure() {
    this->inventory_database.clear();
    this->basin_cities = this->read_input_bin_tree();
}

void River::ship_travelling(Ship& ship, ProductData const& pddata, int& bought_units, int& sold_units) {
    // 1. Look for the optimum destination
    list<pair<int, pair<string, SalesStatus>>> all_destinations;
    SalesStatus accumulated_sale = {
        .sold_units     = 0,
        .bought_units   = 0
    };

    // 1.1. Find all possible destinations
    this->ship_seek_all_routes(all_destinations, ship, 0, accumulated_sale, this->basin_cities);

    // 1.2. Select the most optimum destination
    auto all_dest_it    = ++all_destinations.begin();
    auto all_dest_end   = all_destinations.end();
    auto all_dest_best  = all_destinations.begin();

    int minimum_steps = all_dest_best->first;
    int greatest_sold_bought_sum = this->ship_for_sell_wanted_sum(
        ship,
        all_dest_best->second.second.bought_units,
        all_dest_best->second.second.sold_units
    );
    
    while (all_dest_it != all_dest_end) {
        int this_sold_bought_sum = this->ship_for_sell_wanted_sum(
            ship,
            all_dest_it->second.second.bought_units,
            all_dest_it->second.second.sold_units
        );
        int this_steps = all_dest_it->first;

        // this route has better of sold+bought with the greatest one
        if (this_sold_bought_sum > greatest_sold_bought_sum) {
            greatest_sold_bought_sum = this_sold_bought_sum;
            minimum_steps = this_steps;
            all_dest_best = all_dest_it;
        }
        // this route has the same amount
        else if (this_sold_bought_sum == greatest_sold_bought_sum) {
            if (this_steps < minimum_steps) {
                minimum_steps = this_steps;
                all_dest_best = all_dest_it;
            }
        }

        ++all_dest_it;
    }

    // 1.3 With the most optimum destination, find the route
    list<string> optimum_route;
    pair<int, string> verifier(minimum_steps, all_dest_best->second.first);
    this->ship_get_route(optimum_route, verifier, 0, this->basin_cities);

    // Now the optimum route is stored in the "optimum_route".
    // 2. Transact
    // Before applying the transactions, store the original values for the step (4).
    int ship_initial_wanted_count   = ship.wanted_number();
    int ship_initial_for_sell_count = ship.for_sell_number();

    auto optimum_route_it   = optimum_route.begin();
    auto optimum_route_end  = optimum_route.end();
    // for every city
    while (optimum_route_it != optimum_route_end) {
        this->ship_transact(*optimum_route_it, ship, pddata);
        ++optimum_route_it;
    }

    // 3. Calculate the values for return
    bought_units    = ship_initial_wanted_count - ship.wanted_number();
    sold_units      = ship_initial_for_sell_count - ship.for_sell_number();

    // 4. Register the last visited city only if ship made treats
    if (bought_units + sold_units > 0) {
        ship.add_destination(optimum_route.back());
    }  
}

void River::commercialize(string const& city_1, string const& city_2, ProductData const& pddata) {
    auto it_city_1 = this->inventory_database.find(city_1);
    auto it_city_2 = this->inventory_database.find(city_2);

    it_city_1->second.commercialize_with(it_city_2->second, pddata);
}

void River::redistribute(ProductData const& pddata) {
    this->redistribute_REC(this->basin_cities, pddata);
}

bool River::city_exists_in_basin(string const& city_id) const {
    auto it = this->inventory_database.find(city_id);
    return it != this->inventory_database.end();
}

bool River::city_consult_product(string const& city_id, uint32_t product_id, int& in_demand, int& available) const {
    auto it = this->inventory_database.find(city_id);
    if (it->second.exist_in_inventory(product_id)) {
        it->second.consult_product(product_id, in_demand, available);
        return true;
    }
    else return false;
}

bool River::city_has_product(string const& city_id, uint32_t product) const {
    auto it = this->inventory_database.find(city_id);
    return it->second.exist_in_inventory(product);
}

void River::city_modify_product(string const& city_id, ProductData const& pddata, uint32_t product_id, int in_demand, int available) {
    auto it = this->inventory_database.find(city_id);
    it->second.set_product_in_inventory(product_id, pddata, in_demand, available);
}

void River::city_add_product(string const& city_id, ProductData const& pddata,  uint32_t product_id, int in_demand, int available) {
    auto it = this->inventory_database.find(city_id);
    it->second.add_product_to_inventory(product_id, pddata, in_demand, available);
}

void River::city_delete_product(string const& city_id, ProductData const& pddata, uint32_t product_id) {
    auto it = this->inventory_database.find(city_id);
    it->second.delete_product(product_id, pddata);
}

void River::city_information(string const& city_id, int& total_mass, int& total_volume, bool& has_inventory) const {
    auto it = this->inventory_database.find(city_id);
    it->second.total_mass_and_volume(total_mass, total_volume);
    has_inventory = it->second.has_inventory();
}

void River::city_clear_inventory(string const& city_id) {
    auto it = this->inventory_database.find(city_id);
    it->second.clear_inventory();
}

void River::city_write_inventory(string const& city_id) const {
    auto it = this->inventory_database.find(city_id);
    it->second.write_inventory();
}
#include "river.hh"

BinTree<string> River::read_input_bin_tree()
{
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

void River::ship_seek_all_routes_until_last_transact(
    list<DestinationData>&  all_destinations,
    Ship const&             ship,
    int                     steps,
    int                     last_transact_steps,
    int                     sold_units,
    int                     bought_units,
    BinTree<string>         this_city,
    string                  last_transact_city
    )
{
    if (this_city.empty()) {
        // force to do nothing
        return;
    }

    // ship "simulates" a trading with this city
    auto it = this->inventory_database.find(this_city.value());
    
    // only trades if the city has more than it needs
    int ship_wanted_in_demand_in_city,      ship_wanted_available_in_city,
        ship_for_sell_in_demand_in_city,    ship_for_sell_available_in_city;

    // indicators of if the ship did transactions with this city
    bool wanted_transacted   = false;
    bool for_sell_transacted = false;
    
    // if the city has the wanted product
    if (it->second.exist_in_inventory(ship.wanted_product())) {
        it->second.consult_product(ship.wanted_product(), ship_wanted_in_demand_in_city, ship_wanted_available_in_city);

        // city has more than it needs of what the ship wanted 
        if (ship_wanted_available_in_city > ship_wanted_in_demand_in_city) {
            // buy them
            bought_units += ship_wanted_available_in_city - ship_wanted_in_demand_in_city;
            wanted_transacted = true;
        }
    }

    // if the city has the selling product
    if (it->second.exist_in_inventory(ship.for_sell_product())) {
        it->second.consult_product(ship.for_sell_product(), ship_for_sell_in_demand_in_city, ship_for_sell_available_in_city);

        // city has less than it needs of what the ship is selling
        if (ship_for_sell_available_in_city < ship_for_sell_in_demand_in_city) {
            // sell them
            sold_units += ship_for_sell_in_demand_in_city - ship_for_sell_available_in_city;
            for_sell_transacted = true;
        }
    }

    // update the last_transacted related info when it did actually transact this time,
    // otherwise just continue without updating the info.
    if (wanted_transacted or for_sell_transacted) {
        last_transact_steps = steps;
        last_transact_city = this_city.value();
    }

    // if this is a leaf
    if (this_city.left().empty() and this_city.right().empty()) {
        DestinationData ddata = {
            .depth          = last_transact_steps,
            .identifier     = last_transact_city,
            .sold_units     = sold_units,
            .bought_units   = bought_units
        };
        all_destinations.push_back(ddata);
    } else {
        // proceeds to continue with the recursion
        // if this branch has only one sub-branch, nothing will be affected.
        ship_seek_all_routes_until_last_transact(all_destinations, ship, steps + 1, last_transact_steps, sold_units, bought_units, this_city.left(), last_transact_city);
        ship_seek_all_routes_until_last_transact(all_destinations, ship, steps + 1, last_transact_steps, sold_units, bought_units, this_city.right(), last_transact_city);
    }
}

void River::ship_select_best_destination(Ship const& ship, list<DestinationData>& all_destinations, list<DestinationData>::iterator& best) const
{
    auto all_dest_it    = ++all_destinations.begin();
    auto all_dest_end   = all_destinations.end();
    auto all_dest_best  = all_destinations.begin();

    int minimum_steps = all_dest_best->depth;
    int greatest_sold_bought_sum = this->ship_for_sell_wanted_sum(
        ship,
        all_dest_best->bought_units,
        all_dest_best->sold_units
    );
 
    while (all_dest_it != all_dest_end) {
        int this_sold_bought_sum = this->ship_for_sell_wanted_sum(
            ship,
            all_dest_it->bought_units,
            all_dest_it->sold_units
        );
        int this_steps = all_dest_it->depth;

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

    best = all_dest_best;
}

bool River::ship_get_route(
    list<string>& route,
    pair<int, string> const& verifier,
    int steps,
    BinTree<string> this_city
    ) const
{
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

River::SubrouteInfo River::ship_find_optimum_route(
    list<string>& route,
    BinTree<string> city,
    Ship const& ship,
    SubrouteInfo srinfo
    )
{
    if (city.empty()) {
        return srinfo;
    }

    // try to transact
    bool transacted = false;
    City& city_obj = this->inventory_database.find(city.value())->second;

    if (city_obj.exist_in_inventory(ship.wanted_product())) {
        int in_demand, available;
        city_obj.consult_product(ship.wanted_product(), in_demand, available);
        if (available > in_demand) {
            srinfo.left_for_buy -= available - in_demand;
            transacted = true;
        }
    }
    if (city_obj.exist_in_inventory(ship.for_sell_product())) {
        int in_demand, available;
        city_obj.consult_product(ship.for_sell_product(), in_demand, available);
        if (in_demand > available) {
            srinfo.left_for_sell -= in_demand - available;
            transacted = true;
        }
    }

    if (srinfo.left_for_buy < 0) srinfo.left_for_buy = 0;
    if (srinfo.left_for_sell < 0) srinfo.left_for_sell = 0;

    // if no further trades are needed
    if (srinfo.left_for_buy == 0 and srinfo.left_for_sell == 0) {
        route.push_back(city.value());
        return srinfo;
    }

    list<string> left_subroute, right_subroute;

    SubrouteInfo left_accumulated = ship_find_optimum_route(left_subroute, city.left(), ship, srinfo);
    SubrouteInfo right_accumulated = ship_find_optimum_route(right_subroute, city.right(), ship, srinfo);

    int sum_srinfo_this = srinfo.left_for_buy + srinfo.left_for_sell;
    int sum_srinfo_left = left_accumulated.left_for_buy + left_accumulated.left_for_sell;
    int sum_srinfo_right = right_accumulated.left_for_buy + right_accumulated.left_for_sell;

    // if no further trades are done
    if (sum_srinfo_this == sum_srinfo_left and sum_srinfo_this == sum_srinfo_right) {
        if (transacted) route.push_front(city.value());
        return srinfo;
    }
    // if in both subroutes have done trades
    else if (sum_srinfo_this != sum_srinfo_left and sum_srinfo_this != sum_srinfo_right) {
        if (sum_srinfo_left < sum_srinfo_right) {
            left_subroute.push_front(city.value());
            route = left_subroute;
            return left_accumulated;
        } else if (sum_srinfo_right < sum_srinfo_left) {
            right_subroute.push_front(city.value());
            route = right_subroute;
            return right_accumulated;
        } else {
            if (left_subroute.size() < right_subroute.size()) {
                left_subroute.push_front(city.value());
                route = left_subroute;
                return left_accumulated;
            } else if (right_subroute.size() < left_subroute.size()) {
                right_subroute.push_front(city.value());
                route = right_subroute;
                return right_accumulated;
            } else {
                left_subroute.push_front(city.value());
                route = left_subroute;
                return left_accumulated;
            }
        }
    }
    // left side no trades, so right side yes trades
    else if (sum_srinfo_this == sum_srinfo_left) {
        right_subroute.push_front(city.value());
        route = right_subroute;
        return right_accumulated;
    }
    // now left side yes trades (implying that right side no trades)
    else {
        left_subroute.push_front(city.value());
        route = left_subroute;
        return left_accumulated;
    }
}

void River::ship_transact(string const& city_name, Ship& ship, ProductData const& pddata)
{
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

int River::ship_for_sell_wanted_sum(Ship const& ship, int wanted, int for_sell) const
{
    return min(wanted, ship.wanted_number()) + min(for_sell, ship.for_sell_number());
}

void River::redistribute_REC(BinTree<string> this_city, ProductData const& pddata)
{
    if (this_city.empty()) return;

    BinTree<string> left = this_city.left();
    BinTree<string> right = this_city.right();

    if (not left.empty()) {
        this->trade(this_city.value(), left.value(), pddata);
    }

    if (not right.empty()) {
        this->trade(this_city.value(), right.value(), pddata);
    }

    redistribute_REC(left, pddata);
    redistribute_REC(right, pddata);
}

River::River()
{

}

River::~River()
{

}

void River::input_river_structure()
{
    this->inventory_database.clear();
    this->basin_cities = this->read_input_bin_tree();
}

void River::ship_travelling(Ship& ship, ProductData const& pddata, int& bought_units, int& sold_units)
{
    // 0. Ensure that there are nodes in River
    if (this->basin_cities.empty())
        return;

    // 1. Look for the optimum destination
    list<string> optimum_route;
    SubrouteInfo srinfo = {
        .left_for_sell = ship.for_sell_number(),
        .left_for_buy = ship.wanted_number()
    };
    SubrouteInfo results = this->ship_find_optimum_route(optimum_route, this->basin_cities, ship, srinfo);

    // Now the optimum route is stored in the "optimum_route".
    // 2. Transact

    // If in this route there will be no transactions,
    // then nothing is to be done, obviously.
    if (results.left_for_sell + results.left_for_buy < ship.for_sell_number() + ship.wanted_number()) {
        // Before applying the transactions, store the original values for the step (4).
        int ship_initial_wanted_count   = ship.wanted_number();
        int ship_initial_for_sell_count = ship.for_sell_number();

        auto optimum_route_it   = optimum_route.begin();
        auto optimum_route_end  = optimum_route.end();

        Ship aux_ship;
        aux_ship.set_all(
            ship.wanted_product(),      ship.wanted_number(),
            ship.for_sell_product(),    ship.for_sell_number()
        );

        // for every city
        while (optimum_route_it != optimum_route_end) {
            this->ship_transact(*optimum_route_it, aux_ship, pddata);
            ++optimum_route_it;
        }

        // 3. Calculate the values for return
        bought_units    = ship_initial_wanted_count - aux_ship.wanted_number();
        sold_units      = ship_initial_for_sell_count - aux_ship.for_sell_number();

        // 4. Register the last visited city only if ship made trades
        ship.add_destination(optimum_route.back());
    } else {
        // 2. Return zero directly.
        bought_units = sold_units = 0;
    }
}

void River::trade(string const& city_1, string const& city_2, ProductData const& pddata)
{
    auto it_city_1 = this->inventory_database.find(city_1);
    auto it_city_2 = this->inventory_database.find(city_2);

    it_city_1->second.trade_with(it_city_2->second, pddata);
}

void River::redistribute(ProductData const& pddata)
{
    this->redistribute_REC(this->basin_cities, pddata);
}

bool River::city_exists_in_basin(string const& city_id) const
{
    auto it = this->inventory_database.find(city_id);
    return it != this->inventory_database.end();
}

bool River::city_consult_product(string const& city_id, uint32_t product_id, int& in_demand, int& available) const
{
    auto it = this->inventory_database.find(city_id);
    if (it->second.exist_in_inventory(product_id)) {
        it->second.consult_product(product_id, in_demand, available);
        return true;
    }
    else return false;
}

bool River::city_has_product(string const& city_id, uint32_t product) const
{
    auto it = this->inventory_database.find(city_id);
    return it->second.exist_in_inventory(product);
}

void River::city_modify_product(string const& city_id, ProductData const& pddata, uint32_t product_id, int in_demand, int available)
{
    auto it = this->inventory_database.find(city_id);
    it->second.set_product_in_inventory(product_id, pddata, in_demand, available);
}

void River::city_add_product(string const& city_id, ProductData const& pddata,  uint32_t product_id, int in_demand, int available)
{
    auto it = this->inventory_database.find(city_id);
    it->second.add_product_to_inventory(product_id, pddata, in_demand, available);
}

void River::city_delete_product(string const& city_id, ProductData const& pddata, uint32_t product_id)
{
    auto it = this->inventory_database.find(city_id);
    it->second.delete_product(product_id, pddata);
}

void River::city_information(string const& city_id, int& total_mass, int& total_volume, bool& has_inventory) const
{
    auto it = this->inventory_database.find(city_id);
    it->second.total_mass_and_volume(total_mass, total_volume);
    has_inventory = it->second.has_inventory();
}

void River::city_clear_inventory(string const& city_id)
{
    auto it = this->inventory_database.find(city_id);
    it->second.clear_inventory();
}

void River::city_write_inventory(string const& city_id) const
{
    auto it = this->inventory_database.find(city_id);
    it->second.write_inventory();
}
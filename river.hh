#ifndef RIVER_HH
#define RIVER_HH

#include <iostream>
#include <map>
#include <list>

#include "city.hh"
#include "BinTree.hh"
#include "ship.hh"

using namespace std;

// River holds the BinTree structure and all the cities
// It also handles the input of a new basin structure, and
// therefore clears all the prior data.

class River {
private:
    // Access the inventory of a city using city's identifier
    map<string, City> inventory_database;

    // The structure of the basin
    BinTree<string> basin_cities;

    /** @brief  The function reads a binary tree structure in PreOrder format recursively from the input.
     *  \pre    A valid binary tree description is on the input.
     *  \post   A built BinTree is returned.
    */
    BinTree<string> read_input_bin_tree();

    /** @brief  The struct that stores the sales of the ship at a specific moment.
    */
    struct SalesStatus {
        int sold_units;
        int bought_units;
    };

    /** @brief  
     *  \pre    
     *  \post
    */
    void ship_seek_all_routes(list<pair<int, pair<string, SalesStatus>>>& all_destinations, Ship const& ship, int steps, SalesStatus accumulated_sale, BinTree<string> this_city);

    /** @brief
     * 
    */
    void ship_seek_all_routes_until_last_transact(
    list<pair<int, pair<string, SalesStatus>>>& all_destinations,
    Ship const& ship,
    int steps,
    int last_transact_steps,
    SalesStatus accumulated_sale,
    BinTree<string> this_city,
    string last_transact_city
    );

    /** @brief
     *  \pre
     *  \post
    */
    bool ship_get_route(list<string>& route, pair<int, string>& verifier, int steps, BinTree<string> this_city);

    /** @brief
     *  \pre
     *  \post
    */
    void ship_transact(string const& city_name, Ship& ship, ProductData const& pddata);

    /** @brief
     *  \pre
     *  \post
    */
    int ship_for_sell_wanted_sum(Ship const& ship, int wanted, int for_sell) const;

    /** @brief
     *  \pre
     *  \post
    */
    void redistribute_REC(BinTree<string> this_city, ProductData const& pddata);
public:
    /** @brief  Constructor. It sets everything to its initial state. Basin is empty.
     *  \pre    TRUE.
     *  \post   TRUE.
    */
    River();

    /** @brief  Destructor. It calls the destructor of child elements.
     *  \pre    TRUE.
     *  \post   TRUE.
    */
    ~River();

    /** @brief  Read from input the new structure of the basin.
     *  \pre    There is a valid binary tree description in PreOrder on the input.
     *  \post   River's structure is updated according to the input.
    */
    void input_river_structure();

    /** @brief  Let the ship select route and commercialize.
     *  \pre    TRUE.
     *  \post   The ship's data will be modified. The number of bought and sold units are returned via references.
    */
    void ship_travelling(Ship& ship, ProductData const& pddata, int& bought_units, int& sold_units);

    /** @brief  Commercialize between 2 cities.
     *  \pre    Both cities exist.
     *  \post   Two cities will commercialize between them, modifying their inventory.
    */
    void commercialize(string const& city_1, string const& city_2, ProductData const& pddata);

    /** @brief  Redistribute according to the requirement 17 of the documentation.
     *  \pre    TRUE.
     *  \post   All inventories of the intervened cities will be modified.
    */
    void redistribute(ProductData const& pddata);

    /** @brief  Tells if the city exists in the basin.
     *  \pre    TRUE.
     *  \post   Returns TRUE only if the city exists in the basin.
    */
    bool city_exists_in_basin(string const& city_id) const;

// CITY FUNCTIONS

    /** @brief  Consult the information of a product of a city given their corresponding IDs.
     *  \pre    The city exists in the basin.
     *  \post   Returns FALSE only if the product is not in inventory. Otherwise the data is returned via reference.
    */
    bool city_consult_product(string const& city_id, uint32_t product_id, int& in_demand, int& available) const;

    /** @brief  Tells if city has the product.
     *  \pre    TRUE.
     *  \post   Returns TRUE only if the product is inside the inventory of the city.
    */
    bool city_has_product(string const& city_id, uint32_t product) const;

    /** @brief  Modify the information of a product of a city given their corresponding IDs.
     *  \pre    The city exists in the basin. The product must already exist in city's inventory.
     *  \post   The information will be updated.
    */
    void city_modify_product(string const& city_id, ProductData const& pddata,  uint32_t product_id, int in_demand, int available);

    /** @brief  Add a product to a city given their corresponding IDs.
     *  \pre    The city exists in the basin. The product is valid and did not exist before in its inventory.
     *  \post   The product is added to the inventory.
    */
    void city_add_product(string const& city_id, ProductData const& pddata,  uint32_t product_id, int in_demand, int available);

    /** @brief  Delete one product from the inventory of the city given their corresponding IDs.
     *  \pre    The city exists in the basin and so the product inside it.
     *  \post   The product is deleted from the inventory of the city.
    */
    void city_delete_product(string const& city_id, ProductData const& pddata, uint32_t product_id);

    /** @brief  Returns the city inventory's basic information: total mass, total volume, if has inventory.
     *  \pre    The city exists in the basin.
     *  \post   The three pieces of info are returned via reference.
    */
    void city_information(string const& city_id, int& total_mass, int& total_volume, bool& has_inventory) const;

    /** @brief  Clear the inventory of the city.
     *  \pre    The city exists in the basin.
     *  \post   The inventory is cleared.
    */
    void city_clear_inventory(string const& city_id);

    /** @brief  Write on the output using STL "cout" in the requiered format the whole inventory of the "city" in numerical order of the product.
     *  \pre    TRUE.
     *  \post   The city inventory, if exist and has elements, will be written on the output.
    */
    void city_write_inventory(string const& city_id) const;
};


#endif // RIVER_HH
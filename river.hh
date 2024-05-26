/***************************
 * @file    River.hh
 * 
 * @brief   The definition of the River class, whose usage is to store the basin's structure and to manage the data of the inventories.
 * 
 * @details
 * River holds the BinTree structure and all the cities
 * It also handles the input of a new basin structure, and
 * therefore clears all the prior data.
*/

#ifndef RIVER_HH
#define RIVER_HH

#include <iostream>
#include <map>
#include <list>

#include "city.hh"
#include "BinTree.hh"
#include "ship.hh"

using namespace std;

class River {
private:
    // Access the inventory of a city using city's identifier
    map<string, City> inventory_database; /**< The satabase store inventories identified with string names. */

    // The structure of the basin
    BinTree<string> basin_cities;

    /** @brief  The function reads a binary tree structure in PreOrder format recursively from the input.
     *  \pre    A valid binary tree description is on the input.
     *  \post   The function absorbs the necessary data from the input to generate the BinTree data.
     *  @return A built BinTree data.
    */
    BinTree<string> read_input_bin_tree();

    /** @brief  The struct that stores the data of one destination.
    */
    struct DestinationData {
        int depth;
        string identifier;
        int sold_units;
        int bought_units;
    };

    /** @brief  The 
     *  \pre    
     *  \post
     * 
     *  @param  all_destinations    The list of all possible destinations of a ship's route.
     *  @param  ship                The ship's data.
     *  @param  steps               Recursion parameter (Init=0). To tell the depth of the recursion.
     *  @param  last_transact_steps Data keeper (Init=0). To tell the depth of the last recursion in which a transaction occured.
     *  @param  sold_untis          Data keeper (Init=0). To register the accumulated sold units until a specific moment.
     *  @param  bought_units        Data keeper (Init=0). To register the accumulated bought units until a specific moment.
     *  @param  this_city           The node of the BinTree from which to start.
     *  @param  last_transact_city  Data keeper (Init=""). To register the name (identifier) of the city with who transacted.
     * 
     *  @return Via reference, in "all_destinations" there will be all possible destinations of a route.
    */
    void ship_seek_all_routes_until_last_transact(
        list<DestinationData>& all_destinations,
                   Ship const& ship,
                           int steps,
                           int last_transact_steps,
                           int sold_units,
                           int bought_units,
               BinTree<string> this_city,
                        string last_transact_city
    );

    /**
     * @brief 
     * \pre
     * \post
     * 
     * @param all_destinations 
     */
    void ship_select_best_destination(Ship const& ship, list<DestinationData>& all_destinations, list<DestinationData>::iterator& best) const;

    /** @brief  Given a node's info ("verifier"), find the route from the root to that specific node.
     *  \pre    This_city is a valid node of the BinTree.
     *  \post   The route, if found, is returned via reference through "route".
     * 
     *  @param  route       The returned value. It has to be empty when it's passed.
     *  @param  verifier    The information of the node with which the route should end.
     *  @param  steps       Recursion parameter (Init=0). To register the depth to the root of a specific moment.
     *  @param  this_city   The root node from which the route start.
     * 
     *  @return TRUE if the destination node is found. FALSE otherwise.
    */
    bool ship_get_route(
        list<string>&       route,
        pair<int, string>&  verifier,
        int                 steps,
        BinTree<string>     this_city
    );

    /** @brief  Given the city's name and the ship, transact between them modifying eachone's inventory.
     *  \pre    The city_name is a valid city name. ProductData contains information of all intervened products.
     *  \post   The inventories are modified.
     *  
     *  @param  city_name   The name/identifier of the city.
     *  @param  ship        The Ship object.
     *  @param  pddata      The products' database.
     * 
     *  @return Nothing.
    */
    void ship_transact(string const& city_name, Ship& ship, ProductData const& pddata);

    /** @brief  Returns the sum the "wanted" and "for_sell" values according to the ship's capabilities.
     *  \pre    TRUE.
     *  \post   A sum is returned.
     * 
     *  @param  ship        The Ship object.
     *  @param  wanted      The quantity of the product that ship could buy.
     *  @param  for_sell    The quantity of the product that ship could sell.
     * 
     *  @return The sum of the "wanted" and "for_sell" according to the capabilities of the ship.
    */
    int ship_for_sell_wanted_sum(Ship const& ship, int wanted, int for_sell) const;

    /** @brief  Each city interchange products with the one on the left of the river stucture, and then the one on the right.
     *  \pre    "this_city" is a valid BinTree node with correct city names. "pddata" contains the info of all intervened products.
     *  \post   All inventories that satisfies with the interchange conditions will be modified.
     * 
     *  @param  this_city   A BinTree node in which all names are valid.
     *  @param  pddata      The ProductData that contains the info of all intervened products.
     * 
     *  @return Nothing.
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
     * 
     *  @return Nothing.
    */
    void input_river_structure();

    /** @brief  Let the ship select route and trade.
     *  \pre    TRUE.
     *  \post   The ship's data will be modified. The number of bought and sold units are returned via references.
     * 
     *  @param  ship
     *  @param  pddata
     *  @param  bought_units
     *  @param  sold_units
     * 
     *  @return 
    */
    void ship_travelling(Ship& ship, ProductData const& pddata, int& bought_units, int& sold_units);

    /** @brief  Trade between 2 cities.
     *  \pre    Both cities exist.
     *  \post   Two cities will trade between them, modifying their inventory.
     *  
     *  @param  city_1
     *  @param  city_2
     *  @param  pddata
     * 
     *  @return Nothing.
    */
    void trade(string const& city_1, string const& city_2, ProductData const& pddata);

    /** @brief  Redistribute according to the requirement 17 of the documentation.
     *  \pre    TRUE.
     *  \post   All inventories of the intervened cities will be modified.
     * 
     *  @param  pddata
     * 
     *  @return Nothing.
    */
    void redistribute(ProductData const& pddata);

    /** @brief  Tells if the city exists in the basin.
     *  \pre    TRUE.
     *  \post   Returns TRUE only if the city exists in the basin.
     * 
     *  @param  city_id
     *  
     *  @return TRUE If the 
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
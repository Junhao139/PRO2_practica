/**
 * @file river.hh
 * @brief The definition of the River class, whose usage is to store the basin's structure and to manage the data of the inventories.
*/

#ifndef RIVER_HH
#define RIVER_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <list>
#include "BinTree.hh"
#endif // NO_DIAGRAM

#include "city.hh"
#include "ship.hh"

using namespace std;

/** @brief  River administrates the basin's city structure and the set of all inventories.
 *  @details
 *  River holds the BinTree structure and all the cities
 *  It also handles the input of a new basin structure.
 */
class River {
private:
    /** @brief  The satabase store inventories identified with string names.
    */
    map<string, City> inventory_database; 

    /** @brief The structure of the basin.
     */
    BinTree<string> basin_cities;

    /** @brief  The function reads a binary tree structure in PreOrder format recursively from the input.
     *  \pre    A valid binary tree description is on the input.
     *  \post   The function absorbs the necessary data from the input to generate the BinTree data.
     *  @return A built BinTree data.
    */
    BinTree<string> read_input_bin_tree();

    /** @brief  This is a auxiliary data structure for ship_find_optimum_route function. It is equivalent (but more elegantly) to a pair<int,int>.
     */
    struct SubrouteInfo {
        /** @brief  The units that are left for sell.
         */
        int left_for_sell;

        /** @brief  The units that are left for buy.
         */
        int left_for_buy;
    };

    /** @brief  Finds recursively the best route.
     *  \pre    
     *  \post
     * 
     *  @param  route   The route to be returned. It has to be initially empty.
     *  @param  city    A valid BinTree<string> node.
     *  @param  ship    The information of the ship.
     *  @param  srinfo  The result after current trade. Initially, it has to be the ship.wanted_number() and ship.for_sell_number().
     * 
     *  @return The SubrouteInfo of how is the result of transaction on the optimum route. Through the "route" reference, the optimum route is returned.
     */
    SubrouteInfo ship_find_optimum_route(
        list<string>& route,
        BinTree<string> city,
        Ship const& ship,
        SubrouteInfo srinfo
    );

    /** @brief  Given the city's name and the ship, transact between them modifying eachone's inventory.
     *  \pre    The city_name is a valid city name. ProductData contains information of all intervened products.
     *  \post   The inventories are modified.
     *  
     *  @param  city_name   The ID (name) of the city.
     *  @param  ship        The Ship object. The ship's data is modified if any trade is done.
     *  @param  pddata      The products' database.
    */
    void ship_transact(string const& city_name, Ship& ship, ProductData const& pddata);

    /** @brief  Each city interchange products with the one on the left of the river stucture, and then the one on the right.
     *  \pre    "this_city" is a valid BinTree node with correct city names (when this_city is not empty). "pddata" contains the info of all intervened products.
     *  \post   All inventories that satisfies with the interchange conditions will be modified.
     * 
     *  @param  this_city   A BinTree node in which all names are valid.
     *  @param  pddata      The ProductData that contains the info of all intervened products.
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
     *  \post   No memory are wasted.
    */
    ~River();

    /** @brief  Read from input the new structure of the basin.
     *  \pre    There is a valid binary tree description in PreOrder on the input.
     *  \post   River's structure is updated according to the input.
    */
    void input_river_structure();

    /** @brief  Let the ship select route and trade.
     *  \pre    TRUE.
     *  \post   The ship's data will be modified. The number of bought and sold units are returned via references.
     * 
     *  @param  ship            The ship, if traded something, will register the name of the last visited city.
     *  @param  pddata          The database for all products.
     *  @param  bought_units    The bought units during the trip, which is returned via the reference.
     *  @param  sold_units      The sold units during the trip, which is returned via the reference.
     * 
     *  @return The ship is modified if any trades are done. In bought_units and sold_units there are the info of the trip.
    */
    void ship_travelling(Ship& ship, ProductData const& pddata, int& bought_units, int& sold_units);

    /** @brief  Trade between 2 cities.
     *  \pre    Both cities exist.
     *  \post   Two cities will trade between them, modifying their inventory.
     *  
     *  @param  city_1  The first trading city.
     *  @param  city_2  The second trading city.
     *  @param  pddata  The database for all products.
    */
    void trade(string const& city_1, string const& city_2, ProductData const& pddata);

    /** @brief  Redistribute according to the requirement 17 of the documentation.
     *  \pre    TRUE.
     *  \post   All inventories of the intervened cities will be modified.
     * 
     *  @param  pddata  The database for all products.
    */
    void redistribute(ProductData const& pddata);

    /** @brief  Tells if the city exists in the basin.
     *  \pre    TRUE.
     *  \post   Returns TRUE only if the city exists in the basin.
     * 
     *  @param  city_id The ID (name) of the city.
     *  
     *  @return TRUE if the city is in the basin. Otherwise FALSE.
    */
    bool city_exists_in_basin(string const& city_id) const;

// CITY FUNCTIONS

    /** @brief  Consult the information of a product of a city given their corresponding IDs.
     *  \pre    The city exists in the basin.
     *  \post   Returns FALSE only if the product is not in inventory. Otherwise the data is returned via reference.
     * 
     *  @param  city_id     The ID (name) of the city.
     *  @param  product_id  The ID (tag) of the product.
     *  @param  in_demand   The product's demand of the city, this is the parameter for returning via reference.
     *  @param  available   The product's availability of the city, this is the parameter for returning via reference.
     * 
     *  @return FALSE if the product is not in inventory. Otherwise TRUE, and the data is returned via the two references.
    */
    bool city_consult_product(string const& city_id, uint32_t product_id, int& in_demand, int& available) const;

    /** @brief  Tells if city has the product.
     *  \pre    TRUE.
     *  \post   Returns TRUE only if the product is inside the inventory of the city.
     * 
     *  @param  city_id     The ID (name) of the city.
     *  @param  product     The ID (tag) of the product.
     *  
     *  @return TRUE if the product is inside the inventory of the city. Otherwise FALSE.
    */
    bool city_has_product(string const& city_id, uint32_t product) const;

    /** @brief  Modify the information of a product of a city given their corresponding IDs.
     *  \pre    The city exists in the basin. The product must already exist in city's inventory.
     *  \post   The information will be updated.
     * 
     *  @param  city_id     The ID (name) of the city.
     *  @param  pddata      The database of all products, in which the "product_id" exists.
     *  @param  product_id  The ID (tag) of the product.
     *  @param  in_demand   The product's demand of the city.
     *  @param  available   The product's availability of the city.
    */
    void city_modify_product(string const& city_id, ProductData const& pddata, uint32_t product_id, int in_demand, int available);

    /** @brief  Add a product to a city given their corresponding IDs.
     *  \pre    The city exists in the basin. The product is valid and did not exist before in its inventory.
     *  \post   The product is added to the inventory.
     * 
     *  @param  city_id     The ID (name) of the city.
     *  @param  pddata      The database of all products, in which the "product_id" exists.
     *  @param  product_id  The ID (tag) of the product.
     *  @param  in_demand   The product's demand of the city.
     *  @param  available   The product's availability of the city.
    */
    void city_add_product(string const& city_id, ProductData const& pddata, uint32_t product_id, int in_demand, int available);

    /** @brief  Delete one product from the inventory of the city given their corresponding IDs.
     *  \pre    The city exists in the basin and so the product inside it.
     *  \post   The product is deleted from the inventory of the city.
     * 
     *  @param  city_id     The ID (name) of the city.
     *  @param  pddata      The database of all products.
     *  @param  product_id  The ID (tag) of the product.
    */
    void city_delete_product(string const& city_id, ProductData const& pddata, uint32_t product_id);

    /** @brief  Returns the city inventory's basic information: total mass, total volume, if has inventory.
     *  \pre    The city exists in the basin.
     *  \post   The three pieces of info are returned via reference.
     * 
     *  @param  city_id         The ID (name) of the city.
     *  @param  total_mass      The total mass of the inventory of the city, this is the parameter for returning via reference.
     *  @param  total_volume    The total volume of the inventory of the city, this is the parameter for returning via reference.
     *  @param  has_inventory   Tells if the city has inventory, this is the parameter for returning via reference.
     * 
     *  @return The data is returned via the last three references.
    */
    void city_information(string const& city_id, int& total_mass, int& total_volume, bool& has_inventory) const;

    /** @brief  Clear the inventory of the city.
     *  \pre    The city exists in the basin.
     *  \post   The inventory is cleared.
     * 
     *  @param  city_id     The ID (name) of the city.
    */
    void city_clear_inventory(string const& city_id);

    /** @brief  Write on the output using C++ STL "cout" in the requiered format the whole inventory of the "city" in numerical ascending order of the ID of the product.
     *  \pre    TRUE.
     *  \post   The city inventory, if exists and has elements, will be written on the output.
     * 
     *  @param  city_id     The ID (name) of the city.
    */
    void city_write_inventory(string const& city_id) const;
};


#endif // RIVER_HH
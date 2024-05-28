/**
 * @file city.hh
 * @brief City class definition.
 */

#ifndef CITY_HH
#define CITY_HH

#ifndef NO_DIAGRAM
#include <string>
#include <map>
#include <iostream>
#endif // NO_DIAGRAM

#include "product_data.hh"

using namespace std;

/** @brief  The City stores one inventory's information.
 *  @details 
 *  City corresponds with a node in the River's BinTree structure
 *  It serves mainly for a container to manage city's inventory.
*/
class City {
private:
    /** @brief  The data structure for information of a product in an inventory.
     */
    struct ProductDemand {
        int in_demand;
        int available;
    };

    /** @brief  The inventory of products of the city.
     */
    map<uint32_t, ProductDemand> inventory;
    
    /** @brief  Tells if the city has inventory.
     */
    bool inventory_disposition;

    /** @brief  The total mass of the inventory.
     */
    int total_mass;
    
    /** @brief  The total volume of the inventory.
     */
    int total_volume;
public:
    /** @brief  Initializes all values. The city is therefore ready to be operated with.
     *  \pre    TRUE.
     *  \post   All values are initialized.
    */
    City();

    /** @brief  The destructor does nothing.
    */
    ~City();

    /** @brief  Clear the inventory.
     *  \pre    The city actually has an inventory.
     *  \post   City's inventory is cleared.
    */
    void clear_inventory();

    /** @brief  Add one type of product to inventory.
     *  \pre    The product does not existe before in the inventory.
     *  \post   The product is added.
     * 
     *  @param  pddata      The database of all products, in which the "product_id" exists.
     *  @param  product_id  The ID (tag) of the product.
     *  @param  in_demand   The product's demand of the city.
     *  @param  available   The product's availability of the city.
    */
    void add_product_to_inventory(uint32_t identifier, ProductData const& pd, int in_demand, int available);

    /** @brief  Modify the product in the inventory.
     *  \pre    The product already exists in the inventory.
     *  \post   The product is modified.
     * 
     *  @param  pddata      The database of all products, in which the "product_id" exists.
     *  @param  product_id  The ID (tag) of the product.
     *  @param  in_demand   The product's demand of the city.
     *  @param  available   The product's availability of the city.
    */
    void set_product_in_inventory(uint32_t identifier, ProductData const& pd, int in_demand, int available);

    /** @brief  Tells if the product is in the inventory.
     *  \pre    TRUE.
     *  \post   Return TRUE only if the product is in the inventory. FALSE otherwise.
     * 
     *  @param  product The ID (tag) of the product.
     * 
     *  @return TRUE if the city has the "product". Otherwise FALSE.
    */
    bool exist_in_inventory(uint32_t product) const;

    /** @brief  Consult the information of a specific product.
     *  \pre    The product is in the inventory.
     *  \post   The information is returned via the references.
     * 
     *  @param  identifier  The ID (tag) of the product.
     *  @param  in_demand   The demand of the product of the city, here the data is returned via reference.
     *  @param  available   The availability of the product of the city, here the data is returned via reference.
    */
    void consult_product(uint32_t identifier, int& in_demand, int& available) const;

    /** @brief  The product is deleted from the inventory.
     *  \pre    The product exists.
     *  \post   The product is deleted from the inventory, and the total mass and volume of the inventory is modified.
     *  
     *  @param  identifier  The ID (tag) of the product.
     *  @param  pd          The database of all products, in which the "identifier"'s product exists.
    */
    void delete_product(uint32_t identifier, ProductData const& pd);

    /** @brief  Returns the total mass and volume of the inventory.
     *  \pre    TRUE.
     *  \post   The "mass" and "volume" are returned via reference.
     * 
     *  @param  mass    The total mass to be returned.
     *  @param  volume  The total volume to be returned.
    */
    void total_mass_and_volume(int& mass, int& volume) const;

    /** @brief  Tells if this city has an inventory.
     *  \pre    TRUE.
     *  \post   Returns TRUE only if the city has an inventory.
     *  
     *  @return TRUE is this city has inventory (in this case the inventory is also empty). Otherwise FALSE.
    */
    bool has_inventory() const;

    /** @brief  Trade between this city and the foreign one.
     *  \pre    The foreign city exist, "pd" contains all necessary information for all intervened products.
     *  \post   The inventories of the foreign city and this city are modified.
     * 
     *  @param  foreign The other city with which this city is trading.
     *  @param  pd      The database for all products.
    */
    void trade_with(City& foreign, ProductData const& pd);

    /** @brief  Write on the output using STL "cout" in the requiered format the whole inventory in numerical order of the product.
     *  \pre    TRUE.
     *  \post   The inventory, if exists and has elements, will be written on the output.
    */
    void write_inventory() const;
};

#endif // CITY_HH
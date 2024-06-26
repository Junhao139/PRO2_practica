/**
 * @file product_data.hh
 * @brief The definition of the ProductData class.
 */

#ifndef PRODUCT_DATA_HH
#define PRODUCT_DATA_HH

#ifndef NO_DIAGRAM
#include <vector>
#include <stdint.h>
#endif // NO_DIAGRAM

#include "product.hh"
using namespace std;

/** @brief  This class is aimed for storing information of all products.
 *  @details
 *  The class that administrate the variety of all the products.
 *  Especifically, it serves for the requirements 6 and 7.
 */
class ProductData {
private:
    /** @brief  The storage for all products, ordered according to the product's ID.
    */
    vector<Product> all_products;

    /** @brief  The index of the new product if such new one is to be added.
    */
    int last_available_index;
public:
    /** @brief  Constructor. When called, the ProductData is cleared.
     *  \pre    TRUE.
     *  \post   ProductData is cleared and ready for new data.
    */
    ProductData();

    /** @brief  Destructor.
     *  \pre    TRUE.
     *  \post   Ensures all memory are freed. Since no pointers are used, it does nothing.
    */
    ~ProductData();

    /** @brief  Add a new type of product to all_products.
     *  \pre    TRUE.
     *  \post   The product is stored in the pool, and its assigned identifier is returned.
    */
    void add_new_product(Product const& product);

    /** @brief  Given a Product identifier, return the product (unmodifiable).
     *  \pre    The identifier is existent.
     *  \post   The product's data is returned via reference.
    */
    void consult_product(Product& product, uint32_t identifier) const;

    /** @brief  Returns how many products are there in the pool.
     *  \pre    TRUE.
     *  \post   Returns a integer telling how many products are in the database.
    */
    int database_size() const;

    /** @brief  Tells if the product ID is a valid ID.
     *  \pre    TRUE.
     *  \post   Returns TRUE only if there is a product that has the ID. Otherwise FALSE.
    */
    bool product_exists(uint32_t tag) const;
};

#endif // PRODUCT_DATA_HH
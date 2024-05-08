#ifndef SHIP_HH
#define SHIP_HH

// The Ship class will hold the information for the River class
// to find the optimum route for transactions.

#include "product.hh"

class Ship {
private:
    Product::ProdID wanted;
    Product::ProdID for_sell;
    int wanted_quantity;
    int for_sell_quantity;
public:
    Ship();
    ~Ship();

    /** @brief  Returns the wanted product and value through referenced variables.
     *  \pre    "wanted" and "wanted_number" reference to lvalues.
     *  \post   "wanted" and "wanted_number" contain necessary information. 
    */
    void wanted_products(Product::ProdID& wanted, int& wanted_number) const;

    /** @brief  Returns the product for sell and its value through referenced variables.
     *  \pre    "for_sell" and "for_sell_number" reference to lvalues.
     *  \post   "for_sell" and "for_sell_number" contain necessary information.
    */
    void for_sell_products(Product::ProdID& for_sell, int& for_sell_number) const;

    /** @brief  Sets the wanted product and how many of it, and seemingly for the ones for_sell.
     *  \pre    Both products exist, the numbers are non-negative and one of them is strictly positive.
     *  \post   The information is updated to the class.
    */
    void set_all(Product::ProdID wanted, int wanted_number, Product::ProdID for_sell, int for_sell_number);
};

#endif // SHIP_HH
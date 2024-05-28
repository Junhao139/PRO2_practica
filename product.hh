/**
 * @file product.hh
 * @brief The Product class's definition.
 */

#ifndef PRODUCT_HH
#define PRODUCT_HH

/**
 * @brief This is one product's info.
 */
class Product {
private:
    /** @brief  The mass of one product.
    */
    int mass;

    /** @brief  The volume of one product.
    */
    int volume;
public:
    /** @brief  The constructor. It sets the mass and volume datas.
     *  \pre    TRUE.
     *  \post   "mass" and "volume" are modified.
     *  
     *  @param  mass    The mass of one product.
     *  @param  volume  The volume of one product.
     */
    Product(int mass, int volume);

    /** @brief Destroy the Product object. It actually does nothing except what is automatically done by C++.
     */
    ~Product();

    /** @brief  Get the mass.
     *  \pre    TRUE.
     *  \post   The mass is returned.
    */
    int get_mass() const;

    /** @brief  Get the volume.
     *  \pre    TRUE.
     *  \post   The volume is returned.
    */
    int get_volume() const;
};

#endif // PRODUCT_HH
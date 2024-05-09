#ifndef PRODUCT_HH
#define PRODUCT_HH

// This is a type of product

class Product {
private:
    int mass;
    int volume;
public:
    Product(int mass, int volume);
    ~Product();

    /** @brief  Get the mass.
     *  \pre    TRUE.
     *  \post   TRUE.
    */
    int get_mass() const;

    /** @brief  Get the volume.
     *  \pre    TRUE.
     *  \post   TRUE.
    */
    int get_volume() const;

    /** @brief  Get the ID.
     *  \pre    TRUE.
     *  \post   TRUE.
    */
    int get_ID() const;
};

#endif // PRODUCT_HH
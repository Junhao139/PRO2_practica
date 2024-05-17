#include "product_data.hh"

ProductData::ProductData() {
    this->all_products = vector<Product>();
    this->last_available_index = 0;
}

ProductData::~ProductData() {

}

void ProductData::add_new_product(Product const& product) {
    this->all_products.push_back(product);
    ++this->last_available_index;
}

void ProductData::consult_product(Product& product, uint32_t identifier) const {
    product = this->all_products[identifier - 1];
}

int ProductData::database_size() const {
    return this->last_available_index;
}

bool ProductData::product_exists(uint32_t tag) const {
    return tag - 1 < last_available_index;
}
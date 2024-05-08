#include "product.hh"

Product::Product(int mass, int volume, ProdID identifier) {
    this->mass = mass;
    this->volume = volume;
    this->identifier = identifier;
}

Product::~Product() {

}


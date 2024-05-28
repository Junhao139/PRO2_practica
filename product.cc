/**
 * @file product.cc
 * @brief Implementation for Product class in product.hh.
 */

#include "product.hh"

Product::Product(int mass, int volume)
{
    this->mass = mass;
    this->volume = volume;
}

Product::~Product()
{

}

int Product::get_mass() const
{
    return this->mass;
}

int Product::get_volume() const
{
    return this->volume;
}
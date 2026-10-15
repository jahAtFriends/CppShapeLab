/*
* filename: PlaneVector.java
* author:   Joel Hammer
* date modified: 10/12/26
*
*
*
*/

#ifndef PLANEVECTOR_H
#define PLANEVECTOR_H

#include "Pair.hpp"
#include <iostream>
#include <string>

/**
 * The PlaneVector class represents a vector in the 2D euclidean plane.
 * Basic arithmetic operations are provided. Note that PlaneVector
 * instances are always immutable: each operation always constructs
 * a new PlaneVector.
 * 
 * A "Plane Vector" can be thought of as both an ordered <x, y> pair
 * and a mathematical object with magnitude and direction. For that
 * reason, construction is only possible via the provided factory
 * methods--specifying which definition is used to construct the vector.
 * However, at any moment, both <x, y> and (r, theta) components are
 * available.
 */
struct PlaneVector
{
private:
    Pair<double, double> m_components;
    PlaneVector(const double &x, const double &y);

public:
    /**
     * Construct a new PlaneVector from the given x and y components.
     * @param x The x component
     * @param y The y component
     */
    static PlaneVector fromXY(const double &x, const double &y);
    
    /**
     * Constructs a PlaneVector from polar-form components
     * @param r the magnitude of the vector
     * @param theta the direction of the vector
     */
    static PlaneVector fromPolar(const double &r, const double &theta);
    static const PlaneVector &ZERO();

    const double &x() const;
    const double &y() const;
    const double r() const;
    const double theta() const;

    PlaneVector plus(const PlaneVector &that) const;
    PlaneVector minus(const PlaneVector &that) const;
    const double dot(const PlaneVector &that) const;
    PlaneVector scl(double &scl) const;
    const double normSquared() const;
    const double norm() const;
    PlaneVector unitVector() const;
    const double cross(const PlaneVector &that) const;
    PlaneVector rotate(const double &alpha) const;

    friend bool operator==(const PlaneVector &left, const PlaneVector &right);
    friend std::ostream &operator<<(std::ostream &os, const PlaneVector &v);
    PlaneVector operator+(const PlaneVector &that) const;
    PlaneVector operator-(const PlaneVector &that) const;
};

#endif
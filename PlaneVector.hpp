#ifndef PLANEVECTOR_H
#define PLANEVECTOR_H

#include "Pair.hpp"
#include <iostream>
#include <string>

struct PlaneVector {
private:
    Pair<double, double> m_components;
    PlaneVector(const double& x, const double& y);

public:
    static PlaneVector fromXY(const double& x, const double& y);
    static PlaneVector fromPolar(const double& r, const double& theta);
    static const PlaneVector& ZERO();

    const double& x() const;
    const double& y() const;
    const double r() const;
    const double theta() const;
    
    PlaneVector  plus(const PlaneVector& that)  const;
    PlaneVector  minus(const PlaneVector& that) const;
    const double dot(const PlaneVector& that)   const;
    PlaneVector  scl(double& scl)               const;
    const double normSquared()                  const;
    const double norm()                         const;
    PlaneVector  unitVector()                   const;
    const double cross(const PlaneVector& that) const;
    PlaneVector  rotate(const double& alpha)    const;

    friend bool  operator==(const PlaneVector& left, const PlaneVector& right);
    friend std::ostream& operator<<(std::ostream& os, const PlaneVector v);
    PlaneVector  operator+(const PlaneVector& that) const;
    PlaneVector  operator-(const PlaneVector& that) const;

};

#endif
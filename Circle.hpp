#ifndef CIRCLE_HPP
#define CIRCLE_PP

#include "MeasurableShape.hpp"
#include <iostream>

class Circle : public MeasurableShape {
private:
    PlaneVector m_center;
    double      m_r;

public:
    Circle(const double& x, const double& y, const double& r)
        : m_center{PlaneVector::fromXY(x,y)}
        , m_r{r}
    { 
    }

    const double perimeter()        const override;
    const double area()             const override;
    const PlaneVector center()      const override;
    const double circumference()    const;

    friend std::ostream& operator<<(std::ostream& os, const Circle& c);
};

#endif
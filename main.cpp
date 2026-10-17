/*
 * filename: main.cpp
 * author:   Claude
 * date modified: 10/16/26
 *
 * Tests and demonstrates the shape hierarchy:
 *
 *   MeasurableShape (abstract)
 *   ├── Circle
 *   └── Polygon
 *       └── SimplePolygon
 *           ├── Triangle
 *           └── Rectangle
 *               └── Square
 *
 * The program runs three stages:
 *   1. Compile-time checks (static_assert). If any of these fail, the
 *      program doesn't build at all.
 *   2. Runtime tests, using a small harness defined below. Failures are
 *      reported with file and line, and make main() return EXIT_FAILURE.
 *   3. A demo that stores mixed shapes behind base-class pointers and uses
 *      them polymorphically.
 */

#include "Circle.hpp"
#include "PlaneVector.hpp"
#include "Polygon.hpp"
#include "Rectangle.hpp"
#include "SimplePolygon.hpp"
#include "Square.hpp"
#include "Triangle.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <format>
#include <iostream>
#include <memory>
#include <numbers>
#include <source_location>
#include <sstream>
#include <string_view>
#include <type_traits>
#include <vector>

namespace {

// =============================================================================
// 1. Compile-time checks
// =============================================================================

// PlaneVector's arithmetic is constexpr, so the compiler can evaluate it.
// Exact == is safe here: these values are all exactly representable.
constexpr auto I = PlaneVector::fromXY(1, 0);
constexpr auto J = PlaneVector::fromXY(0, 1);

static_assert(I + J == PlaneVector::fromXY(1, 1));
static_assert(I - J == PlaneVector::fromXY(1, -1));
static_assert(-I + I == PlaneVector::ZERO);
static_assert(PlaneVector{} == PlaneVector::ZERO);
static_assert(2.0 * J == J * 2.0);
static_assert((I * 3.0) / 3.0 == I);
static_assert(I.dot(J) == 0.0, "i and j are perpendicular");
static_assert(I.cross(J) == 1.0, "j is counterclockwise of i");
static_assert(J.cross(I) == -1.0, "i is clockwise of j");
static_assert(PlaneVector::fromXY(3, 4).normSquared() == 25.0);

// Type traits let you assert design decisions about the classes themselves.
static_assert(std::is_abstract_v<MeasurableShape>);
static_assert(std::has_virtual_destructor_v<MeasurableShape>,
              "deleting a derived shape through a base pointer must be safe");
static_assert(std::is_base_of_v<MeasurableShape, Square>);
static_assert(std::is_base_of_v<Rectangle, Square>);
static_assert(std::is_final_v<Circle> && std::is_final_v<Square> && std::is_final_v<Triangle>);
static_assert(!std::is_convertible_v<std::vector<PlaneVector>, Polygon>,
              "Polygon's constructor is explicit: no silent vector -> Polygon conversion");
static_assert(std::is_copy_assignable_v<Rectangle>,
              "Rectangle has no const data members, so it can be reassigned");
static_assert(std::is_nothrow_move_constructible_v<Polygon>,
              "moving a Polygon just moves its vectors' buffers");
static_assert(std::is_trivially_copyable_v<PlaneVector>,
              "PlaneVector is just two doubles; copying is a memcpy");

// =============================================================================
// 2. A tiny test harness
// =============================================================================

int g_passed = 0;
int g_failed = 0;

// std::source_location (C++20) as a default argument captures the *caller's*
// file and line. Before C++20 you needed a macro using __FILE__ and __LINE__.
void check(bool condition, std::string_view description,
           std::source_location where = std::source_location::current())
{
    if (condition) {
        ++g_passed;
        return;
    }
    ++g_failed;
    std::cerr << "  FAIL " << where.file_name() << ':' << where.line()
              << ": " << description << '\n';
}

bool near(double a, double b, double tolerance = 1e-9)
{
    return std::abs(a - b) <= tolerance * std::max({1.0, std::abs(a), std::abs(b)});
}

bool near(const PlaneVector& a, const PlaneVector& b, double tolerance = 1e-9)
{
    return near(a.x(), b.x(), tolerance) && near(a.y(), b.y(), tolerance);
}

// Prints a shape into a string, the same way std::cout would.
std::string toString(const MeasurableShape& shape)
{
    std::ostringstream out;
    out << shape;
    return out.str();
}

void section(std::string_view title)
{
    std::cout << "\n== " << title << " ==\n";
}

// =============================================================================
// Runtime tests, one function per class
// =============================================================================

void testPlaneVector()
{
    using std::numbers::pi;
    section("PlaneVector");

    const auto v = PlaneVector::fromXY(3, 4);
    check(v.norm() == 5.0, "norm of <3, 4> is exactly 5");
    check(v.r() == v.norm(), "r() is norm()");
    check(near(v.unitVector(), PlaneVector::fromXY(0.6, 0.8)), "unit vector of <3, 4>");
    check(near(v.unitVector().norm(), 1.0), "unit vectors have length 1");
    check(PlaneVector::ZERO.unitVector() == PlaneVector::ZERO, "unit vector of ZERO is ZERO");

    const auto p = PlaneVector::fromPolar(2, pi / 3);
    check(near(p.r(), 2.0), "fromPolar round-trips r");
    check(near(p.theta(), pi / 3), "fromPolar round-trips theta");
    check(near(PlaneVector::fromXY(-1, 0).theta(), pi), "theta of <-1, 0> is pi");
    check(near(PlaneVector::fromXY(0, -1).theta(), -pi / 2), "theta of <0, -1> is -pi/2");
    check(PlaneVector::ZERO.theta() == 0.0, "theta of ZERO is 0");
    check(PlaneVector::fromXY(-0.0, 0.0).theta() == 0.0,
          "theta of <-0, 0> is 0, not pi (atan2(+0, -0) would give pi)");

    check(near(I.rotate(pi / 2), J), "rotating i by pi/2 gives j");
    check(near(v.rotate(2 * pi), v), "a full turn is the identity");
    for (int degrees = 0; degrees < 360; degrees += 15) {
        const double radians = degrees * pi / 180;
        check(near(v.rotate(radians).norm(), v.norm()), "rotation preserves length");
    }

    auto w = PlaneVector::fromXY(1, 1);
    w += v;
    w *= 2;
    check(w == PlaneVector::fromXY(8, 10), "compound assignment modifies a non-const vector");

    std::ostringstream out;
    out << PlaneVector::fromXY(1, -2.5);
    check(out.str() == "<1, -2.5>", "operator<< format");
    std::cout << "  e.g. " << v << " rotated 90 degrees is " << v.rotate(pi / 2) << '\n';
}

void testPolygon()
{
    section("Polygon");

    const Polygon unitSquare{{
        PlaneVector::fromXY(0, 0),
        PlaneVector::fromXY(1, 0),
        PlaneVector::fromXY(1, 1),
        PlaneVector::fromXY(0, 1),
    }};
    check(near(unitSquare.area(), 1.0), "counterclockwise unit square has area 1");
    check(near(unitSquare.perimeter(), 4.0), "unit square perimeter");
    check(near(unitSquare.center(), PlaneVector::fromXY(0.5, 0.5)), "unit square center");

    const Polygon clockwise{{
        PlaneVector::fromXY(0, 0),
        PlaneVector::fromXY(0, 1),
        PlaneVector::fromXY(1, 1),
        PlaneVector::fromXY(1, 0),
    }};
    check(near(clockwise.area(), -1.0), "Polygon::area is signed: clockwise is negative");

    // Polygon keeps vertices in the order given. In this order the edges
    // cross each other (a "bowtie"), and the two halves cancel out.
    const Polygon bowtie{{
        PlaneVector::fromXY(1, 1),
        PlaneVector::fromXY(0, 0),
        PlaneVector::fromXY(1, 0),
        PlaneVector::fromXY(0, 1),
    }};
    check(near(bowtie.area(), 0.0), "self-intersecting bowtie has signed area 0");
    check(near(bowtie.perimeter(), 2 + 2 * std::numbers::sqrt2), "bowtie perimeter");
    std::cout << "  bowtie (vertices in the order given):\n" << bowtie;
}

void testSimplePolygon()
{
    section("SimplePolygon");

    // Same scrambled points as the bowtie. SimplePolygon sorts them
    // counterclockwise around their average, which untangles the shape.
    const SimplePolygon untangled{{
        PlaneVector::fromXY(1, 1),
        PlaneVector::fromXY(0, 0),
        PlaneVector::fromXY(1, 0),
        PlaneVector::fromXY(0, 1),
    }};
    check(near(untangled.area(), 1.0), "sorting the bowtie's points gives the unit square");
    check(near(untangled.perimeter(), 4.0), "...with the unit square's perimeter");
    std::cout << "  same points, sorted counterclockwise:\n" << untangled;
}

void testTriangle()
{
    section("Triangle");

    // A 3-4-5 right triangle, with vertices given clockwise on purpose.
    const Triangle t{0, 0, 0, 3, 4, 0};
    check(near(t.area(), 6.0), "3-4-5 triangle area is 6 (positive despite clockwise input)");
    check(near(t.perimeter(), 12.0), "3-4-5 triangle perimeter is 12");
    check(near(t.center(), PlaneVector::fromXY(4.0 / 3.0, 1.0)), "centroid is the vertex average");
}

void testRectangleAndSquare()
{
    section("Rectangle and Square");

    const Rectangle r = Rectangle::fromCenter(2, 2, 10, 4);
    check(near(r.area(), 40.0), "10 x 4 rectangle area");
    check(near(r.perimeter(), 28.0), "10 x 4 rectangle perimeter");
    check(near(r.center(), PlaneVector::fromXY(2, 2)), "fromCenter puts the center where asked");

    check(near(r.area(), r.Polygon::area()), "Rectangle::area agrees with Polygon::area");
    check(near(r.perimeter(), r.Polygon::perimeter()),
          "Rectangle::perimeter agrees with Polygon::perimeter");

    const Rectangle flipped{0, 0, -2, 3};
    check(near(flipped.area(), flipped.Polygon::area()), "negative width: area still agrees");
    check(near(flipped.perimeter(), flipped.Polygon::perimeter()),
          "negative width: perimeter still agrees");

    const Square s = Square::fromCenter(0, 0, 3);
    check(near(s.area(), 9.0), "3 x 3 square area");
    check(near(s.perimeter(), 12.0), "3 x 3 square perimeter");
    check(near(s.center(), PlaneVector::ZERO), "square centered at the origin");

    Rectangle a{0, 0, 1, 1};
    Rectangle b = a;
    b = Rectangle{0, 0, 2, 3};
    check(near(a.area(), 1.0), "assigning to a copy leaves the original alone");
    check(near(b.area(), 6.0), "the copy has the new value");
}

void testCircle()
{
    using std::numbers::pi;
    section("Circle");

    const Circle c{1, -1, 2};
    check(near(c.area(), 4 * pi), "radius-2 circle area");
    check(near(c.perimeter(), 4 * pi), "radius-2 circle perimeter");
    check(c.circumference() == c.perimeter(), "circumference() is perimeter()");
    check(c.center() == PlaneVector::fromXY(1, -1), "center is stored exactly");
    check(near(Circle{0, 0, -2}.area(), c.area()), "a negative radius is treated as its absolute value");
}

void testPolymorphism()
{
    section("Polymorphism");

    const Square square{0, 0, 2};
    const Circle circle{0, 0, 1};

    const MeasurableShape& asShape = square;
    const Polygon& asPolygon = square;
    check(near(asShape.area(), 4.0), "virtual call through MeasurableShape&");
    check(near(asPolygon.area(), 4.0), "virtual call through Polygon&");

    check(toString(circle).starts_with("Circle"), "operator<< dispatches to Circle::print");
    check(toString(square).starts_with("Polygon"), "operator<< dispatches to Polygon::print");
}

// =============================================================================
// 3. Demo: a heterogeneous collection
// =============================================================================


struct NamedShape {
    std::string_view name;
    std::unique_ptr<MeasurableShape> shape;
};

void demo()
{
    section("Demo: shapes sorted by area");

    std::vector<NamedShape> shapes;
    shapes.push_back({"circle", std::make_unique<Circle>(0, 1, 4)});
    shapes.push_back({"rectangle", std::make_unique<Rectangle>(Rectangle::fromCenter(2, 2, 10, 4))});
    shapes.push_back({"square", std::make_unique<Square>(Square::fromCenter(-3, 0, 5))});
    shapes.push_back({"triangle", std::make_unique<Triangle>(0, 0, 4, 0, 0, 3)});
    shapes.push_back({"pentagon", std::make_unique<SimplePolygon>(std::vector{
        PlaneVector::fromPolar(2, 0.0),
        PlaneVector::fromPolar(2, 2 * std::numbers::pi / 5),
        PlaneVector::fromPolar(2, 4 * std::numbers::pi / 5),
        PlaneVector::fromPolar(2, 6 * std::numbers::pi / 5),
        PlaneVector::fromPolar(2, 8 * std::numbers::pi / 5),
    })});

    std::ranges::sort(shapes, std::ranges::greater{},
                      [](const NamedShape& s) { return s.shape->area(); });

    std::cout << std::format("  {:<10} {:>10} {:>10}   {}\n", "shape", "area", "perimeter", "center");
    double totalArea = 0;
    for (const auto& [name, shape] : shapes) {   // structured binding (C++17)
        std::cout << std::format("  {:<10} {:>10.3f} {:>10.3f}   ", name, shape->area(), shape->perimeter())
                  << shape->center() << '\n';
        totalArea += shape->area();
    }
    std::cout << std::format("  {:<10} {:>10.3f}\n", "total", totalArea);

    const auto& [name, shape] = shapes.front();
    std::cout << "\n  The largest shape is the " << name << ":\n" << *shape;

}

} // namespace

int main()
{
    testPlaneVector();
    testPolygon();
    testSimplePolygon();
    testTriangle();
    testRectangleAndSquare();
    testCircle();
    testPolymorphism();

    demo();

    std::cout << "\n" << g_passed << " checks passed, " << g_failed << " failed.\n";
    return g_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

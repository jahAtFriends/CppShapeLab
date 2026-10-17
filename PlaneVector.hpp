/*
 * filename: PlaneVector.hpp
 * author:   Joel Hammer
 * date modified: 10/16/26
 */

#pragma once

#include <iosfwd>

/**
 * A vector in the 2D Euclidean plane.
 *
 * A PlaneVector can be read either as an ordered <x, y> pair or as a
 * magnitude and direction (r, theta); both views are always available.
 * Non-zero vectors are built through the named factories fromXY() and
 * fromPolar(), so every call site says which coordinate system it means.
 *
 * PlaneVector is a small value type: copy it freely and pass it by value or
 * by const&. As with any C++ value, immutability is up to the holder: a
 * `const PlaneVector` can never change, while a non-const one supports the
 * compound-assignment operators (+=, -=, *=, /=).
 *
 * [[nodiscard]] on the class makes the compiler warn whenever a function
 * returning a PlaneVector has its result ignored, e.g. `v.rotate(a);` on a
 * line by itself, which looks like it rotates v but does nothing.
 */
class [[nodiscard]] PlaneVector {
public:
    /** The zero vector <0, 0>. Defined below, once the class is complete. */
    static const PlaneVector ZERO;

    /** Constructs the zero vector. */
    constexpr PlaneVector() = default;

    /**
     * Constructs a PlaneVector from Cartesian components.
     * @param x the x component
     * @param y the y component
     */
    static constexpr PlaneVector fromXY(double x, double y) { return PlaneVector{x, y}; }

    /**
     * Constructs a PlaneVector from polar components.
     * @param r     the magnitude of the vector
     * @param theta the direction of the vector, in radians from the +x axis
     */
    static PlaneVector fromPolar(double r, double theta);

    constexpr double x() const { return m_x; }
    constexpr double y() const { return m_y; }
    double r() const { return norm(); }
    /** The direction in radians, in [-pi, pi]. The zero vector has theta 0. */
    double theta() const;

    constexpr double dot(const PlaneVector& that) const { return m_x * that.m_x + m_y * that.m_y; }
    /** The z component of the 3D cross product; positive if `that` is counterclockwise of this. */
    constexpr double cross(const PlaneVector& that) const { return m_x * that.m_y - m_y * that.m_x; }
    constexpr double normSquared() const { return dot(*this); }
    double norm() const;

    /** A vector of length 1 in the same direction, or ZERO for the zero vector. */
    PlaneVector unitVector() const;
    /** This vector rotated counterclockwise by alpha radians. */
    PlaneVector rotate(double alpha) const;

    constexpr PlaneVector& operator+=(const PlaneVector& that) {
        m_x += that.m_x;
        m_y += that.m_y;
        return *this;
    }

    constexpr PlaneVector& operator-=(const PlaneVector& that) {
        m_x -= that.m_x;
        m_y -= that.m_y;
        return *this;
    }

    constexpr PlaneVector& operator*=(double k) {
        m_x *= k;
        m_y *= k;
        return *this;
    }

    constexpr PlaneVector& operator/=(double k) {
        m_x /= k;
        m_y /= k;
        return *this;
    }

    constexpr PlaneVector operator-() const { return PlaneVector{-m_x, -m_y}; }

    friend constexpr PlaneVector operator+(PlaneVector left, const PlaneVector& right) { return left += right; }
    friend constexpr PlaneVector operator-(PlaneVector left, const PlaneVector& right) { return left -= right; }
    friend constexpr PlaneVector operator*(PlaneVector v, double k) { return v *= k; }
    friend constexpr PlaneVector operator*(double k, PlaneVector v) { return v *= k; }
    friend constexpr PlaneVector operator/(PlaneVector v, double k) { return v /= k; }
    constexpr bool operator==(const PlaneVector&) const = default;

private:
    constexpr PlaneVector(double x, double y) : m_x{x}, m_y{y} {}

    double m_x{0.0};
    double m_y{0.0};
};

inline constexpr PlaneVector PlaneVector::ZERO{};

/** Writes v as "<x, y>". */
std::ostream& operator<<(std::ostream& os, const PlaneVector& v);

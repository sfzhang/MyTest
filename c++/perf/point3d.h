/*************************************************************************
 *
 *   Copyright (C) 2015-2018 by Shanghai Shende Healthcare Co.Ltd.
 *
 *   All rights reserved.
 *
 ************************************************************************/

/**
 * @file point3d.h
 *
 * @author guojunjie
 *
 * @date 2018.04.23
 *
 * @brief point3d template class
 *
 */

#ifndef POINT3D_H
#define POINT3D_H

#include <cmath>
#define HIFU_PRECISION 0.000001

/**
 * @class point 32d class
 *
 * @brief 3D coordinate system point system
 */
template <typename T>
class Point3d {
public:

    /**
     * @brief Default constructor
     *
     * @param N/A
     *
     * @return N/A
     */
    Point3d(): m_x(static_cast<T>(0)), m_y(static_cast<T>(0)),
        m_z(static_cast<T>(0)), m_status(0) {}

    /**
     * @brief Override constructor
     *
     * @param[in] x X axis
     * @param[in] y Y axis
     * @param[in] z Z axis
     *
     * @return N/A
     */
    Point3d(const T &x, const T &y, const T &z, int status = 0): m_x(x), m_y(y), m_z(z),
        m_status(status) {}

    /**
     * @brief Copy constructor
     *
     * @param[in] x X axis
     * @param[in] y Y axis
     *
     * @return N/A
     */
    Point3d(const Point3d &point): m_x(point.m_x), m_y(point.m_y),
        m_z(point.m_z), m_status(point.m_status) {}

    /**
     * @brief Override operator =
     *
     * @param[in] point Right point
     *
     * @return The duplicated point
     */
    Point3d& operator=(const Point3d &point)
    {
        if (this != &point) {
            m_x = point.m_x;
            m_y = point.m_y;
            m_z = point.m_z;
            m_status = point.m_status;
        }

        return *this;
    }

    /**
     * @brief Override operator +
     *
     * @param[in] point Point to add
     *
     * @return The result point
     */
    Point3d operator+(const Point3d &point) const
    {
        return Point3d((m_x + point.m_x), (m_y + point.m_y), (m_z + point.m_z));
    }

    /**
     * @brief Override operator -
     *
     * @param[in] point The subtrahend point
     *
     * @return The result point
     */
    Point3d operator-(const Point3d &point) const
    {
        return Point3d((m_x - point.m_x), (m_y - point.m_y), (m_z - point.m_z));
    }

    /**
     * @brief operator *
     * @param s
     * @return The new Point3d
     */
    Point3d operator*(double s) const
    {
        return Point3d(m_x * s, m_y * s, m_z * s);
    }

    /**
     * @brief operator /
     * @param s
     * @return The new Point3d
     */
    Point3d operator/(double s) const
    {
        return Point3d(m_x / s, m_y / s, m_z / s);
    }

    /**
     * @brief normal
     * @return
     */
    double normal() const
    {
        return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
    }

    /**
     * @brief Normalize
     * @return normalize vector
     */
    Point3d normalize() const
    {
        double n = normal();
        if (n >= HIFU_PRECISION) {
            return Point3d((m_x / n), (m_y / n), (m_z / n));
        }
        else {
            return Point3d();
        }
    }

    /**
     * @brief Override operator ==
     *
     * @param[in] point The point compared
     *
     * @retval true  The two points are equal
     * @retval false The two points are NOT equal
     */
    bool operator==(const Point3d &point) const
    {
        return ((fabs(m_x - point.m_x) <= HIFU_PRECISION) &&
                (fabs(m_y - point.m_y) <= HIFU_PRECISION) &&
                (fabs(m_z - point.m_z) <= HIFU_PRECISION));
    }

    /**
     * @brief Override operator !=
     *
     * @param[in] point The point compared
     *
     * @retval true  The two points are NOT equal
     * @retval false The two points are equal
     */
    bool operator!=(const Point3d &point) const
    {
        return !(*this == point);
    }

    /**
     * @brief Override operator <
     *
     * @param[in] point The point compared
     *
     * @reture if less than point, otherwise false
     */
    bool operator<(const Point3d &point) const
    {
        if (fabs(m_z - point.m_z) > HIFU_PRECISION) {
            return m_z < point.m_z;
        }
        else {
            if (fabs(m_y - point.m_y) > HIFU_PRECISION) {
                return m_y < point.m_y;
            }
            else {
                if (fabs(m_x - point.m_x) > HIFU_PRECISION) {
                    return m_x < point.m_x;
                }
                else {
                    return false; /* Now equal */
                }
            }
        }
    }

    /**
     * @brief Override operator >
     *
     * @param[in] point The point compared
     *
     * @reture true if greater than point
     */
    bool operator>(const Point3d &point) const
    {
        if (fabs(m_z - point.m_z) > HIFU_PRECISION) {
            return m_z > point.m_z;
        }
        else {
            if (fabs(m_y - point.m_y) > HIFU_PRECISION) {
                return m_y > point.m_y;
            }
            else {
                if (fabs(m_x - point.m_x) > HIFU_PRECISION) {
                    return m_x > point.m_x;
                }
                else {
                    return false; /* Now equal */
                }
            }
        }
    }

    /**
     * @brief Raw compare two points is equal or not
     *
     * @param[in] point The point compared
     *
     * @retval true  The two points are equal
     * @retval false The two points are NOT equal
     */
    bool equal(const Point3d &point) const
    {
        return ((m_x == point.m_x) &&
                (m_y == point.m_y) &&
                (m_z == point.m_z));
    }

    /**
     * @brief Raw compare, this point is less than the given point
     *
     * @param[in] point The point compared
     *
     * @reture if less than point, otherwise false
     */
    bool less(const Point3d &point) const
    {
        if (m_z < point.m_z) {
            return true;
        }
        else if (m_z > point.m_z) {
            return false;
        }

        if (m_y < point.m_y) {
            return true;
        }
        else if (m_y > point.m_y) {
            return false;
        }

        return m_x < point.m_x;
    }

    /**
     * @brief Raw compare, this point is greater than the given point
     *
     * @param[in] point The point compared
     *
     * @reture true if greater, otherwise false
     */
    bool greater(const Point3d &point) const
    {
        if (m_z > point.m_z) {
            return true;
        }
        else if (m_z < point.m_z) {
            return false;
        }

        if (m_y > point.m_y) {
            return true;
        }
        else if (m_y < point.m_y) {
            return false;
        }

        return m_x > point.m_x;
    }

    /**
     * @brief Get X
     *
     * @return X
     */
    T x() const
    {
        return m_x;
    }

    /**
     * @brief Get Y
     *
     * @return Y
     */
    T y() const
    {
        return m_y;
    }


    /**
     * @brief Get Z
     *
     * @return Z
     */
    T z() const
    {
        return m_z;
    }

    /**
     * @brief Set X
     *
     * @param[in] x The new x
     */
    void setX(const T& x)
    {
        m_x = x;
    }

    /**
     * @brief Set Y
     *
     * @param[in] y The new y
     */
    void setY(const T& y)
    {
        m_y = y;
    }

    /**
     * @brief Set Z
     *
     * @param[in] z The new z
     */
    void setZ(const T& z)
    {
        m_z = z;
    }

    /**
     * @brief Dot product
     * @param[in] point The other point
     * @return Dot product
     */
    T dot(const Point3d &point) const
    {
        return (m_x * point.m_x + m_y * point.m_y + m_z * point.m_z);
    }

    /**
     * @brief Cross product
     * @param[in] point The other point
     * @return Cross product
     */
    Point3d cross(const Point3d &point) const
    {
        return Point3d(((m_y * point.m_z) - (m_z * point.m_y)),
                       ((m_z * point.m_x) - (m_x * point.m_z)),
                       ((m_x * point.m_y) - (m_y * point.m_x)));
    }

    /**
     * @brief Check if parallel
     * @param[in] point The other point
     * @param[in] precision The precision
     * @return true if parallel, otherwise false
     */
    bool isParallel(const Point3d &point, double precision = HIFU_PRECISION) const
    {
        if (fabs(fabs(normalize().dot(point.normalize())) - 1) <= precision) {
            return true;
        }
        else {
            return false;
        }
    }

    /**
     * @brief Check if perpendicular
     * @param[in] point The other point
     * @param[in] precision The precision
     * @return true if perpendicular, otherwise false
     */
    bool isPerpen(const Point3d &point, double precision = HIFU_PRECISION) const
    {
        if (fabs(normalize().dot(point.normalize())) <= precision) {
            return true;
        }
        else {
            return false;
        }
    }

protected:

    /** X axis */
    T m_x;

    /** Y axis */
    T m_y;

    /** Z axis */
    T m_z;

    /** Redundancy member */
    int m_status;

};

#endif /* !POINT3D_H */

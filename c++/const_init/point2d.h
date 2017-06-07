#ifndef POINT2D_H
#define POINT2D_H

#include <cmath>
#define HIFU_PRECISION 0.000001

/** @brief 2D coordinate system point system */
template <typename T>
class Point2d {
public:

    /**
     * @brief Default constructor
     *
     * @param N/A
     *
     * @return N/A
     */
    Point2d(): m_x(static_cast<T>(0)), m_y(static_cast<T>(0)) {}

    /**
     * @brief Override constructor
     *
     * @param[in] x X axis
     * @param[in] y Y axis
     *
     * @return N/A
     */
    Point2d(const T &x, const T &y): m_x(x), m_y(y) {}

    /**
     * @brief Copy constructor
     *
     * @param[in] x X axis
     * @param[in] y Y axis
     *
     * @return N/A
     */
    Point2d(const Point2d &point): m_x(point.m_x), m_y(point.m_y) {}

    /**
     * @brief Override operator =
     *
     * @param[in] point Right point
     *
     * @return The duplicated point
     */
    Point2d& operator=(const Point2d &point)
    {
        if (this != &point) {
            m_x = point.m_x;
            m_y = point.m_y;
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
    Point2d operator+(const Point2d &point)
    {
        return Point2d((m_x + point.m_x), (m_y + point.m_y));
    }

    /**
     * @brief Override operator -
     *
     * @param[in] point The subtrahend point
     *
     * @return The result point
     */
    Point2d operator-(const Point2d &point)
    {
        return Point2d((m_x - point.m_x), (m_y - point.m_y));
    }

    /**
     * @brief operator *
     * @param s
     * @return
     */
    Point2d operator*(double s)
    {
        return Point2d(m_x * s, m_y * s);
    }

    /**
     * @brief normal
     * @return
     */
    double normal()
    {
        return sqrt(m_x * m_x + m_y * m_y);
    }

    /**
     * @brief Override operator ==
     *
     * @param point[in] The point compared
     *
     * @retval true  The two points are equal
     * @retval false The two points are NOT equal
     */
    bool operator==(const Point2d &point) const
    {
        return (((m_x == point.m_x) && (m_y == point.m_y)) ||
                ((fabs(m_x - point.m_x) < HIFU_PRECISION) &&
                 (fabs(m_y - point.m_y) < HIFU_PRECISION)));
    }

    /**
     * @brief Override operator !=
     *
     * @param[in] point The point compared
     *
     * @retval true  The two points are NOT equal
     * @retval false The two points are equal
     */
    bool operator!=(const Point2d &point) const
    {
        return !(*this == point);
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
     * @brief Set X
     *
     * @param[in] x The new x
     */
    void setX(const T& x)
    {
        m_x = x;
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
     * @brief Set Y
     *
     * @param[in] y The new y
     */
    void setY(const T& y)
    {
        m_y = y;
    }

protected:

    /** X axis */
    T m_x;

    /** Y axis */
    T m_y;

};

#endif /* !POINT2D_H */

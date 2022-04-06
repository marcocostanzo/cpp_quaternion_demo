#pragma once

#include <cmath>

namespace vanvitelli
{

    template <typename Scalar>
    class Vector3
    {
    private:
        Scalar x_, y_, z_;

    public:
        Vector3(const Scalar &x, const Scalar &y, const Scalar &z)
            : x_(x), y_(y), z_(z)
        {
        }

        Vector3(const Vector3<Scalar>& v) = default;

        ~Vector3() = default;

        const Scalar &x() const
        {
            return x_;
        }

        const Scalar &y() const
        {
            return y_;
        }

        const Scalar &z() const
        {
            return z_;
        }

        Scalar &x()
        {
            return x_;
        }

        Scalar &y()
        {
            return y_;
        }

        Scalar &z()
        {
            return z_;
        }

        Scalar squaredNorm() const
        {
            return this->scalarProd(*this);
        }

        Scalar norm() const
        {
            return std::sqrt(squaredNorm());
        }

        Scalar scalarProd(const Vector3<Scalar> &v2) const
        {
            return x_ * v2.x_ + y_ * v2.y_ + z_ * v2.z_;
        }

        Vector3<Scalar> cross(const Vector3<Scalar> &v2) const
        {
            return Vector3<Scalar>(y_ * v2.z_ - z_ * v2.y_, z_ * v2.x_ - x_ * v2.z_, x_ * v2.y_ - y_ * v2.x_);
        }

        Vector3<Scalar> operator-() const
        {
            return Vector3<Scalar>(-x_, -y_, -z_);
        }

        Vector3<Scalar> operator+(const Vector3<Scalar> &v2) const
        {
            return Vector3<Scalar>(x_ + v2.x_, y_ + v2.y_, z_ + v2.z_);
        }

        Vector3<Scalar> operator/(const Scalar &a) const
        {
            return Vector3<Scalar>(x_ / a, y_ / a, z_ / a);
        }

        Vector3<Scalar> operator*(const Scalar &a) const
        {
            return Vector3<Scalar>(x_ * a, y_ * a, z_ * a);
        }

        friend Vector3<Scalar> operator*(const Scalar &a, Vector3<Scalar> v)
        {
            return v * a;
        }
    };

}
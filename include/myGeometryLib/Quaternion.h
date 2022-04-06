#pragma once

#include "Vector3.h"
#include <iostream>

namespace vanvitelli
{

    template <typename Scalar>
    class UnitQuaternion;

    template <typename Scalar>
    class Quaternion
    {
    protected:
        Vector3<Scalar> v_;
        Scalar w_;

    public:
        Quaternion(const Scalar &x, const Scalar &y, const Scalar &z, const Scalar &w) : v_(x, y, z),
                                                                                         w_(w)
        {
        }

        Quaternion(const Vector3<Scalar> &v, const Scalar &w)
            : v_(v),
              w_(w)
        {
        }

        Quaternion(const Scalar &w, const Vector3<Scalar> &v)
            : Quaternion(v, w)
        {
        }

        const Vector3<Scalar> &v() const
        {
            return v_;
        }

        const Scalar &w() const
        {
            return w_;
        }

        virtual void setV(const Vector3<Scalar>& v)
        {
            v_ = v;
        }

        virtual void setW(const Scalar& w)
        {
            w_ = w;
        }

        virtual ~Quaternion() = default;

        virtual Scalar squaredNorm() const
        {
            return v_.squaredNorm() + w_ * w_;
        }

        virtual Scalar norm() const
        {
            return std::sqrt(squaredNorm());
        }

        virtual UnitQuaternion<Scalar> unit() const
        {
            Scalar norm_ = norm();
            return UnitQuaternion<Scalar>(v_ / norm_, w_ / norm_);
        }

        virtual void normalize()
        {
            Scalar norm_ = norm();
            v_ = v_ / norm_;
            w_ = w_ / norm_;
        }

        virtual Quaternion<Scalar> prod(const Quaternion<Scalar> &q2) const
        {
            Scalar w_prod = w_ * q2.w_ - v_.scalarProd(q2.v_);
            Vector3<Scalar> v_prod = w_ * q2.v_ + q2.w_ * v_ + v_.cross(q2.v_);
            return Quaternion<Scalar>(v_prod, w_prod);
        }

        virtual void print()
        {
            std::cout << "Quaternion: < " << v_.x() << " , " << v_.y() << " , " << v_.z() << " > , " << w_ << "\n";
        }
    };

    template <typename Scalar>
    Quaternion<Scalar> conj(const Quaternion<Scalar> &q)
    {
        return Quaternion<Scalar>(-q.v(), q.w());
    }

    template <typename Scalar>
    Quaternion<Scalar>
    inv(const Quaternion<Scalar> &q)
    {
        Scalar norm2_ = q.squaredNorm();
        return Quaternion<Scalar>(-q.v() / norm2_, q.w() / norm2_);
    }

}
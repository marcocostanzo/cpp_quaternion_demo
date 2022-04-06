#pragma once

#include "Quaternion.h"
#include <limits>
#include <stdexcept>

namespace vanvitelli
{

    template <typename Scalar>
    class UnitQuaternion : public Quaternion<Scalar>
    {
    protected:
    public:
        UnitQuaternion()
            : Quaternion<Scalar>(Scalar(0), Scalar(0), Scalar(0), Scalar(1))
        {
        }

        UnitQuaternion(const Scalar &x, const Scalar &y, const Scalar &z, const Scalar &w)
            : Quaternion<Scalar>(x, y, z, w)
        {
            checkNormalized();
        }

        UnitQuaternion(const Vector3<Scalar> &v, const Scalar &w)
            : Quaternion<Scalar>(v, w)
        {
            checkNormalized();
        }

        UnitQuaternion(const Scalar &w, const Vector3<Scalar> &v)
            : UnitQuaternion(v, w)
        {
        }

        void checkNormalized() const
        {
            Scalar tmp = Quaternion<Scalar>::squaredNorm() - Scalar(1.0);
            tmp = tmp*tmp;
            if (tmp > std::numeric_limits<Scalar>::epsilon())
            {
                throw std::runtime_error("UnitQuaternion not unit!, the squared norm is: " + std::to_string(Quaternion<Scalar>::squaredNorm()));
            }
        }

        virtual ~UnitQuaternion() = default;

        virtual void setV(const Vector3<Scalar> &v) override
        {
            this->v_ = v;
            checkNormalized();
        }

        virtual void setW(const Scalar &w) override
        {
            this->w_ = w;
            checkNormalized();
        }

        virtual void forceNormalize()
        {
            Scalar norm_ = std::sqrt(Quaternion<Scalar>::squaredNorm());
            std::cout << "forceNormalize - the norm is:" << norm_ << "\n";
            this->v_ = this->v_ / norm_;
            this->w_ = this->w_ / norm_;
        }

        virtual Scalar squaredNorm() const override
        {
            return Scalar(1);
        }

        virtual Scalar norm() const override
        {
            return Scalar(1);
        }

        virtual UnitQuaternion<Scalar> unit() const override
        {
            return UnitQuaternion<Scalar>(*this);
        }

        virtual UnitQuaternion<Scalar> prod(const UnitQuaternion<Scalar> &q2) const
        {
            return Quaternion<Scalar>::prod(q2).unit();
        }

        virtual void print() override
        {
            std::cout << "UnitQuaternion: << " << Quaternion<Scalar>::v_.x() << " , " << Quaternion<Scalar>::v_.y() << " , " << Quaternion<Scalar>::v_.z() << " >> , " << Quaternion<Scalar>::w_ << "\n";
        }
    };

    template <typename Scalar>
    UnitQuaternion<Scalar> conj(const UnitQuaternion<Scalar> &q)
    {
        return UnitQuaternion<Scalar>(-q.v(), q.w());
    }

    template <typename Scalar>
    UnitQuaternion<Scalar>
    inv(const UnitQuaternion<Scalar> &q)
    {
        return conj(q);
    }

}
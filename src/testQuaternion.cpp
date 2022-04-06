#include "myGeometryLib/UnitQuaternion.h"
#include <memory>

int main(int argc, char const *argv[])
{
    
    vanvitelli::UnitQuaternion<double> uq;

    vanvitelli::UnitQuaternion<double> uq2 = vanvitelli::Quaternion<double>(1,2,3,4).unit();

    uq.print();
    uq2.print();

    auto uq3 = uq.prod(uq2);

    uq3.print();

    auto q4 = conj(uq3);

    auto q5 = q4.prod(uq3);

    printf("\n\n");
    uq3.print();
    q4.print();
    q5.print();

    printf("\n pointers:\n");
    std::shared_ptr<vanvitelli::Quaternion<double>> q_p(new vanvitelli::UnitQuaternion<double> );
    q_p->print();

    {
    std::shared_ptr<vanvitelli::Quaternion<double>> q_p2 = q_p;
    auto v = q_p2->v();
    v.x() = 1;
    try
    {
        q_p2->setV(v);
    }
    catch(const std::runtime_error& e)
    {
        std::cout << e.what() << "\n";
        std::static_pointer_cast<vanvitelli::UnitQuaternion<double>>(q_p2)->forceNormalize();
    }
    }

    q_p->print();

    return 0;
}

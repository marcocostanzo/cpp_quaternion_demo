#include "myGeometryLib/UnitQuaternion.h"
#include <memory>

int main(int argc, char const *argv[])
{

    /*
        these are very fast tests
        please try more complex tests
        I didn't check the results on MATLAB (please inform me if you find a bug)
    */

    // Build a Unit Quaternion by using the default constructor (Identity)
    vanvitelli::UnitQuaternion<double> uq;

    // Unit quaternion from the normalization of <1 2 3>, 4
    vanvitelli::UnitQuaternion<double> uq2 = vanvitelli::Quaternion<double>(1, 2, 3, 4).unit();

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

    // test with pointers
    printf("\n pointers:\n");

    // this is a Quaternion Pointer that points to a UnitQuaternion
    std::shared_ptr<vanvitelli::Quaternion<double>> q_p(new vanvitelli::UnitQuaternion<double>);
    q_p->print(); // calls the print function of the UnitQuaternion

    {
        // we use shared_ptr, we can copy the pointer!
        std::shared_ptr<vanvitelli::Quaternion<double>> q_p2 = q_p;

        // here we get the vector part and set the x to 1
        auto v = q_p2->v();
        v.x() = 1;
        try
        {
            q_p2->setV(v); // this line causes a runtime_error, the quaternion will not be unit
            /*
                note that the setV method checks if the quaternion is unit after the actual set!
                for this reason, in the catch block, the UnitQuaternion is not unit!
                Obviously, we can write the setV function to avoid this case!
            */
        }
        catch (const std::runtime_error &e)
        {
            // in the catch block, we print the error message
            std::cout << e.what() << "\n";

            /*
            std::static_pointer_cast<T> casts a smart pointer in a different type
            it is useful to cast a Base class pointer in a Derived class one
            the operation must be feasible, the pointer must actually point to a Derived class object!
            We want to call the forceNormalize() method that is defined only in the UnitQuaternion class,
            thus, we need a UnitQuaternion pointer!
            */
            std::static_pointer_cast<vanvitelli::UnitQuaternion<double>>(q_p2)->forceNormalize();
        }
        // here the pointer q_p2 goes out of scope, but q_p is still alive
        // -> the pointed object is not destroyed
    }

    q_p->print();

    return 0;
}

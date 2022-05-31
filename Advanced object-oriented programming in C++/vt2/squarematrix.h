/**\file squarematrix.h
* \brief SquareMatrix otsikkotiedosto.
*
*/

#ifndef SQUAREMATRIX_INCLUDED
#define SQUAREMATRIX_INCLUDED
#include "intelement.h"
#include <string>
#include "catch.hpp"

using namespace std;

/**\brief SquareMatrix -luokka.
*
* \param    e11,e12,e21,e22 Matriisin e elementit.
* \param    i11,i12,i21,i22 i elementit e elementtien alustamista varten.
* \param    m Referenssi matriisiin.
*
*/
class SquareMatrix{
    private:
        IntElement e11;
        IntElement e12;
        IntElement e21;
        IntElement e22;

    public:
        SquareMatrix();
        SquareMatrix(IntElement i11, IntElement i12, IntElement i21, IntElement i22);
        SquareMatrix(const SquareMatrix& m);
        ~SquareMatrix();
        SquareMatrix& operator+=(const SquareMatrix& m);
        SquareMatrix& operator-=(const SquareMatrix& m);
        SquareMatrix& operator*=(const SquareMatrix& m);
        void print(std::ostream&) const;
        std::string toString() const;
};

#endif

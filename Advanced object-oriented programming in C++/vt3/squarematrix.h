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
*
*/
class SquareMatrix{
    private:
        int n;
        std::vector<std::vector<IntElement> > elements;

    public:
        SquareMatrix();
        SquareMatrix(int i_n, const std::vector<std::vector<IntElement> >& i_elements);
        SquareMatrix(const SquareMatrix& m);
        ~SquareMatrix();
        SquareMatrix& operator=(const SquareMatrix& m);
        SquareMatrix transpose() const;
        SquareMatrix& operator+=(const SquareMatrix& m);
        SquareMatrix& operator-=(const SquareMatrix& m);
        SquareMatrix& operator*=(const SquareMatrix& m);
        bool operator==(const SquareMatrix& m);
        void print(std::ostream&) const;
        std::string toString() const;
};

IntElement dotProduct(const std::vector<IntElement>& v1, const std::vector<IntElement>& v2);


#endif

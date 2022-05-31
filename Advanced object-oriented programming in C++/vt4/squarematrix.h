/**\file squarematrix.h
* \brief SquareMatrix otsikkotiedosto.
*
*/

#ifndef SQUAREMATRIX_H_INCLUDED
#define SQUAREMATRIX_H_INCLUDED
#include "intelement.h"

/**\brief SquareMatrix -luokka.
* \param    n Matriisin arvon esittely.
* \param    m Referenssi matriisiin.
*/
class SquareMatrix{
    private:
        int n;
        std::vector<std::vector<uniq_elem_ptr>> elements;
    public:
        SquareMatrix();
        SquareMatrix(const std::string& str_m);
        SquareMatrix(const SquareMatrix& m);
        SquareMatrix(SquareMatrix&& m);
        ~SquareMatrix();
        SquareMatrix& operator=(const SquareMatrix& m);
        SquareMatrix& operator=(SquareMatrix&& m);
        SquareMatrix transpose()const;
        SquareMatrix& operator+=(const SquareMatrix& m);
        SquareMatrix& operator-=(const SquareMatrix& m);
        SquareMatrix& operator*=(const SquareMatrix& m);
        bool operator==(const SquareMatrix& m)const;
        void print(std::ostream&)const;
        std::string toString()const;
};


#endif // SQUAREMATRIX_H_INCLUDED

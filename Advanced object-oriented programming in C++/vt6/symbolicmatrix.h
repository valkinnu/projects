/**\file symbolicmatrix.h
* \brief SquareMatrix otsikkotiedosto.
*
*/

#ifndef SYMBOLICMATRIX_H_INCLUDED
#define SYMBOLICMATRIX_H_INCLUDED
#include "element.h"


/**\brief SymbolicSquareMatrix -luokka.
* \param    n Matriisin arvon esittely.
* \param    m Referenssi matriisiin.
*/
class SymbolicSquareMatrix{
    private:
        int n;
        std::vector<std::vector<uniq_intelem_ptr>> elements;
    public:
        SymbolicSquareMatrix();
        SymbolicSquareMatrix(const std::string& str_m);
        SymbolicSquareMatrix(const SymbolicSquareMatrix& m);
        SymbolicSquareMatrix(SymbolicSquareMatrix&& m);
        ~SymbolicSquareMatrix();
        SymbolicSquareMatrix& operator=(const SymbolicSquareMatrix& m);
        SymbolicSquareMatrix& operator=(SymbolicSquareMatrix&& m);
        SymbolicSquareMatrix transpose()const;
        SymbolicSquareMatrix& operator+=(const SymbolicSquareMatrix& m);
        SymbolicSquareMatrix& operator-=(const SymbolicSquareMatrix& m);
        SymbolicSquareMatrix& operator*=(const SymbolicSquareMatrix& m);
        bool operator==(const SymbolicSquareMatrix& m)const;
        void print(std::ostream&)const;
        std::string toString()const;
        SymbolicSquareMatrix operator+(const SymbolicSquareMatrix& m);
        SymbolicSquareMatrix operator-(const SymbolicSquareMatrix& m);
        SymbolicSquareMatrix operator*(const SymbolicSquareMatrix& m);
        int evaluate (const Valuation& val) const;
};

std::ostream& operator<<(std::ostream &os, const SymbolicSquareMatrix &symb);



#endif // SQUAREMATRIX_H_INCLUDED

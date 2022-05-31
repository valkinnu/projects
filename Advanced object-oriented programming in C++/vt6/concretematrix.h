/**\file concretematrix.h
* \brief SquareMatrix otsikkotiedosto.
*
*/

#ifndef CONCRETEMATRIX_H_INCLUDED
#define CONCRETEMATRIX_H_INCLUDED
#include "element.h"


/**\brief ConcreteSquareMatrix -luokka.
* \param    n Matriisin arvon esittely.
* \param    m Referenssi matriisiin.
*/

class ConcreteSquareMatrix{
    private:
        int n;
        std::vector<std::vector<uniq_intelem_ptr>> elements;
    public:
        ConcreteSquareMatrix();
        ConcreteSquareMatrix(const std::string& str_m);
        ConcreteSquareMatrix(const ConcreteSquareMatrix& m);
        ConcreteSquareMatrix(ConcreteSquareMatrix&& m);
        ~ConcreteSquareMatrix();
        ConcreteSquareMatrix& operator=(const ConcreteSquareMatrix& m);
        ConcreteSquareMatrix& operator=(ConcreteSquareMatrix&& m);
        ConcreteSquareMatrix transpose()const;
        ConcreteSquareMatrix& operator+=(const ConcreteSquareMatrix& m);
        ConcreteSquareMatrix& operator-=(const ConcreteSquareMatrix& m);
        ConcreteSquareMatrix& operator*=(const ConcreteSquareMatrix& m);
        bool operator==(const ConcreteSquareMatrix& m)const;
        void print(std::ostream&)const;
        std::string toString()const;
};
ConcreteSquareMatrix operator+(const ConcreteSquareMatrix &m, const ConcreteSquareMatrix &k);
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix &m, const ConcreteSquareMatrix &k);
ConcreteSquareMatrix operator*(const ConcreteSquareMatrix &m, const ConcreteSquareMatrix &k);
std::ostream& operator<<(std::ostream& os, const ConcreteSquareMatrix& conc);



#endif // SQUAREMATRIX_H_INCLUDED

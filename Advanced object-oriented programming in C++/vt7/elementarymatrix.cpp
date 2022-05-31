/**\file elementarytematrix.cpp.
  *\brief ElementarySquareMatrix toteutus ja catch test caset.
*/

#include "elementarymatrix.h"
#include <stdexcept>
#include <vector>
#include <limits>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <ostream>

using namespace std;


/**\brief Operaattori
*
*  \return Palauttaa SymbolicSquareMatrix objektin
*
*   "+" laskutoimitusoperaattori
**/

/*
template<>
SymbolicSquareMatrix SymbolicSquareMatrix::operator+(const SymbolicSquareMatrix& m){

    if(n!=m.n){
        throw(std::out_of_range("Dimensions are no good"));
    }
    SymbolicSquareMatrix ssm;
    auto m_row = m.elements.begin();

    for(auto& row : elements) {
        std::vector<uniq_elem_ptr> rowVector;
        auto m_elem = m_row->begin();
        for(auto& elem : row) {
            rowVector.push_back(uniq_elem_ptr new CompositeElement(*elem,**m_elem,std::plus<int>(),'+'));
            m_elem++;
        }
        m_row++;
        ssm.elements.push_back(std::move(rowVector));
    }
    ssm.n = n;
    return ssm;

}
*/

/**\brief Metodi.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \param iter1 Iteraattori 1.
* \param iter2 Iteraattori 2.
* \param a,b Väliaikaiset muuttujat.
* \return Palauttaa ConcreteSquareMatrix objektin.
*
* "+=" laskutoimitusmetodi.
*/

template<>
ConcreteSquareMatrix& ConcreteSquareMatrix::operator+=(const ConcreteSquareMatrix &m){
    if(n!=m.n){
        throw(std::out_of_range("Dimensions are no good"));
    }
    auto iter1 = elements.begin();
    auto iter2 = m.elements.begin();
    while(iter1!=elements.end() && iter2!=m.elements.end()){
        std::transform(iter1->begin(),iter1->end(),iter2->begin(),iter1->begin(),[](const uniq_intelem_ptr &a, const uniq_intelem_ptr &b){
        uniq_intelem_ptr ptElem = uniq_intelem_ptr(new IntElement (a->getVal()+b->getVal()));
        return ptElem;
        });
        iter1++;
        iter2++;
    }
    return (*this);
}

/**\brief Metodi.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \param iter1 Iteraattori 1.
* \param iter2 Iteraattori 2.
* \param a,b Väliaikaiset muuttujat.
* \return Palauttaa ConcreteSquareMatrix objektin.
*
* "-=" laskutoimitusmetodi.
*/

template <>
ConcreteSquareMatrix& ConcreteSquareMatrix::operator-=(const ConcreteSquareMatrix &m){
   if(n!=m.n){
        throw(std::out_of_range("Dimensions are no good"));
    }
    auto iter1 = elements.begin();
    auto iter2 = m.elements.begin();
    while(iter1!=elements.end() && iter2!=m.elements.end()){
        std::transform(iter1->begin(),iter1->end(),iter2->begin(),iter1->begin(),[](const uniq_intelem_ptr &a, const uniq_intelem_ptr &b){
        uniq_intelem_ptr ptElem = uniq_intelem_ptr(new IntElement (a->getVal()-b->getVal()));
        return ptElem;
        });
        iter1++;
        iter2++;
    }
    return (*this);
}

/**\brief Metodi.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \param new_elements Uusi elementtivektori.
* \param trans Neliömatriisimuuttuja.
* \param row Vektorin rivi.
* \param new_row Vektorin seuraavan rivin vektori.
* \return Palauttaa ConcreteSquareMatrix objektin.
*
* "*=" laskutoimitusmetodi.
*/

template <>
ConcreteSquareMatrix& ConcreteSquareMatrix::operator*=(const ConcreteSquareMatrix &m){
    if(n!=m.n){
        throw(std::out_of_range("Dimensions are no good"));
    }
    std::vector<std::vector<uniq_elem_ptr>> new_elements;
    ConcreteSquareMatrix trans = m.transpose();
    for(auto &row:elements){
        std::vector<uniq_elem_ptr> new_row;
        for(auto &trans_row:trans.elements){
            uniq_intelem_ptr prod = std::inner_product(row.begin(),row.end(),trans_row.begin(),uniq_intelem_ptr(new IntElement(0)),[](const uniq_intelem_ptr &i1, const uniq_intelem_ptr &i2){
            uniq_intelem_ptr ptElem = uniq_intelem_ptr(new IntElement(i1->getVal()+i2->getVal()));
            return ptElem;
            },[](const uniq_intelem_ptr &i1, const uniq_intelem_ptr &i2){uniq_intelem_ptr ptElem = uniq_intelem_ptr(new IntElement(i1->getVal()*i2->getVal()));
            return ptElem;
            });
            new_row.push_back(std::move(prod));
        }
        new_elements.push_back(std::move(new_row));
    }
    return (*this);
}


/**\brief ConcreteSquareMatrix evaluaatio
*
*/
/*
template<>
ConcreteSquareMatrix ConcreteSquareMatrix::evaluate(const Valuation& valu) const
{
    return ConcreteSquareMatrix{*this};
}
*/
/**\brief SymbolicSquareMatrix evaluaatio
*
*/
/*
template<>
SymbolicSquareMatrix SymbolicSquareMatrix::evaluate(const Valuation& valu) const
{
    return SymbolicSquareMatrix{*this};
}
*/

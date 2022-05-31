/**\file squarematrix.cpp.
  *\brief SquareMatrix toteutus ja catch test caset.
*/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "squarematrix.h"
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <limits>
#include <numeric>

using namespace std;

/**\brief Konstruktori.
*
*/

SquareMatrix::~SquareMatrix(){};

SquareMatrix::SquareMatrix(){
    n = 0;
}

/**\brief Konstruktori.
*
* \param n Matriisin dimensiot.
* \param m_row Matriisin rivi.
*
*/

SquareMatrix::SquareMatrix(const SquareMatrix& m){
    n = m.n;
    for(auto &m_row:m.elements){
        std::vector<uniq_elem_ptr> row;
        for(auto &elem:m_row){
            row.push_back(uniq_elem_ptr(elem->clone()));
        }
        elements.push_back(std::move(row));
    }
}

/**\brief Konstruktori.
*
* \param m Referenssi vektoriin.
* \param n Vektorin dimensiot.
* \param elements Elementtivektori.
*
* Kopiokonstruktori.
*/

SquareMatrix::SquareMatrix(SquareMatrix&& m):n(m.n),elements(std::move(m.elements)){}


SquareMatrix::SquareMatrix(const std::string& s){
    std::stringstream ips(s);
    char c;
    int num;
    int num_in_row = 0;
    int row_num = 0;
    n = std::numeric_limits<int>::max();

    ips >> c;
    if(!ips.good() || c!='['){
            throw(std::invalid_argument("Invalid init string"));
        }

    while(row_num < n){
            std::vector<uniq_elem_ptr> row;
            ips >> c;
            if(!ips.good() || c!='['){
                throw(std::invalid_argument("Invalid init string"));
            }
            num_in_row = 0;
            while(c!=']'){
                    ips >> num;
                    if(!ips.good()){
                            throw(std::invalid_argument("Invalid init string"));
                        }
                        ips >> c;
                        if(c!=',' && c!=']'){
                            throw(std::invalid_argument("Invalid init string"));
                        }
                        row.push_back(uniq_elem_ptr(new IntElement(num)));
                        num_in_row++;
                    }
            if(row_num == 0){
                    n = num_in_row;
                }

                if(n != num_in_row){
                    throw(std::invalid_argument("Invalid init string"));
                }
            elements.push_back(std::move(row));
            row_num++;
        }
        ips >> c;
        if(!ips.good() || c!=']'){
                throw(std::invalid_argument("Invalid init string"));
            }
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \param iter1 Iteraattori 1.
* \param iter2 Iteraattori 2.
* \param a,b Väliaikaiset muuttujat.
* \return Palauttaa SquareMatrix objektin.
*
* "+=" laskuoperaattori.
*/

SquareMatrix& SquareMatrix::operator+=(const SquareMatrix &m){
    if(n!=m.n){
        throw(std::out_of_range("Dimensions are no good"));
    }
    auto iter1 = elements.begin();
    auto iter2 = m.elements.begin();
    while(iter1!=elements.end() && iter2!=m.elements.end()){
        std::transform(iter1->begin(),iter1->end(),iter2->begin(),iter1->begin(),[](const uniq_elem_ptr &a, const uniq_elem_ptr &b){
        uniq_elem_ptr ptElem = uniq_elem_ptr(new IntElement (a->getVal()+b->getVal()));
        return ptElem;
        });
        iter1++;
        iter2++;
    }
    return (*this);
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \param iter1 Iteraattori 1.
* \param iter2 Iteraattori 2.
* \param a,b Väliaikaiset muuttujat.
* \return Palauttaa SquareMatrix objektin.
*
* "-=" laskuoperaattori.
*/

SquareMatrix& SquareMatrix::operator-=(const SquareMatrix &m){
   if(n!=m.n){
        throw(std::out_of_range("Dimensions are no good"));
    }
    auto iter1 = elements.begin();
    auto iter2 = m.elements.begin();
    while(iter1!=elements.end() && iter2!=m.elements.end()){
        std::transform(iter1->begin(),iter1->end(),iter2->begin(),iter1->begin(),[](const uniq_elem_ptr &a, const uniq_elem_ptr &b){
        uniq_elem_ptr ptElem = uniq_elem_ptr(new IntElement (a->getVal()-b->getVal()));
        return ptElem;
        });
        iter1++;
        iter2++;
    }
    return (*this);
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \param new_elements Uusi elementtivektori.
* \param trans Neliömatriisimuuttuja.
* \param row Vektorin rivi.
* \param new_row Vektorin seuraavan rivin vektori.
* \return Palauttaa SquareMatrix objektin.
*
* "*=" laskuoperaattori.
*/

SquareMatrix& SquareMatrix::operator*=(const SquareMatrix &m){
    if(n!=m.n){
        throw(std::out_of_range("Dimensions are no good"));
    }
    std::vector<std::vector<uniq_elem_ptr>> new_elements;
    SquareMatrix trans = m.transpose();
    for(auto &row:elements){
        std::vector<uniq_elem_ptr> new_row;
        for(auto &trans_row:trans.elements){
            uniq_elem_ptr prod = std::inner_product(row.begin(),row.end(),trans_row.begin(),uniq_elem_ptr(new IntElement(0)),[](const uniq_elem_ptr &i1, const uniq_elem_ptr &i2){
            uniq_elem_ptr ptElem = uniq_elem_ptr(new IntElement(i1->getVal()+i2->getVal()));
            return ptElem;
            },[](const uniq_elem_ptr &i1, const uniq_elem_ptr &i2){uniq_elem_ptr ptElem = uniq_elem_ptr(new IntElement(i1->getVal()*i2->getVal()));
            return ptElem;
            });
            new_row.push_back(std::move(prod));
        }
        new_elements.push_back(std::move(new_row));
    }
    return (*this);
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \return Palauttaa SquareMatrix objektin.
*
* "=" laskuoperaattori.
*/

SquareMatrix& SquareMatrix::operator=(SquareMatrix &&m){
    n = m.n;
    std::swap(elements,m.elements);
    return (*this);
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \return Palauttaa SquareMatrix objektin.
*
* "=" laskuoperaattori.
*/
SquareMatrix& SquareMatrix::operator=(const SquareMatrix &m){
    if(this == &m){
        return (*this);
    }
    n = m.n;
    elements.clear();
    for(auto &m_row:m.elements){
        std::vector<uniq_elem_ptr> row;
        for(auto &elem:m_row){
            row.push_back(uniq_elem_ptr(elem->clone()));
        }
        elements.push_back(std::move(row));
    }
    return (*this);
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \return Palauttaa boolean true tai false.
*
* "==" laskuoperaattori.
*/

bool SquareMatrix::operator==(const SquareMatrix& m)const{
    if(n!=m.n){
        return false;
    }

    return true;
}
/**\brief Transpoosifunktio.
*
* En saanut toimimaan
*
*/

SquareMatrix SquareMatrix::transpose()const{
/*
    SquareMatrix tr;
    tr.n = n;
    for(auto &row:m.elements){
        for(auto &elem:m_row){
            row.push_back();
        }
    }

    tr.elements = std::vector<std::vector<uniq_elem_ptr>>(n);
    for(auto &row:elements){
            for(auto& element:row){
                tr.elements[row]->push_back(element);
            }
    }
    return tr;

*/

}


/**\brief Tulostusfunktio.
*
*/
void SquareMatrix::print(std::ostream &os)const{
    os << toString();
}

/**\brief String konversiofunktio.
*
* \param strm Stringstream.
* \param first Vektorin ensimmäinen rivi.
* \param row Vektorin rivit.
* \param elem Vektorin elementti.
* \return Palauttaa stringstreamin sisällön.
*
* Palauttaa matriisin stringinä.
*/

std::string SquareMatrix::toString()const{
    std::stringstream strm;
    strm << "[";
    for(auto& row:elements){
        strm << "[";
        bool first = true;
        for(auto& elem:row){
            if(!first){
                strm << ",";
            }
            strm << (*elem);
            first = false;
        }
        strm << "]";
    }
    strm << "]";
    return strm.str();
}

TEST_CASE("IntElement", "[element]"){
    IntElement i1(2),i2(3),i3(4),i4(5);
    IntElement j1(1),j2(-1),j3(2),j4(-3);

    REQUIRE(j2.getVal()==-1);

    i1+=i2;
    REQUIRE(i1.getVal()==5);

    i3-=j4;
    REQUIRE(i3.getVal()==7);

    j1*=i4;
    REQUIRE(j1.getVal()==5);

    i4=i2+j2;
    REQUIRE(i4.getVal()==2);

}

TEST_CASE("SquareMatrix", "[matrix]"){

}


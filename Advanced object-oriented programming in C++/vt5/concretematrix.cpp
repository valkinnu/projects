/**\file concretematrix.cpp.
  *\brief ConcreteSquareMatrix toteutus ja catch test caset.
*/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "concretematrix.h"
#include <stdexcept>
#include <vector>
#include <limits>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <ostream>

using namespace std;

/**\brief Konstruktori.
*
*/

ConcreteSquareMatrix::~ConcreteSquareMatrix(){};

ConcreteSquareMatrix::ConcreteSquareMatrix(){
    n = 0;
}

/**\brief Konstruktori.
*
* \param n Matriisin dimensiot.
* \param m_row Matriisin rivi.
*
*/

ConcreteSquareMatrix::ConcreteSquareMatrix(const ConcreteSquareMatrix& m){
    n = m.n;
    for(auto &m_row:m.elements){
        std::vector<uniq_elem_ptr> row;
        for(auto &elem:m_row){
            row.push_back(uniq_elem_ptr(elem->clone()));
        }
        //elements.push_back(uniq_elem_ptr(row));
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

ConcreteSquareMatrix::ConcreteSquareMatrix(ConcreteSquareMatrix&& m):n(m.n),elements(std::move(m.elements)){}


ConcreteSquareMatrix::ConcreteSquareMatrix(const std::string& s){
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
            //elements.push_back(std::move(row));
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
* \return Palauttaa ConcreteSquareMatrix objektin.
*
* "+=" laskuoperaattori.
*/

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

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \param iter1 Iteraattori 1.
* \param iter2 Iteraattori 2.
* \param a,b Väliaikaiset muuttujat.
* \return Palauttaa ConcreteSquareMatrix objektin.
*
* "-=" laskuoperaattori.
*/

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

/**\brief Operaattori.
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
* "*=" laskuoperaattori.
*/

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

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \return Palauttaa ConcreteSquareMatrix objektin.
*
* "=" laskuoperaattori.
*/

ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(ConcreteSquareMatrix &&m){
    n = m.n;
    std::swap(elements,m.elements);
    return (*this);
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \return Palauttaa ConcreteSquareMatrix objektin.
*
* "=" laskuoperaattori.
*/
ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(const ConcreteSquareMatrix &m){
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
       // elements.push_back(std::move(row));
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

bool ConcreteSquareMatrix::operator==(const ConcreteSquareMatrix& m)const{
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

ConcreteSquareMatrix ConcreteSquareMatrix::transpose()const{
/*
   ConcreteSquareMatrix tr;
    tr.n = n;
    tr.elements = std::vector<std::vector<uniq_intelem_ptr>>(n);
    int col_num = 0;
    for(auto& row:elements){
            for(auto& element:row){
                tr.elements[col_num].push_back(uniq_intelem_ptr(static_cast<IntElement>(element->clone())));
                col_num = (col_num+1) % n;
            }
    }
    return tr;
*/


}


/**\brief Tulostusfunktio.
*
*/
void ConcreteSquareMatrix::print(std::ostream &os)const{
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

std::string ConcreteSquareMatrix::toString()const{
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

std::ostream& operator<<(std::ostream& os, const ConcreteSquareMatrix& conc){
    os << conc.toString();
    return os;
}

/** Catch testit
*
*
*/

TEST_CASE("IntElement 1", "[intelement]"){
    IntElement intelem1(10);
    IntElement intelem2(-5);
    IntElement zero;

    CHECK(intelem1.getVal()==10);
    CHECK(intelem2.getVal()==-5);
    CHECK(zero.getVal()==0);
    intelem1 += intelem2;
    CHECK(intelem1.getVal()==5);
    intelem2 -= intelem1;
    CHECK(intelem2.getVal()==-10);
    intelem1 *= intelem2;
    CHECK(intelem1.getVal()==-50);
    intelem2 *= zero;
    CHECK(intelem2.getVal()==0);

}

TEST_CASE("IntElement 2", "[intelement]"){
    IntElement i1(2),i2(3),i3(4),i4(5);

    IntElement ie= i1+i2;
    REQUIRE(ie.getVal()==5);
    ie=i2-i3;
    REQUIRE(ie.getVal()== -1);
    ie=i3*i4;
    REQUIRE(ie.getVal()== 20);
    REQUIRE(ie.toString() == "20");
}

TEST_CASE("VariableElement", "[varelement]"){
    VariableElement v1('a'),v2('b');
    REQUIRE(v1.toString() == "a");

    Valuation mappi;
    mappi['a'] = 10;
    mappi['b'] = 20;
    mappi['c'] = 30;

    REQUIRE(v1.evaluate(mappi) == 10);

}

TEST_CASE("Elements"){
    IntElement i1(2),i2(3),i3(4),i4(5);
    IntElement j1(1),j2(-1),j3(2),j4(-3);
    VariableElement v1('a');
    VariableElement v2('b');

    Valuation vv;
    vv.insert(std::pair<char,int>('a', 2));
    vv.insert(std::pair<char,int>('b', 3));
    CHECK(v1.evaluate(vv)==i1.evaluate(vv));

    REQUIRE(j1.getVal()==1);

    i1+=i2;
    REQUIRE(i1.getVal()==5);

    i3-=j4;
    REQUIRE(i3.getVal()==7);

    j1*=i4;
    REQUIRE(j1.getVal()==5);
}

/**\brief ConcreteSquareMatrixin test caset
*/

TEST_CASE("ConcreteSquareMatrix"){
    ConcreteSquareMatrix m("[[2,3][4,5]]");
    ConcreteSquareMatrix k("[[1,-1][2,-3]]");
    ConcreteSquareMatrix j("[[1,2][3,4]]");
    ConcreteSquareMatrix i("[[1,2][3,4]]");

    CHECK(m.toString()=="[[2,3][4,5]]");
    CHECK(k.toString()=="[[1,-1][2,-3]]");

    m=k;
    CHECK(m.toString()=="[[1,-1][2,-3]]");

    CHECK(m==k);

    m+=k;
    CHECK(m.toString()=="[[2,-2][4,-6]]");

    m-=k;
    CHECK(m.toString()=="[[1,-1][2,-3]]");

    m*=k;
    CHECK(m.toString()=="[[-1,2][-4,7]]");
    j*=i;
    CHECK(j.toString()=="[[7,10][15,22]]");
}

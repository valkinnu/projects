/**\file squarematrix.cpp
* \brief SquareMatrix toteutus ja catch test caset.
*
*/

#define CATCH_CONFIG_MAIN
#include "squarematrix.h"
#include <iostream>
#include <string>
#include "catch.hpp"

using namespace std;

/**\brief Konstruktori.
*
*/
SquareMatrix::SquareMatrix(){};

/**\brief Konstruktori.
*
* \param i_n Matriisin dimensiot.
* \param i_elements Matriisin elementit.
* \param line Vektorin rivi.
*
* Alustaa vektorin.
*/
SquareMatrix::SquareMatrix(int i_n, const std::vector<std::vector<IntElement> >& i_elements){
    bool ok = true;
    n = i_n;
    if(n<0){
        ok = false;
    }
    if(ok){
        if(i_elements.size()!=n){
            ok = false;
        }
        if(ok){
            for(auto line : i_elements){
                if(line.size()!=n){
                    ok = false;
                    break;
                }
                else{
                    elements.push_back(line);
                }
            }
        }
    }
    if(!ok){
        throw(std::invalid_argument("Not a square matrix"));
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
SquareMatrix::SquareMatrix(const SquareMatrix &m):n(m.n), elements(m.elements){}

/**\brief Hajottaja.
*
*/
SquareMatrix::~SquareMatrix(){}

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
    n = m.n;
    elements = m.elements;
    return *this;
}

/**\brief Transpoosifunktio.
*
* \param old_line Vektorin vanha rivi.
* \param elements Elementtivektori.
* \param new_elements Uusi elementtivektori.
* \param new_mat_iter Uuden matriisin iteraattori.
* \param mat_elem matriisin elementti.
* \return Palauttaa transpoosatun matriisin.
*
* Transpoosaa matriisin.
*/
SquareMatrix SquareMatrix::transpose() const{
    std::vector<std::vector<IntElement> > new_elements(n);
    for(auto old_line : elements){
        auto new_mat_iter = new_elements.begin();
        for(auto mat_elem : old_line){
            new_mat_iter->push_back(mat_elem);
            new_mat_iter++;
        }
    }
    SquareMatrix newMatrix = SquareMatrix(n,new_elements);
    return newMatrix;
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
        std::transform(iter1->begin(),iter1->end(),iter2->begin(),iter1->begin(),[](const IntElement &a, const IntElement &b){return (a + b);});
        iter1++;
        iter2++;
    }
    return *this;
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
        std::transform(iter1->begin(),iter1->end(),iter2->begin(),iter1->begin(),[](const IntElement &a, const IntElement &b){return (a - b);});
        iter1++;
        iter2++;
    }
    return *this;
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \param new_elements Uusi elementtivektori.
* \param sm Neliömatriisimuuttuja.
* \param line Vektorin rivi.
* \param tr_line Transpoosatun vektorin rivi.
* \param nextLine Vektorin seuraavan rivin vektori.
* \param nextElement Vektorin seuraava elementti.
* \return Palauttaa SquareMatrix objektin.
*
* "*=" laskuoperaattori.
*/

SquareMatrix& SquareMatrix::operator*=(const SquareMatrix &m){
    if(n!=m.n){
        throw(std::out_of_range("Dimensions are no good"));
    }
    std::vector<std::vector<IntElement> > new_elements;
    SquareMatrix sm = m.transpose();
    for(auto line : elements){
        std::vector<IntElement> nextLine;
        for(auto tr_line : sm.elements){
           IntElement nextElement = dotProduct(line,tr_line);
           nextLine.push_back(nextElement);
        }
        new_elements.push_back(nextLine);
    }
    std::swap(elements,new_elements);
    return *this;
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \param sm Neliömatriisimuuttuja.
* \param line Vektorin rivit.
* \param elem Vektorin elementti.
* \return Palauttaa boolean true tai false.
*
* "==" laskuoperaattori.
*/
bool SquareMatrix::operator==(const SquareMatrix &m){
    if(n!=m.n){
        return false;
    }
    SquareMatrix sm = *this;
    sm-=m;
    for(auto line : sm.elements){
        for(auto elem : line){
            if(elem.getVal()!=0){
                return false;
            }
        }
    }
    return true;
}

/**\brief Tulostusfunktio.
*
*/
void SquareMatrix::print(std::ostream &os) const{
    os << toString();
}

/**\brief String konversiofunktio.
*
* \param strm Stringstream.
* \param firstLine Vektorin ensimmäinen rivi.
* \param line Vektorin rivit.
* \param elem Vektorin elementti.
* \return Palauttaa stringstreamin sisällön.
*
* Palauttaa matriisin stringinä.
*/
std::string SquareMatrix::toString() const{
    std::stringstream strm;
    strm << "[";
    bool firstLine=true;
    for(auto line : elements){
        if(!firstLine){
            strm << ",";
        }
        firstLine = false;
        strm << "[";
        bool firstElement = true;
        for(auto elem : line){
            if(!firstElement){
                strm << ",";
            }
        strm << elem;
        firstElement = false;
        }
        strm << "]";
    }
    strm << "]";
    return strm.str();
}

/**\brief Pistetulofunktio.
*
* \param v1 Vektori 1.
* \param v2 Vektori 2.
* \param result Pistetulo.
* \param iter1 Iteraattori 1.
* \param iter2 Iteraattori 2.
* \return Palauttaa pistetulon.
*
* Palauttaa vektorien pistetulon.
*/


IntElement dotProduct(const std::vector<IntElement>& v1, const std::vector<IntElement>& v2){
    if(v1.size()!=v2.size()){
        throw(std::out_of_range("Dimensions are no good"));
    }
    IntElement result(0);
    auto iter1=v1.begin();
    auto iter2=v2.begin();
    while(iter1!=v1.end() && iter2!=v2.end()){
        result+=*iter1++ * *iter2++;
    }
    return result;
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
    IntElement i1(2),i2(3),i3(4),i4(5);
    IntElement j1(1),j2(-1),j3(2),j4(-3);
    std::vector<IntElement> line1 = {i1, i2};
    std::vector<IntElement> line2 = {i3, i4};
    std::vector<IntElement> line3 = {j1, j2};
    std::vector<IntElement> line4 = {j3, j4};

    std::vector<std::vector<IntElement>> i_elements1 = {line1, line2};
    std::vector<std::vector<IntElement>> i_elements2 = {line3, line4};

    SquareMatrix m(2,i_elements1);
    SquareMatrix k(2,i_elements2);

    REQUIRE(m.toString()=="[[2,3],[4,5]]");
    REQUIRE(k.toString()=="[[1,-1],[2,-3]]");

    m+=k;
    REQUIRE(m.toString()=="[[3,2],[6,2]]");

    m-=k;
    REQUIRE(m.toString()=="[[2,3],[4,5]]");

    m*=k;
    REQUIRE(m.toString()=="[[8,-11],[14,-19]]");

}


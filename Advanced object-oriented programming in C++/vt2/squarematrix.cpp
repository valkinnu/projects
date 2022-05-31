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
* \param e11,e12,e21,e22 Matriisin e elementit.
* \param i11,i12,i21,i22 i elementit e elementtien alustamista varten.
*
* Alustaa matriisin e elementit.
*/
SquareMatrix::SquareMatrix(IntElement i11, IntElement i12, IntElement i21, IntElement i22){
    e11 = i11;
    e12 = i12;
    e21 = i21;
    e22 = i22;
}

/**\brief Konstruktori.
*
* \param e11,e12,e21,e22 Matriisin e elementit.
* \param m Referenssi matriisiin.
*
* Kopiokonstruktori.
*/
SquareMatrix::SquareMatrix(const SquareMatrix &m):e11(m.e11),e12(m.e12),e21(m.e21),e22(m.e22){}

/**\brief Hajottaja.
*
*/
SquareMatrix::~SquareMatrix(){}

/**\brief Operaattori.
*
* \param e11,e12,e21,e22 Matriisin e elementit.
* \param m Referenssi matriisiin.
* \return Palauttaa SquareMatrix objektin.
*
* "+=" laskuoperaattori.
*/
SquareMatrix& SquareMatrix::operator+=(const SquareMatrix &m){
    e11 += m.e11;
    e12 += m.e12;
    e21 += m.e21;
    e22 += m.e22;
    return *this;
}

/**\brief Operaattori.
*
* \param e11,e12,e21,e22 Matriisin e elementit.
* \param m Referenssi matriisiin.
* \return Palauttaa SquareMatrix objektin.
*
* "-=" laskuoperaattori.
*/
SquareMatrix& SquareMatrix::operator-=(const SquareMatrix &m){
    e11 -= m.e11;
    e12 -= m.e12;
    e21 -= m.e21;
    e22 -= m.e22;
    return *this;
}

/**\brief Operaattori.
*
* \param e11,e12,e21,e22 Matriisin e elementit.
* \param m Referenssi matriisiin.
* \param temp11,temp12,temp21,temp22 Väliaikaisesti kertolaskussa syntyvän matriisin elementit.
* \return Palauttaa SquareMatrix objektin.
*
* "*=" laskuoperaattori.
*/
SquareMatrix& SquareMatrix::operator*=(const SquareMatrix &m){
    IntElement temp11 = e11 * m.e11 + e12 * m.e21;
    IntElement temp12 = e11 * m.e12 + e12 * m.e22;
    IntElement temp21 = e21 * m.e11 + e22 * m.e21;
    IntElement temp22 = e21 * m.e12 + e22 * m.e22;
    e11 = temp11;
    e12 = temp12;
    e21 = temp21;
    e22 = temp22;
    return *this;
}

/**\brief Tulostusfunktio.
*
*/
void SquareMatrix::print(std::ostream &os) const{
    os << toString();
}

/**\brief String konversiofunktio.
*
* \param e11,e12,e21,e22 Matriisin e elementit.
* \return Palauttaa stringstreamin.
*
* Palauttaa matriisin stringinä.
*/
std::string SquareMatrix::toString() const{
    std::stringstream strm;
    strm << "[[" << e11 << "," << e12 << "][" << e21 << "," << e22 << "]]";

    return strm.str();
}

TEST_CASE("IntElement"){
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

TEST_CASE("SquareMatrix"){
    IntElement i1(2),i2(3),i3(4),i4(5);
    IntElement j1(1),j2(-1),j3(2),j4(-3);
    SquareMatrix m(i1,i2,i3,i4);
    SquareMatrix k(j1,j2,j3,j4);

    REQUIRE(m.toString()=="[[2,3][4,5]]");
    REQUIRE(k.toString()=="[[1,-1][2,-3]]");

    m+=k;
    REQUIRE(m.toString()=="[[3,2][6,2]]");

    m-=k;
    REQUIRE(m.toString()=="[[2,3][4,5]]");

    m*=k;
    REQUIRE(m.toString()=="[[8,-11][14,-19]]");
}

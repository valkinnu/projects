/**\file intelement.cpp
* \brief IntElement toteutus.
*
*/

#include <iostream>
#include "intelement.h"
#include "catch.hpp"

int val; /** < Elementin arvon esittely.*/

/**\brief Konstruktori.
*
* \param val Elementin arvo.
*
*/
IntElement::IntElement(){
    val = 0;
}

/**\brief Konstruktori.
*
* \param v Elementin arvo.
*
*/
IntElement::IntElement(int v){
    val = v;
}

/**\brief Hajottaja.
*
*/
IntElement::~IntElement(){}

/**\brief Arvon setteri.
*
* \param v Annettu arvo.
* \param val Asetettu arvo.
*
*/
void IntElement::setVal(int v){
    val = v;
}

/**\brief Arvon getteri.
*
* \param val Elementin arvo.
* \return Palauttaa arvon.
*
*/
int IntElement::getVal() const{
    return val;
}

/**\brief Operaattori.
*
* \param val Elementin arvo.
* \param i Referenssi annettuun elementtiin.
* \return Palauttaa IntElement objektin.
*
* "+=" laskuoperaattori.
*/
IntElement& IntElement::operator+=(const IntElement &i){
    val += i.val;
    return *this;
}

/**\brief Operaattori.
*
* \param val Elementin arvo.
* \param i Referenssi annettuun elementtiin.
* \return Palauttaa IntElement objektin.
*
* "-=" laskuoperaattori.
*/
IntElement& IntElement::operator-=(const IntElement &i){
    val -= i.val;
    return *this;
}

/**\brief Operaattori.
*
* \param val Elementin arvo.
* \param i Referenssi annettuun elementtiin.
* \return Palauttaa IntElement objektin.
*
* "*=" laskuoperaattori.
*/
IntElement& IntElement::operator*=(const IntElement &i){
    val *= i.val;
    return *this;
}

/**\brief Operaattori.
*
* \param ie IntElementin arvo.
* \param i1,i2 Referenssit annettuihin elementteihin.
* \return Palauttaa IntElement objektin.
*
* "+" laskuoperaattori.
*/
IntElement operator+(const IntElement &i1, const IntElement &i2){
    IntElement ie(i1);
    ie += i2;
    return ie;
}

/**\brief Operaattori.
*
* \param ie IntElementin arvo.
* \param i1,i2 Referenssit annettuihin elementteihin.
* \return Palauttaa IntElement objektin.
*
* "-" laskuoperaattori.
*/
IntElement operator-(const IntElement &i1, const IntElement &i2){
    IntElement ie(i1);
    ie -= i2;
    return ie;
}

/**\brief Operaattori.
*
* \param ie IntElementin arvo.
* \param i1,i2 Referenssit annettuihin elementteihin.
* \return Palauttaa IntElement objektin.
*
* "*" laskuoperaattori.
*/
IntElement operator*(const IntElement &i1, const IntElement &i2){
    IntElement ie(i1);
    ie *= i2;
    return ie;
}

/**\brief Operaattori.
*
* \param os ostream.
* \param i Referenssi annettuun elementtiin.
* \return Palauttaa ostream sisällön.
*
* Tulostusoperaattori.
*/
std::ostream& operator<<(std::ostream& os, const IntElement &i) {
    os << i.getVal();
    return os;
}

/**\file intelement.cpp
*  \brief IntElement toteutus
*/
#include "intelement.h"
#include <iostream>

int val; /** < Elementin arvon esittely. */

/**\brief Konstruktori
  *param val Elementin arvo.
*/
IntElement::IntElement(){
    val = 0;
}

/**\brief Konstruktori.
  *\param v Elementin arvo.
*/
IntElement::IntElement(int v){
    val = v;
}

/**\brief Hajottaja
  */
IntElement::~IntElement(){
}

/**\brief Arvon setteri.
  *\param v Annettu arvo.
  *\param val Asetettu arvo.
*/
void IntElement::setVal(int v){
    val = v;
}

/**\brief Arvon getteri.
  *\param val Elementin arvo.
  *\return Palauttaa arvon.
*/
int IntElement::getVal()const{
    return val;
}

IntElement* IntElement::clone()const{
    IntElement *pElem = new IntElement(val);
    return pElem;
}

/**\brief Operaattori
  *\param val Elementin arvo.
  *\param i Referenssi annettuun elementtiin.
  *\return Palauttaa IntElement objektin.
  *"+=" Laskuoperaattori.
*/
IntElement& IntElement::operator+=(const IntElement &i){
    val += i.val;
    return *this;
}

/**\brief Operaattori
  *\param val Elementin arvo.
  *\param i Referenssi annettuun elementtiin.
  *\return Palauttaa IntElement objektin.
  *"-=" Laskuoperaattori.
*/
IntElement& IntElement::operator-=(const IntElement &i){
    val -= i.val;
    return *this;
}

/**\brief Operaattori
  *\param val Elementin arvo.
  *\param i Referenssi annettuun elementtiin.
  *\return Palauttaa IntElement objektin.
  "=" Laskuoperaattori.
*/
IntElement& IntElement::operator*=(const IntElement &i){
    val *= i.val;
    return *this;
}


/**\brief Operaattori
  *\param temp Väliaikainen arvo elementille
  *\param i Referenssi annettuun elementtiin.
  *\param j Referenssi annettuun elementtiin.
  *\return Väliaikainen elementin arvo.
  "" Laskuoperaattori.
*/
IntElement operator*(const IntElement& i, const IntElement& j){
    IntElement temp = i;
    temp *= j;
    return temp;
}

/**\brief Operaattori
  *\param temp Väliaikainen arvo elementille
  *\param i Referenssi annettuun elementtiin.
  *\param j Referenssi annettuun elementtiin.
  *\return Väliaikainen elementin arvo.
  *"+" Laskuoperaattori.
*/
IntElement operator+(const IntElement& i, const IntElement& j){
    IntElement temp = i;
    temp += j;
    return temp;
}

/**\brief Operaattori
  *\param temp Väliaikainen arvo elementille
  *\param i Referenssi annettuun elementtiin.
  *\param j Referenssi annettuun elementtiin.
  *\return Väliaikainen elementin arvo.
  *"-" Laskuoperaattori.
*/
IntElement operator-(const IntElement& i, const IntElement& j){
    IntElement temp = i;
    temp -= j;
    return temp;
}

/**\brief Operaattori
  *\param os ostream
  *\param i Referenssi annettuun elementtiin.
  *\return Palauttaa ostreamin sisällön.
*/
std::ostream& operator << (std::ostream& os, const IntElement &i){
    os << i.getVal();
    return os;
}

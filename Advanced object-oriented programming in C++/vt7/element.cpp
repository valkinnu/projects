/**\file element.cpp
*  \brief Element toteutus
*/
#include "element.h"
#include <iostream>
#include <sstream>



std::ostream& operator<<(std::ostream& os, const Element& elem){
    os << elem.toString();
    return os;
}

/**\brief Vertailuoperaattori
*
*/
bool operator==(const Element& e1,const Element& e2){
    return e1.toString() == e2.toString();
}


/**\brief Konstruktori
  *param val Elementin arvo.
*/

template<>
IntElement::TElement(){
    val = 0;
}

/**\brief Evaluaatio
*
*/

template<>
int IntElement::evaluate(const Valuation& valuation) const{
    return val;
}

/**\brief Operaattori
  *\param val Elementin arvo.
  *\param i Referenssi annettuun elementtiin.
  *\return Palauttaa IntElement objektin.
  *"+=" Laskuoperaattori.
*/

template<>
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

template<>
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

template<>
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

std::ostream& operator << (std::ostream& os, const IntElement &i){
    os << i.getVal();
    return os;
}


template<>
VariableElement::TElement():val('x'){
}

/**\brief Konstruktori.
  *\param c Elementin arvo.
*/

/*
template<>
VariableElement::TElement(char c):val(c){
}
*/
/**\brief Evaluaatio
*
*/

template<>
int VariableElement::evaluate(const Valuation& valu) const  {
    return valu.at(val);
}

 CompositeElement::CompositeElement(const Element&e1, const Element&e2, const CEFunction& opf, char opc): op_fun(opf),op_ch(opc){
    oprnd1 = uniq_elem_ptr(e1.clone());
    oprnd2 = uniq_elem_ptr(e2.clone());
}

/**\brief CompositeElement kloonaus
*  \param Element* pointteri Elementtiin
*  \return Palauttaa CompositeElement kloonin
*/

Element* CompositeElement::clone() const{
    //return Element*(new CompositeElement(*this));
}

std::string CompositeElement::toString() const{
    std::stringstream strm;
    strm << op_ch;
    return strm.str();
}

/**\brief CompositeElement evaluaatio
*  \param oprnd1 ja oprnd2
*  \param op_fun CEFunction
*/

int CompositeElement::evaluate(const Valuation& val) const{
    return op_fun(oprnd1->evaluate(val),oprnd2->evaluate(val));
}


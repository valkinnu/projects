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


int val; /** < Elementin arvon esittely. */
char var; /** < Elementin arvon esittely. */

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
/**\brief IntElementin kloonaus
  *\param uniq_elem_ptr pointteri Elementtiin
  *\return Palauttaa IntElement kloonin
*/

uniq_elem_ptr IntElement::clone() const{
    return uniq_elem_ptr(new IntElement(*this));
}

std::string IntElement::toString() const{
    std::stringstream strm;
    strm << val;
    return strm.str();

}

int IntElement::evaluate(const Valuation& valuation) const{
    return val;
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

std::ostream& operator << (std::ostream& os, const IntElement &i){
    os << i.getVal();
    return os;
}


VariableElement::VariableElement():var('x'){

}


/**\brief Konstruktori.
  *\param c Elementin arvo.
*/

VariableElement::VariableElement(char c):var(c){
}

/**\brief Hajottaja
  */
VariableElement::~VariableElement(){
}

/**\brief Arvon setteri.
  *\param c Annettu arvo.
  *\param var Asetettu arvo.
*/

void VariableElement::setVal(char c){
    var = c;
}

/**\brief Arvon getteri.
  *\param var Elementin arvo.
  *\return Palauttaa arvon.
*/
char VariableElement::getVal()const{
    return var;
}

/**\brief Operaattori
*  \param var Elementin arvo
*
*/
bool VariableElement::operator==(const VariableElement& i) const {
    return var == i.var;
}

/**\brief VariableElement kloonaus
*  \param uniq_elem_ptr pointteri Elementtiin
*  \return Palauttaa VariableElement kloonin
*/

uniq_elem_ptr VariableElement::clone() const {
    return uniq_elem_ptr(new VariableElement(*this));
}

std::string VariableElement::toString() const{
    std::stringstream strm;
    strm << var;
    return strm.str();

}
/**\brief VariableElement evaluaatio
*  \param val
*
*/

int VariableElement::evaluate(const Valuation& val) const  {
    return val.at(var);
}

 CompositeElement::CompositeElement(const Element&e1, const Element&e2, const CEFunction& opf, char opc): op_fun(opf),op_ch(opc){
    oprnd1 = e1.clone();
    oprnd2 = e2.clone();
}

/**\brief CompositeElement kloonaus
*  \param uniq_elem_ptr pointteri Elementtiin
*  \return Palauttaa CompositeElement kloonin
*/

uniq_elem_ptr CompositeElement::clone() const{
    //return uniq_elem_ptr(new CompositeElement(*this));
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

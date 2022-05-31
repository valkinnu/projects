/**\file intelement.h
* \brief IntElement otsikkotiedosto.
*
*/

#ifndef INTELEMENT_INCLUDED
#define INTELEMENT_INCLUDED
#include <iostream>
#include "catch.hpp"

/**\brief IntElement -luokka.
*
* \param    val Elementin arvon esittely.
* \param    v Elementin arvo.
* \param    i Referenssi elementtiin.
*/
class IntElement{
    private:
        int val;

    public:
        IntElement();
        IntElement(int v);
        ~IntElement();
        int getVal() const;
        void setVal(int v);
        IntElement& operator+=(const IntElement& i);
        IntElement& operator-=(const IntElement& i);
        IntElement& operator*=(const IntElement& i);
};

IntElement operator+(const IntElement &i1, const IntElement &i2);
IntElement operator-(const IntElement &i1, const IntElement &i2);
IntElement operator*(const IntElement &i1, const IntElement &i2);
std::ostream& operator<<(std::ostream& os, const IntElement &i) ;

#endif

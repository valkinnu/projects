/**\file intelement.h
* \brief IntElement otsikkotiedosto.
*
*/

#ifndef INTELEMENT_H_INCLUDED
#define INTELEMENT_H_INCLUDED
#include <ostream>
#include <string>
#include <vector>
#include <memory>

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
        int getVal()const;
        void setVal(int v);
        IntElement* clone()const;
        IntElement& operator+=(const IntElement& i);
        IntElement& operator-=(const IntElement& i);
        IntElement& operator*=(const IntElement& i);
        bool operator==(const IntElement& i);
};
IntElement operator+(const IntElement &i, const IntElement& j);
IntElement operator-(const IntElement &i, const IntElement& j);
IntElement operator*(const IntElement &i, const IntElement& j);
std::ostream& operator<<(std::ostream& os, const IntElement &i);

typedef std::unique_ptr<IntElement> uniq_elem_ptr;
#endif // INTELEMENT_H_INCLUDED

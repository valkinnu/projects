/**\file element.h
* \brief Element otsikkotiedosto.
*
*/

#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED
#include "catch.hpp"
#include <ostream>
#include <string>
#include <vector>
#include <memory>
#include <map>


using Valuation = std::map<char,int>;


class Element;
using uniq_elem_ptr = std::unique_ptr<Element>;


/**\brief Element -luokka
*
*/

class Element {
    public:
        virtual ~Element(){};
        virtual uniq_elem_ptr clone() const = 0;
        virtual std::string toString() const = 0;
        virtual int evaluate(const Valuation& val) const = 0;

};

std::ostream& operator<<(std::ostream& os, const Element& elem);

/**\brief IntElement -luokka.
*
* \param    val Elementin arvon esittely.
* \param    v Elementin arvo.
* \param    i Referenssi elementtiin.
*/

class IntElement;
using uniq_intelem_ptr = std::unique_ptr<IntElement>;

class IntElement : public Element {
    private:
        int val;
    public:
        IntElement();
        IntElement(int v);
        ~IntElement();
        int getVal()const;
        void setVal(int v);
        IntElement& operator+=(const IntElement& i);
        IntElement& operator-=(const IntElement& i);
        IntElement& operator*=(const IntElement& i);
        bool operator==(const IntElement& i);
        virtual uniq_elem_ptr clone() const override;
        std::string toString() const override;
        int evaluate(const Valuation& val) const override;
};

IntElement operator+(const IntElement &i, const IntElement& j);
IntElement operator-(const IntElement &i, const IntElement& j);
IntElement operator*(const IntElement &i, const IntElement& j);
std::ostream& operator<<(std::ostream& os, const IntElement &i);



class VariableElement : public Element {
    private:
        char var;
    public:
        VariableElement();
        VariableElement(char c);
        ~VariableElement();
        char getVal()const;
        void setVal(char v);
        bool operator==(const VariableElement& i) const;
        uniq_elem_ptr clone() const override;
        std::string toString() const override;
        int evaluate(const Valuation& val) const override;
};

typedef std::unique_ptr<IntElement> uniq_intelem_ptr;
typedef std::unique_ptr<Element> uniq_elem_ptr;

#endif // INTELEMENT_H_INCLUDED

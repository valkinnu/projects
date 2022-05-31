/**\file element.h
* \brief Element otsikkotiedosto.
*
*/

#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED
#include <ostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <functional>



using Valuation = std::map<char,int>;

/**\brief Element -luokan forward declaration
*  \param uniq_elem_ptr Element pointteri
*/
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


/**\brief IntElement -luokan Forward declaration
*  \param uniq_intelem_ptr IntElement pointteri
*/
class IntElement;
using uniq_intelem_ptr = std::unique_ptr<IntElement>;

/**\brief IntElement -luokka.
*
* \param    val Elementin arvon esittely.
* \param    v Elementin arvo.
* \param    i Referenssi elementtiin.
*/

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


/**\brief VariableElement -luokka.
*
* \param    var Elementin arvon esittely.
* \param    c Elementin arvo.
* \param    i Referenssi elementtiin.
*/

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

using CEFunction = std::function<int(int,int)>;

/**\brief CompositeElement -luokka.
*
* \param    op_ch Elementin arvon esittely.
* \param    oprnd1 ja oprnd2 Operandit
* \param    op_fun CompositeElement Funktio
* \param    e Referenssi elementtiin.
*/

class CompositeElement : public Element {
    private:
        uniq_elem_ptr oprnd1;
        uniq_elem_ptr oprnd2;
        CEFunction op_fun;
        char op_ch;
    public:
        CompositeElement(const Element&e1, const Element&e2, const CEFunction& opf, char opc);
        ~CompositeElement(){};
        CompositeElement(const CompositeElement& e);
        CompositeElement& operator=(const CompositeElement& e);
        uniq_elem_ptr clone() const override;
        std::string toString() const override;
        int evaluate(const Valuation& val) const override;
};


#endif // INTELEMENT_H_INCLUDED

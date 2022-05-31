/**\file element.h
* \brief Element otsikkotiedosto.
*
*/

#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED
#include <ostream>
#include <sstream>
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
        virtual Element* clone() const = 0;
        virtual std::string toString() const = 0;
        virtual int evaluate(const Valuation& val) const = 0;
};

std::ostream& operator<<(std::ostream& os, const Element& elem);
bool operator==(const Element& e1,const Element& e2);

/**\brief TElement -malliluokka.
*
* \param    val Elementin arvon esittely.
* \param    v Elementin arvo.
* \param    i Referenssi elementtiin.
*/

template <typename T>
class TElement : public Element {
    private:
        T val;
    public:
        TElement();
        TElement(T v);
        ~TElement(){};
        T getVal()const;
        void setVal(T v);
        TElement& operator+=(const TElement& i);
        TElement& operator-=(const TElement& i);
        TElement& operator*=(const TElement& i);
        virtual Element* clone() const override;
        std::string toString() const override;
        int evaluate(const Valuation& val) const override;
};

using IntElement = TElement<int>;
using VariableElement = TElement<char>;

using uniq_intelem_ptr = std::unique_ptr<IntElement>;

/**\brief Konstruktori
*
*/

template <typename T>
TElement<T>::TElement(T v):val(v){
}

/**\brief Arvon getteri
*
*/

template <typename T>
T TElement<T>::getVal() const {
    return val;
}

/**\brief Arvon setteri
*
*/

template <typename T>
void TElement<T>::setVal(T v){
    val = v;
}

/**\brief Kloonaus
*
*/

template <typename T>
Element* TElement<T>::clone() const{
    return (new TElement<T>(*this));
}


template <typename T>
std::string TElement<T>::toString() const{
    std::stringstream strm;
    strm << val;
    return strm.str();
}

IntElement operator+(const IntElement&, const IntElement&);
IntElement operator-(const IntElement&, const IntElement&);
IntElement operator*(const IntElement&, const IntElement&);

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
        Element* clone() const override;
        std::string toString() const override;
        int evaluate(const Valuation& val) const override;
};


#endif // INTELEMENT_H_INCLUDED


/**\file elementarymatrix.h
* \brief ElementarySquareMatrix otsikkotiedosto.
*
*/

#ifndef ELEMENTARYMATRIX_H_INCLUDED
#define ELEMENTARYMATRIX_H_INCLUDED
#include <stdexcept>
#include <vector>
#include <limits>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <ostream>
#include "element.h"


template <typename T>
class ElementarySquareMatrix{
    private:
        int n;
        std::vector<std::vector<std::unique_ptr<T>>> elements;
        friend class ElementarySquareMatrix<Element>;
    public:
        ElementarySquareMatrix();
        ElementarySquareMatrix(const std::string& str);
        ElementarySquareMatrix(const ElementarySquareMatrix& m);
        ElementarySquareMatrix(ElementarySquareMatrix&& m);
        virtual ~ElementarySquareMatrix(){};
        ElementarySquareMatrix& operator=(const ElementarySquareMatrix&  m);
        ElementarySquareMatrix& operator=(ElementarySquareMatrix&& m);
        bool operator==(const ElementarySquareMatrix& m) const;
        void print(std::ostream& os) const;
        std::string toString() const;
        ElementarySquareMatrix transpose() const;
        ElementarySquareMatrix<IntElement> evaluate(const Valuation& valu) const;
        ElementarySquareMatrix& operator+=(const ElementarySquareMatrix& m);
        ElementarySquareMatrix& operator-=(const ElementarySquareMatrix& m);
        ElementarySquareMatrix& operator*=(const ElementarySquareMatrix& m);
        ElementarySquareMatrix operator+(const ElementarySquareMatrix& m);
        ElementarySquareMatrix operator-(const ElementarySquareMatrix& m);
        ElementarySquareMatrix operator*(const ElementarySquareMatrix& m);
};

using ConcreteSquareMatrix = ElementarySquareMatrix<IntElement>;
using SymbolicSquareMatrix = ElementarySquareMatrix<Element>;

/**\brief Konstruktori
*
*/

template <typename T>
ElementarySquareMatrix<T>::ElementarySquareMatrix(){
    n = 0;
}

/**\brief Konstruktori.
*
* \param n Matriisin dimensiot.
* \param m_row Matriisin rivi.
*
*/
/*
template <typename T>
ElementarySquareMatrix<T>::ElementarySquareMatrix(const ElementarySquareMatrix& m){
    n = m.n;
    for(auto &m_row:m.elements){
        std::vector<T> row;
        for(auto &elem:m_row){
            row.push_back(T(elem->clone()));
        }
        //elements.push_back(<T>(row));
    }
}*/

template <typename T>
ElementarySquareMatrix<T>::ElementarySquareMatrix(const std::string& s){
    std::stringstream ips(s);
    char c;
    int num;
    int num_in_row = 0;
    int row_num = 0;
    n = std::numeric_limits<int>::max();

    ips >> c;
    if(!ips.good() || c!='['){
            throw(std::invalid_argument("Invalid init string"));
        }

    while(row_num < n){
            std::vector<T> row;
            ips >> c;
            if(!ips.good() || c!='['){
                throw(std::invalid_argument("Invalid init string"));
            }
            num_in_row = 0;
            while(c!=']'){
                    ips >> num;
                    if(!ips.good()){
                            throw(std::invalid_argument("Invalid init string"));
                        }
                        ips >> c;
                        if(c!=',' && c!=']'){
                            throw(std::invalid_argument("Invalid init string"));
                        }
                        row.push_back(T(new IntElement(num)));
                        num_in_row++;
                    }
            if(row_num == 0){
                    n = num_in_row;
                }

                if(n != num_in_row){
                    throw(std::invalid_argument("Invalid init string"));
                }
            //elements.push_back(std::move(row));
            row_num++;
        }
        ips >> c;
        if(!ips.good() || c!=']'){
                throw(std::invalid_argument("Invalid init string"));
            }
}

/**\brief Transpoosifunktio.
*
*/

template <typename T>
ElementarySquareMatrix<T> ElementarySquareMatrix<T>::transpose()const{
    ElementarySquareMatrix<T> temp{};
    temp.n = n;
    temp.elements = std::vector<std::vector<std::unique_ptr<T>>>{n};
        for(const auto& row : elements)
            {
            auto it = temp.elements.begin();
            for(auto& e : row)
                {
                it++->push_back
                (std::unique_ptr<T>{static_cast<T*>(e->clone())});
                }
            }

    return temp;
}

/**\brief String konversiofunktio.
*
* \param strm Stringstream.
* \param first Vektorin ensimmäinen rivi.
* \param row Vektorin rivit.
* \param elem Vektorin elementti.
* \return Palauttaa stringstreamin sisällön.
*
* Palauttaa matriisin stringinä.
*/

template <typename T>
std::string ElementarySquareMatrix<T>::toString()const{
    std::stringstream strm;
    strm << "[";
    for(auto& row:elements){
        strm << "[";
        bool first = true;
        for(auto& elem:row){
            if(!first){
                strm << ",";
            }
            strm << (*elem);
            first = false;
        }
        strm << "]";
    }
    strm << "]";
    return strm.str();
}

/**\brief Tulostusfunktio.
*
*/

template <typename T>
void ElementarySquareMatrix<T>::print(std::ostream &os)const{
    os << toString();
}

#endif // ELEMENTARYMATRIX_H_INCLUDED

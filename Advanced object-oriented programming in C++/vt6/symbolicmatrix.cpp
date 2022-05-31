/**\file symbolicmatrix.cpp.
  *\brief SymbolicSquareMatrix toteutus ja catch test caset.
*/


#include "symbolicmatrix.h"
#include <stdexcept>
#include <vector>
#include <limits>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <ostream>

using namespace std;

/**\brief Konstruktori.
*
*/

SymbolicSquareMatrix::~SymbolicSquareMatrix(){};

SymbolicSquareMatrix::SymbolicSquareMatrix(){
    n = 0;
}

/**\brief Konstruktori.
*
* \param n Matriisin dimensiot.
* \param m_row Matriisin rivi.
*
*/

SymbolicSquareMatrix::SymbolicSquareMatrix(const SymbolicSquareMatrix& m){
    n = m.n;
    for(auto &m_row:m.elements){
        std::vector<uniq_elem_ptr> row;
        for(auto &elem:m_row){
            row.push_back(uniq_elem_ptr(elem->clone()));
        }
        //elements.push_back(uniq_elem_ptr(row));
    }
}

/**\brief Konstruktori.
*
* \param m Referenssi vektoriin.
* \param n Vektorin dimensiot.
* \param elements Elementtivektori.
*
* Kopiokonstruktori.
*/

SymbolicSquareMatrix::SymbolicSquareMatrix(SymbolicSquareMatrix&& m):n(m.n),elements(std::move(m.elements)){}


SymbolicSquareMatrix::SymbolicSquareMatrix(const std::string& s){
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
            std::vector<uniq_elem_ptr> row;
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
                        row.push_back(uniq_elem_ptr(new IntElement(num)));
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

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \param iter1 Iteraattori 1.
* \param iter2 Iteraattori 2.
* \param a,b Väliaikaiset muuttujat.
* \return Palauttaa SymbolicSquareMatrix objektin.
*
* "+=" laskuoperaattori.
*/

SymbolicSquareMatrix& SymbolicSquareMatrix::operator+=(const SymbolicSquareMatrix &m){
    if(n!=m.n){
        throw(std::out_of_range("Dimensions are no good"));
    }
    auto iter1 = elements.begin();
    auto iter2 = m.elements.begin();
    while(iter1!=elements.end() && iter2!=m.elements.end()){
        std::transform(iter1->begin(),iter1->end(),iter2->begin(),iter1->begin(),[](const uniq_intelem_ptr &a, const uniq_intelem_ptr &b){
        uniq_intelem_ptr ptElem = uniq_intelem_ptr(new IntElement (a->getVal()+b->getVal()));
        return ptElem;
        });
        iter1++;
        iter2++;
    }
    return (*this);
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \param iter1 Iteraattori 1.
* \param iter2 Iteraattori 2.
* \param a,b Väliaikaiset muuttujat.
* \return Palauttaa SymbolicSquareMatrix objektin.
*
* "-=" laskuoperaattori.
*/

SymbolicSquareMatrix& SymbolicSquareMatrix::operator-=(const SymbolicSquareMatrix &m){
   if(n!=m.n){
        throw(std::out_of_range("Dimensions are no good"));
    }
    auto iter1 = elements.begin();
    auto iter2 = m.elements.begin();
    while(iter1!=elements.end() && iter2!=m.elements.end()){
        std::transform(iter1->begin(),iter1->end(),iter2->begin(),iter1->begin(),[](const uniq_intelem_ptr &a, const uniq_intelem_ptr &b){
        uniq_intelem_ptr ptElem = uniq_intelem_ptr(new IntElement (a->getVal()-b->getVal()));
        return ptElem;
        });
        iter1++;
        iter2++;
    }
    return (*this);
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \param new_elements Uusi elementtivektori.
* \param trans Neliömatriisimuuttuja.
* \param row Vektorin rivi.
* \param new_row Vektorin seuraavan rivin vektori.
* \return Palauttaa SymbolicSquareMatrix objektin.
*
* "*=" laskuoperaattori.
*/

SymbolicSquareMatrix& SymbolicSquareMatrix::operator*=(const SymbolicSquareMatrix &m){
    if(n!=m.n){
        throw(std::out_of_range("Dimensions are no good"));
    }
    std::vector<std::vector<uniq_elem_ptr>> new_elements;
    SymbolicSquareMatrix trans = m.transpose();
    for(auto &row:elements){
        std::vector<uniq_elem_ptr> new_row;
        for(auto &trans_row:trans.elements){
            uniq_intelem_ptr prod = std::inner_product(row.begin(),row.end(),trans_row.begin(),uniq_intelem_ptr(new IntElement(0)),[](const uniq_intelem_ptr &i1, const uniq_intelem_ptr &i2){
            uniq_intelem_ptr ptElem = uniq_intelem_ptr(new IntElement(i1->getVal()+i2->getVal()));
            return ptElem;
            },[](const uniq_intelem_ptr &i1, const uniq_intelem_ptr &i2){uniq_intelem_ptr ptElem = uniq_intelem_ptr(new IntElement(i1->getVal()*i2->getVal()));
            return ptElem;
            });
            new_row.push_back(std::move(prod));
        }
        new_elements.push_back(std::move(new_row));
    }
    return (*this);
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \return Palauttaa SymbolicSquareMatrix objektin.
*
* "=" laskuoperaattori.
*/

SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(SymbolicSquareMatrix &&m){
    n = m.n;
    std::swap(elements,m.elements);
    return (*this);
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \param elements Elementtivektori.
* \return Palauttaa SymbolicSquareMatrix objektin.
*
* "=" laskuoperaattori.
*/
SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(const SymbolicSquareMatrix &m){
    if(this == &m){
        return (*this);
    }
    n = m.n;
    elements.clear();
    for(auto &m_row:m.elements){
        std::vector<uniq_elem_ptr> row;
        for(auto &elem:m_row){
            row.push_back(uniq_elem_ptr(elem->clone()));
        }
       //elements.push_back(std::move(row));
    }
    return (*this);
}

/**\brief Operaattori.
*
* \param n Vektorin dimensiot.
* \param m Referenssi vektoriin.
* \return Palauttaa boolean true tai false.
*
* "==" laskuoperaattori.
*/

bool SymbolicSquareMatrix::operator==(const SymbolicSquareMatrix& m)const{
    if(n!=m.n){
        return false;
    }

    return true;
}
/**\brief Transpoosifunktio.
*
* En saanut toimimaan
*
*/

SymbolicSquareMatrix SymbolicSquareMatrix::transpose()const{
/*
   SymbolicSquareMatrix tr;
    tr.n = n;
    tr.elements = std::vector<std::vector<uniq_intelem_ptr>>(n);
    int col_num = 0;
    for(auto& row:elements){
            for(auto& element:row){
                tr.elements[col_num].push_back(uniq_intelem_ptr(static_cast<IntElement*>(element->clone())));
                col_num = (col_num+1) % n;
            }
    }
    return tr;

*/

}


/**\brief Operaattori
*
*  \return Palauttaa SymbolicSquareMatrix objektin
*
*
**/

/*
SymbolicSquareMatrix SymbolicSquareMatrix::operator+(const SymbolicSquareMatrix& m){

    if(n!=m.n){
        throw(std::out_of_range("Dimensions are no good"));
    }
    SymbolicSquareMatrix ssm;
    auto m_row = m.elements.begin();

    for(auto& row : elements) {
        std::vector<uniq_elem_ptr> rowVector;
        auto m_elem = m_row->begin();
        for(auto& elem : row) {
            rowVector.push_back(uniq_elem_ptr new CompositeElement(*elem,**m_elem,std::plus<int>(),'+'));
            m_elem++;
        }
        m_row++;
        ssm.elements.push_back(std::move(rowVector));
    }
    ssm.n = n;
    return ssm;

}
*/

/**\brief Tulostusfunktio.
*
*/
void SymbolicSquareMatrix::print(std::ostream &os)const{
    os << toString();
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

std::string SymbolicSquareMatrix::toString()const{
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

std::ostream& operator<<(std::ostream& os, const SymbolicSquareMatrix& symb){
    os << symb.toString();
    return os;
}




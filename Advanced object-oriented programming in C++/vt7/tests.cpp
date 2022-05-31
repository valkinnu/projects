/**\file tests.cpp
* \brief Catch testitiedosto
*
*/

//#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "element.h"
#include "elementarymatrix.h"



/** \brief IntElement testit
*
*/

TEST_CASE("IntElement 1", "[intelement]"){
    IntElement intelem1(10);
    IntElement intelem2(-5);
    IntElement intelem3(5);
    IntElement zero;

    CHECK(intelem1.getVal()==10);
    CHECK(intelem2.getVal()==-5);
    CHECK(intelem3.getVal()==5);
    CHECK(zero.getVal()==0);
    intelem1 += intelem2;
    CHECK(intelem1.getVal()==5);
    intelem2 -= intelem1;
    CHECK(intelem2.getVal()==-10);
    intelem1 *= intelem2;
    CHECK(intelem1.getVal()==-50);
    intelem2 *= zero;
    CHECK(intelem2.getVal()==0);
    intelem3 *= zero;
    CHECK(intelem3.getVal()==0);

}

TEST_CASE("IntElement 2", "[intelement]"){
    IntElement i1(2),i2(3),i3(4),i4(5);

    IntElement ie= i1+i2;
    REQUIRE(ie.getVal()==5);
    ie=i2-i3;
    REQUIRE(ie.getVal()== -1);
    ie=i3*i4;
    REQUIRE(ie.getVal()== 20);
    REQUIRE(ie.toString() == "20");
}
/**\brief VariableElement testit
*
*/
TEST_CASE("VariableElement", "[varelement]"){
    VariableElement v1('a'),v2('b'),v3('c'),v4('d'),v5('e');
    REQUIRE(v1.toString() == "a");
    REQUIRE(v2.toString() == "b");
    REQUIRE(v3.toString() == "c");
    REQUIRE(v4.toString() == "d");
    REQUIRE(v5.toString() == "e");

    Valuation mappi;
    mappi['a'] = 10;
    mappi['b'] = 20;
    mappi['c'] = 30;
    mappi['d'] = 40;
    mappi['e'] = 50;

    REQUIRE(v1.evaluate(mappi) == 10);
    REQUIRE(v2.evaluate(mappi) == 20);
    REQUIRE(v3.evaluate(mappi) == 30);
    REQUIRE(v4.evaluate(mappi) == 40);
    REQUIRE(v5.evaluate(mappi) == 50);
}

/**\brief Lisää IntElement testejä
*/

TEST_CASE("Elements"){
    IntElement i1(2),i2(3),i3(4),i4(5);
    IntElement j1(1),j2(-1),j3(2),j4(-3);
    VariableElement v1('a');
    VariableElement v2('b');

    Valuation vv;
    vv.insert(std::pair<char,int>('a', 2));
    vv.insert(std::pair<char,int>('b', 3));
    CHECK(v1.evaluate(vv)==i1.evaluate(vv));

    REQUIRE(j1.getVal()==1);

    i1+=i2;
    REQUIRE(i1.getVal()==5);

    i3-=j4;
    REQUIRE(i3.getVal()==7);

    j1*=i4;
    REQUIRE(j1.getVal()==5);
}

/**\brief CompositeElement testit
*/
TEST_CASE("CompositeElement"){
    Valuation valu;
    valu['x'] = 10;
    valu['a'] = 10;
    valu['b'] = 20;
    valu['c'] = 30;
    VariableElement v1('b');
    VariableElement v2('c');
    VariableElement v3('x');
    VariableElement v4('a');
    IntElement ie(15);
    CHECK(v1.evaluate(valu)==20);
    CHECK(v2.evaluate(valu)==30);
    CHECK(v3.evaluate(valu)==10);
    CHECK(v4.evaluate(valu)==10);
    CompositeElement ce(v1, v2, std::plus<int>(),'+');
    CHECK(ce.evaluate(valu)==50);
    CompositeElement ce2(v1, ie, std::multiplies<int>(),'*');
    CHECK(ce2.evaluate(valu)==300);
    CompositeElement ce3(v2, v3, std::minus<int>(),'-');
    CHECK(ce3.evaluate(valu)==20);

}

/**\brief ConcreteSquareMatrixin testit
*/

/*
TEST_CASE("ConcreteSquareMatrix"){
    ConcreteSquareMatrix m("[[2,3][4,5]]");
    ConcreteSquareMatrix k("[[1,-1][2,-3]]");
    ConcreteSquareMatrix j("[[1,2][3,4]]");
    ConcreteSquareMatrix i("[[1,2][3,4]]");

    //CHECK(m.toString()=="[[2,3][4,5]]");
    //CHECK(k.toString()=="[[1,-1][2,-3]]");

    m=k;
    //CHECK(m.toString()=="[[1,-1][2,-3]]");

    CHECK(m==k);

    m+=k;
    //CHECK(m.toString()=="[[2,-2][4,-6]]");

    m-=k;
    //CHECK(m.toString()=="[[1,-1][2,-3]]");

    m*=k;
    //CHECK(m.toString()=="[[-1,2][-4,7]]");
    j*=i;
    //CHECK(j.toString()=="[[7,10][15,22]]");
}
*/

/**\brief SymbolicSquareMatrix testit
*/
/*
TEST_CASE("SymbolicSquareMatrix"){
    SymbolicSquareMatrix ssm("[[a,b][a,c]]");
    SymbolicSquareMatrix ssmx("[[a,b][x,c]]");

    CHECK(!(ssm==ssmx));
    Valuation valu;
    valu['x'] = 10;
    valu['a'] = 10;
    valu['b'] = 20;
    valu['c'] = 30;
    CHECK(ssm.evaluate(valu).toString()=="[[10,20][10,30]]");
    CHECK(ssm.evaluate(valu)==ssmx.evaluate(valu));
    SymbolicSquareMatrix ssmex("[[a,b][-5,y]]");
    CHECK_THROWS(ssmex.evaluate(valu));
    valu.insert(std::pair<char,int>('y',-3));
    ConcreteSquareMatrix csm = ssmex.evaluate(valu);
    CHECK(csm.toString()=="[[10,20][-5,-3]]");
    SymbolicSquareMatrix empty("[[]]");
    CHECK(empty.toString()=="[[]]");

}
*/


#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "isSquareMatrix.h"
#include <iostream>
#include <sstream>


TEST_CASE("Testit", "[matriisi]") {
CHECK(isSquareMatrix("[[1,2,3][4,5,6][7,8,9]]"));
CHECK_FALSE(isSquareMatrix("]]"));
CHECK(isSquareMatrix("[[1,2,3,4][5,6,7,8][9,10,11,12][13,14,15,16]]"));
CHECK(isSquareMatrix("[[1]"));
CHECK(!isSquareMatrix("[123,-123]"));
CHECK(!isSquareMatrix("][]]"));
CHECK(isSquareMatrix("[[11,12,13][14a,15aa,16][17,18,19]]"));
CHECK(!isSquareMatrix("[-18,-13]"));
CHECK(isSquareMatrix("[[11,12,13][14a,15b,16c][17d,18e,19f]]"));
CHECK(!isSquareMatrix("[1111111]]"));
CHECK(isSquareMatrix("[[1,2,3,4][5,6,7,8][9,10,11,12]]"));


}
bool isSquareMatrix(const std::string &str){
    std::stringstream inputstrm(str);

    if(str == "[[]]")
        return true;

    int number = 0;
    char c;
    int col = 0;
    int numcols = 0;
    int rows = 0;

    inputstrm >> c;

    if(!inputstrm.good() || c!= '[')
        return false;



    inputstrm >> c;
    while(c!='['){
        if(!inputstrm.good() || c!= '[')
            return false;

        do{
            inputstrm >> number >> c;

        if(!inputstrm.good() || c!= ',' && ']')
            return false;

        } while(c!=']');

    inputstrm >> c;
    }


    return true;

}

/** \file main.cpp
 *  \brief Käyttöliittymä.
 */

#include <iostream>
#include <stack>
#include <memory>
#include <locale>
#include <exception>
#include "utils.h"
#include "element.h"
#include "elementarymatrix.h"

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"


int main(int argc, char** argv)
{
    int res = Catch::Session().run(argc, argv);

    std::stack<std::unique_ptr<Element>> mstack;
    std::string buffer;
    Valuation valuation;

    std::cout << "*** SQUARE MATRIX CALCULATOR ***" << std::endl;
    std::cout << "* Make a selection:" << std::endl;
    std::cout << "* Input operation: " << "\"+\" \"-\" \"*\"" << "." << std::endl;
    std::cout << "* Input " << "\"quit\"" << " to quit." << std::endl;
    std::cout << "* Input " << "\"clearval\"" << " to clear valuation map." << std::endl;
    std::cout << "* Input " << "\"printval\"" << " to print valuation map." << std::endl;
    std::cout << "* Input " << "\"stacksize\"" << " to print stack size." << std::endl;
    std::cout << "* Input " << "\"=\"" << " to evaluate matrix at the stack top." << std::endl;
    std::cout << "* Input matrix in string format to add it to stack." << std::endl;
    std::cout << "* \tExample: " << "\"[[1,2][a,b]]\"." << std::endl;
    std::cout << "* \tExample: " << "\"[[4,2][5,6]]\"." << std::endl;
    std::cout << "* Input valuation in format " << "\"x=2\"" << " to add it to valuation map." << std::endl;

    std::string prompt{"Please input a selection and press ENTER." };

    while(get_user_input(std::cout, std::cin, prompt, buffer))
    {
        if(buffer == "clearval")
        {
            valuation.clear();
            std::cout << "Valuation map cleared." << std::endl;
        }
        else if(buffer == "stacksize")
        {
            std::cout << "Stack size: " << mstack.size() << std::endl;
        }
        else if(buffer == "printval")
        {
            if(valuation.size() == 0)
            {
                std::cout << "Valuation map is empty." << std::endl;
            }
            else
            {
                for(auto it = valuation.begin(); it != valuation.end(); it++)
                {
                    std::cout << it->first << " = " << it->second << std::endl;
                }
            }
        }
        else if(buffer == "quit")
        {
            break;
        }
        else if(buffer == "+" || buffer == "-" ||
                buffer == "*")
        {
            if(mstack.size() < 2)
            {
                std::cout << "Too few matrices in stack." << std::endl;
            }
            else
            {
                auto m1 = std::move(mstack.top());
                mstack.pop();
                auto m2 = std::move(mstack.top());
                mstack.pop();

                char opchar = buffer[0];

                std::function<ConcreteSquareMatrix(
                    const ConcreteSquareMatrix&,
                    const ConcreteSquareMatrix&)> func;

                switch(opchar)
                {
/*
                    case '+':
                        func = [](const ConcreteSquareMatrix& m1,
                                  const ConcreteSquareMatrix& m2)
                                  {return m1 + m2;};
                        break;

                    case '-':
                        func = [](const ConcreteSquareMatrix& m1,
                                  const ConcreteSquareMatrix& m2)
                                  {return m1 - m2;};
                        break;

                    case '*':
                        func = [](const ConcreteSquareMatrix& m1,
                                  const ConcreteSquareMatrix& m2)
                                  {return m1 * m2;};
                        break;
*/
                    default:
                        std::cout << "Something went terribly wrong." << std::endl;
                        return -1;
                }
/*
                CompositeElement csm{*m1, *m2, func, opchar};

                csm.print(std::cout);
                std::cout << std::endl;

                mstack.push(
                    std::move(std::unique_ptr<CompositeElement>{
                        static_cast<CompositeElement*>(csm.clone())}));
*/
            }
        }
        else if(buffer == "=")
        {
            if(mstack.size() < 1)
            {
                std::cout << "Stack is empty." << std::endl;
            }
            else
            {
                try
                {
                    /*
                    std::unique_ptr<Element> mptr{mstack.top()->clone()};
                    std::cout << "Calculating : " << std::endl;
                    std::cout << "Result : ";
                    mptr->evaluate(valuation).print(std::cout);
                    std::cout << std::endl;
                    */
                }
                catch(std::exception& e)
                {
                    std::cout << "Error while calculating matrices: ";
                    std::cout << e.what() << std::endl;
                }
            }

        }
        else if(isalpha(buffer[0]))
        {
            std::string num;
            char var = buffer[0];

            if(buffer[1] != '=')
            {
                std::cout << "Invalid valuation input." << std::endl;
            }
            else
            {
                for(unsigned int i = 2; i < buffer.size(); i++)
                {
                    if(!std::isdigit(buffer[i]))
                    {
                        std::cout << "Invalid valuation input." << std::endl;
                        break;
                    }
                    num += buffer[i];
                }

                try
                {
                  /*  valuation.insert({var, std::stoi(num)});
                    std::cout << "Added valuation." << std::endl;
                    */

                }
                catch(std::exception)
                {
                    std::cout << "Invalid valuation input." << std::endl;
                }
            }

        }
        else if(buffer[0] == '[')
        {
            bool is_alpha;

            for(unsigned int i = 2; i < buffer.size(); i++)
            {
                if(isalpha(buffer[i]))
                {
                    is_alpha = true;
                    break;
                }
            }

            try
            {
                if(is_alpha)
                {
                   /* mstack.push(
                        std::unique_ptr<Element>{
                            new SymbolicSquareMatrix{buffer}});
                    */
                }
                else
                {
                    /*
                    mstack.push(
                        std::unique_ptr<IntElement>{
                            new ConcreteSquareMatrix{buffer}});
                    */
                }

                std::cout << "Added matrix to stack." << std::endl;
            }
            catch(std::exception)
            {
                std::cout << "Input was not recognized." << std::endl;
            }
        }
        else
        {
            std::cout << "Input was not recognized." << std::endl;
        }
    }

    return res;

}


/** \file utils.hpp
 *  \brief Utility functions and global variables.
 */

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <string>

/** \brief Function for prompting user input and reading it to desired string.
 *  \param os Reference to std::ostream (where the prompt message is written to).
 *  \param is Reference to std::istream (where user input is read from).
 *  \param prompt String to write to os.
 *  \param buffer Target for input.
 *  \return Input stream reference (parameter is).
 */
std::istream& get_user_input(
    const std::ostream& os, std::istream& is,
    const std::string& prompt, std::string& buffer);

#endif // UTILS_H_INCLUDED


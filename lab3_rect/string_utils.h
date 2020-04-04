#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <iostream>
#include <sstream>
#include <string>

template <class Container>
void split(const std::string& str, Container& cont, char delimiter = ' ');

#endif //STRING_UTILS_H

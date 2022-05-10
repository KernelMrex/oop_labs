#ifndef TEMPLATE_UTILS_H
#define TEMPLATE_UTILS_H

#include <map>
#include <string>

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params);

#endif // TEMPLATE_UTILS_H

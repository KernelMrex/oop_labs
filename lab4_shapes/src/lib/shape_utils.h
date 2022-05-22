#ifndef SHAPE_UTILS_H
#define SHAPE_UTILS_H

#include "IShape.h"
#include <memory>
#include <vector>

std::vector<std::unique_ptr<IShape>>::iterator FindMaxArea(std::vector<std::unique_ptr<IShape>>& shapes);

std::vector<std::unique_ptr<IShape>>::iterator FindMinPerimeter(std::vector<std::unique_ptr<IShape>>& shapes);


#endif // SHAPE_UTILS_H

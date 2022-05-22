#include "shape_utils.h"

std::vector<std::unique_ptr<IShape>>::iterator FindMaxArea(std::vector<std::unique_ptr<IShape>>& shapes)
{
	return std::max_element(shapes.begin(), shapes.end(), [](const std::unique_ptr<IShape>& a, const std::unique_ptr<IShape>& b) -> bool {
		return a->GetArea() < b->GetArea();
	});
}

std::vector<std::unique_ptr<IShape>>::iterator FindMinPerimeter(std::vector<std::unique_ptr<IShape>>& shapes)
{
	return std::min_element(shapes.begin(), shapes.end(), [](const std::unique_ptr<IShape>& a, const std::unique_ptr<IShape>& b) -> bool {
		return a->GetPerimeter() < b->GetPerimeter();
	});
}

#include "lib/CShapeTextDumperVisitor.h"
#include "lib/IShape.h"
#include "lib/parse_shape.h"
#include "lib/shape_utils.h"
#include <iostream>
#include <memory>
#include <vector>

int main()
{
	std::vector<std::unique_ptr<IShape>> shapes;
	try
	{
		shapes = ParseShapesFromTextStream(std::cin);
	}
	catch (std::invalid_argument& ex)
	{
		std::cout << "Error while reading shapes: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	CShapeTextDumperVisitor shapeTextDumper(std::cout);

	auto minAreaShape = FindMaxArea(shapes);
	if (minAreaShape != shapes.end())
	{
		std::cout << "Min area shape: ";
		minAreaShape->get()->Accept(shapeTextDumper);
		std::cout << std::endl;
	}

	auto maxPerimeterShape = FindMinPerimeter(shapes);
	if (maxPerimeterShape != shapes.end())
	{
		std::cout << "Min perimeter shape: ";
		maxPerimeterShape->get()->Accept(shapeTextDumper);
		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}

#include "lib/CCanvas.h"
#include "lib/CShapeTextDumperVisitor.h"
#include "lib/IShape.h"
#include "lib/ShapeDrawerVisitor.h"
#include "lib/parse_shape.h"
#include "lib/shape_utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "lab4_shapes");
	CCanvas canvas(window);
	ShapeDrawerVisitor shapeDrawer(canvas);

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
	for (auto& shape : shapes)
	{
		shape->Accept(shapeTextDumper);
		std::cout << std::endl;
	}

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();

		for (auto& shape : shapes)
		{
			shape->Accept(shapeDrawer);
		}

		window.display();
	}

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

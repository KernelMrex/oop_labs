#ifndef RECTANGLES_H
#define RECTANGLES_H

#include "CRectangle.h"
#include <iostream>
#include <optional>
#include <vector>

enum class CRectangleCommands
{
	NOP = 0,
	NEW = 1,
	MOVE = 2,
	SCALE = 3,
};

std::optional<std::vector<CRectangle>> ParseRectangles(std::istream& input);

#endif //RECTANGLES_H

#ifndef PARSE_SHAPE_H
#define PARSE_SHAPE_H

#include "IShape.h"
#include <istream>
#include <memory>
#include <vector>

std::vector<std::unique_ptr<IShape>> ParseShapesFromTextStream(std::istream& in);

std::unique_ptr<IShape> ParseShapeFromTextStream(std::istream& in);

std::unique_ptr<IShape> ParseShapeFromText(const std::string& line);

std::unique_ptr<CRectangle> ParseRectangleFromText(const std::string& line);

std::unique_ptr<CCircle> ParseCircleFromText(const std::string& line);

std::unique_ptr<CTriangle> ParseTriangleFromText(const std::string& line);

std::unique_ptr<CLineSegment> ParseLineSegmentFromText(const std::string& line);


#endif // PARSE_SHAPE_H

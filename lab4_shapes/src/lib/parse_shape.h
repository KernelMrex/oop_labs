#ifndef SHAPE_UTILS_H
#define SHAPE_UTILS_H

#include "IShape.h"
#include <istream>
#include <memory>

std::unique_ptr<IShape> ParseShapeFromText(std::istream& in);

std::unique_ptr<CRectangle> ParseRectangleFromText(const std::string& line);

std::unique_ptr<CCircle> ParseCircleFromText(const std::string& line);

std::unique_ptr<CTriangle> ParseTriangleFromText(const std::string& line);

std::unique_ptr<CLineSegment> ParseLineSegmentFromText(const std::string& line);


#endif // SHAPE_UTILS_H

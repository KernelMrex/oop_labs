#include "parse_shape.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <regex>

typedef std::function<std::unique_ptr<IShape>(const std::string& line)> ShapeParsingLambda;
static const std::map<std::string, ShapeParsingLambda> shapeToParsingLambda = { // NOLINT(cert-err58-cpp)
	{
		"rectangle",
		[](const std::string& line) -> std::unique_ptr<IShape> { return ParseRectangleFromText(line); }
	},
	{
		"circle",
		[](const std::string& line) -> std::unique_ptr<IShape> { return ParseCircleFromText(line); }
	},
	{
		"triangle",
		[](const std::string& line) -> std::unique_ptr<IShape> { return ParseTriangleFromText(line); }
	},
	{
		"line_segment",
		[](const std::string& line) -> std::unique_ptr<IShape> { return ParseLineSegmentFromText(line); }
	}
};

std::vector<std::unique_ptr<IShape>> ParseShapesFromTextStream(std::istream& in)
{
	std::vector<std::unique_ptr<IShape>> shapes;

	while (in)
	{
		try
		{
			shapes.push_back(ParseShapeFromTextStream(in));
		}
		catch (std::invalid_argument& ex)
		{
			if (ex.what() == std::string{"Empty line given"})
			{
				continue;
			}

			throw ex;
		}
	}

	return shapes;
}

std::unique_ptr<IShape> ParseShapeFromTextStream(std::istream& in)
{
	if (!in)
	{
		throw std::invalid_argument("Input stream is not readable");
	}

	std::string line;
	std::getline(in, line);
	return ParseShapeFromText(line);
}

std::unique_ptr<IShape> ParseShapeFromText(const std::string& line)
{
	static std::regex figureTypeRegex("^(\\w+)");
	std::smatch matches;

	if (line.empty())
	{
		throw std::invalid_argument("Empty line given");
	}

	if (!std::regex_search(line, matches, figureTypeRegex))
	{
		throw std::invalid_argument("Invalid input line");
	}

	std::string shapeType = matches[1];
	auto parsingRule = shapeToParsingLambda.find(shapeType);
	if (parsingRule != shapeToParsingLambda.end())
	{
		return parsingRule->second(line);
	}
	else
	{
		throw std::invalid_argument("Unknown figure " + shapeType);
	}
}

std::unique_ptr<CRectangle> ParseRectangleFromText(const std::string& line)
{
	std::smatch matches;
	static std::regex regex(R"(^rectangle (\d+\.?\d*) (\d+\.?\d*) (\d+\.?\d*) (\d+\.?\d*) 0x([0-9a-fA-F]{6}) 0x([0-9a-fA-F]{6}))");
	if (!std::regex_search(line, matches, regex))
	{
		throw std::invalid_argument("Rectangle record is invalid");
	}

	return std::make_unique<CRectangle>(
		CPoint(std::stod(matches[1]), std::stod(matches[2])),
		std::stod(matches[3]),
		std::stod(matches[4]),
		static_cast<uint32_t>(std::stoul(matches[5], nullptr, 16)),
		static_cast<uint32_t>(std::stoul(matches[6], nullptr, 16))
	);
}

std::unique_ptr<CCircle> ParseCircleFromText(const std::string& line)
{
	std::smatch matches;
	static std::regex regex(R"(^circle (\d+\.?\d*) (\d+\.?\d*) (\d+\.?\d*) 0x([0-9a-fA-F]{6}) 0x([0-9a-fA-F]{6}))");
	if (!std::regex_search(line, matches, regex))
	{
		throw std::invalid_argument("Circle record is invalid");
	}

	return std::make_unique<CCircle>(
		CPoint(std::stod(matches[1]), std::stod(matches[2])),
		std::stod(matches[3]),
		static_cast<uint32_t>(std::stoul(matches[4], nullptr, 16)),
		static_cast<uint32_t>(std::stoul(matches[5], nullptr, 16))
	);
}

std::unique_ptr<CTriangle> ParseTriangleFromText(const std::string& line)
{
	std::smatch matches;
	static std::regex regex(R"(^triangle (\d+\.?\d*) (\d+\.?\d*) (\d+\.?\d*) (\d+\.?\d*) (\d+\.?\d*) (\d+\.?\d*) 0x([0-9a-fA-F]{6}) 0x([0-9a-fA-F]{6}))");
	if (!std::regex_search(line, matches, regex))
	{
		throw std::invalid_argument("Triangle record is invalid");
	}

	return std::make_unique<CTriangle>(
		CPoint(std::stod(matches[1]), std::stod(matches[2])),
		CPoint(std::stod(matches[3]), std::stod(matches[4])),
		CPoint(std::stod(matches[5]), std::stod(matches[6])),
		static_cast<uint32_t>(std::stoul(matches[7], nullptr, 16)),
		static_cast<uint32_t>(std::stoul(matches[8], nullptr, 16))
	);
}

std::unique_ptr<CLineSegment> ParseLineSegmentFromText(const std::string& line)
{
	std::smatch matches;
	static std::regex regex(R"(^line_segment (\d+\.?\d*) (\d+\.?\d*) (\d+\.?\d*) (\d+\.?\d*) 0x([0-9a-fA-F]{6}))");
	if (!std::regex_search(line, matches, regex))
	{
		throw std::invalid_argument("LineSegment record is invalid");
	}

	return std::make_unique<CLineSegment>(
		CPoint(std::stod(matches[1]), std::stod(matches[2])),
		CPoint(std::stod(matches[3]), std::stod(matches[4])),
		static_cast<uint32_t>(std::stoul(matches[5], nullptr, 16))
	);
}

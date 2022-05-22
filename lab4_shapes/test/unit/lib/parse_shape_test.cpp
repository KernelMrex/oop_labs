#include "../../../../catch.hpp"
#include "../../../src/lib/CCircle.h"
#include "../../../src/lib/CLineSegment.h"
#include "../../../src/lib/CRectangle.h"
#include "../../../src/lib/CTriangle.h"
#include "../../../src/lib/parse_shape.h"
#include "MockShapeVisitor.h"
#include <sstream>

TEST_CASE("ParseShapeFromText unit tests", "[ParseShape_unit_tests]")
{
	SECTION("ParseShapeFromText must parse all figures")
	{
		std::stringstream mockStream;
		mockStream
			<< "triangle 0 0 0 5 12 5 0x012345 0x098765" << std::endl
			<< "triangle 0.1 0.2 0.3 5.4 12.5 5.6 0x012345 0x098765" << std::endl
			<< "rectangle 5 10 20 40 0x012345 0x098765" << std::endl
			<< "rectangle 5.1 10.2 20.3 40.4 0x012345 0x098765" << std::endl
			<< "circle 5 10 20 0x012345 0x098765" << std::endl
			<< "circle 5.1 10.2 20.3 0x012345 0x098765" << std::endl
			<< "line_segment 1 2 3 4 0x012345" << std::endl
			<< "line_segment 1.1 2.2 3.3 4.4 0x012345" << std::endl;

		std::unique_ptr<IShape> mockShape;
		MockShapeVisitor mockShapeVisitor;

		mockShape = ParseShapeFromTextStream(mockStream);
		mockShape->Accept(mockShapeVisitor);
		REQUIRE(mockShapeVisitor.m_visited == "triangle");
		mockShapeVisitor.m_visited = "";

		mockShape = ParseShapeFromTextStream(mockStream);
		mockShape->Accept(mockShapeVisitor);
		REQUIRE(mockShapeVisitor.m_visited == "triangle");
		mockShapeVisitor.m_visited = "";

		mockShape = ParseShapeFromTextStream(mockStream);
		mockShape->Accept(mockShapeVisitor);
		REQUIRE(mockShapeVisitor.m_visited == "rectangle");
		mockShapeVisitor.m_visited = "";

		mockShape = ParseShapeFromTextStream(mockStream);
		mockShape->Accept(mockShapeVisitor);
		REQUIRE(mockShapeVisitor.m_visited == "rectangle");
		mockShapeVisitor.m_visited = "";

		mockShape = ParseShapeFromTextStream(mockStream);
		mockShape->Accept(mockShapeVisitor);
		REQUIRE(mockShapeVisitor.m_visited == "circle");
		mockShapeVisitor.m_visited = "";

		mockShape = ParseShapeFromTextStream(mockStream);
		mockShape->Accept(mockShapeVisitor);
		REQUIRE(mockShapeVisitor.m_visited == "circle");
		mockShapeVisitor.m_visited = "";

		mockShape = ParseShapeFromTextStream(mockStream);
		mockShape->Accept(mockShapeVisitor);
		REQUIRE(mockShapeVisitor.m_visited == "line_segment");
		mockShapeVisitor.m_visited = "";

		mockShape = ParseShapeFromTextStream(mockStream);
		mockShape->Accept(mockShapeVisitor);
		REQUIRE(mockShapeVisitor.m_visited == "line_segment");
		mockShapeVisitor.m_visited = "";
	}
}

TEST_CASE("ParseRectangleFromText unit tests", "[ParseRectangle_unit_tests]")
{
	SECTION("ParseRectangleFromText must parse CRectangle")
	{
		std::stringstream mockStream;
		mockStream
			<< "rectangle 5 10 20 40 0x012345 0x098765" << std::endl
			<< "rectangle 5.1 10.2 20.3 40.4 0x012345 0x098765" << std::endl;

		std::string line;
		std::getline(mockStream, line);
		auto rect = ParseRectangleFromText(line);
		REQUIRE(rect->GetLeftTop() == CPoint(5, 10));
		REQUIRE(rect->GetWidth() == 20);
		REQUIRE(rect->GetHeight() == 40);
		REQUIRE(rect->GetOutlineColor() == 0x012345);
		REQUIRE(rect->GetFillColor() == 0x098765);

		std::getline(mockStream, line);
		rect = ParseRectangleFromText(line);
		REQUIRE(rect->GetLeftTop() == CPoint(5.1, 10.2));
	}
}

TEST_CASE("ParseTriangleFromText unit tests", "[ParseTriangleFromText]")
{
	SECTION("ParseTriangleFromText must parse CTriangle")
	{
		std::stringstream mockStream;
		mockStream
			<< "triangle 0 0 0 5 12 5 0x012345 0x098765" << std::endl
			<< "triangle 0.1 0.2 0.3 5.4 12.5 5.6 0x012345 0x098765" << std::endl;

		std::string line;
		std::getline(mockStream, line);
		auto triangle = ParseTriangleFromText(line);
		REQUIRE(triangle->GetVertex1() == CPoint(0, 0));
		REQUIRE(triangle->GetVertex2() == CPoint(0, 5));
		REQUIRE(triangle->GetVertex3() == CPoint(12, 5));
		REQUIRE(triangle->GetOutlineColor() == 0x012345);
		REQUIRE(triangle->GetFillColor() == 0x098765);

		std::getline(mockStream, line);
		triangle = ParseTriangleFromText(line);
		REQUIRE(triangle->GetVertex1() == CPoint(0.1, 0.2));
		REQUIRE(triangle->GetVertex2() == CPoint(0.3, 5.4));
		REQUIRE(triangle->GetVertex3() == CPoint(12.5, 5.6));
	}
}

TEST_CASE("ParseCircleFromText unit tests", "[ParseCircleFromText]")
{
	SECTION("ParseCircleFromText must parse CCircle")
	{
		std::stringstream mockStream;
		mockStream
			<< "circle 5 10 20 0x012345 0x098765" << std::endl
			<< "circle 5.1 10.2 20.3 0x012345 0x098765" << std::endl;

		std::string line;
		std::getline(mockStream, line);
		auto circle = ParseCircleFromText(line);
		REQUIRE(circle->GetCenter() == CPoint(5, 10));
		REQUIRE(circle->GetRadius() == 20);
		REQUIRE(circle->GetOutlineColor() == 0x012345);
		REQUIRE(circle->GetFillColor() == 0x098765);

		std::getline(mockStream, line);
		circle = ParseCircleFromText(line);
		REQUIRE(circle->GetCenter() == CPoint(5.1, 10.2));
		REQUIRE(circle->GetRadius() == 20.3);
	}
}


TEST_CASE("ParseLineSegmentFromText unit tests", "[ParseLineSegmentFromText]")
{
	SECTION("ParseLineSegmentFromText must parse CLineSegment")
	{
		std::stringstream mockStream;
		mockStream
			<< "line_segment 1 2 3 4 0x012345" << std::endl
			<< "line_segment 1.1 2.2 3.3 4.4 0x012345" << std::endl;

		std::string line;
		std::getline(mockStream, line);
		auto lineSegment = ParseLineSegmentFromText(line);
		REQUIRE(lineSegment->GetStartPoint() == CPoint(1, 2));
		REQUIRE(lineSegment->GetEndPoint() == CPoint(3, 4));
		REQUIRE(lineSegment->GetOutlineColor() == 0x012345);

		std::getline(mockStream, line);
		lineSegment = ParseLineSegmentFromText(line);
		REQUIRE(lineSegment->GetStartPoint() == CPoint(1.1, 2.2));
		REQUIRE(lineSegment->GetEndPoint() == CPoint(3.3, 4.4));
	}
}

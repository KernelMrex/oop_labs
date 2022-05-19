#include "../../../src/lib/CShapeTextDumperVisitor.h"
#include "../../../../catch.hpp"
#include "../../../src/lib/CCircle.h"
#include "../../../src/lib/CRectangle.h"
#include "../../../src/lib/CTriangle.h"
#include "../../../src/lib/CLineSegment.h"
#include <sstream>

TEST_CASE("CShapeTextDumperVisitor unit tests", "[CShapeTextDumperVisitor_unit_tests]")
{
	SECTION("CShapeTextDumperVisitor must dump CCircle")
	{
		std::stringstream mockOut;
		CShapeTextDumperVisitor shapeTextDumper(mockOut);

		shapeTextDumper.VisitCircle(CCircle(
			CPoint(5, 10),
			20,
			0x012345,
			0x098765));
		mockOut.flush();
		REQUIRE(mockOut.str() == "circle 5 10 20 0x012345 0x098765");

		mockOut.str("");
		mockOut.clear();

		shapeTextDumper.VisitCircle(CCircle(
			CPoint(5.1, 10.2),
			20.3,
			0x012345,
			0x098765));
		mockOut.flush();
		REQUIRE(mockOut.str() == "circle 5.1 10.2 20.3 0x012345 0x098765");
	}

	SECTION("CShapeTextDumperVisitor must dump CRectangle")
	{
		std::stringstream mockOut;
		CShapeTextDumperVisitor shapeTextDumper(mockOut);

		shapeTextDumper.VisitRectangle(CRectangle(
			CPoint(5, 10),
			20,
			40,
			0x012345,
			0x098765));
		mockOut.flush();
		REQUIRE(mockOut.str() == "rectangle 5 10 20 40 0x012345 0x098765");

		mockOut.str("");
		mockOut.clear();

		shapeTextDumper.VisitRectangle(CRectangle(
			CPoint(5.1, 10.2),
			20.3,
			40.4,
			0x012345,
			0x098765));
		mockOut.flush();
		REQUIRE(mockOut.str() == "rectangle 5.1 10.2 20.3 40.4 0x012345 0x098765");
	}

	SECTION("CShapeTextDumperVisitor must dump CTriangle")
	{
		std::stringstream mockOut;
		CShapeTextDumperVisitor shapeTextDumper(mockOut);

		shapeTextDumper.VisitTriangle(CTriangle(
			CPoint(0, 0),
			CPoint(0, 5),
			CPoint(12, 5),
			0x012345,
			0x098765));
		mockOut.flush();
		REQUIRE(mockOut.str() == "triangle 0 0 0 5 12 5 0x012345 0x098765");

		mockOut.str("");
		mockOut.clear();

		shapeTextDumper.VisitTriangle(CTriangle(
			CPoint(0.1, 0.2),
			CPoint(0.3, 5.4),
			CPoint(12.5, 5.6),
			0x012345,
			0x098765));
		mockOut.flush();
		REQUIRE(mockOut.str() == "triangle 0.1 0.2 0.3 5.4 12.5 5.6 0x012345 0x098765");
	}

	SECTION("CShapeTextDumperVisitor must dump CLineSegment")
	{
		std::stringstream mockOut;
		CShapeTextDumperVisitor shapeTextDumper(mockOut);

		shapeTextDumper.VisitLineSegment(CLineSegment(CPoint(1, 2), CPoint(3, 4), 0x012345));
		mockOut.flush();
		REQUIRE(mockOut.str() == "line_segment 1 2 3 4 0x012345");

		mockOut.str("");
		mockOut.clear();

		shapeTextDumper.VisitLineSegment(CLineSegment(CPoint(1.1, 2.2), CPoint(3.3, 4.4), 0x012345));
		mockOut.flush();
		REQUIRE(mockOut.str() == "line_segment 1.1 2.2 3.3 4.4 0x012345");
	}
}
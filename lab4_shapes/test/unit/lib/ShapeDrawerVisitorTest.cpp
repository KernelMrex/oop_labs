#include "../../../../catch.hpp"
#include "../../../../fakeit.hpp"
#include "../../../src/lib/ICanvas.h"
#include "../../../src/lib/ShapeDrawerVisitor.h"
#include "../../../src/lib/CRectangle.h"

TEST_CASE("ShapeDrawerVisitor unit tests")
{
	SECTION("VisitRectangle must call specific methods on Canvas")
	{
		fakeit::Mock<ICanvas> mockCanvas;

		fakeit::Fake(Method(mockCanvas, DrawPolygon), Method(mockCanvas, FillPolygon));

		ShapeDrawerVisitor shapeDrawer(mockCanvas.get());

		shapeDrawer.VisitRectangle(CRectangle{
			CPoint{10.1, 10.2},
			20.1,
			30.1,
			0x000001,
			0x000002
		});

		fakeit::Verify(Method(mockCanvas, DrawPolygon).Using(
			std::vector<CPoint>{
				CPoint{10.1, 10.2},
				CPoint{10.1, 40.3},
				CPoint{30.2, 40.3},
				CPoint{30.2, 10.2},
			}, 0x000001)).Once();

		fakeit::Verify(Method(mockCanvas, FillPolygon).Using(
			std::vector<CPoint>{
				CPoint{10.1, 10.2},
				CPoint{10.1, 40.3},
				CPoint{30.2, 40.3},
				CPoint{30.2, 10.2},
			}, 0x000002)).Once();
	}
}
#include "../../../../catch.hpp"
#include "../../../src/lib/template_utils.h"

TEST_CASE("ExpandTemplate must apply template", "[expand_template]")
{
	SECTION("Expanding templates")
	{
		auto result1 = ExpandTemplate(
			"Template1 %template1% Template2 %template2% Template3 %template3%",
			std::map<std::string, std::string>{
				{ "%template1%", "replace1" },
				{ "%template2%", "replace2" },
				{ "%template3%", "replace3" },
			});
		REQUIRE(result1 == "Template1 replace1 Template2 replace2 Template3 replace3");
	}
}
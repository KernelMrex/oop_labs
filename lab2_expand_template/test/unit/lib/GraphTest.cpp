#include "../../../../catch.hpp"
#include "../../../src/lib/Graph.h"

TEST_CASE("Graph class unit tests", "[graph_unit_tests]")
{
	SECTION("Graph must store nodes")
	{
		Graph<int, int> graph;

		graph.AddNode(0, 20);
		graph.AddNode(1, 21);
		graph.AddNode(2, 22);

		auto stored = graph.GetNodeValue(0);
		REQUIRE(stored.has_value());
		REQUIRE(stored.value() == 20);

		stored = graph.GetNodeValue(1);
		REQUIRE(stored.has_value());
		REQUIRE(stored.value() == 21);

		stored = graph.GetNodeValue(2);
		REQUIRE(stored.has_value());
		REQUIRE(stored.value() == 22);

		stored = graph.GetNodeValue(3);
		REQUIRE(!stored.has_value());
	}

	SECTION("Graph must add edges and provide related vertices")
	{
		Graph<int, int> graph;

		graph.AddNode(0, 20);
		graph.AddNode(1, 21);
		graph.AddNode(2, 22);

		REQUIRE(graph.GetRelatedVertices(0).empty());
		graph.AddEdge(0, 1);
		graph.AddEdge(0, 2);
		REQUIRE(graph.GetRelatedVertices(0) == std::unordered_set<int>{1, 2});

		REQUIRE(graph.GetRelatedVertices(1).empty());
		graph.AddEdge(1, 2);
		REQUIRE(graph.GetRelatedVertices(1) == std::unordered_set<int>{2});
	}
}
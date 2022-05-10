#ifndef GRAPH_H
#define GRAPH_H

#include <memory>
#include <unordered_map>
#include <unordered_set>

template <class IndexType, class NodeValueType>
class Graph
{
public:
	Graph()
		: m_edges()
		, m_nodes(std::unordered_map<IndexType, NodeValueType>()){};

	void AddNode(IndexType index, NodeValueType value)
	{
		if (m_nodes.find(index) != m_nodes.end())
		{
			throw std::runtime_error("Node with given index already exists!");
		}
		m_nodes.insert(std::pair<IndexType, NodeValueType>(index, value));
	}

	std::optional<NodeValueType> GetNodeValue(IndexType index) const
	{
		auto node = m_nodes.find(index);
		return (node == m_nodes.end()) ? std::nullopt : std::optional<NodeValueType>{node->second};
	}

	void AddEdge(IndexType from, IndexType to)
	{
		m_edges.insert(std::pair(from, to));
	}

	std::unordered_set<IndexType> GetRelatedVertices(const IndexType& vertexIndex) const
	{
		std::unordered_set<IndexType> foundVertices;
		std::for_each(m_edges.begin(), m_edges.end(), [&vertexIndex, &foundVertices](const std::pair<IndexType, IndexType> &edge) -> void {
			if (edge.first == vertexIndex)
			{
				foundVertices.insert(edge.second);
			}
		});
		return foundVertices;
	}

private:
	struct EdgeHashFunction
	{
		std::size_t operator()(const std::pair<IndexType, IndexType>& item) const
		{
			return std::hash<IndexType>()(item.first) ^ (std::hash<IndexType>()(item.second) << 1);
		}
	};

	std::unordered_set<std::pair<IndexType, IndexType>, EdgeHashFunction> m_edges;
	std::unordered_map<IndexType, NodeValueType> m_nodes;
};

#endif // GRAPH_H

#pragma once

#include <vector>
#include <cassert>
#include <memory>
#include <tuple>
#include <list>

class SquareGridGraph
{
public:
	using node_crd = std::pair<size_t, size_t>;
	using twoLenghtChain = std::tuple<node_crd, node_crd, node_crd>;
	using threeLenghtChain = std::tuple<node_crd, node_crd, node_crd, node_crd>;
public:
	SquareGridGraph() = default;
	SquareGridGraph(size_t horizontalSize, size_t verticalSize)
		: m_verticalSize(verticalSize)
		, m_horizontalSize(horizontalSize)
	{
		buildGrid();
		connectGrid();
	}

	void setVerticalSize(size_t size);
	void setHorizontalSize(size_t size);
	void twoThreeLenghtSimpleChainCoverage();
	void printCoverage();
private:
	void threeLenghtSimpleChainCoverage();
	void twoLenghtSimpleChainCoverage();
	void endGridCoverage();
	void connectExternalNode();
	void connectInternalNode();
	void buildGrid();
	void connectGrid();
private:
	struct GraphNode
	{
		GraphNode() = default;

		GraphNode* left = nullptr;
		GraphNode* right = nullptr;
		GraphNode* up = nullptr;
		GraphNode* down = nullptr;
	};
private:
	std::vector<std::vector<GraphNode*>> m_grid;
	std::list<threeLenghtChain> m_threeLenghtChains;
	std::list<twoLenghtChain> m_twoLenghtChains;
	size_t m_verticalSize;
	size_t m_horizontalSize;
};


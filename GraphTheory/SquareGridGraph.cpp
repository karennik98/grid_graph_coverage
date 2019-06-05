#include "SquareGridGraph.h"

#include <iostream>
#include <stdexcept>


void SquareGridGraph::setVerticalSize(size_t count)
{
	assert(count > 0);

	m_verticalSize = count;
}
void SquareGridGraph::setHorizontalSize(size_t count)
{
	assert(count > 0);

	m_horizontalSize = count;
}
void SquareGridGraph::buildGrid()
{
	if (!m_grid.empty())
	{
		m_grid.clear();
	}
	std::vector<GraphNode*> tmpVec;
	for (size_t i = 0; i < m_horizontalSize; ++i)
	{
		for (size_t j = 0; j < m_verticalSize; ++j)
		{
			tmpVec.push_back(new GraphNode());
		}
		m_grid.push_back(tmpVec);
		tmpVec.clear();
	}
}

void SquareGridGraph::threeLenghtSimpleChainCoverage()
{
	size_t m = m_horizontalSize; // horizontal size of grid
	for (size_t i = 1; i < m_verticalSize; ++i)
	{
		m_threeLenghtChains.push_back(std::make_tuple(std::make_pair( m - 1,i ), std::make_pair( m - 1,i - 1 ), std::make_pair( m - 2,i-1), std::make_pair(m - 2, i)));
	}
}
void SquareGridGraph::twoLenghtSimpleChainCoverage()
{
	size_t m = m_horizontalSize; // horizontal size of grid
	for (size_t i = 0; i < m_verticalSize - 1; ++i)
	{
		for (size_t j = 2; j < m_horizontalSize; ++j)
		{
			m_twoLenghtChains.push_back(std::make_tuple(std::make_pair(m - j, i), std::make_pair(m - (j + 1), i), std::make_pair(m - (j + 1), i + 1)));
		}
	}
}
void SquareGridGraph::endGridCoverage()
{
	size_t n = m_verticalSize - 1; // vertical size of grid
	if (m_horizontalSize % 2 == 1)
	{
		for (size_t i = 0; i < m_horizontalSize - 1; i+=2)
		{
			m_twoLenghtChains.push_back(std::make_tuple(std::make_pair(i, n), std::make_pair(i + 1, n), std::make_pair(i + 2, n)));
		}
	}
	else
	{
		size_t m = m_horizontalSize - 1;
		m_threeLenghtChains.push_back(std::make_tuple(std::make_pair(m,n), std::make_pair(m-1,n), std::make_pair(m-2,n), std::make_pair(m-3,n)));
		for (size_t i = 0; i < m_horizontalSize - 4; i+=2)
		{
			m_twoLenghtChains.push_back(std::make_tuple(std::make_pair(i, n), std::make_pair(i + 1, n), std::make_pair(i + 2, n)));
		}
	}
}
void SquareGridGraph::twoThreeLenghtSimpleChainCoverage()
{
	if (m_horizontalSize == 2 && m_verticalSize  == 2)
	{
		throw std::invalid_argument("Trivial grid graph");
	}

	if (m_horizontalSize == 2)
	{
		std::cout << "WARNING: Two horizontal lenght! grid will be rotate." << std::endl<<std::endl;
		size_t tmpSize = m_horizontalSize;
		setHorizontalSize(m_verticalSize);
		setVerticalSize(tmpSize);
		buildGrid();
		connectGrid();
	}
	threeLenghtSimpleChainCoverage();
	twoLenghtSimpleChainCoverage();
	endGridCoverage();
}

void SquareGridGraph::connectExternalNode()
{
	size_t j = 0;
	size_t i = 0;
	while (j < m_verticalSize - 2)
	{
		m_grid[0][j]->up = m_grid[1][j];
		m_grid[0][j]->right = m_grid[0][j + 1];
		j++;
	}

	j = 0;
	i = m_horizontalSize - 1;
	while (j < m_verticalSize - 2)
	{
		m_grid[i][j]->down = m_grid[i - 1][j];
		m_grid[i][j]->right = m_grid[i][j + 1];
		j++;
	}

	i = 0;
	while (i < m_horizontalSize - 2)
	{
		m_grid[i][0]->up = m_grid[i + 1][0];
		m_grid[i][0]->right = m_grid[i][1];
		i++;
	}

	i = 0;
	j = m_verticalSize - 1;
	while (i < m_horizontalSize - 2)
	{
		m_grid[i][j]->up = m_grid[i+1][j];
		m_grid[i][j]->left = m_grid[i][j - 1];
		i++;
	}
}
void SquareGridGraph::connectInternalNode()
{
	for (size_t i = 1; i < m_horizontalSize - 2; ++i)
	{
		for (size_t j = 1; j < m_verticalSize - 2; ++j)
		{
			m_grid[i][j]->up    = m_grid[i + 1][j];
			m_grid[i][j]->down  = m_grid[i - 1][j];
			m_grid[i][j]->left  = m_grid[i][j - 1];
			m_grid[i][j]->right = m_grid[i][j + 1];
		}
	}
}
void SquareGridGraph::connectGrid()
{
	connectExternalNode();
	connectInternalNode();
}

void SquareGridGraph::printCoverage()
{
	std::cout << ".......Three Lenght Simple Chains......." << std::endl;
	for (const auto& it : m_threeLenghtChains)
	{
		std::cout << "{ ( " << std::get<0>(it).first << ", " << std::get<0>(it).second << " ), ( "
			<< std::get<1>(it).first << ", " << std::get<1>(it).second << " ), ( "
			<< std::get<2>(it).first << ", " << std::get<2>(it).second << " ), ( "
			<< std::get<3>(it).first << ", " << std::get<3>(it).second << " ) } " << std::endl;
	}
	std::cout << std::endl;

	std::cout << ".......Two Lenght Simple Chains......." << std::endl;
	for (const auto& it : m_twoLenghtChains)
	{
		std::cout << "{ ( " << std::get<0>(it).first << ", " << std::get<0>(it).second << " ), ( "
			<< std::get<1>(it).first << ", " << std::get<1>(it).second << " ), ( "
			<< std::get<2>(it).first << ", " << std::get<2>(it).second << " ) } " <<std::endl;
	}
	std::cout << std::endl;
}

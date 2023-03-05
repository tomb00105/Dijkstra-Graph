#pragma once
#include <iostream>
#include <string>
#include <array>
#include <memory>
#include "Graph.h"
#include "GraphNode.h"
#include "MinHeap.h"
#include "Dijkstra.h"
#include "Edge.h"
class MemTest
{
public:
	std::vector<GraphNode> GraphTest()
	{
		std::vector<GraphNode> test{};
		test.reserve(16);

		test.push_back(GraphNode(0, 0, 0, GraphNode::Type::GRASS));
		test.push_back(GraphNode(1, 0, 0, GraphNode::Type::DIRT));
		test.push_back(GraphNode(2, 0, 0, GraphNode::Type::DIRT));
		test.push_back(GraphNode(3, 0, 0, GraphNode::Type::DIRT));
		test.push_back(GraphNode(0, 0, 1, GraphNode::Type::DIRT));
		test.push_back(GraphNode(1, 0, 1, GraphNode::Type::DIRT));
		test.push_back(GraphNode(2, 0, 1, GraphNode::Type::ROAD));
		test.push_back(GraphNode(3, 0, 1, GraphNode::Type::WATER));
		test.push_back(GraphNode(0, 0, 2, GraphNode::Type::DIRT));
		test.push_back(GraphNode(1, 0, 2, GraphNode::Type::GRASS));
		test.push_back(GraphNode(2, 0, 2, GraphNode::Type::DIRT));
		test.push_back(GraphNode(3, 0, 2, GraphNode::Type::WATER));
		test.push_back(GraphNode(0, 0, 3, GraphNode::Type::DIRT));
		test.push_back(GraphNode(1, 0, 3, GraphNode::Type::ROAD));
		test.push_back(GraphNode(2, 0, 3, GraphNode::Type::ROAD));
		test.push_back(GraphNode(3, 0, 3, GraphNode::Type::DIRT));

		//std::cout << "test[1] location: " << test[1].GetLocation()[0] << test[1].GetLocation()[1] << test[1].GetLocation()[2] << '\n';

		return test;
	}

	void Test()
	{
		//Test code for building a path.

		std::vector<GraphNode> arr{ GraphTest() };

		//std::cout << "arr[1] location: " << arr[1].GetLocation()[0] << arr[1].GetLocation()[1] << arr[1].GetLocation()[2] << '\n';

		//std::cout << "arr size: " << arr.size() << '\n';

		Graph<GraphNode, int> graph{ arr };

		int edgeCount = graph.EdgeSetup();


		//std::cout << "Edge count: " << edgeCount << '\n';

		Dijkstra dijkstra{};

		std::vector<std::shared_ptr<Edge>> edgePath{ dijkstra.DijkstraCalc<GraphNode, int>(graph.GetNodes(), graph.GetNodes()[1], graph.GetNodes()[15], 0) };

		for (std::shared_ptr<Edge> edge : edgePath)
		{
			std::cout << edge->m_destination->GetDijkstraComparable()[0]
				<< edge->m_destination->GetDijkstraComparable()[1]
				<< edge->m_destination->GetDijkstraComparable()[2] << '\n';
		}
	}
	
};


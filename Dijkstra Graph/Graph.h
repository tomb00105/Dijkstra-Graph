#pragma once
#include <vector>
#include <iostream>
#include "Edge.h"
#include "DijkstraStatus.h"

template <typename T, typename U>
class Graph
{
private:
	std::vector <std::shared_ptr<T>> m_nodes;
public:

	Graph() {};

	Graph(std::vector<T>& nodeList) 
	{
		for (T& node : nodeList)
		{
			m_nodes.push_back(std::make_shared<T>(node));
		}
	};

	~Graph()
	{
		ResetGraph();
	}

	std::vector<std::shared_ptr<T>>& GetNodes()
	{
		return m_nodes;
	}

	int EdgeSetup()
	{
		//std::cout << "Inside EdgeSetup()\n";
	//std::wcout << "m_nodes count: " << m_nodes.size() << '\n';
		int edgeCount{ 0 };

		for (std::shared_ptr<T> node : m_nodes)
		{
			//std::cout << "Inside node for loop\n";
			std::vector<U> nodeLocation = node->GetDijkstraComparable();
			//std::cout << nodeLocation[0] << nodeLocation[1] << nodeLocation[2] << '\n';
			for (std::shared_ptr<T>& nodeToCheck : m_nodes)
			{
				if (nodeToCheck->GetDijkstraComparable() == nodeLocation)
				{
					continue;
				}

				//const auto& existingedges{ node.m_edges };
				if (node->GetEdges().size() > 0)
				{
					//std::cout << "edge vector larger than 0 \n";
					for (std::shared_ptr<Edge> edge : node->GetEdges())
					{
						if (edge->m_destination->GetDijkstraComparable() == nodeToCheck->GetDijkstraComparable())
						{
							//std::cout << "edge already exists \n";
							continue;
						}
					}
				}

				if (node->CompareNodes(node, nodeToCheck))
				{
					node->AddEdge(node, nodeToCheck);
					edgeCount++;
				}
			}
		}
		return edgeCount;
	}

	void ResetGraph()
	{
		for (std::shared_ptr<T> node : m_nodes)
		{
			node->SetStatus(UNVISITED);
			node->SetNullPath();
		}
	}
};


#pragma once
#include <vector>
#include "Graph.h"
#include "MinHeap.h"
#include "Edge.h"
#include "DijkstraStatus.h"

class Dijkstra 
{
public:

	~Dijkstra() = default;

	template <typename T, typename U>
	std::vector<std::shared_ptr<Edge>> DijkstraCalc
	(std::vector<std::shared_ptr<T>>& graph, std::shared_ptr<T> startNode, std::shared_ptr<T> endNode, U value)
	{
		MinHeap<T, U> heap(startNode, 0);
		startNode->SetPriority(0);

		while (heap.GetSize() > 0)
		{
			if (heap.GetMin()->GetDijkstraComparable() == endNode->GetDijkstraComparable())
			{
				break;
			}
			auto minNode = heap.ExtractMin();
			std::cout << minNode->GetStatus() << '\n';
			if (minNode->GetStatus() != Status::VISITED)
			{
				std::cout << "minNode edge count: " << minNode->GetEdges().size() << '\n';
				for (auto edge : minNode->GetEdges())
				{
					if (edge->m_destination->GetStatus() != Status::VISITED)
					{
						std::cout << "Destination node not visited!\n";
						std::cout << minNode->GetPriority() /*+ edge.m_cost << " < " << edge.m_destination.GetPriority()*/ << '\n';
						if (minNode->GetPriority() + edge->m_cost < edge->m_destination->GetPriority())
						{
							if (edge->m_destination->GetStatus() == Status::LABELLED)
							{
								heap.DecreaseKey(heap.GetIndex(std::dynamic_pointer_cast<T>(edge->m_destination)), minNode->GetPriority() + edge->m_cost);
							}
							else
							{
								//std::cout << "Adding node to heap!\n";
								edge->m_destination->SetPriority(minNode->GetPriority() + edge->m_cost);
								auto temp = edge->m_destination;
								heap.InsertKey(std::dynamic_pointer_cast<T>(edge->m_destination));
								//std::cout << "heap size after insertion: " << heap.GetSize() << '\n';
							}
							//std::cout << "Pathto set \n";
							edge->m_destination->SetPathTo(*edge);
						}
						if (edge->m_destination->GetStatus() == Status::UNVISITED)
						{
							edge->m_destination->SetStatus(Status::LABELLED);
						}
					}
				}
				//std::cout << "minNode status pointer: " << minNode->m_status << '\n';
				minNode->SetStatus(Status::VISITED);
			}
			//std::cout << "heap size at end of while loop: " << heap.GetSize() << '\n';
		}
		std::vector<std::shared_ptr<Edge>> route{};

		auto nextNode = endNode;
		while (nextNode->GetDijkstraComparable() != startNode->GetDijkstraComparable())
		{
			std::cout << "pathTo: " << nextNode->GetPathTo()->m_origin->GetDijkstraComparable()[0]
				<< nextNode->GetPathTo()->m_origin->GetDijkstraComparable()[1]
				<< nextNode->GetPathTo()->m_origin->GetDijkstraComparable()[2] << '\n';

			route.push_back(nextNode->GetPathTo());
			nextNode = std::dynamic_pointer_cast<T>(nextNode->GetPathTo()->m_origin);
			
		}

		std::reverse(route.begin(), route.end());

		return route;
	}
};


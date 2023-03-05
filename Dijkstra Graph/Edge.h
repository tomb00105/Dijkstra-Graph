#pragma once
#include <memory>
#include "DijkstraNode.h"


class Edge
{
public:
	std::shared_ptr<DijkstraNode> m_origin;
	std::shared_ptr<DijkstraNode> m_destination;
	int m_cost;
	bool m_active;

	Edge(std::shared_ptr<DijkstraNode> origin, std::shared_ptr<DijkstraNode> destination, int cost = 1, bool active = true)
		: m_origin{ origin },
		m_destination{ destination },
		m_cost{ cost }, m_active{ active }
	{
		
	};

	Edge(const Edge& edge)
	{
		m_origin = edge.m_origin;
		m_destination = edge.m_destination;
		m_cost = edge.m_cost;
		m_active = edge.m_active;
	}

	~Edge() = default;

	//Operator overloads.
	friend bool operator==(Edge& edge1, Edge& edge2)
	{
		if (edge1.m_cost == edge2.m_cost)
		{
			return true;
		}
		return false;
	}

	friend bool operator>(Edge& edge1, Edge& edge2)
	{
		if (edge1.m_cost > edge2.m_cost)
		{
			return true;
		}
		return false;
	}

	friend bool operator>=(Edge& edge1, Edge& edge2)
	{
		if (edge1.m_cost >= edge2.m_cost)
		{
			return true;
		}
		return false;
	}

	friend bool operator<(Edge& edge1, Edge& edge2)
	{
		if (edge1.m_cost < edge2.m_cost)
		{
			return true;
		}
		return false;
	}

	friend bool operator<=(Edge& edge1, Edge& edge2)
	{
		if (edge1.m_cost <= edge2.m_cost)
		{
			return true;
		}
		return false;
	}

	void SetEdgeStatus(Edge& edge, bool active)
	{
		edge.m_active = active;
	}
};



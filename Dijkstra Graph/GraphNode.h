#pragma once
#include <typeinfo>
#include <vector>
#include "DijkstraNode.h"
#include "Edge.h"


class GraphNode : public DijkstraNode
{
public:
	enum Type
	{
		GRASS,
		DIRT,
		ROAD,
		WATER
	};

private:
	int m_xLocation;
	int m_yLocation;
	int m_zLocation;

	Status m_status;

	std::vector<std::shared_ptr<Edge>> m_edges;

	std::shared_ptr<Edge> m_pathTo{ nullptr };

	int m_priority;

	Type m_type;
	
public:
	GraphNode(const int x, const int y, const int z, Type type)
		: m_xLocation{ x }, m_yLocation{ y }, m_zLocation{ z }, m_type{ type }, 
		m_status{ UNVISITED }, m_priority{ 10000 }, m_pathTo{ nullptr }
	{}

	GraphNode(const GraphNode& node)
	{
		m_xLocation = node.m_xLocation;
		m_yLocation = node.m_yLocation;
		m_zLocation = node.m_zLocation;
		m_status = node.m_status;
		m_priority = node.m_priority;
		m_type = node.m_type;

		m_pathTo = node.m_pathTo;

		m_edges.clear();

		for (std::shared_ptr<Edge> edge : node.m_edges)
		{
			m_edges.push_back(edge);
		}
	}

	GraphNode& operator=(const GraphNode& node)
	{
		m_xLocation = node.m_xLocation;
		m_yLocation = node.m_yLocation;
		m_zLocation = node.m_zLocation;
		m_status = node.m_status;
		m_priority = node.m_priority;
		m_type = node.m_type;

		m_pathTo = node.m_pathTo;

		m_edges.clear();

		for (std::shared_ptr<Edge> edge : node.m_edges)
		{
			m_edges.push_back(edge);
		}
	}

	~GraphNode() = default;
	
	const int GetPriority() const override
	{
		return m_priority;
	}

	Status GetStatus() const override
	{
		return m_status;
	}

	void SetStatus(Status status) override
	{
		m_status = status;
	}

	void SetPriority(int value) override
	{
		m_priority = value;
	}

	std::shared_ptr<Edge> GetPathTo() override
	{
		return m_pathTo;
	}

	void SetPathTo(Edge& edge) override
	{
		m_pathTo = std::make_shared<Edge>(edge);
	}

	void SetNullPath() override
	{
		m_pathTo = nullptr;
	}

	const int GetTypeInt() const override
	{
		return static_cast<int>(m_type);
	}

	void SetTypeInt(int value) override
	{
		m_type = static_cast<Type>(value);
	}

	std::vector<std::shared_ptr<Edge>>& GetEdges() override
	{
		return m_edges;
	}

	//Returns a vector of the location of the node. 
	const std::vector<int> GetDijkstraComparable() const override
	{
		std::vector<int> loc{};
		loc.push_back(m_xLocation);
		loc.push_back(m_yLocation);
		loc.push_back(m_zLocation);
		return loc;
	}

	bool CompareNodes(std::shared_ptr<DijkstraNode> node1, std::shared_ptr<DijkstraNode> node2) const override
	{
		std::vector<int> nodeLocation = GetDijkstraComparable();
		std::vector<int> checkLocation = node2->GetDijkstraComparable();

		auto xDiff{ abs(nodeLocation[0] - checkLocation[0]) };
		auto yDiff{ abs(nodeLocation[1] - checkLocation[1]) };
		auto zDiff{ abs(nodeLocation[2] - checkLocation[2]) };

		if (xDiff <= 1 && zDiff <= 1 && yDiff <= 1)
		{
			if (xDiff + zDiff <= 1)
			{
				return true;
			}
		}
		return false;
	}
	void AddEdge(std::shared_ptr<DijkstraNode> node1, std::shared_ptr<DijkstraNode> node2) override
	{
		int typeInt{ std::dynamic_pointer_cast<GraphNode>(node2)->GetTypeInt() };

		int cost{};

		if (typeInt == GraphNode::GRASS)
		{
			cost = 2;
		}
		else if (typeInt == GraphNode::DIRT)
		{
			cost = 3;
		}
		else if (typeInt == GraphNode::ROAD)
		{
			cost = 1;
		}
		else if (typeInt == GraphNode::WATER)
		{
			cost = 5;
		}

		Edge tempEdge{ node1, node2, cost };

		m_edges.push_back(std::make_shared<Edge>(tempEdge));
	}

	const GraphNode& operator=(const DijkstraNode& node) override
	{
		return dynamic_cast<const GraphNode&>(node);
	}


	//Overloaded operators to use priority to check equivalency.
	bool operator== (const DijkstraNode& node2) override
	{
		
			if (m_priority == node2.GetPriority())
			{
				return true;
			}
		
		else
		{
			//THROW EXCEPTION
		}
		return false;
	}

	
	bool operator> (const DijkstraNode& node2) override
	{
		
			if (m_priority > node2.GetPriority())
			{
				return true;
			}
		
		else
		{
			//THROW EXCEPTION
		}
		return false;
	}
	
	bool operator>= (const DijkstraNode& node2) override
	{
		
			if (m_priority >= node2.GetPriority())
			{
				return true;
			}
		
		else
		{
			//THROW EXCEPTION
		}
		return false;
	}
	
	bool operator< (const DijkstraNode& node2) override
	{

		
			if (m_priority < node2.GetPriority())
			{
				return true;
			}
		
		else
		{
			//THROW EXCEPTION
		}
		return false;
	}
	
	bool operator<= (const DijkstraNode& node2) override
	{
		
			if (m_priority <= node2.GetPriority())
			{
				return true;
			}
		
		else
		{
			//THROW EXCEPTION
		}
		
		return false;
	}
};




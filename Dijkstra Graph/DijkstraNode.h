#pragma once
#include <vector>
#include <memory>
#include "DijkstraStatus.h"

class Edge;

class DijkstraNode
{
public:
	virtual ~DijkstraNode() = 0 {};

	virtual const std::vector<int> GetDijkstraComparable() const = 0;

	virtual bool CompareNodes(std::shared_ptr<DijkstraNode>, std::shared_ptr<DijkstraNode>) const = 0;

	virtual Status GetStatus() const = 0;

	virtual void SetStatus(Status) = 0;

	virtual std::vector<std::shared_ptr<Edge>>& GetEdges() = 0;

	virtual std::shared_ptr<Edge> GetPathTo() = 0;

	virtual void SetPathTo(Edge&) = 0;

	virtual void SetNullPath() = 0;

	virtual const int GetPriority() const = 0 ;

	virtual const int GetTypeInt() const = 0;

	virtual void SetTypeInt(int) = 0;

	virtual void SetPriority(int) = 0;

	virtual void AddEdge(std::shared_ptr<DijkstraNode>, std::shared_ptr<DijkstraNode>) = 0;

	virtual const DijkstraNode& operator=(const DijkstraNode&) = 0;

	virtual bool operator== (const DijkstraNode& node2) = 0;

	virtual bool operator> (const DijkstraNode& node2) = 0;

	virtual bool operator>= (const DijkstraNode& node2) = 0;

	virtual bool operator< (const DijkstraNode& node2) = 0;

	virtual bool operator<= (const DijkstraNode& node2) = 0;
};




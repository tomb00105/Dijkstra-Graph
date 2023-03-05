#include <iostream>
#include <string>
#include <array>
#include <memory>
#include "Graph.h"
#include "GraphNode.h"
#include "MinHeap.h"
#include "Dijkstra.h"
#include "Edge.h"
#include "MemTest.h"

using namespace std;



int main()
{
	int i{ 1 };
	while (i < 6)
	{
		MemTest mem{};
		mem.Test();
		i++;
	}
	

    return 0;
}
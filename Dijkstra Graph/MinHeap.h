#pragma once
#include <vector>
#include <iostream>
#include <concepts>

//Concept to ensure that the types used in the heap can be compared properly.

template <typename T, typename U>
concept hasPriority = requires(T v, U w)
{
	{ v.GetPriority() } -> std::convertible_to<U>;
	v.SetPriority(w);
};

//Templated binary in heap.
template <typename T, typename U>
class MinHeap
{
private:
	std::vector<std::shared_ptr<T>> heapArray;

public:

	//Reserves a certain amount of memory for the vector to ensure memory is contiguous from the start.
	MinHeap() requires(hasPriority<T, U>)
	{
		heapArray.reserve(50);
	}

	//Takes a vector and pushes each item onto the heap. Optionally takes a value (to be implemented).
	MinHeap(std::vector<std::shared_ptr<T>> source, U value) requires(hasPriority<T, U>)
	{
		for (T item : source)
		{
			heapArray.push_back(item);
		}
	}
	//Takes a single item an pushes it on the heap. Optionally takes a value (to be implemented).
	MinHeap(std::shared_ptr<T> source, U value) requires(hasPriority<T, U>)
	{
		heapArray.push_back(source);
	}

	~MinHeap() = default;

	//Returns the number of elements in the heap.
	int GetSize()
	{
		return static_cast<int>(heapArray.size());
	}

	//Returns the parent of the given index in the heap.
	int Parent(int i)
	{
		return (i - 1) / 2;
	}

	//Returns the left sibling of the given index.
	int Left(int i)
	{
		return (2 * i + 1);
	}

	//Return the right sibling of the given index.
	int Right(int i)
	{
		return (2 * i + 2);
	}

	//Takes pointers to two items in the heap and swaps them.
	void Swap(std::shared_ptr<T> x, std::shared_ptr<T> y)
	{
		auto temp = x;
		x = y;
		y = temp;
	}

	//Returns a reference to the first element in the heap.
	std::shared_ptr<T> ExtractMin()
	{
		if (heapArray.size() <= 0)
		{
			//EXCEPTION to be added.
		}
		
		//Sets a reference to the first elements of the heap.
		auto root{ heapArray[0] };

		//If the heap has more than one element, sets the first element to the last element 
		//so the last element can be removed.
		if (heapArray.size() > 1)
		{
			heapArray[0] = heapArray[heapArray.size() - 1];
		}

		//Removes the last (empty element)
		heapArray.pop_back();
		//Heapify the heap.
		MinHeapify(0);

		return root;
	}

	//Decreases the value of a single element in the heap.
	//
	void DecreaseKey(int i, U newValue)
	{
		heapArray[i]->SetPriority(newValue);
		while (i != 0 && &heapArray[Parent(i)] > &heapArray[i])
		{
			Swap(heapArray[i], heapArray[Parent(i)]);
			i = Parent(i);
		}
		
		//Add exception.
	}

	int GetIndex(std::shared_ptr<T> node)
	{
		return static_cast<int>(std::distance(heapArray.begin(), std::find(heapArray.begin(), heapArray.end(), node)));
	}

	std::shared_ptr<T> GetMin()
	{ 
		return heapArray[0]; 
	}

	//Deletes an element of the heap by setting it the lowest value and extracting it.
	void DeleteKey(int i)
	{
		DecreaseKey(i, -100000);
		ExtractMin();
	}

	void InsertKey(std::shared_ptr<T> newKey)
	{
		if (heapArray.size() > 0)
		{
			int i = static_cast<int>(heapArray.size()) - 1;
			heapArray.push_back(newKey);
			while (i != 0 && heapArray[Parent(i)] > heapArray[i])
			{
				//std::cout << "InsertKey() Swap()\n";
				Swap(heapArray[i], heapArray[Parent(i)]);
				i = Parent(i);
			}
		}
		else
		{
			heapArray.push_back(newKey);
		}
	}

	void MinHeapify(int i)
	{
		int l = Left(i);
		int r = Right(i);
		int smallest = i;
		if (l < heapArray.size() && heapArray[l] < heapArray[i])
		{
			smallest = l;
		}
		if (r < heapArray.size() && heapArray[r] < heapArray[smallest])
		{
			smallest = r;
		}
		if (smallest != i)
		{
			Swap(heapArray[i], heapArray[smallest]);
			MinHeapify(smallest);
		}
	}
};
//Author: Mary Hamidi 
#include <iostream>
#include <string>
#include "json.hpp"

#include "priorityqueue.h"

using namespace std; 
using namespace nlohmann;

void MaxPriorityQueue::insert(int key)
{
	if (currSize == max_Size)
		cout << "PriorityQueue::insert called on full priority queue" << endl; 

	else 
	{
		array[currSize + 1] = key; 
		heapifyUp(currSize + 1); 
		currSize++;
	}
}

void MaxPriorityQueue::heapifyUp(int index)
{ 
	for (int child = index; (child > 0) && (array[child] > array[parent(child)]); child = parent(child)) //+ child)
	{
		int temp = 0; 
		temp = array[parent(child)]; 
		array[parent(child)] = array[child]; 
		array[child] = temp; 
	}//keep swapping with parents that are bigger than the current key
}

void  MaxPriorityQueue::removeMax()
{
	if (currSize == 0)
		cout << "PriorityQueue::removeMax called on an empty priority queue" << endl; 
	else
	{
		int temp = 0; 
		temp = array[1]; //max/1st element of heap 
		array[1] = array[currSize]; //swap last element with top 
		array[currSize] = temp;
		--currSize;  
		heapifyDown(1);
	}// "delete" maximum element by putting it in the end of the array and sorting new heap 

}

void MaxPriorityQueue::heapifyDown(int index)
{
	/*int parentIndex = index; 
	while((left(parentIndex) <= currSize) && (right(parentIndex) <= currSize))
	{
		int temp = 0; 
		if (array[left(parentIndex)] > array[parentIndex]) //heapfify down on left subtree
		{
			temp = array[left(parentIndex)]; //Swap 
			array[left(parentIndex)] = array[parentIndex]; 
			array[parentIndex] = temp; 
			parentIndex = left(parentIndex); //update new parent index 
		}
		 else if (array[right(parentIndex)] > array[parentIndex]) //right side is bigger, so heapfiy down on right subtree 
		{
			temp = array[right(parentIndex)];  	//Swap 
			array[right(parentIndex)] = array[parentIndex]; 
			array[parentIndex] = temp; 
			parentIndex = right(parentIndex); 	//update new parent index 
		}
		else 
			break; 
	}*/

	int child;
	int temp = array[index];

	for (; index * 2 <= currSize; index = child) // stop loop when there are no more children in the scope (index * 2)
	{
		child = left(index);

		if (child != currSize && array[child + 1] > array[child]) // if right child > left child, child to swap is right
			child = right(index);

		if (temp < array[child]) // value to be percolated is less than child
			array[index] = array[child];
		else                     // no need to swap
			break;
	}
	array[index] = temp;
}


void  MaxPriorityQueue::removeKey(int key)
{
	int deleteIndex= 0;
	bool found = false;  
	for (int i =0 ; i <= currSize ; i ++)
	{
		if (array[i] == key) //key found
		{
			array[i] = array[currSize]; //delete by overwritting with last element in the heap
			deleteIndex = i; 
			currSize--; 
			found = true; 
			break; 
		}
	}//find the key and remove 

	if (found != true) //key not found 
		cout << "PriorityQueue::removeKey key "<< key << " not found" << endl; 

	else
	{
		if (array[parent(deleteIndex)] < array[deleteIndex] ) //swap with parent, it's larger then new key 
			heapifyUp(deleteIndex); 

		else if ((left(deleteIndex) <= currSize) && (right(deleteIndex) <= currSize)) //index of children is not out if range 
			heapifyDown(deleteIndex); 
	}//sorting the new heap 

}

void  MaxPriorityQueue::change(int key, int newKey)
{
	int changeIndex =0; 
	bool found = false;  
	for (int i =0 ; i <= currSize ; i ++)
	{
		if (array[i] == key) //key found
		{
			array[i] = newKey; //delete by overwritting with last element in the heap
			changeIndex= i; 
			found = true; 
			break; 
		}
	}//Find and replace 

	if (found != true) //key not found 
		cout << "PriorityQueue::change key "<< key << " not found" << endl; 

	else
	{
		if (array[parent(changeIndex)] < array[changeIndex] ) //swap with parent, it's larger then new key 
			heapifyUp(changeIndex); 

		else if ((left(changeIndex) <= currSize) && (right(changeIndex) <= currSize)) //index of children is not out if range 
			heapifyDown(changeIndex); 
	}//sorting the new heap 
}


void MaxPriorityQueue::createJSON() //Outputs every element in the heap (with details about parents and children) into a JSON object 
{
	int leftI = 0; int rightI = 0; int parentI = 0; int key = 0; 

	for(int i = 1; i <= currSize; i++)
	{
		leftI = left(i); 
		rightI = right(i);  
		parentI = parent(i); 
		key = array[i]; 

		string left = to_string(leftI);
		string right= to_string(rightI); 
		string parent = to_string(parentI); 
        string index = to_string(i);
        //string index = prependZeroes(i); 

		jsonObject[index]["key"]= key; 

		if ((parentI >= 1) && (i != 1))
		{
			jsonObject[index]["parent"] = parent ;
		}

		if (leftI <= currSize)
		{
			jsonObject[index]["leftChild"] = left;
		}

		if (rightI <= currSize)
		{
			jsonObject[index]["rightChild"] = right;  
		}

	}

	jsonObject["metadata"]["maxHeapSize"] = max_Size; 
	jsonObject["metadata"]["max_size"] = max_Size; 
	jsonObject["metadata"]["numOperations"] = numOperations; 
	jsonObject["metadata"]["size"] = currSize; 

	string dump = jsonObject.dump(2);
	cout << dump << endl; 
}



void MaxPriorityQueue::printSomething() //for DEBUGGING, call this function to print out priority queue array
{
	for (int j = 1; j <= currSize; j++)
		cout << "array" << j << " " << array[j] << endl; 
}


/*int main()
{

    MaxPriorityQueue heap(6); 

    heap.insert(12);
    heap.insert(10); 
    heap.insert(3);
    heap.insert(20); 
    heap.insert(5); 
    heap.insert(7);

	heap.printSomething();
	heap.createJSON(); 
	return 0;
}*/ 

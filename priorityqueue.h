//Author: Mary Hamidi 
#include "json.hpp"
#include <iostream>
#include <string>

using namespace std; 
using namespace nlohmann;


class MaxPriorityQueue
{
public: 
	MaxPriorityQueue(int size) : max_Size(size),currSize(0) //Constructor 
	{
		array = new int[size + 1];
		for (int j = 1; j <= max_Size; j++)
			array[j] = -1; 
	};

	void insert(int key);
	void removeMax(); 
	void removeKey(int key); 
	void change(int key, int newKey);
	void createJSON();

	void printSomething();			//FOR DEBUGGING 
	void heapifyUp(int index);
	void heapifyDown(int index); 

	int parent(int index)
	{
		int i = 0; 
		if (index == 1 )
			return 1;

		i = (index/2);
		return i;
	}
	int left(int index)
	{
		int i =0; 
		i = (2*index);
		return i;
	}
	int right(int index)
	{
		int i=0; 
		i = (2*index) +1;
		return i; 
	}

	/*string prependZeroes(int i) //prepends zeroes to the string array index to the jsonObject[index] key 
	{

		string howmanyzereos = to_string(max_Size); 

		int maxlength = howmanyzereos.length(); 

		string result = to_string(i);
		int rlength = 0; 
		rlength = result.length(); 

		int numzeroes = maxlength - rlength; 

		for (int l=1; l <=numzeroes ; l++ )
		{
			result = "0" + result; 
		}
 		
 		return result; 
	}*/

	json jsonObject;
	int max_Size; 
    int currSize;
	int *array;
	int numOperations;
};

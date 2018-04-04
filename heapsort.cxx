//Author: Mary Hamidi 
#include <iostream>
#include <fstream>
#include <string>

#include "json.hpp"
#include "priorityqueue.h"

using namespace std; 
using namespace nlohmann;


int main(int argc, char** argv) {
 
	std::ifstream file;
	file.open(argv[1]);
	nlohmann::json jsonObject;
	// Store the contents filename into jsonObject
	if (file.is_open()) {
	  file >> jsonObject;
	}
		
	string fileName;
	fileName.append(argv[1]);

	json newObject; // Object to output sorted arrays 


	newObject["metadata"]["arraySize"] = jsonObject["metadata"]["arraySize"];
	newObject["metadata"]["numSamples"] = jsonObject["metadata"]["numSamples"];  

	string sampleName; 

	int max = jsonObject["metadata"]["arraySize"];

	for (auto itr = jsonObject.begin(); itr != (--jsonObject.end()); ++itr)
	{ //iterates through every Sample[]
		sampleName = itr.key(); 

		json currSample; 

		MaxPriorityQueue heap(max); //Declare priority queue object 

		for (auto arrayItr = jsonObject[sampleName].begin(); arrayItr != jsonObject[sampleName].end(); ++arrayItr) 
	  { //iterates through every element in array       
	      int val = *arrayItr;
	  		heap.insert(val); 
		}

		while (heap.currSize != 0)
		{
			heap.removeMax(); // reapeatdly removing max element and inserting in the end of heap 
		}//sample array is sorted 

		for (int j = 1; j <= heap.max_Size; j++)
		{
			currSample.push_back(heap.array[j]);
		}//pushing onto json array

		newObject[sampleName]= currSample;
	}

	string dump = newObject.dump(4);
	cout << dump << endl; //Outputing sorted arrays and json in a easy to read way 

}
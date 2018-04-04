//Author: Mary Hamidi 
#include <iostream>
#include <fstream>
#include <string>

#include "json.hpp"
#include "priorityqueue.h"

using namespace std; 
using namespace nlohmann;

int main(int argc, char** argv) 
{
	std::ifstream file;
	file.open(argv[1]);
	nlohmann::json jsonObject;
	// Store the contents filename into jsonObject
	if (file.is_open()) {
	  file >> jsonObject;
	}
		
	string fileName;
	fileName.append(argv[1]);

	int key =0; 
	int newkey =0; 
	string opnum; 

	int max = jsonObject["metadata"]["maxHeapSize"]; 
	MaxPriorityQueue heap(max); 

	heap.numOperations = jsonObject["metadata"]["numOperations"]; 

	for (auto itr = jsonObject.begin(); itr != (--jsonObject.end()); ++itr)
	{//every operation
		opnum = itr.key();

		if(jsonObject[opnum]["operation"] != "removeMax")
		{
			key = jsonObject[opnum]["key"]; 

			if (jsonObject[opnum]["operation"] == "insert")
			{
				heap.insert(key); 
            }
			else if (jsonObject[opnum]["operation"] == "change")
			{
				newkey = jsonObject[opnum]["newKey"];
				heap.change(key,newkey); 
			}
			else 
			{
				if (jsonObject[opnum]["operation"] == "removeKey")
			      	heap.removeKey(key);
			}
		}

		else if (jsonObject[opnum]["operation"] == "removeMax")
			heap.removeMax(); 

		else
		{
			cout <<"Operation does not exist. Usage: insert, change, removeKey, removeMax" << endl; 
		}
	}

	heap.createJSON();  //outputing newObject 
}
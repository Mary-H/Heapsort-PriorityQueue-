#include <cstdio>
#include <iostream>
#include <random>
#include <set>
#include <string>

#include "json.hpp"

typedef unsigned int 		Key;

Key createKey(std::mt19937_64& rng, std::set<Key>& insertedKeys);
Key findKey(std::mt19937_64& rng, std::set<Key>& insertedKeys);

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Usage: %s numOperations maxHeapSize\n", argv[0]);
		return EXIT_FAILURE;
	}
	unsigned int numOperations = 0, maxHeapSize = 0;
	if (sscanf(argv[1], "%u", &numOperations) != 1 || sscanf(argv[2], "%u", &maxHeapSize) != 1) {
		printf("numOperations and maxHeapSize must be positive integers\n");
		return EXIT_FAILURE;
	}

	nlohmann::json samples;
	std::set<Key> insertedKeys;
	size_t initialInserts = std::min(maxHeapSize, numOperations) / 2;
	size_t minHeapSize = 1 + maxHeapSize / 4;
	samples["metadata"]["numOperations"] = numOperations;
	samples["metadata"]["maxHeapSize"] = maxHeapSize;

	// C++11 random number tutorial: https://gist.github.com/PhDP/5289449
	// Seed random number generator
	std::random_device rd;
	std::mt19937_64 rng(rd());
	// Create distributions
	enum class HeapOperation { insert, removeMax, removeKey, change };
	std::uniform_int_distribution<int> opDist(0, 3);

	unsigned int totalZeros = (int) floor(log10((double) numOperations)) + 1;
	for (unsigned int op = 1; op <= numOperations; op++) {
		int opZeros =  (int) floor(log10((double) op)) + 1;
		std::string opNum = std::string(totalZeros - opZeros, '0').append(std::to_string(op));
		nlohmann::json newOp;
		// Add random integer to array
		HeapOperation operation =
			((op < initialInserts) ? HeapOperation::insert : (HeapOperation) opDist(rng));
		switch (operation) {
			case HeapOperation::insert:
				if (insertedKeys.size() < maxHeapSize) {
					newOp["operation"] = "insert";
					Key key = createKey(rng, insertedKeys);
					newOp["key"] = key;
					insertedKeys.insert(key);
					break;
				}
			case HeapOperation::removeMax:
				if (insertedKeys.size() > minHeapSize) {
					newOp["operation"] = "removeMax";
					insertedKeys.erase(--insertedKeys.end());
					break;
				}
			case HeapOperation::removeKey:
				if (insertedKeys.size() > minHeapSize) {
					newOp["operation"] = "removeKey";
					Key key = findKey(rng, insertedKeys);
					newOp["key"] = key;
					insertedKeys.erase(insertedKeys.find(key));
					break;
				}
			case HeapOperation::change:
				if (insertedKeys.size() > 1) {
					newOp["operation"] = "change";
					Key key = findKey(rng, insertedKeys);
					newOp["key"] = key;
					insertedKeys.erase(insertedKeys.find(key));
					Key newKey = createKey(rng, insertedKeys);
					newOp["newKey"] = newKey;
					insertedKeys.insert(newKey);
					break;
				}
			default:
				op--;
				continue;
		}
		samples["Op" + opNum] = newOp;
	}
	std::cout << samples.dump(2) << std::endl;
	return EXIT_SUCCESS;
}

Key createKey(std::mt19937_64& rng, std::set<Key>& insertedKeys) {
	std::uniform_int_distribution<Key> keyDist(0, 5000);
	while (true) {
		Key key = keyDist(rng);
		if (insertedKeys.count(key) == 0) {
			return key;
		}
	}
}

Key findKey(std::mt19937_64& rng, std::set<Key>& insertedKeys) {
	std::uniform_int_distribution<int> unifDist(0, 100);
	if (insertedKeys.empty()) {
		std::cerr << "findKey: called on empty set" << std::endl;
		exit(EXIT_FAILURE);
	}
	auto itr = insertedKeys.begin();
	while (true) {
		if (++itr == insertedKeys.end()) {
			itr = insertedKeys.begin();
		}
		if (unifDist(rng) < 500) {
			return *itr;
		}
	}
}
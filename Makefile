CC=g++
DEV=-Wall -g -std=c++14
OPT=-O3 -std=c++14

JSON=json.hpp

CREATE_DATA_SRC=createsortingdata.cxx createheapoperationdata.cxx
CREATE_DATA_EXE=$(CREATE_DATA_SRC:.cxx=.exe)

PRIORITYQUEUE_SRC=priorityqueue.cpp
PRIORITYQUEUE_HDR=$(PRIORITYQUEUE_SRC:.cpp=.h)
PRIORITYQUEUE_DEV_OBJ=$(PRIORITYQUEUE_SRC:.cpp=.o)
PRIORITYQUEUE_OPT_OBJ=$(PRIORITYQUEUE_SRC:.cpp=.o3)

HEAPSORT_EXE_SRC=heapsort.cxx
HEAPSORT_EXE=$(HEAPSORT_EXE_SRC:.cxx=.exe)

BUILDHEAP_EXE_SRC=buildheap.cxx
BUILDHEAP_EXE=$(BUILDHEAP_EXE_SRC:.cxx=.exe)

.PHONY: all
all: priorityqueue_lib $(HEAPSORT_EXE) $(CREATE_DATA_EXE) $(BUILDHEAP_EXE)

.PHONY: $(PRIORITYQUEUE_LIB)
priorityqueue_lib: $(PRIORITYQUEUE_DEV_OBJ) $(PRIORITYQUEUE_OPT_OBJ)

$(PRIORITYQUEUE_DEV_OBJ): %.o: %.cpp %.h
	$(CC) $(DEV) -c $< -o $@

$(PRIORITYQUEUE_OPT_OBJ): %.o3: %.cpp %.h
	$(CC) $(DEV) -c $< -o $@

# EXECUTABLES ------------------------------------

$(HEAPSORT_EXE): %.exe: %.cxx $(PRIORITYQUEUE_OPT_OBJ) 
	$(CC) $(DEV) $^ -o $@

$(BUILDHEAP_EXE): %.exe: %.cxx $(PRIORITYQUEUE_OPT_OBJ)
	$(CC) $(DEV) $^ -o $@

$(CREATE_DATA_EXE): %.exe: %.cxx $(JSON)
	$(CC) $(OPT) $< -o $@


# Build
.PHONY: clean
clean:
	rm -f *.o
	rm -f *.o3
	rm -f *.exe
	rm -f *.out
	rm -rf *.exe.dSYM

.PHONY: update
update:
	make clean
	make all
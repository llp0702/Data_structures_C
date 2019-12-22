CC=gcc
CFLAGS = -g -Wall -O3
COMPIL = $(CC) $(CFLAGS)
SRC_TREES= src/trees/heap.c src/trees/btrees.c src/trees/bSTrees.c src/trees/bAVLTress.c
OBJ_TREES = $(SRC_TREES:.c=.o) 
SRC_LISTS =  src/lists/lists.c src/lists/stacks.c src/lists/queues.c 
OBJ_LISTS =$(SRC_LISTS:.c=.o)
SRC_GRAPHS = src/graphs/graph.c
OBJ_GRAPHS =$(SRC_GRAPHS:.c=.o)
SRC_HASHT = src/hashTables/ht.c
OBJ_HASHT =$(SRC_HASHT:.c=.o)
SRC_TST_GRAPHS = src/tests/graphs/fordFulkerson.c src/tests/graphs/dijkstraSmallestTarget.c src/tests/graphs/generateRandomGraph.c src/tests/graphs/containsGraphCycle.c src/tests/graphs/drawgraph.c src/tests/graphs/browseGraphDepth.c src/tests/graphs/browseGraphWidth.c
OBJ_TST_GRAPHS = $(SRC_TST_GRAPHS:.c=.o)
SRC_TST_TREES = src/tests/trees/testHeap.c src/tests/trees/generateRandomBAVLTree src/tests/trees/generateRandomBSTree.c src/tests/trees/drawBtree.c
OBJ_TST_TREES = $(SRC_TST_TREES:.c=.o)
SRC_TST_HASHT = src/tests/hashTables/testHt.c
OBJ_TST_HASHT = $(SRC_TST_HASHT:.c=.o)
SRC_TST = $(SRC_TST_GRAPHS) $(SRC_TST_TREES) $(SRC_TST_HASHT)
OBJ_TST = $(OBJ_TST_GRAPHS) $(OBJ_TST_TREES) $(OBJ_TST_HASHT)
OBJ =  $(OBJ_GRAPHS) $(OBJ_LISTS) $(OBJ_TREES) $(OBJ_HASHT)
EXEC_GRAPHS = bin/graphs/fordFulkerson bin/graphs/dijkstraSmallestTarget bin/graphs/generateRandomGraph bin/graphs/containsGraphCycle bin/graphs/drawgraph bin/graphs/browseGraphDepth bin/graphs/browseGraphWidth
EXEC_TREES = bin/trees/testHeap bin/trees/generateRandomBAVLTree bin/trees/generateRandomBSTree bin/trees/drawBtree
EXEC_HASHT = bin/hashTables/testHt
EXEC = $(EXEC_GRAPHS) $(EXEC_TREES) $(EXEC_HASHT)
all: $(EXEC)

bin/graphs/generateRandomGraph : src/tests/graphs/generateRandomGraph.o $(OBJ)
	$(COMPIL) $^ -o $@
bin/graphs/containsGraphCycle : src/tests/graphs/containsGraphCycle.o $(OBJ)
	$(COMPIL) $^ -o $@
bin/graphs/drawgraph : src/tests/graphs/drawgraph.o $(OBJ)
	$(COMPIL) $^ -o $@ 
bin/graphs/browseGraphDepth : src/tests/graphs/browseGraphDepth.o $(OBJ) 
	$(COMPIL) $^ -o $@
bin/graphs/browseGraphWidth : src/tests/graphs/browseGraphWidth.o $(OBJ) 
	$(COMPIL) $^ -o $@
bin/graphs/dijkstraSmallestTarget : src/tests/graphs/dijkstraSmallestTarget.o $(OBJ)
	$(COMPIL) $^ -o $@
bin/graphs/fordFulkerson : src/tests/graphs/fordFulkerson.o $(OBJ)
	$(COMPIL) $^ -o $@

bin/trees/generateRandomBSTree : src/tests/trees/generateRandomBSTree.o $(OBJ)
	$(COMPIL) $^ -o $@
bin/trees/drawBtree : src/tests/trees/drawBtree.o $(OBJ)
	$(COMPIL) $^ -o $@
bin/trees/generateRandomBAVLTree : src/tests/trees/generateRandomBAVLTree.o $(OBJ)
	$(COMPIL) $^ -o $@
bin/trees/testHeap : src/tests/trees/testHeap.o $(OBJ)
	$(COMPIL) $^ -o $@

bin/hashTables/testHt : src/tests/hashTables/testHt.o $(OBJ)
	$(COMPIL) $^ -o $@


%.o : %.c
	$(COMPIL) -c $^ -o $@

clean:
	@find ./ -name "*.o" -delete 
.PHONY: clean
# Ideas for Efficiency and Completion

* Is there a way to avoid committing the graph to memory?
* Is a dictionary the best for storing the graph, if we must store it?
* Can we avoid storing an edge twice? (a, b) and (b, a) for example. The current input implementation only stores an edge once.
* If we do the heuristic track, how important is finding the best solution versus find any solution?

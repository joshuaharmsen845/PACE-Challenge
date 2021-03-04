# Ideas for Efficiency and Completion

* Is there a way to avoid committing the graph to memory?
* Is a dictionary the best for storing the graph, if we must store it?
* Can we avoid storing an edge twice? (a, b) and (b, a) for example. The current input implementation only stores an edge once.
* If we do the heuristic track, how important is finding the best solution versus find any solution?
* Is the file input actually done correctly? Or should we just read from std in?
* Should we even use python?
* If # edges < # vertices ^ (# vertices), can we just cut the edges to find a simple cluster editing with no edges?
* Can we speed up file reading by not having to compare key to "p" for every line?
* What type is most memory efficient?
* Profiling memory with the built in python module would be advantageous in future.

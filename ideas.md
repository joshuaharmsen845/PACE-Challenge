# Ideas for Efficiency and Completion

* Is there a way to avoid committing the graph to memory?
* Is a dictionary the best for storing the graph, if we must store it?
* Can we avoid storing an edge twice? (a, b) and (b, a) for example. The current input implementation only stores an edge once.
* If we do the heuristic track, how important is finding the best solution versus find any solution?
  * it looks like most algorithms, even ones going for perfect solutions have timeout issues so it might be preferable to just find the quickest solution
* Is the file input actually done correctly? Or should we just read from std in?
* Should we even use python?
* If # edges < # vertices ^ (# vertices), can we just cut the edges to find a simple cluster editing with no edges?
* Can we speed up file reading by not having to compare key to "p" for every line?
* What type is most memory efficient?
* Profiling memory with the built in python module would be advantageous in future.
* Look into using conflict triples, it's the idea that three nodes will always be in a clique besides the one case where two are connected to one other node but not eachother
  * using this maybe a quick way to identify where to cut and make smaller connected segments like the bridge search
* Optimal solution never connects unconnected components
* branching strategy - uses the conflict triples in the one case where they are not cliqued and tries both one deletion and one addition to see which is faster for the overall graph
* almost-clique rule - preliminary search looking for nodes that are 1-2 additions or deletions from being a clique
* limiting search space - vertices at a distance of more than three away are almost never going to be part of the same clique in the mpst efficient solution
* potentially mark certain edges as unmoddifiable because they are parts of cliques to avoid accidently messing with them
* using parrellel threads to check multiple cases at once, is this possible on python? on our computers?
* Limiting timeouts needs to be a big priority since it is better to find a solution then to have none

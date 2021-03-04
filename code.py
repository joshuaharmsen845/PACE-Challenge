# Main PACE Challenge Code

import fileinput

# GLOBALS
vertices = 0
edges = 0

# DIMACS-like .gr file as input (see heur00x.gr or ez-input.gr)
# readIn(): Puts the input file into a dictionary as we have done in CS123
# Also writes the number of vertices and edges to global variables
# Returns graph as a dictionary
def readIn():
    global vertices
    global edges
    graph = {}
    for line in fileinput.input():
        row = line.rstrip().split(" ")
        key = row[0]
        if key != "c" and key != "p": #If we have a data line...
                if int(key) in graph: #Create new key or update old one
                    graph[int(key)].append(row[1])
                else:
                    graph[int(key)] = [int(row[1])]
        elif key == "p":
            vertices = row[2]
            edges = row[3]
    return graph


def main():
    graph = readIn()
    print(graph)
    print("with", vertices, "vertices")
    print("with", edges, "edges")


main()

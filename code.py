# Main PACE Challenge Code

import fileinput

#DIMACS-like .gr file as input (see heur00x.gr or ez-input.gr)
#readIn(): Puts the input file into a dictionary as we have done in CS123
def readIn():
    graph = {}
    for line in fileinput.input():
        row = line.rstrip().split(" ")
        print(row)
        key = row[0]
        if key != "c" and key != "p": #If we have a data line...
                if int(key) in graph: #Create new key or update old one
                    graph[int(key)].append(row[1])
                else:
                    graph[int(key)] = [int(row[1])]
    return graph


def main():
    graph = readIn()
    print(graph)


main()

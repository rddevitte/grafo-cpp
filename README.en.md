# Graph in C++

This is a small project of mine from some years ago, in C++ language, which I made while studying
about graphs.

Basically, the code implements the undirected graph of the pic below, do the visiting on its nodes
by Breadth- (BFS) and Depth-First Search (DFS) algorithms, list the components of the graph and
its vertices and applies the Shortest Path Algorithm (aka &ldquo;Dijkstra's Algorithm&rdquo;).

![Undirected graph](https://raw.githubusercontent.com/rddevitte/grafo-cpp/master/graph.svg)

## Build

Assuming you already have CMake 3.16 or later installed, run the `./build` script.

## Run executable

After building, run `./_build/grafo-cpp`.

## Clean

Just do `rm -r _build`.

## Build and run (Docker)

Assuming the Docker engine has been already installed, just run the `./docker-build-and-run` script.

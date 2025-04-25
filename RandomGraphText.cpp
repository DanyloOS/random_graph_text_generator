#include "RandomGraphText.h"

#include <algorithm>
#include <set>
#include <vector>
#include <list>
#include <sstream>
#include <numeric>
#include <random>
#include <fstream>

using namespace std;

void RandomGraphText::generateRandomGraph_new(int vertexesNumber, int edgesNumber, std::ofstream file) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, vertexesNumber - 1);

    std::set<std::pair<int, int>> generatedEdges;

    while (edgesNumber > 0) {
        int a = distrib(gen);
        int b = distrib(gen);

        // Avoid loops and duplicates
        if (a == b) continue;
        auto edge = std::minmax(a, b);
        if (generatedEdges.count(edge)) continue;

        generatedEdges.insert(edge);

        file << "w" << edge.first + 1 << " w" << edge.second + 1 << ".";
        if (--edgesNumber > 0) file << " ";
    }

    file.close();
}


void RandomGraphText::generateRandomGraph(int vertexesNumber, int edgesNumber, std::ofstream file)
{
    // PROFILE_ME; // Macro or function for profiling the method's performance.

    // Create a random number generator seeded with a random device
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define a uniform integer distribution for vertex selection
    std::uniform_int_distribution<> row_distrib(0, vertexesNumber - 1);

    // Create a vector of lists to represent the adjacency list of the graph
    std::vector<list<int>> graph(vertexesNumber);

    // Open an output file to store the generated random graph


    // Initialize the graph by filling each vertex's adjacency list with potential edges
    for (int i = 0; i < vertexesNumber; i++) {
        graph[i].resize(i); // Resize the list to hold `i` elements
        iota(graph[i].begin(), graph[i].end(), 1); // Fill the list with sequential numbers starting from 1
    }

    // Randomly generate edges until the desired number of edges is created
    while (edgesNumber > 0) {
        int row = row_distrib(gen); // Randomly select a vertex (row)
        list<int>& row_list = graph[row]; // Get the adjacency list for the selected vertex

        if (row_list.size()) {
            std::stringstream outText;
            // If the adjacency list is not empty
            // Define a uniform integer distribution for edge selection from the adjacency list
            std::uniform_int_distribution<> col_distrib(0, row_list.size() - 1);
            int col = col_distrib(gen); // Randomly select an edge (column)

            // Get an iterator to the selected edge in the adjacency list
            auto listIter = row_list.begin();
            advance(listIter, col); // Move the iterator to the selected position

            outText << "w" << row + 1 << " w" << *listIter << ".";


            // Remove the selected edge from the adjacency list to avoid duplicates
            row_list.erase(listIter);

            // Decrease the number of edges left to generate
            edgesNumber--;
            if (edgesNumber != 0)
                outText << " ";

            file << outText.str();
        }
    }


    file.close();
    // Close the output file
}

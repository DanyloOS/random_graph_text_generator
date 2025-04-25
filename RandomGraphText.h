#ifndef RANDOMGRAPHTEXT_H
#define RANDOMGRAPHTEXT_H

#include <fstream>

class RandomGraphText
{
public:
    RandomGraphText() = delete;
    static void generateRandomGraph(int vertexesNumber, int edgesNumber, std::ofstream file);
    static void generateRandomGraph_new(int vertexesNumber, int edgesNumber, std::ofstream file);
};

#endif // RANDOMGRAPHTEXT_H

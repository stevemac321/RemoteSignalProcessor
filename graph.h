
#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "common.h"
#include <cstdint>
#include <cstdlib>
#include <array>
#include <iostream>

// Define the Color enumeration used in graph traversal
enum Color : uint32_t {
    WHITE = 0x00000000,  // No color (default)
    GRAY  = 0x40000000,  // 01 in the MSBs (used in graph traversal)
    BLACK = 0x80000000   // 10 in the MSBs (used in graph traversal)
};


// Template class for the Graph
template <size_t Capacity>
class Graph {
public:
    // Define the Vertex structure within the Graph template class
    struct Vertex {
        float magnitude;    // Magnitude value (or other related data)
        Color color;        // Color used in graph traversal
        int distance;       // Distance from source vertex
        int parent;         // Parent vertex in traversal
        uint32_t adjList;   // 32-bit adjacency list bit vector
    };

    // Constructor to initialize graph properties
    Graph() : numVertices(0) {}

    // Add a vertex with a specified magnitude
    void addVertex(float mag) {
        if (numVertices >= Capacity) {
            std::cerr << "Graph is at full capacity, cannot add more vertices.\n";
            return;
        }
        vertices[numVertices].magnitude = mag;
        vertices[numVertices].color = Color::WHITE;
        vertices[numVertices].distance = 0;
        vertices[numVertices].parent = -1;
        vertices[numVertices].adjList = 0;  // No edges initially
        ++numVertices;
    }

    // Add an edge between two vertices
    void addEdge(size_t v, size_t w) {
        if (v >= numVertices || w >= numVertices) {
            std::cerr << "Invalid vertex index, cannot add edge.\n";
            return;
        }
        vertices[v].adjList |= (1 << (w % Capacity));
    }

    // Get the number of vertices in the graph
    size_t getNumVertices() const {
        return numVertices;
    }

    // Print the graph (for debugging purposes)
    void printGraph() const {
        for (size_t i = 0; i < numVertices; ++i) {
            std::cout << "Vertex " << i << " (Magnitude: " << vertices[i].magnitude << ") -> ";
            for (size_t j = 0; j < numVertices; ++j) {
                if (vertices[i].adjList & (1 << j)) {
                    std::cout << j << " ";
                }
            }
            std::cout << "\n";
        }
    }

    // Access a vertex by index
    Vertex& operator[](size_t index) {
        return vertices[index];
    }

    const Vertex& operator[](size_t index) const {
        return vertices[index];
    }

private:
    std::array<Vertex, Capacity> vertices;  // Array of vertices
    size_t numVertices;                     // Current number of vertices in the graph
};
// Function to analyze results and construct a graph from the priority queue
template <size_t Capacity>
Graph<Capacity> analyze_results(std::priority_queue<float, std::vector<float>, std::greater<float>> &pq) {
    // Create a new graph with the specified capacity
    Graph<Capacity> graph;

    // Add vertices to the graph from the priority queue
    while (!pq.empty()) {
        float magnitude = pq.top();
        graph.addVertex(magnitude);
        pq.pop();
    }

    // Analyze the graph to identify peaks and valleys
    for (size_t i = 1; i < graph.getNumVertices() - 1; ++i) {
        float prev_val = graph[i - 1].magnitude;
        float curr_val = graph[i].magnitude;
        float next_val = graph[i + 1].magnitude;

        // Check for peak
        if (curr_val > prev_val && curr_val > next_val) {
            // Add edges between current peak and its neighbors
            graph.addEdge(i, i - 1);
            graph.addEdge(i, i + 1);
        }
        // Check for valley
        else if (curr_val < prev_val && curr_val < next_val) {
            // Add edges between current valley and its neighbors
            graph.addEdge(i, i - 1);
            graph.addEdge(i, i + 1);
        }
    }

    // Return the constructed graph
    return graph;
}

#endif // GRAPH_HPP

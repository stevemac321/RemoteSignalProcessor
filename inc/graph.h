#ifndef GRAPH_H
#define GRAPH_H

#include <ncurses.h>
#include <vector>
#include <complex>
#include <array>

// Define the Color enumeration used in graph traversal
enum Color : uint32_t {
    WHITE = 0x00000000,  // No color (default)
    GRAY = 0x40000000,  // 01 in the MSBs (used in graph traversal)
    BLACK = 0x80000000   // 10 in the MSBs (used in graph traversal)
};

// Template class for the Graph
template <size_t Capacity>
class Graph {
public:
    // Define the Vertex structure within the Graph template class
    struct Vertex {
        float magnitude = 0;    // Magnitude value (or other related data)
        Color color = Color::WHITE;        // Color used in graph traversal
        int distance = 0;       // Distance from source vertex
        int parent = -1;         // Parent vertex in traversal
    };

    // Constructor to initialize graph properties
    Graph() : numVertices(0) {
        // Initialize adjacency matrix to zero
        for (size_t i = 0; i < Capacity; ++i) {
            adjMatrix[i].fill(0);
        }
    }

    // Add a vertex with a specified magnitude
    void addVertex(float mag) {
        if (numVertices >= Capacity) {
            return;
        }
        vertices[numVertices].magnitude = mag;
        vertices[numVertices].color = Color::WHITE;
        vertices[numVertices].distance = 0;
        vertices[numVertices].parent = -1;
        ++numVertices;
    }

    // Add an edge between two vertices using the adjacency matrix
    void addEdge(size_t v, size_t w) {
        
        if (v >= numVertices || w >= numVertices) {
            return;
        }
        adjMatrix[v][w] = 1;  // Set the value in the adjacency matrix
    }

    // Get the number of vertices in the graph
    size_t getNumVertices() const {
        return numVertices;
    }

    // Print the graph as a 32x32 adjacency matrix
    void printGraph(WINDOW* win, const std::vector<float> &magnitudes) const {
        int start_column = 1;
        for (size_t i = 0; i < numVertices; ++i) {
            // Print row label (vertex index and magnitude)
            mvwprintw(win, i + 1, start_column, "Vertex %2zu (Mag: %.2f): ", i, magnitudes[i]);

            // Print each value in the adjacency matrix (0 or 1)
            for (size_t j = 0; j < numVertices; ++j) {
                mvwprintw(win, i + 1, start_column + 40 + j * 2, "%d", adjMatrix[i][j]);
            }
        }
        wrefresh(win);
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
    std::array<std::array<int, Capacity>, Capacity> adjMatrix;  // 2D array for adjacency matrix
    size_t numVertices;                     // Current number of vertices in the graph
    int debug_row = 1;
};

// Function to analyze results and construct a graph from the priority queue
template <size_t Capacity>
Graph<Capacity> analyze_results(const std::vector<std::complex<float>>& complex_data) {
    // Create a new graph with the specified capacity
    Graph<Capacity> graph;

    // Check if the complex data has sufficient size
    if (complex_data.size() < Capacity) {
        return graph;
    }

    // Populate the graph vertices with real values from complex data
    for (size_t i = 0; i < Capacity; ++i) {
        graph.addVertex(complex_data[i].real()); // Use real part of complex data for vertex magnitude
    }

    // Analyze the graph to identify peaks and valleys
    for (size_t i = 1; i < graph.getNumVertices() - 1; ++i) {
        float prev_val = graph[i - 1].magnitude;
        float curr_val = graph[i].magnitude;
        float next_val = graph[i + 1].magnitude;

        // Check for peak (no tolerance, just direct comparison)
        if (curr_val > prev_val && curr_val > next_val) {
            // Add edges between current peak and its neighbors
            graph.addEdge(i, i - 1);
            graph.addEdge(i, i + 1);
        }
        // Check for valley (no tolerance, just direct comparison)
        else if (curr_val < prev_val && curr_val < next_val) {
            // Add edges between current valley and its neighbors
            graph.addEdge(i, i - 1);
            graph.addEdge(i, i + 1);
        }
    }

    // Return the constructed graph without additional debug output
    return graph;
}

#endif // GRAPH_HPP

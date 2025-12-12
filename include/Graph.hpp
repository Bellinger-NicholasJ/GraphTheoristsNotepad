/* Graph Theorist's Notepad
    Copyright (c) 2025 Nicholas Bellinger
    Licensed under the "Graph Theorist's Notepad, Nicholas Bellinger, Non-Commercial License 1.0".
    See the LICENSE file in the project root for full details. */

#ifndef GRAPH_HPP
#define GRAPH_HPP

/// @brief A vertex of a graph.
typedef struct vertex {
    /// @brief The name of the vertex.
    std::string Name;

    /// @brief The position of the vertex.
    sf::Vector2f Position;

    /// @brief The sprite of the vertex.
    sf::CircleShape Sprite;

    /// @brief The color of the vertex for vertex coloring algorithms, not for graphics.
    int VertexColor;
} Vertex;

/// @brief An edge of a graph.
typedef struct edge {
    /// @brief A reference to the first vertex of the edge.
    Vertex *Vertex1;

    /// @brief A reference to the second vertex of the edge.
    Vertex *Vertex2;

    /// @brief The weight value of the edge.
    float Weight;

    /// @brief The sprite of the edge.
    sf::RectangleShape Sprite;
} Edge;

/// @brief A graph obj, storing vertices and edges.
class Graph {
    public:
        /** 
         * @brief Creates a graph obj.
         * @param isDirected Is this a directed graph?
        */
        Graph(bool isDirected = false);

        /**
         * @brief Add a edge to the graph.
         * @param v1 A reference to the first vertex of the edge.
         * @param v2 A reference to the second vertex of the edge.
         * @param weight The weight value of the edge.
         */
        void AddEdge(Vertex& v1, Vertex& v2, float weight);

        /**
         * @brief Adds a vertex to the graph.
         * @param name The name of the vertex.
         * @param position The position of the vertex.
         */
        void AddVertex(std::string name, sf::Vector2f position);

        /**
         * @brief Calculate if the graph is bipartite.
         * @return True if the graph is bipartite, false otherwise.
         */
        bool CalculateBipartite(void);

        /**
         * @brief Calculate the number of spanning trees in the graph.
         * @return The number of spanning trees.
         */
        int CalculateNumberOfSpanningTrees(void);

        /**
         * @brief Draw the graph.
         * @param window A pointer to the window being drawn on.
         */
        void Draw(sf::RenderWindow *window);

        /**
         * @brief Get the list of vertices.
         * @return A reference to the list of vertices.
         */
        std::vector<Vertex>& GetVertices(void);

        /**
         * @brief Get the vertex at the mouse position.
         * @param window A pointer to the window being drawn on.
         * @return A pointer to the vertex at the mouse position, or nullptr if none.
         */
        Vertex* GetVertexAtMouse(sf::RenderWindow *window);

        /**
         * @brief Remove a vertex from the graph.
         * @param n The index of the vertex to remove.
         * @return The removed vertex.
         */
        Vertex RemoveVertex(int n);

        /// @brief Is this graph currently active?
        bool IsActive;

        /// @brief The adjacency matrix of the graph.
        std::vector<std::vector<float>> AdjacencyMatrix;

        /// @brief The color of the graph.
        sf::Color Color;

        /// @brief The name of the graph.
        std::string Name;

    private:
        /**
         * @brief A helper to draw an edge.
         * @param window A pointer to the window being drawn on.
         * @param edge A reference to the edge being drawn.
         */
        void drawEdge(sf::RenderWindow *window, Edge& edge);

        /**
         * @brief A helper to draw a vertex.
         * @param window A pointer to the window being drawn on.
         * @param vertex A reference to the vertex being drawn.
         */
        void drawVertex(sf::RenderWindow *window, Vertex& vertex);

        /// @brief A list of edges of the graph.
        std::vector<Edge> m_edges;

        /// @brief Is this graph directed?
        bool m_isDirected;

        /// @brief A list of vertices of the graph.
        std::vector<Vertex> m_vertices;
};

#endif
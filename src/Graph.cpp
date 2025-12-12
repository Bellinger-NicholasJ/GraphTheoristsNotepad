/* Graph Theorist's Notepad
    Copyright (c) 2025 Nicholas Bellinger
    Licensed under the "Graph Theorist's Notepad, Nicholas Bellinger, Non-Commercial License 1.0".
    See the LICENSE file in the project root for full details. */

#include "pch.hpp"
#include "Graph.hpp"

Graph::Graph(bool isDirected) {
    m_isDirected = isDirected;
    IsActive = false;
    Color = sf::Color::Black;
    Name = "";
}

void Graph::AddVertex(std::string name, sf::Vector2f position) {
    // Create a new vertex.
    Vertex newVertex = { name, position, sf::CircleShape() };
    newVertex.Sprite.setOutlineColor(Color);
    newVertex.Sprite.setOutlineThickness(2.0f);
    newVertex.VertexColor = 0;
    std::cout << "Added vertex: " << name << " at position (" << position.x << ", " << position.y << ")" << std::endl;

    // Add vertex to the list.
    m_vertices.push_back(newVertex);

    // Keep adjacency matrix square and in-bounds
    const std::size_t n = m_vertices.size();

    // Update adjacency matrix size.
    AdjacencyMatrix.resize(n);

    for (auto& row : AdjacencyMatrix) {
        row.resize(n, 0.0f);
    }
}

void Graph::AddEdge(Vertex& vertex1, Vertex& vertex2, float weight) {
    // Create a new edge.
    Edge newEdge = { &vertex1, &vertex2, weight, sf::RectangleShape() };
    std::cout << "Added edge from { " << vertex1.Position.x << ", " << vertex1.Position.y << " } to { " << vertex2.Position.x << ", " << vertex2.Position.y << " } with weight " << weight << std::endl;

    // Update adjacency matrix.
    AdjacencyMatrix[&vertex1 - &m_vertices[0]][&vertex2 - &m_vertices[0]] = weight;
    if (!m_isDirected) {
        AdjacencyMatrix[&vertex2 - &m_vertices[0]][&vertex1 - &m_vertices[0]] = weight;
    }

    // Add edge to the list.
    m_edges.push_back(newEdge);
}

bool Graph::CalculateBipartite(void) {
    for (int i = 0; i < m_vertices.size(); i++) {
        for (int j = 0; j < m_vertices.size(); j++) {
            if (AdjacencyMatrix[i][j] != 0) {
                if (m_vertices[i].VertexColor == 0 && m_vertices[j].VertexColor == 0) {
                    m_vertices[i].VertexColor = 1;
                    m_vertices[j].VertexColor = 2;
                } else if (m_vertices[i].VertexColor == 0 && m_vertices[j].VertexColor != 0) {
                    m_vertices[i].VertexColor = (m_vertices[j].VertexColor == 1) ? 2 : 1;
                } else if (m_vertices[i].VertexColor != 0 && m_vertices[j].VertexColor == 0){
                    m_vertices[j].VertexColor = (m_vertices[i].VertexColor == 1) ? 2 : 1;
                }
            }
        }
    }

    // Verify bipartiteness.
    for (int i = 0; i < m_vertices.size(); i++) {
        for (int j = 0; j < m_vertices.size(); j++) {
            if (AdjacencyMatrix[i][j] != 0) {
                if (m_vertices[i].VertexColor == m_vertices[j].VertexColor) {
                    return false;
                }
            }
        }
    }

    // Reset the vertex colors for future calculations.
    for (auto& vertex : m_vertices) {
        vertex.VertexColor = 0;
    }

    return true;
}

int Graph::CalculateNumberOfSpanningTrees(void) {
    // Create the Diagonal Matrix.
    std::vector<int>  degreeCount;
    for (std::size_t i = 0; i < AdjacencyMatrix.size(); i++) {
        degreeCount.push_back(0);
        for (std::size_t j = 0; j < AdjacencyMatrix.size(); j++) {
            if (AdjacencyMatrix[i][j] != 0) {
                degreeCount[i]++;
            }
        }
    }

    std::vector<std::vector<float>> diagonalMatrix;
    for (std::size_t i = 0; i < AdjacencyMatrix.size(); i++) {
        diagonalMatrix.push_back(std::vector<float>(AdjacencyMatrix.size(), 0.0f));
        diagonalMatrix[i][i] = static_cast<float>(degreeCount[i]);  
    }

    // Create the Laplacian Matrix.
    std::vector<std::vector<float>> laplacianMatrix;
    for (std::size_t i = 0; i < AdjacencyMatrix.size(); i++) {
        laplacianMatrix.push_back(std::vector<float>(AdjacencyMatrix.size(), 0.0f));
        for (std::size_t j = 0; j < AdjacencyMatrix.size(); j++) {
            laplacianMatrix[i][j] = diagonalMatrix[i][j] - AdjacencyMatrix[i][j];
        }
    }

    // Convert L to L_k.
    std::vector<std::vector<float>> minorMatrix;
    for (std::size_t i = 0; i < laplacianMatrix.size() - 1; i++) {
        minorMatrix.push_back(std::vector<float>());
        for (std::size_t j = 0; j < laplacianMatrix.size() - 1; j++) {
            minorMatrix[i].push_back(laplacianMatrix[i][j]);
        }  
    }

    // Calculate the determinant of L_k.
    float determinant = 1;
    int n = minorMatrix.size();

    // Convert to upper triangular matrix.
    for (int i = 0; i < n; i++) {
        if (minorMatrix[i][i] == 0.0f) {
            for (int j = i; j < n; j++) {
                if (minorMatrix[j][i] != 0.0f) {
                    std::swap(minorMatrix[i], minorMatrix[j]);
                    determinant *= -1;
                    break;
                }

                if (j == n - 1) {
                    return 0;
                }
            }
        } 
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            float factor = minorMatrix[j][i] / minorMatrix[i][i];
            std::vector<float> tempRow = minorMatrix[i];
            for (int k = 0; k < n; k++) {
                tempRow[k] *= factor;
                minorMatrix[j][k] = minorMatrix[j][k] - tempRow[k];
            }
        }
    }

    // Muliply diagonal elements to get determinant.
    for (int i = 0; i < n; i++) {
        determinant *= minorMatrix[i][i];
    }

    return std::round(determinant);
}

Vertex* Graph::GetVertexAtMouse(sf::RenderWindow *window) {
    for (Vertex& v : m_vertices) {
        sf::FloatRect hitbox = v.Sprite.getGlobalBounds();
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        if (hitbox.contains(mousePos)) {
            return &v;
        }
    }
    
    return nullptr;
}

void Graph::Draw(sf::RenderWindow *window) {
    // Draw vertices.
    for (Vertex &vertex : m_vertices) {
        drawVertex(window, vertex);
    }

    // Draw edges.
    for (Edge &edge : m_edges) {
        drawEdge(window, edge);
    }
}

std::vector<Vertex>& Graph::GetVertices(void){ 
    return m_vertices; 
}

Vertex Graph::RemoveVertex(int n) {
    if (n >= 0 && n < m_vertices.size()) {
        std::vector<Vertex>::iterator it = m_vertices.begin() + n;
        Vertex v = *it;
        // std::cout << "Removed vertex: { " << v.Position.x << ", " << v.Position.y << " }" << std::endl;
        m_vertices.erase(it);

        // Remove associated edges.
        for (int i = m_edges.size() - 1; i >= 0; i--) {
            Edge* edge = &m_edges[i];
            if (edge->Vertex1 == &v || edge->Vertex2 == &v) {
                m_edges.erase(m_edges.begin() + i); 
            }
        }

        // Adjust the adjacency matrix.
        AdjacencyMatrix.erase(AdjacencyMatrix.begin() + n);
        for (auto& row : AdjacencyMatrix) {
            row.erase(row.begin() + n);
        }

        return v;
    }

    return Vertex();
}

void Graph::drawEdge(sf::RenderWindow *window, Edge& edge) {
    // Initialize the sprite.
    edge.Sprite.setFillColor(Color);

    Vertex& left = (edge.Vertex1->Position.x < edge.Vertex2->Position.x) ? *edge.Vertex1 : *edge.Vertex2;
    Vertex& right = (edge.Vertex1->Position.x < edge.Vertex2->Position.x) ? *edge.Vertex2 : *edge.Vertex1;
    sf::Vector2f dir = right.Position - left.Position;
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    edge.Sprite.setSize({length, 2.0f});
    edge.Sprite.setOrigin({0.0f, 0.0f});
    edge.Sprite.setPosition(left.Position);

    float angle = std::atan2(dir.y, dir.x);
    edge.Sprite.setRotation(sf::radians(angle));

    // Draw the sprite.
    window->draw(edge.Sprite);
}

void Graph::drawVertex(sf::RenderWindow *window, Vertex& vertex) {
    // Initialize the sprite.
    float radius = 10.0f;
    vertex.Sprite.setRadius(radius);
    vertex.Sprite.setOrigin({radius, radius});
    vertex.Sprite.setFillColor(Color);
    vertex.Sprite.setPosition(vertex.Position);

    // Draw the sprite.
    window->draw(vertex.Sprite);
}
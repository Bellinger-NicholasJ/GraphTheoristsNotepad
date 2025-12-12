/* Graph Theorist's Notepad
    Copyright (c) 2025 Nicholas Bellinger
    Licensed under the "Graph Theorist's Notepad, Nicholas Bellinger, Non-Commercial License 1.0".
    See the LICENSE file in the project root for full details. */

#include "pch.hpp"
#include "Notepad.hpp"

int Notepad::Start(void) {
    // Run the program as long as the window is open.
    while (true) {
        // Manage state machine.
        switch(m_state) {
            case INITIALIZING:
                init();
                m_state = RUNNING;
                break;
            case RUNNING:
                // Main application loop.
                loop();
                break;
            case EXITING:
                // Exit the application.
                return exit();
            default:
                // Unknown state.
                std::cerr << "Notepad in unknown state." << std::endl;
                return -1;
        
        }
    } 
}

bool Notepad::createWindow(void) {
    // Create the window.
    m_window = new sf::RenderWindow(sf::VideoMode({800, 600}), "Graph Theorist's Notepad");
    if (!m_window) {
        std::cerr << "Failed to create SFML RenderWindow." << std::endl;
        return false;
    }

    // Initialize ImGui-SFML
    if (!ImGui::SFML::Init(*m_window)) {
        std::cerr << "Failed to initialize ImGui-SFML." << std::endl;
        return false;
    }

    return true;
}

int Notepad::exit(void) {
    // Cleanup ImGui-SFML
    ImGui::SFML::Shutdown();

    // Cleanup SFML window
    if (m_window) {
        m_window->close();
        delete m_window;
    }

    return 0;
}

void Notepad::handleAddEdge(sf::RenderWindow *window) {
    if (m_selectedVertices.size() == 2) {
        m_activeGraph->AddEdge(*m_selectedVertices[0], *m_selectedVertices[1], 1.0f);
        m_selectedVertices[0]->Sprite.setOutlineColor(m_activeGraph->Color);
        m_selectedVertices[1]->Sprite.setOutlineColor(m_activeGraph->Color);
        m_selectedVertices.clear();
    } else {
        Vertex* vertex = m_activeGraph->GetVertexAtMouse(m_window);
        if (vertex) {
            sf::Color outlineColor = m_activeGraph->Color == sf::Color::Red ? sf::Color::Black : sf::Color::Red;
            vertex->Sprite.setOutlineColor(sf::Color::Red);
            m_selectedVertices.push_back(vertex);
        }
    }
}
        
void Notepad::handleAddVertex(sf::RenderWindow *window) {
    bool vertexExists = false;
    for (Vertex vertex : m_activeGraph->GetVertices()) {
        Vertex *v = m_activeGraph->GetVertexAtMouse(m_window);
        if (v == &vertex) {
            vertexExists = true;
            break;
        }
    }
    if (!vertexExists) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
        sf::Vector2f worldPos = m_window->mapPixelToCoords(mousePos);
        std::string vertexName = "";
        m_activeGraph->AddVertex(vertexName, worldPos);
    }
}

void Notepad::handleDelete(sf::RenderWindow *window) {
    Vertex *vertex = m_activeGraph->GetVertexAtMouse(m_window);
    int n = 0;
    for (Vertex &v : m_activeGraph->GetVertices()) {
        if (&v == vertex) {
            m_activeGraph->RemoveVertex(n);
            break;
        } else {
            n++;
        }
    }
}

void Notepad::handleSelect(sf::RenderWindow *window) {
    if (m_selectedVertices.size() > 0) {
        Vertex* vertex = m_activeGraph->GetVertexAtMouse(m_window);
        if (vertex) {
            m_selectedVertices[0]->Sprite.setOutlineColor(m_activeGraph->Color);
            m_selectedVertices.clear();
        } else {
            m_selectedVertices[0]->Position = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
        }
    } else {
        Vertex* vertex = m_activeGraph->GetVertexAtMouse(m_window);
        if (vertex) {
            m_selectedVertices.push_back(vertex);
            vertex->Sprite.setOutlineColor(sf::Color::Red);
        }
    }
}

bool Notepad::init(void) {
    // Create the window.
    if (!createWindow()) {
        return false;
    }

    // Create a default graph.
    Graph* defaultGraph = new Graph();
    defaultGraph->Name = "1";
    m_graphs.push_back(defaultGraph);
    m_activeGraph = defaultGraph;
    Sidebar::currentActiveGraph = defaultGraph;
    defaultGraph->IsActive = true;

    return true;
}

void Notepad::loop(void) {
    // Process events.
    processEvents();

    // Update active graph.
    for (Graph* graph : m_graphs) {
        if (graph->IsActive) {
            m_activeGraph = graph;
            break;
        }
    }

    // Render the screen.
    render();
}

void Notepad::processEvents(void) {
    // check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional<sf::Event> event = m_window->pollEvent()) {
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>()) {
            m_state = EXITING;
        }

        // Process ImGui-SFML events.
        ImGui::SFML::ProcessEvent(*m_window, *event);

        // Mouse click
        // Ask ImGui if it wants the mouse
        ImGuiIO& io = ImGui::GetIO();
        if (!io.WantCaptureMouse) {
            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    switch (Sidebar::Mode) {
                        case Sidebar::AddVertex:
                            handleAddVertex(m_window);
                            break;
                        case Sidebar::AddEdge:
                            handleAddEdge(m_window);
                            break;
                        case Sidebar::Delete:
                            handleDelete(m_window);
                            break;
                        case Sidebar::Select:
                            handleSelect(m_window);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

void Notepad::render(void) {
    // clear the window with black color
    m_window->clear(sf::Color::White);

    // Draw graphs.
    Sidebar::Draw(m_window, m_graphs, m_time.restart());
    Canvas::Draw(m_window, m_graphs);

    // draw the previous frame.
    m_window->display();
}

Graph* Notepad::m_activeGraph = nullptr;
std::vector<Graph*> Notepad::m_graphs;
Notepad::State Notepad::m_state = Notepad::INITIALIZING;
sf::Clock Notepad::m_time;
sf::RenderWindow *Notepad::m_window = nullptr;

std::vector<Vertex*> Notepad::m_selectedVertices;
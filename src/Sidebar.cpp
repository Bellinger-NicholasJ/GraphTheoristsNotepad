/* Graph Theorist's Notepad
    Copyright (c) 2025 Nicholas Bellinger
    Licensed under the "Graph Theorist's Notepad, Nicholas Bellinger, Non-Commercial License 1.0".
    See the LICENSE file in the project root for full details. */

#include "pch.hpp"
#include "Sidebar.hpp"

void Sidebar::Draw(sf::RenderWindow *window, std::vector<Graph*>& graphs, sf::Time deltaTime) {
    float panelWidth = 260.0f;
    auto size = window->getSize();

    ImGui::SFML::Update(*window, deltaTime);

    ImGui::SetNextWindowPos(ImVec2(size.x - panelWidth, 0.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, size.y), ImGuiCond_Always);

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Sidebar", nullptr, flags);

    ImGui::RadioButton("Select/Move", &Mode, Sidebar::Select);
    ImGui::RadioButton("Add Vertex", &Mode, Sidebar::AddVertex);
    ImGui::RadioButton("Add Edge", &Mode, Sidebar::AddEdge);
    ImGui::RadioButton("Delete", &Mode, Sidebar::Delete);

    if (graphs.size() > 0) {
        ImGui::Separator();
    }

    for (std::size_t idx = 0; idx < graphs.size(); idx++) {
        Graph* graph = graphs[idx];
        if (!graph) continue;

        ImGui::Separator();

        ImGui::PushID(idx);

        // This draws the “header” and darkens when selected
        if (ImGui::Selectable(("Graph: " + graph->Name).c_str(), graph->IsActive, ImGuiSelectableFlags_SpanAllColumns)) {
            graph->IsActive = !graph->IsActive;
            for (Graph* temp : graphs) {
                if (temp != graph) {
                    temp->IsActive = false;
                }
            }
        }

        for (Graph* temp : graphs) {
            if (temp->IsActive) {
                currentActiveGraph = temp;
                break;
            }
        }
        
        // Color picker

        // Convert sf::Color -> ImVec4
        ImVec4 col = ImVec4(
            graph->Color.r / 255.0f,
            graph->Color.g / 255.0f,
            graph->Color.b / 255.0f,
            1.0f
        );

        // Unique IDs for ImGui so multiple graphs don't collide
        std::string baseId   = "Color::" + std::to_string(idx);
        std::string buttonId = baseId + "_btn";
        std::string popupId  = baseId + "_popup";

        // Label + color box in same line
        ImGui::Text("Color:");
        ImGui::SameLine();
        if (ImGui::ColorButton(buttonId.c_str(), col)) {
            ImGui::OpenPopup(popupId.c_str());
        }

        if (ImGui::BeginPopup(popupId.c_str())) {
            ImGui::Text("Pick graph color");
            ImGui::Separator();

            if (ImGui::ColorPicker3("##picker", (float*)&col)) {
                // Update the graph color whenever user changes it
                graph->Color = sf::Color((col.x * 255.0f), (col.y * 255.0f), (col.z * 255.0f));
            }

            ImGui::EndPopup();
        }

        int n = static_cast<int>(graph->AdjacencyMatrix.size());
        if (n <= 0) {
            ImGui::PopID();
            continue;
        }

        ImGui::Text("Adjacency Matrix (%d x %d)", n, n);

        // unique ID per graph so ImGui doesn't confuse the tables
        std::string tableId = "Table::" + std::to_string(idx);

        if (ImGui::BeginTable(tableId.c_str(), n + 1, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {

            // Header row.
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text(" ");

            for (int col = 0; col < n; ++col) {
                ImGui::TableSetColumnIndex(col + 1);
                ImGui::Text("%d", col);
            }

            // Data rows.
            for (int row = 0; row < n; ++row) {
                ImGui::TableNextRow();

                // Row label.
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%d", row);

                for (int col = 0; col < n; ++col) {
                    ImGui::TableSetColumnIndex(col + 1);
                    ImGui::Text("%.0f", graph->AdjacencyMatrix[row][col]);
                }
            }

            ImGui::EndTable();
        }
        ImGui::PopID();
        ImGui::Separator();
    }

    if (graphs.size() > 0) {
        ImGui::Separator();
    }

    ImVec2 newGraphButtonSize(28.0f, 28.0f);

    if (ImGui::Button("+", newGraphButtonSize)) {
        //std::cout << "Add new graph!" << std::endl;
        Graph* newGraph = new Graph(false);
        newGraph->Color = sf::Color::Black;
        newGraph->Name = std::to_string(graphs.size() + 1);
        graphs.push_back(newGraph);
    }

    ImVec2 calcButtonSize(300.0f, 28.0f);

    if (ImGui::Button("Calc Spanning Trees", calcButtonSize)) {
        std::cout << "Number of spanning trees in Graph " << currentActiveGraph->Name << ": " << currentActiveGraph->CalculateNumberOfSpanningTrees() << "." << std::endl;
    }

    if (ImGui::Button("Calc Bipartite", calcButtonSize)) {
        bool bipartite = currentActiveGraph->CalculateBipartite();
        if (bipartite) {
            std::cout << "Graph " << currentActiveGraph->Name << " is bipartite." << std::endl;
        } else {
            std::cout << "Graph " << currentActiveGraph->Name << " is not bipartite." << std::endl;
        }
    }

    ImGui::End();
    ImGui::SFML::Render(*window);
}

int Sidebar::Mode = Sidebar::Select;
Graph* Sidebar::currentActiveGraph = nullptr;
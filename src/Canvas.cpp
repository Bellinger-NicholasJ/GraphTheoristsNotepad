/* Graph Theorist's Notepad
    Copyright (c) 2025 Nicholas Bellinger
    Licensed under the "Graph Theorist's Notepad, Nicholas Bellinger, Non-Commercial License 1.0".
    See the LICENSE file in the project root for full details. */

#include "pch.hpp"
#include "Canvas.hpp"

void Canvas::Draw(sf::RenderWindow *window, std::vector<Graph*>& graphs) {
    for (Graph* graph : graphs) {
        graph->Draw(window);
    }
}
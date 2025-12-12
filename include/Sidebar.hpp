/* Graph Theorist's Notepad
    Copyright (c) 2025 Nicholas Bellinger
    Licensed under the "Graph Theorist's Notepad, Nicholas Bellinger, Non-Commercial License 1.0".
    See the LICENSE file in the project root for full details. */

#ifndef SIDEBAR_HPP
#define SIDEBAR_HPP

#include "Graph.hpp"

class Sidebar {
    public:
        /// @brief Interaction modes for the sidebar.
        enum Mode {
            Select, AddVertex, AddEdge, Delete
        };

        /**
         * @brief Draw's the sidebar panel.
         * @param window A pointer to the window being drawn on.
         * @param graphs A list of graphs.
         * @param deltaTime The time since last frame.
         */
        static void Draw(sf::RenderWindow *window, std::vector<Graph*>& graphs, sf::Time deltaTime);

        /// @brief Current interaction mode.
        static int Mode;

        static Graph* currentActiveGraph;

    private:
        
};

#endif
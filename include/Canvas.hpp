/* Graph Theorist's Notepad
    Copyright (c) 2025 Nicholas Bellinger
    Licensed under the "Graph Theorist's Notepad, Nicholas Bellinger, Non-Commercial License 1.0".
    See the LICENSE file in the project root for full details. */

#ifndef CANVAS_HPP
#define CANVAS_HPP

#include "Graph.hpp"

/// @brief A canvas to draw graphs and planes on.
class Canvas {
    public:
        /**
         * @brief Draw's the canvas, including graphs and planes.
         * @param window A pointer to the window being drawn on.
         * @param graphs A reference to a list of graphs.
         */
        static void Draw(sf::RenderWindow *window, std::vector<Graph*>& graphs);

    private:
};

#endif
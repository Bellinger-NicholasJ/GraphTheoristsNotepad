/* Graph Theorist's Notepad
    Copyright (c) 2025 Nicholas Bellinger
    Licensed under the "Graph Theorist's Notepad, Nicholas Bellinger, Non-Commercial License 1.0".
    See the LICENSE file in the project root for full details. */

#ifndef NOTEPAD_HPP
#define NOTEPAD_HPP

#include "Canvas.hpp"
#include "Sidebar.hpp"

class Notepad {
    public:
        /** 
         * @brief Application states.
         */
        enum State {
            INITIALIZING, RUNNING, EXITING
        };

        /**
         * @brief Start the Notepad application.
         * @return int Exit code.
         * @retval 0 Success.
         * @retval -1 Setup Failure.
         */
        static int Start(void);

    private:
        /** 
         * @brief Create the main application window.
         * @return success status.
         * @retval true - Success.
         * @retval false - Failure.
         */
        static bool createWindow(void);

        /** 
         * @brief Exit the Notepad application.
         * @return int Exit code.
         * @retval 0 - Success.
         */
        static int exit(void);

        static void handleAddEdge(sf::RenderWindow *window);

        static void handleAddVertex(sf::RenderWindow *window);

        static void handleDelete(sf::RenderWindow *window);

        static void handleSelect(sf::RenderWindow *window);

        /**
         * @brief Sets up the window for the app and initializes state.
         * @return Success status.
         * @retval true - Success
         * @retval false - Failure
         */
        static bool init(void);

        /** 
         * @brief Main application loop.
         */
        static void loop(void);

        /** 
         * @brief Process SFML events.
         */
        static void processEvents(void);

        /** 
         * @brief Render graphics in the window.
         */
        static void render(void);

        /// @brief The graph currently being selected.
        static Graph* m_activeGraph;

        /// @brief A list of graphs for the program.
        static std::vector<Graph*> m_graphs;

        /// @brief Current application state.
        static State m_state;

        /// @brief Time tracker for ImGui-SFML.
        static sf::Clock m_time;

        /// @brief Pointer to the SFML RenderWindow.
        static sf::RenderWindow *m_window;

        /// @brief List of currently selected vertices.
        static std::vector<Vertex*> m_selectedVertices;

};

#endif
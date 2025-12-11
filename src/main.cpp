/* Graph Theorist's Notepad
    Copyright (c) 2025 Nicholas Bellinger
    Licensed under the "Graph Theorist's Notepad, Nicholas Bellinger, Non-Commercial License 1.0".
    See the LICENSE file in the project root for full details. */

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Graph Theorist's Notepad");

    // Initialize ImGui-SFML
    if (!ImGui::SFML::Init(window)) {
        return -1;
    }

    sf::Clock deltaClock;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::White);

        // Make a test ImGui window
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Test Window");
        ImGui::Text("Hello, world!");
        ImGui::End();
        ImGui::SFML::Render(window);

        // end the current frame
        window.display();
    }

    return 0;
}
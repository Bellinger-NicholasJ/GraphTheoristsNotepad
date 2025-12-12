# GraphTheoristsNotepad

This is a small tool designed for creating different kinds of graphs.

This application allows you to draw graphs by creating, removing, moving vertices and edges. Several helpful features include adding multiple graphs, changing their color, and their adjacency matrix is displayed. Finally options for calculating the number of spanning trees and determininig if a graph is bipartite are also included.

This application was developed with SFML for most of the graphics rendering and window creation and Dear ImGUI for ui elements in teh tools panel. This is compiled for c++ 20 using cmake 1.16.

The overall architecture of this program runs off of a statemachine in Notepad.cpp with a sub-statemachine for the programloop. The Canvas.cpp and Sidebar.cpp act as a presentation layer, graph.cpp acting as the backend, and Notepad.cpp acting as the broker/master of the program. I tried my best to decouple the different layers for easy development and maintenence as well as structures in place for more advanced features dealing with multiple graphs, directed graphs, etc. The structure of the graph itself is a vector of edges and a vector of vertices with edges containing pointers to vertices.

In the Future I would like to implement a plane which can be changed to represent other surfaces like a klein bottle or torus. I also wanted to implement an api layer to run scripts that can visually demonstrate algorithms such as Djkstra's algorithm or a maze generator for example. There are also several edge cases with bugs that need to be patched.

## License

This project is licensed under the:

**Graph Theorist's Notepad, Nicholas Bellinger, Non-Commercial License 1.0**

Copyright (c) 2025 Nicholas Bellinger

You are free to use, copy, modify, merge, publish, and distribute this software
for **non-commercial** purposes, under the conditions described in the
[LICENSE](./LICENSE) file in this repository.

Commercial use (including but not limited to selling, licensing, monetizing,
or using this software for direct or indirect financial gain) **is not
permitted** without prior written permission from the author.

To request a commercial license, contact:

- **Name:** Nicholas Bellinger  
- **Email:** bellinger.nicholasj@icloud.com

## Third-Party Libraries & Licenses

Graph Theorist's Notepad uses the following third-party libraries:

### SFML

- **Name:** SFML (Simple and Fast Multimedia Library)  
- **Use:** Window creation, input handling, 2D graphics rendering  
- **License:** zlib/png license  
- **Repository:** https://github.com/SFML/SFML  

SFML is redistributed in this project under the terms of the zlib/png license.
See the SFML repository for the full license text, or the `LICENSE` files
within `vendors/sfml` if present.

### Dear ImGui

- **Name:** Dear ImGui  
- **Use:** Immediate-mode GUI (panels, controls, etc.)  
- **License:** MIT License  
- **Repository:** https://github.com/ocornut/imgui  

Dear ImGui is included as a vendored dependency in `vendors/imgui` and is
licensed under the MIT License. See `vendors/imgui/LICENSE.txt` (or equivalent)
for the full terms.

### ImGui-SFML

- **Name:** ImGui-SFML  
- **Use:** Integration layer between Dear ImGui and SFML  
- **License:** MIT License  
- **Repository:** https://github.com/SFML/imgui-sfml  

ImGui-SFML is included as a vendored dependency in `vendors/imgui-sfml` and is
licensed under the MIT License. See `vendors/imgui-sfml/LICENSE` (or
equivalent) for the full terms.

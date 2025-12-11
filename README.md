# GraphTheoristsNotepad

This is a small tool designed for creating different kinds of graphs.

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

#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Undo/Redo stacks to manage drawing history
std::stack<sf::Image> undoStack;
std::stack<sf::Image> redoStack;

// Save the current canvas state to the Undo stack
void saveToUndoStack(const sf::Image& canvas) {
    if (undoStack.size() >= 10) undoStack.pop(); // Limit stack size to 10
    undoStack.push(canvas);
}

// Undo function
void undo(sf::Image& canvas, sf::Texture& texture) {
    if (!undoStack.empty()) {
        redoStack.push(canvas); // Save current state to the Redo stack
        canvas = undoStack.top();
        undoStack.pop();
        texture.loadFromImage(canvas);
    }
}

// Redo function
void redo(sf::Image& canvas, sf::Texture& texture) {
    if (!redoStack.empty()) {
        undoStack.push(canvas); // Save current state to the Undo stack
        canvas = redoStack.top();
        redoStack.pop();
        texture.loadFromImage(canvas);
    }
}

int main() {
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Collaborative Whiteboard");
    window.setFramerateLimit(60);

    // Create the canvas
    sf::Image canvas;
    canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color::White);

    sf::Texture texture;
    texture.loadFromImage(canvas);

    sf::Sprite sprite(texture);

    // Drawing tools
    sf::Vector2i lastMousePosition;
    bool isDrawing = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle mouse press to start drawing
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                isDrawing = true;
                lastMousePosition = sf::Mouse::getPosition(window);

                // Save the canvas state for Undo
                saveToUndoStack(canvas);
            }

            // Handle mouse release to stop drawing
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                isDrawing = false;
            }

            // Handle keyboard input for Undo/Redo
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Z) { // Undo (Ctrl+Z equivalent)
                    undo(canvas, texture);
                } else if (event.key.code == sf::Keyboard::Y) { // Redo (Ctrl+Y equivalent)
                    redo(canvas, texture);
                } else if (event.key.code == sf::Keyboard::C) { // Clear the canvas
                    saveToUndoStack(canvas);
                    canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color::White);
                    texture.loadFromImage(canvas);
                }
            }
        }

        // Draw on the canvas while holding the left mouse button
        if (isDrawing) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f start(lastMousePosition.x, lastMousePosition.y);
            sf::Vector2f end(mousePosition.x, mousePosition.y);

            // Draw a line on the canvas
            sf::RenderTexture renderTexture;
            renderTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
            renderTexture.clear(sf::Color::White);
            renderTexture.draw(sprite); // Start with the current canvas

            // Draw the line
            sf::Vertex line[] = {
                sf::Vertex(start, sf::Color::Black),
                sf::Vertex(end, sf::Color::Black)
            };
            renderTexture.draw(line, 2, sf::Lines);

            renderTexture.display();

            // Update the canvas and texture
            canvas = renderTexture.getTexture().copyToImage();
            texture.loadFromImage(canvas);

            lastMousePosition = mousePosition;
        }

        // Render the updated canvas
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }

    return 0;
}

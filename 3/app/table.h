#ifndef LAB3_APP_TABLE_H
#define LAB3_APP_TABLE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class ScrollableTable {
public:
    ScrollableTable(float width, float height, sf::Font& font) 
        : tableWidth(width), tableHeight(height), offset(0.f), _font(font) {
        // Set up the table background
        background.setSize(sf::Vector2f(tableWidth, tableHeight));
        background.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black

        // Create a view for scrolling
        view.setSize(width, height);
        view.setViewport(sf::FloatRect(0, 0, 1, 1));
    }

    void addRow(const std::vector<std::string>& row) {
        rows.push_back(row);
    }

    void draw(sf::RenderWindow& window) {
        window.setView(view);
        window.draw(background);

        float rowHeight = 30.f;
        for (size_t i = 0; i < rows.size(); ++i) {
            if (i * rowHeight + offset >= 0 && i * rowHeight + offset < tableHeight) {
                drawRow(window, rows[i], i * rowHeight + offset);
            }
        }
    }

    void scroll(float delta) {
        offset += delta;
        if (offset > 0) offset = 0; // Prevent scrolling above the first row
        if (-offset > static_cast<float>(rows.size()) * 30.f - tableHeight) {
            offset = -static_cast<float>(rows.size()) * 30.f + tableHeight; // Prevent scrolling below the last row
        }
    }

private:
    void drawRow(sf::RenderWindow& window, const std::vector<std::string>& row, float y) {
        sf::Text text;
        text.setFont(_font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);

        for (size_t i = 0; i < row.size(); ++i) {
            text.setString(row[i]);
            text.setPosition(10 + i * 150, y);
            window.draw(text);
        }
    }

    sf::RectangleShape background;
    sf::View view;
    std::vector<std::vector<std::string>> rows;
    float tableWidth;
    float tableHeight;
    float offset;

public:
    sf::Font _font; // Static font variable
};

#endif //LAB3_APP_TABLE_H

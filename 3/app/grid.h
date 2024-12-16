#ifndef LAB3_APP_GRID_H
#define LAB3_APP_GRID_H

#include <SFML/Graphics.hpp>
#include <vector>

class Grid {

public:
    Grid(int x0 = 0, int y0 = 0, int cellWidth = 50, int cellHeight = 50) {
        _x0 = x0;
        _y0 = y0;
        _cellWidth = cellWidth;
        _cellHeight = cellHeight;
    }
    ~Grid() = default;

    void setX0(int x0) {
        _x0 = x0;
    }

    void setY0(int y0) {
        _y0 = y0;
    }

    void addCell(sf::Sprite &cell) {
        cell.setScale(0.25f, 0.25f);
        _cells.push_back(cell);
    }

    void render() {
        int curX = _x0, curY = _y0;
        for (auto &cell : _cells) {
            cell.setPosition(curX, curY);
            curX += _cellWidth;
            if (curX >= _cellWidth * 2 + _x0) {
                curX = _x0;
                curY += _cellHeight;
            }
        }
    }

    std::vector<sf::Sprite> &getCells() {
        return _cells;
    }

    class iterator {
    public:
        iterator(std::vector<sf::Sprite>::iterator begin, std::vector<sf::Sprite>::iterator end) : _begin(begin), _end(end) {}
        iterator &operator++() {
            _begin++;
            return *this;
        }

        sf::Sprite &operator*() {
            return *_begin;
        }

        bool operator!=(const iterator &other) {
            return _begin != other._begin;
        }

    private:
        std::vector<sf::Sprite>::iterator _begin;
        std::vector<sf::Sprite>::iterator _end;
    };

    iterator begin() {
        return iterator(_cells.begin(), _cells.end());
    }

    iterator end() {
        return iterator(_cells.end(), _cells.end());
    }

private:
    std::vector<sf::Sprite> _cells;
    int _cellWidth = 50;   
    int _cellHeight = 50;
    int _x0 = 0;
    int _y0 = 0;
};


#endif //LAB3_APP_GRID_H

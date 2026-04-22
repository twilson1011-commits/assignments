#include "Rotate.h"

Rotate::Rotate(int degrees) : degrees_(degrees) {}

std::string Rotate::name() const {
    return "rotate(" + std::to_string(degrees_) + ")";
}

void Rotate::apply(Grid& pixels) {
    int height = static_cast<int>(pixels.size());
    if (height == 0) return;
    int width  = static_cast<int>(pixels[0].size());
    

    if (degrees_ == 0) {
        return;  // nothing to do
    }

    Grid result;

    if (degrees_ == 180) {
       result = Grid(height, std::vector<Pixel>(width));
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                result[height - 1 - row][width - 1 - col] = pixels[row][col];
            }
        }
    }

    if (degrees_ == 90) {
        result = Grid(width, std::vector<Pixel>(height));
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                result[col][height - 1 - row] = pixels[row][col];
            }
        }
    }

    if (degrees_ == 270) {
       result = Grid(width, std::vector<Pixel>(height));
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                result[width - 1 - col][row] = pixels[row][col];
            }
        }
    }

    pixels = result;
}

#include "FlipV.h"
#include <algorithm>    // std::swap

std::string FlipV::name() const {
    return "flipV";
}

void FlipV::apply(Grid& pixels) {
    
       int height = pixels.size();
       for (int row = 0; row < height / 2; ++row) {
          std::swap(pixels[row], pixels[height - 1 - row]);
       }
}

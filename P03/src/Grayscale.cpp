#include "Grayscale.h"

std::string Grayscale::name() const {
    return "grayscale";
}

void Grayscale::apply(Grid& pixels) {
    for (auto& row : pixels) {
        for ([[maybe_unused]] Pixel& p : row) {
            
               int gray = static_cast<int>(0.299*p.r + 0.587*p.g + 0.114*p.b);
        
               p.r = gray;
               p.g = gray;
               p.b = gray;
        }
    }
}    



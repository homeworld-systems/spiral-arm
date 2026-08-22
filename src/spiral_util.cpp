# include "spiral_util.h"
# include <iostream>

void SPIRAL::LogI (const char* category, const char* message) {
    std::cout << "[INFO] " << category << ": " << message;
}

void SPIRAL::LogD (const char* category, const char* message) {
    std::cout << "[DEBUG] " << category << ": " << message;
}

void SPIRAL::LogW (const char* category, const char* message) {
    std::cout << "[WARN] " << category << ": " << message;
}
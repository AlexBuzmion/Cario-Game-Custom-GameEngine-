#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <functional>
#include <cmath>
#include <string>

#define LOG(X) std::cout << X
#define LOG_LINE(X) std::cout << X << std::endl
#define ENGINE_PRINT(X, Y, Z) AccessEngine()->DrawText(AccessEngine()->LoadFont("resources/play-regular.ttf", 16), exVector2{Y,Z}, (std::string(X)).c_str(), exColor{ 0,0,0,255 }, 0);


#include <print>
#include "../include/Engine/Engine.h"

int main() {
    auto* engine = new Engine();
    engine->loop();
    return 0;
}
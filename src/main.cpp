#include <Engine.h>

int main() {

    Engine engine;

    if (!engine.initialize()) {
        return 1;
    }
    engine.run();


    return 0;
}
#include "lib/dialogue_funcs.hpp"

int main() {
    TEncoder encoder;
    bool eof = 0;
    while (!eof) {
        eof = choose_action(encoder);
    }
    return 0;
}

#include <iostream>
#include "Bus.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Please specify a rom!" << endl;
        return 0;
    }

    Bus bus = Bus();
    bus.memory.readFile(argv[1]);
    bus.cpu.launch();

    return 0;
}
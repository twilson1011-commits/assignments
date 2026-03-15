#include "Args.h"
#include <iostream>
using namespace std;

void print_usage() {
    cout << "Usage: ./imgtool <input_image> <output_image> [options]\n";
}

int main(int argc, char* argv[]) {

    try {

        Args args = Args::parse(argc, argv);

        cout << "INPUT  : " << args.input << "\n";
        cout << "OUTPUT : " << args.output << "\n";

        std::cout << "FLAGS  : ";
        if (args.grayscale) cout << "grayscale ";
        if (args.blur) cout << "blur ";
        if (args.flipH) cout << "flipH ";
        if (args.flipV) cout << "flipV ";
        cout << "\n";

        cout << "PARAMS : ";
        if (args.use_brighten)
            cout << "brighten=" << args.brighten << " ";
        if (args.use_rotate)
            cout << "rotate=" << args.rotate << " ";
            cout << "\n";

    }
    catch (const exception& e) {

        cout << "Error: " << e.what() << "\n";
        print_usage();
        return 1;
    }

    return 0;
}
#include "Args.h"
#include <iostream>
#include <stdexcept>

static void usage() {
    std::cerr << "Usage: ./imgtool <input_image> <output_image> [options]\n";
}

static void error(const std::string& msg) {
    std::cerr << "Error: " << msg << "\n";
    usage();
    throw std::runtime_error(msg);
}

static bool is_option(const std::string& s) {
    return !s.empty() && s[0] == '-';
}

static int parse_int(const std::string& s, const std::string& opt) {
    try {
        size_t idx;
        int val = std::stoi(s, &idx);
        if (idx != s.size()) throw std::invalid_argument("extra chars");
        return val;
    } catch (...) {
        error("invalid integer for " + opt + ": " + s);
    }
    return 0;
}

static void validate_brighten(int val) {
    if (val < -255 || val > 255)
        error("brighten must be in [-255, 255]");
}

static void validate_rotate(int val) {
    if (!(val == 0 || val == 90 || val == 180 || val == 270))
        error("rotate must be one of {0, 90, 180, 270}");
}

Args Args::parse(int argc, char* argv[]) {
    if (argc < 3) {
        error("missing required arguments");
    }

    Args args;
    args.input = argv[1];
    args.output = argv[2];

    for (int i = 3; i < argc; ++i) {
        std::string token = argv[i];

        // Handle --option=value
        std::string opt = token;
        std::string val;

        size_t eq = token.find('=');
        if (eq != std::string::npos) {
            opt = token.substr(0, eq);
            val = token.substr(eq + 1);
        }

        // -------- FLAGS --------
        if (opt == "--grayscale" || opt == "-g") {
            args.grayscale = true;
        }
        else if (opt == "--blur" || opt == "-l") {
            args.blur = true;
        }
        else if (opt == "--flipH" || opt == "-h") {
            args.flipH = true;
        }
        else if (opt == "--flipV" || opt == "-v") {
            args.flipV = true;
        }

        // -------- BRIGHTEN --------
        else if (opt == "--brighten" || opt == "-b") {
            if (val.empty()) {
                if (i + 1 >= argc)
                    error("--brighten requires an integer value");

                val = argv[++i];
                if (is_option(val))
                    error("--brighten expected a value but got option " + val);
            }

            int num = parse_int(val, "--brighten");
            validate_brighten(num);

            args.use_brighten = true;
            args.brighten = num;
        }

        // -------- ROTATE --------
        else if (opt == "--rotate" || opt == "-r") {
            if (val.empty()) {
                if (i + 1 >= argc)
                    error("--rotate requires an integer value");

                val = argv[++i];
                if (is_option(val))
                    error("--rotate expected a value but got option " + val);
            }

            int num = parse_int(val, "--rotate");
            validate_rotate(num);

            args.use_rotate = true;
            args.rotate = num;
        }

        // -------- GROUPED SHORT FLAGS (EXTRA CREDIT) --------
        else if (token.size() > 2 && token[0] == '-' && token[1] != '-') {
            for (size_t j = 1; j < token.size(); ++j) {
                char c = token[j];
                if (c == 'g') args.grayscale = true;
                else if (c == 'l') args.blur = true;
                else if (c == 'h') args.flipH = true;
                else if (c == 'v') args.flipV = true;
                else error(std::string("unknown option -") + c);
            }
        }

    
        else {
            error("unknown option " + token);
        }
    }

    return args;
}

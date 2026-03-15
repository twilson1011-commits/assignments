#include "Args.h"
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

static bool is_option(const string& s) {
    return !s.empty() && s[0] == '-';
}

static bool parse_int(const string& s, int& value) {
    try {
        size_t idx;
        value = stoi(s, &idx);
        return idx == s.size();
    } catch (...) {
        return false;
    }
}

static void validate_brighten(int v) {
    if (v < -255 || v > 255)
        throw runtime_error("brighten must be in [-255, 255]");
}

static void validate_rotate(int v) {
    if (!(v == 0 || v == 90 || v == 180 || v == 270))
        throw runtime_error("rotate must be one of {0, 90, 180, 270}");
}

Args Args::parse(int argc, char* argv[]) {

    if (argc < 3)
        throw runtime_error("missing output file");

    Args args;

    args.input = argv[1];
    args.output = argv[2];

    for (int i = 3; i < argc; ++i) {

        string token = argv[i];

        if (token == "--grayscale" || token == "-g") {
            args.grayscale = true;
        }

        else if (token == "--blur" || token == "-l") {
            args.blur = true;
        }

        else if (token == "--flipH" || token == "-h") {
            args.flipH = true;
        }

        else if (token == "--flipV" || token == "-v") {
            args.flipV = true;
        }

        else if (token.rfind("--brighten=",0) == 0) {

            string val = token.substr(11);
            int num;

            if (!parse_int(val,num))
                throw runtime_error("invalid integer for --brighten: " + val);

            validate_brighten(num);

            args.use_brighten = true;
            args.brighten = num;
        }

        else if (token == "--brighten" || token == "-b") {

            if (i+1 >= argc)
                throw runtime_error("--brighten requires an integer value");

            string val = argv[++i];

            if (is_option(val))
                throw runtime_error("--brighten expected a value but got option " + val);

            int num;

            if (!parse_int(val,num))
                throw runtime_error("invalid integer for --brighten: " + val);

            validate_brighten(num);

            args.use_brighten = true;
            args.brighten = num;
        }

        else if (token.rfind("--rotate=",0) == 0) {

            string val = token.substr(9);
            int num;

            if (!parse_int(val,num))
                throw runtime_error("invalid integer for --rotate: " + val);

            validate_rotate(num);

            args.use_rotate = true;
            args.rotate = num;
        }

        else if (token == "--rotate" || token == "-r") {

            if (i+1 >= argc)
                throw runtime_error("--rotate requires an integer value");

            string val = argv[++i];

            if (is_option(val))
                throw runtime_error("--rotate expected a value but got option " + val);

            int num;

            if (!parse_int(val,num))
                throw runtime_error("invalid integer for --rotate: " + val);

            validate_rotate(num);

            args.use_rotate = true;
            args.rotate = num;
        }

        else {
            throw runtime_error("unknown option " + token);
        }
    }

    return args;
}
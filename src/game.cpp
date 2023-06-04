#include "../inc/PirateJump.h"


int main(int argc, char *argv[]) {
    int width = 500;
    int height = 700;

    if (argc > 3) {
        std::cerr << "Too many arguments. Correct argument format: -window {}x{}" << std::endl;
        return 1;
    }

    if (argc > 1) {
        std::string window_size = argv[2];
        size_t pos = window_size.find('x');
        size_t size = window_size.size();

        if ((std::string) argv[1] != "-window" || pos == std::string::npos ||
            pos == size - 1 || pos == 0) {

            std::cerr << "Invalid argument. Correct argument format: -window {}x{}" << std::endl;
            return 1;
        }

        try {
            width = std::stoi(window_size.substr(0, pos));
            height = std::stoi(window_size.substr(pos + 1, size));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << std::endl;
        }
    }

    return run(new PirateJump(width, height));
}

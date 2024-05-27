#include "../Headers/Exceptions.h"

GeneralException::GeneralException(const std::string& error) : std::runtime_error(error) {
    if (!error.empty()) {
        std::cerr << error << '\n';
    }
}

MissingFont::MissingFont(const std::string& error) : GeneralException(error) {}

MissingTexture::MissingTexture(const std::string &error) : GeneralException(error) {}
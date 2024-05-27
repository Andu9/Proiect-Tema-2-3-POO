#ifndef OOP_EXCEPTIONS_H
#define OOP_EXCEPTIONS_H

#include <iostream>
#include <string>
#include <stdexcept>

class GeneralException : public std::runtime_error {
    public:
        explicit GeneralException(const std::string& error);
};

class MissingFont : public GeneralException {
    public:
        explicit MissingFont(const std::string& error);
};

class MissingTexture : public GeneralException {
    public:
        explicit MissingTexture(const std::string& error);
};

class InvalidTrapType : public GeneralException {
    public:
        explicit InvalidTrapType(const std::string& error);
};

#endif

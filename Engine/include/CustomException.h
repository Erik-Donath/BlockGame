//
// Created by erikd on 05.08.2024.
//

#pragma once
#include <exception>

#include "Define.h"

class CustomException : public std::exception {
public:
    explicit CustomException(str msg): msg(msg) {}
    [[nodiscard]] str what() const noexcept override {
        return msg;
    }
private:
    str msg;
};

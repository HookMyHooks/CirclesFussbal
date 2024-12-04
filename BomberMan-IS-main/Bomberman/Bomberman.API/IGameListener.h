#pragma once

#include <utility>

class IGameListener {
public:
    virtual ~IGameListener() = default;

    virtual void OnKeyPressed() = 0;
};
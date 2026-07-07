#pragma once

#include <vector>
#include <string>

#include "Graphics.h"
#include "Utils.h"

int AlignedX(int x, int width, int childWidth, string alignment) {
    if (alignment == "center") {
        return x + (width - childWidth) / 2;
    } else if (alignment == "right") {
        return x + width - childWidth;
    } else if (alignment == "left") {
        return x;
    }
    return x;
}

int AlignedY(int y, int height, int childHeight, string alignment) {
    if (alignment == "center") {
        return y + (height - childHeight) / 2;
    } else if (alignment == "bottom") {
        return y + height - childHeight;
    } else if (alignment == "top") {
        return y;
    }
    return y;
}

int RelativeX(int x, int ChildX) {
    return ChildX + x;
}

int RelativeY(int y, int ChildY) {
    return ChildY + y;
}

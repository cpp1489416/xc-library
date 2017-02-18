#include "stdafx.h"
#include "XSize.h"

inline xreal XSize::getWidth() const { return width; }
inline xreal XSize::getHeight() const { return height; }
inline xreal & XSize::rWidth() { return width; }
inline xreal & XSize::rHeight() { return height; }

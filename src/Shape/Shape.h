#pragma once

#include <variant>
#include "Rect.h"
#include "Path.h"
#include "Circle.h"
#include "ITriangle.h"
#include "RTriangle.h"
#include "Diamond.h"
#include "Text.h"

using Shape = std::variant<Path, Rect, Circle, ITriangle, RTriangle, Diamond, Text>;
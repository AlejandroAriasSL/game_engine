#pragma once

#include <string>

namespace ONI {

  enum class InputKey {
    A,
    B,
    C,
    D,
    E,
    S,
    W,
    L_THUMB_X,
    L_THUMB_Y,
    R_THUMB_X,
    R_THUMB_Y,
    MOUSE_POS_X,
    MOUSE_POS_Y,
    MOUSE_MOVE_X,
    MOUSE_MOVE_Y,
    MOUSE_RIGHT,
    MOUSE_LEFT,
    MOUSE_MIDDLE,
    UNKNOWN
  };
  enum class InputSource {
    KEYBOARD,
    MOUSE,
    GAMEPAD,
    UNKNOWN
  };

  struct InputAction {
    std::string actionName;
    float scale;
  };

  InputSource getInputSourceFromKey(InputKey key);
}

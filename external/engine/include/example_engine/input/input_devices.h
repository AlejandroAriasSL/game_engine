#pragma once

#include <functional>

#include "input_key.h"

namespace ONI {

  enum class InputDeviceType {
    KEYBOARD,
    MOUSE,
    GAMEPAD
  };
  
  struct InputDeviceState {
    float value {-99.f};
  };
  
  using InputDeviceStateCallbackFunc = std::function<std::unordered_map<InputKey, InputDeviceState>(int)>;
  
  struct InputDevice {
    InputDeviceType type;
    int index;
    std::unordered_map<InputKey, InputDeviceState> currentState;
    InputDeviceStateCallbackFunc stateFunc;
  };
}
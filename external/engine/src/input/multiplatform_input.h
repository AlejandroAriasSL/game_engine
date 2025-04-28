#pragma once

#include <unordered_map>
#include <example_engine/input/input_key.h>
#include <example_engine/input/input_devices.h>

namespace ONI {
  
  class MultiplatformInput{
    public:
      std::unordered_map<InputKey, InputDeviceState> getKeyboardState(int index) { return _keyboardState; }
      std::unordered_map<InputKey, InputDeviceState> getMouseState(int index) { return _mouseState; }
      std::unordered_map<InputKey, InputDeviceState> getGamepadState(int index) { return _gamepadStates[index]; }
      
      void updateKeyboardState(int key, float value);
      void updateMouseState(int button, float value);
    private:
      static InputKey multiplatformKeyToInputKey(int key);
      static InputKey multiplatformMouseButtonToInputKey(int button);
    private:
      std::unordered_map<InputKey, InputDeviceState> _keyboardState {};
      std::unordered_map<InputKey, InputDeviceState> _mouseState {};
      std::unordered_map<int, std::unordered_map<InputKey, InputDeviceState>> _gamepadStates {};
  };
}
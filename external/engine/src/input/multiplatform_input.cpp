#include "multiplatform_input.h"
#include <GLFW/glfw3.h>

namespace ONI {

  void MultiplatformInput::updateKeyboardState(int key, float value){
    InputKey iKey = multiplatformKeyToInputKey(key);

    _keyboardState[iKey].value = value;
  }

  void MultiplatformInput::updateMouseState(int button, float value){
    InputKey iKey = multiplatformKeyToInputKey(button);

    _mouseState[iKey].value = value;
  }

  InputKey MultiplatformInput::multiplatformKeyToInputKey(int key){
    switch(key){
      case GLFW_KEY_A:
        return InputKey::A;
      case GLFW_KEY_B:
        return InputKey::B;
      case GLFW_KEY_C:
        return InputKey::C;
      case GLFW_KEY_D:
        return InputKey::D;
      case GLFW_KEY_E:
        return InputKey::E;
      case GLFW_KEY_S: 
        return InputKey::S;
      case GLFW_KEY_W:
        return InputKey::W;
      default:
        return InputKey::UNKNOWN;        
    }
  }

  InputKey MultiplatformInput::multiplatformMouseButtonToInputKey(int button){
    switch(button){
      case GLFW_MOUSE_BUTTON_LEFT:
        return InputKey::MOUSE_LEFT;
      case GLFW_MOUSE_BUTTON_RIGHT:
        return InputKey::MOUSE_RIGHT;
      case GLFW_MOUSE_BUTTON_MIDDLE:
        return InputKey::MOUSE_MIDDLE;
      default:
        return InputKey::UNKNOWN;        
      }
  }
}
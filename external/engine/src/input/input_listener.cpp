#include "example_engine/input/input_listener.h"
#include <iostream>

namespace ONI {

    InputSource getInputSourceFromKey(InputKey key) {
      switch(key){
        case InputKey::A:
        case InputKey::B:
        case InputKey::C:
        case InputKey::D:
        case InputKey::E:
          return InputSource::KEYBOARD;
        case InputKey::L_THUMB_X:
        case InputKey::L_THUMB_Y:
        case InputKey::R_THUMB_X:
        case InputKey::R_THUMB_Y:
          return InputSource::GAMEPAD;
        case InputKey::MOUSE_LEFT:
        case InputKey::MOUSE_RIGHT:
        case InputKey::MOUSE_MIDDLE:
        case InputKey::MOUSE_MOVE_X:
        case InputKey::MOUSE_MOVE_Y:
          return InputSource::MOUSE;
        default:
          return InputSource::UNKNOWN;
        }
    }

  InputListener::InputListener(){
    _active = true;
  }
  
  InputListener::~InputListener(){
    _active = false;
  }

  void InputListener::registerActionCallback(const std::string& actionName, const ActionCallback& callback){
    _actionCallbacks[actionName].emplace_back(callback);
  }

  void InputListener::removeActionCallback(const std::string& actionName, const std::string& callbackRef){
    erase_if(_actionCallbacks[actionName], [callbackRef](ActionCallback& callback) {
        return callback.ref == callbackRef;
    });
  }

  void InputListener::mapInputToAction(const InputKey& key, const InputAction& action){
    _inputActionMapping[key].emplace_back(action);
  }

  void InputListener::unmapInputFromAction(const InputKey& key, const std::string& action){
    erase_if(_inputActionMapping[key], [action](InputAction inputAction){
        return inputAction.actionName == action; 
    });
  }

  void InputListener::processInput(){
    std::vector<ActionEvent> events {};
    for(auto& device : _devices){
      auto newState = device.stateFunc(device.index);
      
      for(auto& keyState : newState){
        if(device.currentState[keyState.first].value != keyState.second.value){
          auto generatedEvents = generateActionEvent(device.index, keyState.first, keyState.second.value);
          events.insert(events.end(), generatedEvents.begin(), generatedEvents.end());
          device.currentState[keyState.first].value = keyState.second.value;
        }
      }
    }

    for(auto& event : events){
      propagateActionEvent(event);
    }
  }

  std::vector<InputListener::ActionEvent> InputListener::generateActionEvent(int deviceIndex, InputKey key, float newValue){
    auto& actions = _inputActionMapping[key];

    std::vector<ActionEvent> actionEvents {};

    InputSource source = getInputSourceFromKey(key);

    for(auto& action : actions){
      std::cout << "Generating event for action: " << action.actionName << std::endl;
      actionEvents.emplace_back(ActionEvent {
        .actionName = action.actionName,
        .source = source,
        .sourceIndex = deviceIndex,
        .value = newValue * action.scale
      });

    }

    return actionEvents;
  }

  void InputListener::propagateActionEvent(const ActionEvent& event){
    for (size_t i = _actionCallbacks[event.actionName].size() -1; i >= 0; i--){
      auto& actionCallback = _actionCallbacks[event.actionName][i];

      if(actionCallback.func(event.source, event.sourceIndex, event.value)) break;
    }

//     auto& callbacks = _actionCallbacks[event.actionName];
//     for(auto it = callbacks.rbegin(); it != callbacks.rend(); ++it){
//       ActionCallback& actionCallback = *it;

//       if(actionCallback.func(event.source, event.sourceIndex, event.value)) break;
//     }
//   
  }

  void InputListener::registerDevice(const InputDevice& device){
    _devices.emplace_back(device);
  }

  void InputListener::removeDevice(InputDeviceType type, int inputIndex){
    erase_if(_devices, [type, inputIndex](const InputDevice& device) {
      return device.type == type && device.index == inputIndex;
    });
  }
}
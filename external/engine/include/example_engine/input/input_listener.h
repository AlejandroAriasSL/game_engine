#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <functional>

#include "input_key.h"
#include "input_devices.h"

namespace ONI {

  class InputListener {
    public:
      using ActionCallbackFunc = std::function<bool(InputSource, int, float)>;
    
      struct ActionCallback {
        std::string ref;
        ActionCallbackFunc func;
      };
    
    private:
      struct ActionEvent {
        std::string actionName;
        InputSource source;
        int sourceIndex;
        float value;
      };

    public:
      InputListener();
      ~InputListener();
      
      void registerDevice(const InputDevice& device);
      void removeDevice(InputDeviceType type, int inputIndex);

      void registerActionCallback(const std::string& actionName, const ActionCallback& callback);
      void removeActionCallback(const std::string& actionName, const std::string& callbackRef);
      void mapInputToAction(const InputKey& key, const InputAction& action);
      void unmapInputFromAction(const InputKey& key, const std::string& action);
      
    private:
      friend class Game;
      void processInput();
      std::vector<ActionEvent> generateActionEvent(int deviceIndex, InputKey key, float newValue);
      void propagateActionEvent(const ActionEvent& event);

    private:
      bool _active { false };

      std::unordered_map<InputKey, std::vector<InputAction>> _inputActionMapping {};
      std::unordered_map<std::string, std::vector<ActionCallback>> _actionCallbacks {};

      std::vector<InputDevice> _devices;
  };    
}
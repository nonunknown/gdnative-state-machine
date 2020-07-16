#include "native_state_machine.hpp"

using namespace godot;

void NativeStateMachine::_register_methods()
{
    register_method("register_state", &NativeStateMachine::register_state);
    register_method("change_state", &NativeStateMachine::change_state);
    register_method("update", &NativeStateMachine::update);
}

void NativeStateMachine::_init()
{
}

void NativeStateMachine::update()
{
    target->call("st_update_"+states[current_state]);
}

void NativeStateMachine::change_state(uint8_t state_to)
{
    target->call("st_exit_"+states[current_state]);
    last_state = current_state;
    current_state = state_to;
    target->call("st_init_"+states[current_state]);
}

void NativeStateMachine::register_state(Node* _target, Array keys)
{
    target = _target;
    states = new String[keys.size()];

    for (int i = 0;i<keys.size();i++) {
        states[i] = keys[i];

    }

    current_state = 0;
    last_state = 0;

    target->call("st_init_"+states[0]);
}

NativeStateMachine::NativeStateMachine()
{
}

NativeStateMachine::~NativeStateMachine()
{
}

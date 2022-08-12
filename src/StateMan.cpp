#include "StateMan.hpp"

Engine::StateMan::StateMan() {

}

Engine::StateMan::~StateMan() {

}


void Engine::StateMan::Add(std::unique_ptr<State> toAdd, bool replace = false) {

}

void Engine::StateMan::PopCurrent() {

}

void Engine::StateMan::ProcessStateChange() {

}

std::unique_ptr<Engine::State>& Engine::StateMan::GetCurrent() {

}
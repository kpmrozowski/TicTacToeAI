#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

namespace mro {
	typedef std::unique_ptr<State> StateRef;

	class StateMachine {
		public:
		StateMachine() {}
		~StateMachine() {}

		void AddState(StateRef newState, bool isReplacing = true);
		void RemoveState();
		// Run at start of each loop in Game.cpp
		void ProcessStateChanges();

		StateRef& GetActiveState();

		private:
		std::stack<StateRef> _states; //All states on our stack
		StateRef _newState;

		bool _isRemoving{}, _isAdding{}, _isReplacing{};
	};
}
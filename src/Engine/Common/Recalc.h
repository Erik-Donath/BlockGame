//
// Created by erikd on 07.05.2024.
//

#pragma once

namespace Engine::Common {
    template<typename Object, typename Watch>
    class Recalc {
    public:
        Recalc(Object(*function)(Watch*), Watch* state): m_function(function), m_lastState(*state), m_currentState(state), m_object(function(state)) { };

        Object get() {
            if(m_lastState != *m_currentState) {
                m_object = m_function(*m_currentState);
                m_lastState = *m_currentState;
            }
            return m_object;
        }

        inline explicit operator Object() {
            return get();
        }
    private:
        Object (*m_function)(Watch*);
        Object m_object;
        Watch m_lastState;
        Watch* m_currentState;
    };
}
#pragma once
#include "SharedContext.h"
#include "BaseState.h"

enum class StateType{ MainMenu = 1, Game, Paused };

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager
{
public:
    StateManager(SharedContext* shared);
    ~StateManager();

    void Update(const sf::Time& time);
    void Draw();

    void ProcessRequests();

    SharedContext* GetContext();
    bool HasState(const StateType type);

    void SwitchTo(const StateType type);
    void Remove(const StateType type);

    void HandlePlayerInput(const std::optional<sf::Event>& event);
private:
    void CreateState(const StateType type);
    void RemoveState(const StateType type);

    template<class T>
    void RegisterState(const StateType type){
        m_stateFactory[type] = [this]() -> BaseState*
        {
            return new T(this);
        };
    }

    SharedContext* m_shared;
    StateContainer m_states;
    TypeContainer m_toRemove;
    StateFactory m_stateFactory;
};

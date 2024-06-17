#pragma once
#include "Component.h"
#include "AIState.h"
#include <string>
#include <unordered_map>
class AIComponent :
    public Component
{
public:
    AIComponent(Actor* owner);

    void Update(float deltaTime)override;
    /// <summary>
    /// 根据状态名改变状态
    /// </summary>
    /// <param name="name">状态名</param>
    void ChangeState(const std::string& name);

    /// <summary>
    /// 组件注册对应的一系列状态
    /// </summary>
    /// <param name="state">状态</param>
    void RegisterState(AIState* state);
private:
    std::unordered_map<std::string, AIState*>mStateMap;
    AIState* mCurrentState;                              //当前状态   
};


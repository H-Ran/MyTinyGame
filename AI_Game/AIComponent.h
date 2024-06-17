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
    /// ����״̬���ı�״̬
    /// </summary>
    /// <param name="name">״̬��</param>
    void ChangeState(const std::string& name);

    /// <summary>
    /// ���ע���Ӧ��һϵ��״̬
    /// </summary>
    /// <param name="state">״̬</param>
    void RegisterState(AIState* state);
private:
    std::unordered_map<std::string, AIState*>mStateMap;
    AIState* mCurrentState;                              //��ǰ״̬   
};


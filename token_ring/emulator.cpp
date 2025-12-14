#include "emulator.hpp"
#include <iostream>
#include <algorithm>

Emulator::Emulator() : current_agent_index(0), current_data(std::make_unique<Token>()) {}

void Emulator::AddAgent(std::shared_ptr<BaseAgent> agent) {
    if (agent_map.find(agent->getId()) != agent_map.end()) {
        return;
    }
    
    agents.push_back(agent);
    agent_map[agent->getId()] = agent;
}

void Emulator::DelAgent(int agent_id) {
    if (agent_id == 0) {
        return;
    }
    
    auto it = std::find_if(agents.begin(), agents.end(),
        [agent_id](const std::shared_ptr<BaseAgent>& agent) {
            return agent->getId() == agent_id;
        });
    
    if (it != agents.end()) {
        agent_map.erase(agent_id);
        agents.erase(it);
        if (current_agent_index >= agents.size()) {
            current_agent_index = 0;
        }
    }
}

void Emulator::Run() {
    while (true) {
        RunSingleCycle();
    }
}

void Emulator::RunSingleCycle() {
    if (agents.empty()) {
        return;
    }
    
    auto& agent = agents[current_agent_index];
    auto next_data = agent->Process(*current_data);
    
    current_data = std::move(next_data);
    current_agent_index = (current_agent_index + 1) % agents.size();
}

BaseAgent* Emulator::getAgentById(int id) {
    auto it = agent_map.find(id);
    if (it != agent_map.end()) {
        return it->second.get();
    }
    return nullptr;
}

std::vector<int> Emulator::getAllAgentIds() const {
    std::vector<int> ids;
    for (const auto& agent : agents) {
        ids.push_back(agent->getId());
    }
    return ids;
}

bool Emulator::agentExists(int id) const {
    return agent_map.find(id) != agent_map.end();
}

void Emulator::sendToNextAgent() {
    RunSingleCycle();
}
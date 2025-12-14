#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "agent.hpp"
#include <vector>
#include <memory>
#include <unordered_map>

class Emulator {
public:
    Emulator();
    
    void AddAgent(std::shared_ptr<BaseAgent> agent);
    void DelAgent(int agent_id);
    void Run();
    void RunSingleCycle();
    
    BaseAgent* getAgentById(int id);
    std::vector<int> getAllAgentIds() const;
    bool agentExists(int id) const;
    
private:
    std::vector<std::shared_ptr<BaseAgent>> agents;
    std::unordered_map<int, std::shared_ptr<BaseAgent>> agent_map;
    size_t current_agent_index;
    std::unique_ptr<Data> current_data;
    
    void sendToNextAgent();
};

#endif // EMULATOR_HPP
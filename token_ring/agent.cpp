#include "agent.hpp"
#include "emulator.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

const size_t MAX_MESSAGE_SIZE = 32;
SimpleAgent::SimpleAgent(int id) : BaseAgent(id) {}

std::unique_ptr<Data> SimpleAgent::Process(Data& recvdata) {
    if (recvdata.GetType() == DataType::kToken) {
        if (!message_queue.empty()) {
            auto [receiver_id, message] = message_queue.front();
            message_queue.pop();
            
            if (message_queue.empty()) {
                has_data = false;
            }
            auto parts = splitMessage(message, MAX_MESSAGE_SIZE - 20);
            
            if (parts.size() == 1) {
                return std::make_unique<Message>(id, receiver_id, message);
            } else {
                int msg_id = Message::generateMessageId();
                return std::make_unique<Message>(id, receiver_id, parts[0], true, parts.size(), 1, msg_id);
            }
        }
        return std::make_unique<Token>();
    }
    Message& msg = dynamic_cast<Message&>(recvdata);
    if (msg.getSenderId() == id) {
        return std::make_unique<Token>();
    }
    if (msg.getReceiverId() == id || msg.getReceiverId() == -1) {
        if (msg.getIsPart()) {
            int msg_id = msg.getMessageId();
            if (partial_messages.find(msg_id) == partial_messages.end()) {
                MessagePart mp;
                mp.message_id = msg_id;
                mp.parts.resize(msg.getTotalParts());
                mp.received_parts = 0;
                partial_messages[msg_id] = mp;
            }
            auto& mp = partial_messages[msg_id];
            mp.parts[msg.getPartNum() - 1] = msg.getData();
            mp.received_parts++;
            
            if (mp.received_parts == msg.getTotalParts()) {
                auto full_message = assembleMessage(msg_id, mp);
                partial_messages.erase(msg_id);
                if (full_message) {
                    Message* full_msg = dynamic_cast<Message*>(full_message.get());
                    printReceivedMessage(full_msg->getSenderId(), full_msg->getData());
                }
            }
        } else {
            printReceivedMessage(msg.getSenderId(), msg.getData());
        }
    }
    return std::make_unique<Message>(msg);
}

void SimpleAgent::addMessageToQueue(int receiver_id, const std::string& message) {
    message_queue.push({receiver_id, message});
    has_data = true;
}

void SimpleAgent::printReceivedMessage(int sender_id, const std::string& message) {
    std::cout << "#" << id << " recv from #" << sender_id << ": " << message << std::endl;
}

std::vector<std::string> SimpleAgent::splitMessage(const std::string& message, size_t max_size) {
    std::vector<std::string> parts;
    size_t start = 0;
    
    while (start < message.length()) {
        size_t end = start + max_size;
        if (end > message.length()) {
            end = message.length();
        }
        parts.push_back(message.substr(start, end - start));
        start = end;
    }
    
    return parts;
}

std::unique_ptr<Data> SimpleAgent::assembleMessage(int message_id, const MessagePart& mp) {
    std::string full_message;
    for (const auto& part : mp.parts) {
        full_message += part;
    }
    
    return std::make_unique<Message>(0, id, full_message);
}

AutoReplyAgent::AutoReplyAgent(int id) : BaseAgent(id) {}

std::unique_ptr<Data> AutoReplyAgent::Process(Data& recvdata) {
    if (recvdata.GetType() == DataType::kToken) {
return std::make_unique<Token>();
    }
    
    Message& msg = dynamic_cast<Message&>(recvdata);
    
    if (msg.getSenderId() == id) {
        return std::make_unique<Token>();
    }
    
    if (msg.getReceiverId() == id || msg.getReceiverId() == -1) {
        if (msg.getIsPart()) {
            int msg_id = msg.getMessageId();
            
            if (partial_messages.find(msg_id) == partial_messages.end()) {
                MessagePart mp;
                mp.message_id = msg_id;
                mp.parts.resize(msg.getTotalParts());
                mp.received_parts = 0;
                partial_messages[msg_id] = mp;
            }
            
            auto& mp = partial_messages[msg_id];
            mp.parts[msg.getPartNum() - 1] = msg.getData();
            mp.received_parts++;
            
            if (mp.received_parts == msg.getTotalParts()) {
                auto full_message = assembleMessage(msg_id, mp);
                partial_messages.erase(msg_id);
                
                if (full_message) {
                    Message* full_msg = dynamic_cast<Message*>(full_message.get());
                    printReceivedMessage(full_msg->getSenderId(), full_msg->getData());
                    reverseAndSend(full_msg->getSenderId(), full_msg->getData());
                }
            }
        } else {
            printReceivedMessage(msg.getSenderId(), msg.getData());
            reverseAndSend(msg.getSenderId(), msg.getData());
        }
    }
    
    return std::make_unique<Message>(msg);
}

void AutoReplyAgent::addMessageToQueue(int receiver_id, const std::string& message) {
}

void AutoReplyAgent::printReceivedMessage(int sender_id, const std::string& message) {
    std::cout << "#" << id << " recv from #" << sender_id << ": " << message << std::endl;
}

void AutoReplyAgent::reverseAndSend(int sender_id, const std::string& message) {
    std::string reversed = reverseWords(message);
    
    auto parts = splitMessage(reversed, MAX_MESSAGE_SIZE - 20);
    std::cout << "#" << id << " auto-reply to #" << sender_id << ": " << reversed << std::endl;
}

std::vector<std::string> AutoReplyAgent::splitMessage(const std::string& message, size_t max_size) {
    std::vector<std::string> parts;
    size_t start = 0;
    
    while (start < message.length()) {
        size_t end = start + max_size;
        if (end > message.length()) {
            end = message.length();
        }
        parts.push_back(message.substr(start, end - start));
        start = end;
    }
    
    return parts;
}

std::unique_ptr<Data> AutoReplyAgent::assembleMessage(int message_id, const MessagePart& mp) {
    std::string full_message;
    for (const auto& part : mp.parts) {
        full_message += part;
    }
    
    return std::make_unique<Message>(0, id, full_message);
}

std::string AutoReplyAgent::reverseWords(const std::string& text) {
    std::stringstream ss(text);
    std::vector<std::string> words;
    std::string word;
    
    while (ss >> word) {
        words.push_back(word);
    }
    
    std::reverse(words.begin(), words.end());
    
    std::string result;
    for (size_t i = 0; i < words.size(); ++i) {
        if (i > 0) result += " ";
        result += words[i];
    }
    
    return result;
}

MainAgent::MainAgent(int id, Emulator* emulator) 
    : BaseAgent(id), emulator(emulator), should_exit(false) {}

std::unique_ptr<Data> MainAgent::Process(Data& recvdata) {
    if (recvdata.GetType() == DataType::kToken) {
        bool any_agent_has_data = false;
        auto agent_ids = emulator->getAllAgentIds();
for (int agent_id : agent_ids) {
            auto agent = emulator->getAgentById(agent_id);
            if (agent && agent->hasData()) {
                any_agent_has_data = true;
                break;
            }
        }
        
        if (!any_agent_has_data) {
            handleConsoleInput();
        }
        
        if (!message_queue.empty()) {
            auto [receiver_id, message] = message_queue.front();
            message_queue.pop();
            
            if (message_queue.empty()) {
                has_data = false;
            }
            
            auto parts = splitMessage(message, MAX_MESSAGE_SIZE - 20);
            
            if (parts.size() == 1) {
                return std::make_unique<Message>(id, receiver_id, message);
            } else {
                int msg_id = Message::generateMessageId();
                return std::make_unique<Message>(id, receiver_id, parts[0], true, parts.size(), 1, msg_id);
            }
        }
        
        return std::make_unique<Token>();
    }
    
    Message& msg = dynamic_cast<Message&>(recvdata);
    
    if (msg.getSenderId() == id) {
        return std::make_unique<Token>();
    }
    
    if (msg.getReceiverId() == id || msg.getReceiverId() == -1) {
        if (msg.getIsPart()) {
            int msg_id = msg.getMessageId();
            
            if (partial_messages.find(msg_id) == partial_messages.end()) {
                MessagePart mp;
                mp.message_id = msg_id;
                mp.parts.resize(msg.getTotalParts());
                mp.received_parts = 0;
                partial_messages[msg_id] = mp;
            }
            
            auto& mp = partial_messages[msg_id];
            mp.parts[msg.getPartNum() - 1] = msg.getData();
            mp.received_parts++;
            
            if (mp.received_parts == msg.getTotalParts()) {
                auto full_message = assembleMessage(msg_id, mp);
                partial_messages.erase(msg_id);
                
                if (full_message) {
                    Message* full_msg = dynamic_cast<Message*>(full_message.get());
                    printReceivedMessage(full_msg->getSenderId(), full_msg->getData());
                }
            }
        } else {
            printReceivedMessage(msg.getSenderId(), msg.getData());
        }
    }
    
    return std::make_unique<Message>(msg);
}

void MainAgent::handleConsoleInput() {
    std::cout << "> ";
    std::string line;
    if (!std::getline(std::cin, line)) {
        return;
    }
    
    auto tokens = splitString(line, ' ');
    if (tokens.empty()) return;
    
    std::string command = tokens[0];
    
    try {
        if (command == "r" || command == "run") {
            runCycle();
        } else if (command == "a" || command == "add") {
            if (tokens.size() < 2) {
                std::cout << "Error: missing agent id" << std::endl;
                return;
            }
            int agent_id = std::stoi(tokens[1]);
            addSimpleAgent(agent_id);
        } else if (command == "aa" || command == "aadd") {
            if (tokens.size() < 2) {
                std::cout << "Error: missing agent id" << std::endl;
                return;
            }
            int agent_id = std::stoi(tokens[1]);
            addAutoReplyAgent(agent_id);
        } else if (command == "d" || command == "del") {
            if (tokens.size() < 2) {
                std::cout << "Error: missing agent id" << std::endl;
                return;
            }
            int agent_id = std::stoi(tokens[1]);
            deleteAgent(agent_id);
        } else if (command == "s" || command == "send") {
            if (tokens.size() < 4) {
                std::cout << "Error: missing parameters" << std::endl;
return;
            }
            int sender_id = std::stoi(tokens[1]);
            int receiver_id = std::stoi(tokens[2]);
            
            std::string message;
            for (size_t i = 3; i < tokens.size(); ++i) {
                if (i > 3) message += " ";
                message += tokens[i];
            }
            
            sendMessage(sender_id, receiver_id, message);
        } else if (command == "e" || command == "exit") {
            should_exit = true;
        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void MainAgent::addSimpleAgent(int id) {
    if (emulator->agentExists(id)) {
        std::cout << "Error: agent #" << id << " already exists" << std::endl;
        return;
    }
    
    auto agent = std::make_shared<SimpleAgent>(id);
    emulator->AddAgent(agent);
    std::cout << "Added simple agent #" << id << std::endl;
}

void MainAgent::addAutoReplyAgent(int id) {
    if (emulator->agentExists(id)) {
        std::cout << "Error: agent #" << id << " already exists" << std::endl;
        return;
    }
    
    auto agent = std::make_shared<AutoReplyAgent>(id);
    emulator->AddAgent(agent);
    std::cout << "Added auto-reply agent #" << id << std::endl;
}

void MainAgent::deleteAgent(int id) {
    if (id == 0) {
        std::cout << "Error: cannot delete main agent (id=0)" << std::endl;
        return;
    }
    
    if (!emulator->agentExists(id)) {
        std::cout << "Error: agent #" << id << " does not exist" << std::endl;
        return;
    }
    
    emulator->DelAgent(id);
    std::cout << "Deleted agent #" << id << std::endl;
}

void MainAgent::sendMessage(int sender_id, int receiver_id, const std::string& message) {
    auto agent = emulator->getAgentById(sender_id);
    if (!agent) {
        std::cout << "Error: sender agent #" << sender_id << " does not exist" << std::endl;
        return;
    }
    
    // Check if sender is an AutoReplyAgent
    if (dynamic_cast<AutoReplyAgent*>(agent)) {
        std::cout << "Error: cannot send from auto-reply agent" << std::endl;
        return;
    }
    
    agent->addMessageToQueue(receiver_id, message);
    std::cout << "Message queued for sending from #" << sender_id << " to #" << receiver_id << std::endl;
}

void MainAgent::runCycle() {
    emulator->RunSingleCycle();
}

void MainAgent::addMessageToQueue(int receiver_id, const std::string& message) {
    message_queue.push({receiver_id, message});
    has_data = true;
}

void MainAgent::printReceivedMessage(int sender_id, const std::string& message) {
    std::cout << "#" << id << " recv from #" << sender_id << ": " << message << std::endl;
}

std::vector<std::string> MainAgent::splitMessage(const std::string& message, size_t max_size) {
    std::vector<std::string> parts;
    size_t start = 0;
    
    while (start < message.length()) {
        size_t end = start + max_size;
        if (end > message.length()) {
            end = message.length();
        }
        parts.push_back(message.substr(start, end - start));
        start = end;
    }
    
    return parts;
}

std::unique_ptr<Data> MainAgent::assembleMessage(int message_id, const MessagePart& mp) {
    std::string full_message;
    for (const auto& part : mp.parts) {
        full_message += part;
    }
    
    return std::make_unique<Message>(0, id, full_message);
}

std::vector<std::string> MainAgent::splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

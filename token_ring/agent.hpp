#ifndef AGENT_HPP
#define AGENT_HPP

#include "data.hpp"
#include <queue>
#include <string>
#include <memory>
#include <unordered_map>

class BaseAgent {
public:
    BaseAgent(int id) : id(id), has_data(false) {}
    virtual ~BaseAgent() = default;
    
    int getId() const { return id; }
    bool hasData() const { return has_data; }
    
    virtual std::unique_ptr<Data> Process(Data& recvdata) = 0;
    virtual void addMessageToQueue(int receiver_id, const std::string& message) = 0;
    virtual void printReceivedMessage(int sender_id, const std::string& message) = 0;
    virtual void reverseAndSend(int sender_id, const std::string& message) {}
    
protected:
    int id;
    bool has_data;
};

class SimpleAgent : public BaseAgent {
public:
    SimpleAgent(int id);
    std::unique_ptr<Data> Process(Data& recvdata) override;
    void addMessageToQueue(int receiver_id, const std::string& message) override;
    void printReceivedMessage(int sender_id, const std::string& message) override;
    
private:
    struct MessagePart {
        int message_id;
        std::vector<std::string> parts;
        int received_parts;
    };
    
    std::queue<std::pair<int, std::string>> message_queue;
    std::unordered_map<int, MessagePart> partial_messages;
    std::unique_ptr<Data> assembleMessage(int message_id, const MessagePart& mp);
    std::vector<std::string> splitMessage(const std::string& message, size_t max_size);
};

class AutoReplyAgent : public BaseAgent {
public:
    AutoReplyAgent(int id);
    std::unique_ptr<Data> Process(Data& recvdata) override;
    void addMessageToQueue(int receiver_id, const std::string& message) override;
    void printReceivedMessage(int sender_id, const std::string& message) override;
    void reverseAndSend(int sender_id, const std::string& message) override;
    
private:
    struct MessagePart {
        int message_id;
        std::vector<std::string> parts;
        int received_parts;
    };
    
    std::unordered_map<int, MessagePart> partial_messages;
    std::vector<std::string> splitMessage(const std::string& message, size_t max_size);
    std::unique_ptr<Data> assembleMessage(int message_id, const MessagePart& mp);
    std::string reverseWords(const std::string& text);
};

class MainAgent : public BaseAgent {
public:
    MainAgent(int id, class Emulator* emulator);
    std::unique_ptr<Data> Process(Data& recvdata) override;
    void addMessageToQueue(int receiver_id, const std::string& message) override;
    void printReceivedMessage(int sender_id, const std::string& message) override;
    
    void handleConsoleInput();
    void addSimpleAgent(int id);
    void addAutoReplyAgent(int id);
    void deleteAgent(int id);
    void sendMessage(int sender_id, int receiver_id, const std::string& message);
    void runCycle();
    
private:
    struct MessagePart {
        int message_id;
        std::vector<std::string> parts;
        int received_parts;
    };
    
    class Emulator* emulator;
    std::queue<std::pair<int, std::string>> message_queue;
    std::unordered_map<int, MessagePart> partial_messages;
    bool should_exit;
    
    std::vector<std::string> splitMessage(const std::string& message, size_t max_size);
    std::unique_ptr<Data> assembleMessage(int message_id, const MessagePart& mp);
    std::vector<std::string> splitString(const std::string& str, char delimiter);
};

#endif
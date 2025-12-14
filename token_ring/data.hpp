#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <vector>

enum class DataType {
    kToken,
    kMessage
};

class Data {
public:
    explicit Data(DataType dt) : datatype(dt) {}
    virtual ~Data() = default;
    DataType GetType() const { return datatype; }
    
protected:
    DataType datatype;
};

class Token : public Data {
public:
    Token() : Data(DataType::kToken) {}
};

class Message : public Data {
public:
    Message(int sender_id, int receiver_id, const std::string& data, bool is_part = false, 
            int total_parts = 1, int part_num = 1, int message_id = -1)
        : Data(DataType::kMessage), 
          sender_id(sender_id), receiver_id(receiver_id), 
          data(data), is_part(is_part), 
          total_parts(total_parts), part_num(part_num),
          message_id(message_id == -1 ? generateMessageId() : message_id) {}
    
    int getSenderId() const { return sender_id; }
    int getReceiverId() const { return receiver_id; }
    std::string getData() const { return data; }
    bool getIsPart() const { return is_part; }
    int getTotalParts() const { return total_parts; }
    int getPartNum() const { return part_num; }
    int getMessageId() const { return message_id; }
    
    static int generateMessageId() {
        static int counter = 0;
        return ++counter;
    }
    
private:
    int sender_id;
    int receiver_id;
    std::string data;
    bool is_part;
    int total_parts;
    int part_num;
    int message_id;
};

#endif

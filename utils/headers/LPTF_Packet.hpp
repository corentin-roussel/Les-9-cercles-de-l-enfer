#include <cstdint>

class LPTF_Packet
{
private:
    
public:
    LPTF_Packet(/* args */);
    ~LPTF_Packet();

    struct command_exchange
    {
        uint8_t type;
        uint8_t data;
        uint16_t size;
    };
    
};



#include "ip_math.h"

struct ipNotation {
    uint8_t first;
    uint8_t second;
    uint8_t third;
    uint8_t fourth;
};

uint32_t ipFormatToInteger(const string ip) {
    uint8_t ipFormat[4] = {0};
    
	sscanf(ip, "%hhu.%hhu.%hhu.%hhu", 
        ipFormat,
	    ipFormat + 1,
	    ipFormat + 2,
	    ipFormat + 3);
    
    return (ipFormat[0] << 24) | (ipFormat[1] << 16) | (ipFormat[2] << 8) | ipFormat[3];
    // ipNotation notation = {0};

    // sscanf(ip, "%hhu.%hhu.%hhu.%hhu",
    //     &notation.fourth,
    //     &notation.third,
    //     &notation.second,
    //     &notation.first);

    // return *(uint32_t *)&notation;
}

void integerToIPFormat(uint32_t ip, const string buffer) {
    sprintf(buffer, "%u.%u.%u.%u", 
            (ip & 0xff000000) >> 24,
            (ip & 0xff0000) >> 16,
            (ip & 0xff00) >> 8,
            (ip & 0xff));

    // ipNotation notation = *(ipNotation *)&ip;
    // sprintf(buffer, "%u.%u.%u.%u", 
    //     notation.fourth,
    //     notation.third,
    //     notation.second,
    //     notation.first);
}

uint32_t getNetworkMask(uint8_t mask) {
    uint32_t networkMask = 0x00000000;

    for (uint8_t bitPos = MASK_MAX_LEN - 1; mask != 0; --mask, --bitPos) {
        networkMask |= (1 << bitPos);
    }

    return networkMask;
}

void getNetworkID(const string ipAddress, uint8_t mask, const string buffer) {
    integerToIPFormat(
        (uint32_t)(ipFormatToInteger(ipAddress) & getNetworkMask(mask)),
        buffer);
}

uint32_t getSubnetCardinality(uint8_t mask) {
    return (1 << (MASK_MAX_LEN - mask)) - 2;
}

bool checkSubnetMembership(const string networkID, uint8_t mask, const string ip) {
    uint8_t buffer[PREFIX_LEN] = {0};
    getNetworkID(ip, mask, buffer);

    if (strcmp(networkID, buffer) == 0) {
        return true;
    } else {
        return false;
    }
}

void getBroadcastAddress(string ipAddress, uint8_t mask, const string outputBuffer) {
    uint32_t integerIP = ipFormatToInteger(ipAddress);
    uint32_t networkMask = getNetworkMask(mask);
    uint32_t networkID = integerIP & networkMask;
    uint32_t broadcastIP = networkID | (~networkMask);

    integerToIPFormat(broadcastIP, outputBuffer);
}
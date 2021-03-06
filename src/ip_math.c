#include "ip_math.h"

struct ipv4AddressFormat {
    uint8_t first;
    uint8_t second;
    uint8_t third;
    uint8_t fourth;
};

struct ipv4Notation {
    union {
        uint32_t numIP;
        uint8_t strIP[PREFIX_LEN + 1];
    };
    union {
        uint8_t numMask;
        uint8_t strMask[PREFIX_LEN + 1];
    };
};

uint32_t ipFormatToInteger(const string ip) {
    ipv4AddressFormat format = {0};

    sscanf(ip, "%hhu.%hhu.%hhu.%hhu",
        &format.fourth,
        &format.third,
        &format.second,
        &format.first);

    return *(uint32_t *)&format;
}

void integerToIPFormat(uint32_t ip, const string buffer) {
    ipv4AddressFormat format = *(ipv4AddressFormat *)&ip;

    sprintf(buffer, "%u.%u.%u.%u", 
        format.fourth,
        format.third,
        format.second,
        format.first);
}

uint32_t getNetworkMask(uint8_t mask) {
    uint32_t networkMask = 0x00000000;

    for (uint8_t bitPos = MASK_MAX_LEN - 1; mask != 0; --mask, --bitPos) {
        networkMask |= (1 << bitPos);
    }

    return networkMask;
}

ipv4Notation *parseIPv4address(const string ip) {
    ipv4Notation *notation = (ipv4Notation *)malloc(sizeof(ipv4Notation));
    sscanf(ip, "%[^/]/%hhu", notation->strIP, &notation->numMask);
    return notation;
}

void getNetworkID(const string ip, const string buffer) {
    ipv4Notation *notation = parseIPv4address(ip);
    uint32_t integerIP = ipFormatToInteger(notation->strIP);
    uint32_t networkMask = getNetworkMask(notation->numMask);
    
    integerToIPFormat(integerIP & networkMask, buffer);

    free(notation);
}

uint32_t getSubnetCardinality(uint8_t mask) {
    if (1 < mask && mask < 31) {
        return (1 << (MASK_MAX_LEN - mask)) - 2;
    } else if (mask == 31) {
        // point-to-point link
        return 2;
    } else if (mask == 32) {
        // host route
        return 1;
    } else {
        return 0;
    }
}

bool checkSubnetMembership(const string networkID, const string ip) {
    uint8_t checkIP[PREFIX_LEN + 1] = {0};
    getNetworkID(ip, checkIP);

    if (strcmp(networkID, checkIP) == 0) {
        return true;
    } else {
        return false;
    }
}

void getBroadcastAddress(const string ip, const string outputBuffer) {
    ipv4Notation *notation = parseIPv4address(ip); 
    uint32_t integerIP = ipFormatToInteger(notation->strIP);
    uint32_t networkMask = getNetworkMask(notation->numMask);
    uint32_t networkID = integerIP & networkMask;
    uint32_t broadcastIP = networkID | (~networkMask);

    integerToIPFormat(broadcastIP, outputBuffer);
    free(notation);
}

uint8_t **getHosts(const string ip, uint32_t *quanity) {
    ipv4Notation *notation = parseIPv4address(ip);
    *quanity = getSubnetCardinality(notation->numMask);
    uint32_t startHost = ipFormatToInteger(notation->strIP);
    uint8_t ipBuffer[PREFIX_LEN + 1] = {0};
    uint8_t **hosts = (uint8_t **)malloc((*quanity) * sizeof(uint8_t *));
    memset(hosts, 0, (*quanity) * sizeof(uint8_t *));

    for (uint32_t hostIdx = 0; hostIdx < (*quanity); ++hostIdx) {
        integerToIPFormat(startHost + hostIdx + 1, ipBuffer);
        hosts[hostIdx] = (uint8_t *)malloc((PREFIX_LEN + 1) * sizeof(uint8_t));
        strcpy(hosts[hostIdx], ipBuffer);
    }

    free(notation);
    return hosts;
}
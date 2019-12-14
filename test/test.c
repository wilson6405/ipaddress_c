#include "../src/ip_math.h"
#include "assert.h"

int main(void) {
    
    /* Q1 */
    // Test case 1
    {
        uint8_t ipBuffer[PREFIX_LEN + 1] = {0};
        string ipAddress = "192.168.2.10";
        uint8_t mask = 24;
        getBroadcastAddress(ipAddress, mask, ipBuffer);
        assert(strcmp(ipBuffer, "192.168.2.255") == 0);
    }
    

    // Test case 2
    {
        uint8_t ipBuffer[PREFIX_LEN + 1] = {0};
        string ipAddress = "10.1.23.10";
        uint8_t mask = 20;
        getBroadcastAddress(ipAddress, mask, ipBuffer);
        assert(strcmp(ipBuffer, "10.1.31.255") == 0);
    }
    

    /* Q2 */
    // Test case 1
    {
        string ipAddress = "192.168.2.10";
        uint32_t intIP = ipFormatToInteger(ipAddress);
        assert(intIP == 3232236042);
    }
    

    // Test case 2
    {
        string ipAddress = "10.1.23.10";
        uint32_t intIP = ipFormatToInteger(ipAddress);
        assert(intIP == 167843594);
    }
    

    /* Q3 */
    {
        uint8_t ipBuffer[PREFIX_LEN + 1] = {0};
        uint32_t intIP = 2058138165;
        integerToIPFormat(intIP, ipBuffer);
        assert(strcmp(ipBuffer, "122.172.178.53") == 0);
    }
    

    /* Q4 */
    {
        uint8_t ipBuffer[PREFIX_LEN + 1] = {0};
        string ipAddress = "192.168.2.10";
        uint8_t mask = 20;
        getNetworkID(ipAddress, mask, ipBuffer);
        assert(strcmp(ipBuffer, "192.168.0.0") == 0);
    }
    

    /* Q5 */
    {
        uint8_t mask = 24;
        assert(getSubnetCardinality(mask) == 254);
    }
    

    /* Q6 */
    {
        string networkID = "192.168.0.0";
        uint8_t mask = 24;
        string checkIP = "192.168.0.13";
        bool result = checkSubnetMembership(networkID, mask, checkIP);
        assert(result == true);
    }
    
    printf("All pass!\n");
    return 0;
}
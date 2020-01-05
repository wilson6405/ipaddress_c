#include "../src/ip_math.h"
#include "assert.h"

int main(void) {
    
    /* Q1 */
    // Test case 1
    {
        uint8_t ipBuffer[PREFIX_LEN + 1] = {0};
        string ipAddress = "192.168.2.10/24";
        getBroadcastAddress(ipAddress, ipBuffer);
        assert(strcmp(ipBuffer, "192.168.2.255") == 0);
    }
    

    // Test case 2
    {
        uint8_t ipBuffer[PREFIX_LEN + 1] = {0};
        string ipAddress = "10.1.23.10/20";
        getBroadcastAddress(ipAddress, ipBuffer);
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
        string ipAddress = "192.168.2.10/20";
        getNetworkID(ipAddress, ipBuffer);
        assert(strcmp(ipBuffer, "192.168.0.0") == 0);
    }
    

    /* Q5 */
    {
        uint8_t mask = 24;
        assert(getSubnetCardinality(mask) == 254);
    }

    {
        uint8_t mask = 30;
        assert(getSubnetCardinality(mask) == 2);
    }

    {
        uint8_t mask = 31;
        assert(getSubnetCardinality(mask) == 2);
    }

    {
        uint8_t mask = 32;
        assert(getSubnetCardinality(mask) == 1);
    }

    {
        uint8_t mask = 33;
        assert(getSubnetCardinality(mask) == 0);
    }
    
    /* Q6 */
    {
        string networkID = "192.168.0.0";
        string checkIP = "192.168.0.13/24";
        bool result = checkSubnetMembership(networkID, checkIP);
        assert(result == true);
    }

    {
        string ipNetwork = "192.0.2.0/29";
        string testHosts[] = {
            "192.0.2.1",
            "192.0.2.2",
            "192.0.2.3",
            "192.0.2.4",
            "192.0.2.5",
            "192.0.2.6"
        };
        uint32_t quantity = 0;
        uint8_t **hosts = getHosts(ipNetwork, &quantity);
        
        for (uint32_t idx = 0; idx < quantity; ++idx) {
            assert(strcmp(testHosts[idx], hosts[idx]) == 0);
            free(hosts[idx]);
        }

        free(hosts);
    }
    
    printf("All pass!\n");
    return 0;
}
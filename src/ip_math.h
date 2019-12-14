#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define PREFIX_LEN 15
#define MASK_MAX_LEN 32
typedef unsigned char *string;
typedef struct ipNotation ipNotation;

uint32_t ipFormatToInteger(const string);
void integerToIPFormat(uint32_t, const string);
uint32_t getNetworkMask(uint8_t);
void getBroadcastAddress(string, uint8_t, const string);
void getNetworkID(const string, uint8_t, const string);
uint32_t getSubnetCardinality(uint8_t);
bool checkSubnetMembership(const string, uint8_t, const string);
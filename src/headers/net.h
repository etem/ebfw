#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <net/ip.h>
#include <linux/tcp.h>

void initNetModule(void);
void cleanupNetModule(void);

extern unsigned long long blockedPackets;
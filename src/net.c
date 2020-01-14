#include "cdev.h"
#include "net.h"

unsigned long long blockedPackets = 0;

static unsigned int inHook(void *priv, struct sk_buff *skb, const struct nf_hook_state *state);
static unsigned int outHook(void *priv, struct sk_buff *skb, const struct nf_hook_state *state);

static struct nf_hook_ops nfho_pre = {
    .hook     = inHook,
    .pf       = PF_INET,
    .hooknum  = NF_INET_PRE_ROUTING,
    .priority = NF_IP_PRI_FIRST
};

static struct nf_hook_ops nfho_post = {
    .hook     = outHook,
    .pf       = PF_INET,
    .hooknum  = NF_INET_POST_ROUTING,
    .priority = NF_IP_PRI_LAST,
};

static unsigned int inHook(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
	struct iphdr *iph;
    int eb;
    
    if(evilBlockMode)
    {
        iph = ip_hdr(skb);
        eb = iph->frag_off & 0x80; // LITTLE ENDIAN
        if (eb)
        {
            blockedPackets += 1;
            return NF_DROP;
        }
    }

    return NF_ACCEPT;
}

static unsigned int outHook(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
	struct iphdr *iph;

    if(evilUserMode)
    {
        iph = ip_hdr(skb);
        iph->check = 0;
        iph->frag_off |= 0x80; // LITTLE ENDIAN
        ip_send_check (iph);
    }

    return NF_ACCEPT;
}

void initNetModule(void)
{
    nf_register_net_hook(&init_net, &nfho_pre);
    nf_register_net_hook(&init_net, &nfho_post);
}

void cleanupNetModule(void)
{
	nf_unregister_net_hook(&init_net, &nfho_pre);
	nf_unregister_net_hook(&init_net, &nfho_post);
}
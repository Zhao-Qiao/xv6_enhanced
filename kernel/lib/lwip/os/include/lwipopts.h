#define NO_SYS 1

#define SYS_LIGHTWEIGHT_PROT 0

#define LWIP_NETCONN 0
#define LWIP_SOCKET 0

#define LWIP_ARP 1
#define LWIP_DHCP 1
#define LWIP_DNS 1
#define LWIP_ETHERNET 1
#define LWIP_ICMP 1
#define LWIP_RAW 1

#define LWIP_EVENT_API 1
#define TCP_LISTEN_BACKLOG 1
#define SO_REUSE 1

#define LWIP_NETIF_LOOPBACK 1

#define LWIP_DEBUG 1
//#define TCP_DEBUG LWIP_DBG_ON
//#define DHCP_DEBUG LWIP_DBG_ON
//#define NETIF_DEBUG LWIP_DBG_ON
//#define ETHARP_DEBUG LWIP_DBG_ON

#define MEM_USE_POOLS 1
#define MEMP_USE_CUSTOM_POOLS 1

#undef __USE_EXTERN_INLINES

#include <inttypes.h>
#include <unistd.h>
#include <sys/types.h>

#include <libnl3/netlink/netlink.h>
#include <libnl3/netlink/route/link.h>
#include <libnl3/netlink/netlink.h>
#include <libnl3/netlink/genl/genl.h>
#include <libnl3/netlink/genl/ctrl.h>
#include <libnl3/netlink/addr.h>
#include <linux/nl80211.h>

#define SIZE_BUF 64
#define MAX_MTU 1500
#define MIN_MTU 46

struct tc_info_entry {
    char *name;
    uint64_t val;
};

char *get_mac(struct rtnl_link *link);

/**
 * @brief Get statistics for an link representing interface.
 *
 * @param[in] buf Character buffer containing statistics type.
 * @param[in] stat Value read for given statistics.
 * @param[out] tc_info Entry to fill with value.
 * @param[in] stat Number of overall entries.
 */
int parse_tc_info(char buf[SIZE_BUF], uint64_t stat,
                  struct tc_info_entry *tc_info, const int count);

/**
 * @brief Get statistics for an link representing interface.
 *
 * @param[in] tc_info Entries for names and uint64 value pairs.
 * @param[in] count Number of entries to print.
 */
void print_tc_info(struct tc_info_entry *tc_info, uint32_t count);

/**
 * @brief Get statistics for an link representing interface.
 *
 * @param[in] link Link is assumed to by initialized by something like rtnl_link_get_by_name.
 */
void get_tc_info(struct rtnl_link *link);

int get_ip(char *if_name, char *ipv4);
void set_ip(char *ipv4);

/**
 * @brief Get MTU for an interface.
 *
 * @param[in] link Link is assumed to by initialized by something like rtnl_link_get_by_name.
 */
 uint16_t get_mtu(struct rtnl_link *link);

/**
 * @brief Set operational state of given link.
 */
 void set_operstate(struct rtnl_link *link, uint8_t operstate);

/**
 * @brief Get operational status for given interface.
 *
 * @param[in] link Link is assumed to by initialized by something like rtnl_link_get_by_name.
 */
 char * get_operstate(struct rtnl_link *link);

/**
 * Initialization function for libnl functionalities.
 * Idea is to initialize context (link cache, address cache, etc.) and then
 * to use that as an API for functions. This is done to lighten API for the functionalities
 * so we don't always need to initialize from socket to everything else.
 */
int functions_init();

#ifndef LNSOCKET_H
#define LNSOCKET_H

#include <stdint.h>
#include <stdlib.h>

struct lnsocket;

enum peer_wire {
        WIRE_INIT = 16,
        WIRE_ERROR = 17,
        WIRE_WARNING = 1,
        WIRE_PING = 18,
        WIRE_PONG = 19,
        WIRE_TX_ADD_INPUT = 66,
        WIRE_TX_ADD_OUTPUT = 67,
        WIRE_TX_REMOVE_INPUT = 68,
        WIRE_TX_REMOVE_OUTPUT = 69,
        WIRE_TX_COMPLETE = 70,
        WIRE_TX_SIGNATURES = 71,
        WIRE_OPEN_CHANNEL = 32,
        WIRE_ACCEPT_CHANNEL = 33,
        WIRE_FUNDING_CREATED = 34,
        WIRE_FUNDING_SIGNED = 35,
        WIRE_FUNDING_LOCKED = 36,
        WIRE_OPEN_CHANNEL2 = 64,
        WIRE_ACCEPT_CHANNEL2 = 65,
        WIRE_INIT_RBF = 72,
        WIRE_ACK_RBF = 73,
        WIRE_SHUTDOWN = 38,
        WIRE_CLOSING_SIGNED = 39,
        WIRE_UPDATE_ADD_HTLC = 128,
        WIRE_UPDATE_FULFILL_HTLC = 130,
        WIRE_UPDATE_FAIL_HTLC = 131,
        WIRE_UPDATE_FAIL_MALFORMED_HTLC = 135,
        WIRE_COMMITMENT_SIGNED = 132,
        WIRE_REVOKE_AND_ACK = 133,
        WIRE_UPDATE_FEE = 134,
        WIRE_UPDATE_BLOCKHEIGHT = 137,
        WIRE_CHANNEL_REESTABLISH = 136,
        WIRE_ANNOUNCEMENT_SIGNATURES = 259,
        WIRE_CHANNEL_ANNOUNCEMENT = 256,
        WIRE_NODE_ANNOUNCEMENT = 257,
        WIRE_CHANNEL_UPDATE = 258,
        WIRE_QUERY_SHORT_CHANNEL_IDS = 261,
        WIRE_REPLY_SHORT_CHANNEL_IDS_END = 262,
        WIRE_QUERY_CHANNEL_RANGE = 263,
        WIRE_REPLY_CHANNEL_RANGE = 264,
        WIRE_GOSSIP_TIMESTAMP_FILTER = 265,
        WIRE_OBS2_ONION_MESSAGE = 387,
        WIRE_ONION_MESSAGE = 513,
};

/* A single TLV field, consisting of the data and its associated metadata. */
struct tlv {
	uint64_t type;
	size_t length;
	unsigned char *value;
};

struct lnsocket *lnsocket_create();

/* messages */

int lnsocket_make_network_tlv(unsigned char *buf, int buflen, const unsigned char **blockids, int num_blockids, struct tlv *tlv_out);
int lnsocket_make_ping_msg(unsigned char *buf, int buflen, unsigned short num_pong_bytes, unsigned short ignored_bytes, int *outlen);
int lnsocket_make_init_msg(unsigned char *buf, int buflen, const unsigned char *globalfeatures, unsigned short gflen, const unsigned char *features, unsigned short flen, const struct tlv **tlvs, unsigned short num_tlvs, int *outlen);

int lnsocket_connect(struct lnsocket *, const char *node_id, const char *host);
int lnsocket_write(struct lnsocket *, const unsigned char *msg, int msg_len);
int lnsocket_read(struct lnsocket *, unsigned char **buf, int *len);
void lnsocket_genkey(struct lnsocket *);
void lnsocket_destroy(struct lnsocket *);
void lnsocket_print_errors(struct lnsocket *);

#endif /* LNSOCKET_H */
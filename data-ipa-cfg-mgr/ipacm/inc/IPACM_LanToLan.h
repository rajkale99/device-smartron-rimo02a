/*
Copyright (c) 2014, The Linux Foundation. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
		* Redistributions of source code must retain the above copyright
			notice, this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above
			copyright notice, this list of conditions and the following
			disclaimer in the documentation and/or other materials provided
			with the distribution.
		* Neither the name of The Linux Foundation nor the names of its
			contributors may be used to endorse or promote products derived
			from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
 * IPACM_LanToLan.h
 *
 *  Created on: Mar 4th, 2014
 *      Author: Shihuan Liu
 */

#ifndef IPACM_LANTOLAN_H
#define IPACM_LANTOLAN_H

#include <stdint.h>
#include "linux/msm_ipa.h"
#include "IPACM_Iface.h"
#include "IPACM_Defs.h"
#include "IPACM_Lan.h"
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include <unordered_map>
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
=======
#include <unordered_map>
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr

#ifdef FEATURE_IPA_ANDROID
#include <libxml/list.h>
#else/* defined(FEATURE_IPA_ANDROID) */
#include <list>
#endif /* ndefined(FEATURE_IPA_ANDROID)*/

<<<<<<< HEAD
<<<<<<< HEAD
#define MAX_NUM_CACHED_CLIENT_ADD_EVENT 10
#define MAX_NUM_IFACE 10
#define MAX_NUM_CLIENT 16

struct rt_rule_info
{
	int num_hdl[IPA_IP_MAX];	/* one client may need more than one routing rules on the same routing table depending on tx_prop */
	uint32_t  rule_hdl[IPA_IP_MAX][MAX_NUM_PROP];
};

struct client_info
{
	uint8_t mac_addr[6];
	rt_rule_info inter_iface_rt_rule_hdl[IPA_HDR_L2_MAX];	/* routing rule handles of inter interface communication based on source l2 header type */
	rt_rule_info intra_iface_rt_rule_hdl;	/* routing rule handles of inter interface communication */
};

struct flt_rule_info
{
	client_info *p_client;
	uint32_t flt_rule_hdl[IPA_IP_MAX];
};

struct peer_iface_info
{
	class IPACM_LanToLan_Iface *peer;
	char rt_tbl_name_for_rt[IPA_IP_MAX][IPA_RESOURCE_NAME_MAX];
	char rt_tbl_name_for_flt[IPA_IP_MAX][IPA_RESOURCE_NAME_MAX];
	list<flt_rule_info> flt_rule;
};

class IPACM_LanToLan_Iface
{
public:
	IPACM_LanToLan_Iface(IPACM_Lan *p_iface);
	~IPACM_LanToLan_Iface();

	void add_client_rt_rule_for_new_iface();

	void add_all_inter_interface_client_flt_rule(ipa_ip_type iptype);

	void add_all_intra_interface_client_flt_rule(ipa_ip_type iptype);

	void handle_down_event();

	void handle_wlan_scc_mcc_switch();

	void handle_intra_interface_info();

	void handle_new_iface_up(char rt_tbl_name_for_flt[][IPA_RESOURCE_NAME_MAX], char rt_tbl_name_for_rt[][IPA_RESOURCE_NAME_MAX],
		IPACM_LanToLan_Iface *peer_iface);

	void handle_client_add(uint8_t *mac);

	void handle_client_del(uint8_t *mac);

	void print_data_structure_info();

	IPACM_Lan* get_iface_pointer();

	bool get_m_is_ip_addr_assigned(ipa_ip_type iptype);

	void set_m_is_ip_addr_assigned(ipa_ip_type iptype, bool value);

	bool get_m_support_inter_iface_offload();

	bool get_m_support_intra_iface_offload();

	void increment_ref_cnt_peer_l2_hdr_type(ipa_hdr_l2_type peer_l2_type);

	void decrement_ref_cnt_peer_l2_hdr_type(ipa_hdr_l2_type peer_l2_type);

private:

	IPACM_Lan *m_p_iface;
	bool m_is_ip_addr_assigned[IPA_IP_MAX];
	bool m_support_inter_iface_offload;
	bool m_support_intra_iface_offload;

	int ref_cnt_peer_l2_hdr_type[IPA_HDR_L2_MAX];	/* reference count of l2 header type of peer interfaces */
	uint32_t hdr_proc_ctx_for_inter_interface[IPA_HDR_L2_MAX];
	uint32_t hdr_proc_ctx_for_intra_interface;

	list<client_info> m_client_info;	/* client list */
	list<peer_iface_info> m_peer_iface_info;	/* peer information list */

	/* The following members are for intra-interface communication*/
	peer_iface_info m_intra_interface_info;

	void add_one_client_flt_rule(IPACM_LanToLan_Iface *peer_iface, client_info *client);

	void add_client_flt_rule(peer_iface_info *peer, client_info *client, ipa_ip_type iptype);

	void del_one_client_flt_rule(IPACM_LanToLan_Iface *peer_iface, client_info *client);

	void del_client_flt_rule(peer_iface_info *peer, client_info *client);

	void add_client_rt_rule(peer_iface_info *peer, client_info *client);

	void del_client_rt_rule(peer_iface_info *peer, client_info *client);

	void clear_all_flt_rule_for_one_peer_iface(peer_iface_info *peer);

	void clear_all_rt_rule_for_one_peer_iface(peer_iface_info *peer);

	void add_hdr_proc_ctx(ipa_hdr_l2_type peer_l2_type);

	void del_hdr_proc_ctx(ipa_hdr_l2_type peer_l2_type);

	void print_peer_info(peer_iface_info *peer_info);

};

class IPACM_LanToLan : public IPACM_Listener
{

public:

	IPACM_LanToLan();

private:

	~IPACM_LanToLan();

	list<class IPACM_LanToLan_Iface> m_iface;

	list<ipacm_event_eth_bridge> m_cached_client_add_event;

	void handle_iface_up(ipacm_event_eth_bridge *data);

	void handle_iface_down(ipacm_event_eth_bridge *data);

	void handle_client_add(ipacm_event_eth_bridge *data);

	void handle_client_del(ipacm_event_eth_bridge *data);

	void handle_wlan_scc_mcc_switch(ipacm_event_eth_bridge *data);

	void handle_new_iface_up(IPACM_LanToLan_Iface *new_iface, IPACM_LanToLan_Iface *exist_iface);

	void event_callback(ipa_cm_event_id event, void* param);

	void handle_cached_client_add_event(IPACM_Lan *p_iface);

	void clear_cached_client_add_event(IPACM_Lan *p_iface);

	void print_data_structure_info();
=======
=======
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
struct client_info;

struct peer_info
{
	struct client_info* peer_pointer;
	int num_connection;
};

//used to store rule handles for offload link (one direction)
struct offload_link_info
{
	struct client_info* peer_pointer;
	uint32_t flt_rule_hdl;
	lan_to_lan_rt_rule_hdl rt_rule_hdl;
	uint32_t hdr_hdl;
};

typedef list<peer_info> peer_info_list;
typedef list<offload_link_info> offload_link_info_list;
typedef list<ipacm_event_connection> connection_list;

struct client_info
{
	union
	{
		uint32_t ipv4_addr;
		uint32_t ipv6_addr[4];
	} ip;
	uint8_t mac_addr[6];
	bool is_active;
	bool is_powersave;
	IPACM_Lan* p_iface;
	peer_info_list peer;
	offload_link_info_list link;
};

struct v6_addr
{
	uint32_t ipv6_addr[4];
};

typedef unordered_map<uint32_t, client_info> client_table_v4;
typedef unordered_map<uint64_t, client_info> client_table_v6;


class IPACM_LanToLan : public IPACM_Listener
{

public:

		IPACM_LanToLan();
		~IPACM_LanToLan();

		void handle_new_connection(ipacm_event_connection* new_conn);
		void handle_del_connection(ipacm_event_connection* del_conn);

		static IPACM_LanToLan* getLan2LanInstance();

private:

		uint8_t num_offload_pair_v4_;
		uint8_t num_offload_pair_v6_;
		client_table_v4 client_info_v4_;
		client_table_v6 client_info_v6_;

		connection_list connection_v4_;
		connection_list connection_v6_;

		static IPACM_LanToLan* p_instance;

		void event_callback(ipa_cm_event_id event, void* param);

		void handle_client_active(ipacm_event_lan_client* data);

		void check_potential_link(ipa_ip_type iptype, client_info* client);

		int add_offload_link(ipa_ip_type iptype, client_info* client, client_info* peer);

		void handle_client_inactive(ipacm_event_lan_client* data);

		int turnoff_offload_links(ipa_ip_type iptype, client_info* client);

		int del_offload_link(ipa_ip_type iptype, IPACM_Lan* client, IPACM_Lan* peer, offload_link_info* link);

		void handle_client_disconnect(ipacm_event_lan_client* data);

		int clear_peer_list(client_info* client);

		void handle_client_power_save(ipacm_event_lan_client* data);

		void handle_client_power_recover(ipacm_event_lan_client* data);

		int remove_flt_rules(ipa_ip_type iptype, client_info* client);

		int add_flt_rules(ipa_ip_type iptype, client_info* client);

//the following are for connections

		void handle_new_lan2lan_connection(ipacm_event_connection* data);

		bool add_connection(client_info* src_client, client_info* dst_client);

		void handle_del_lan2lan_connection(ipacm_event_connection* data);

		bool remove_connection(client_info* src_client, client_info* dst_client);

		void erase_offload_link(ipa_ip_type iptype, client_info* src_client, client_info* dst_client);

		void generate_new_connection(ipa_ip_type iptype, client_info* client);

		bool is_lan2lan_connection(ipacm_event_connection* data);

		bool is_potential_lan2lan_connection(ipacm_event_connection* new_conn);

		void cache_new_connection(ipacm_event_connection* new_conn);

		void remove_cache_connection(ipacm_event_connection* del_conn);

		void check_cache_connection(ipa_ip_type iptype, client_info* client);
<<<<<<< HEAD
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
=======
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr

};

#endif

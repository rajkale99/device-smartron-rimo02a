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
/*!
	@file
	IPACM_LanToLan.cpp

	@brief
	This file implements the functionality of offloading LAN to LAN traffic.

	@Author
	Shihuan Liu

*/

#include <stdlib.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include "IPACM_LanToLan.h"
#include "IPACM_Wlan.h"

#define __stringify(x...) #x

const char *ipa_l2_hdr_type[] = {
	__stringify(NONE),
	__stringify(ETH_II),
	__stringify(802_3),
	__stringify(L2_MAX)
};

IPACM_LanToLan_Iface::IPACM_LanToLan_Iface(IPACM_Lan *p_iface)
{
	int i;

	m_p_iface = p_iface;
	memset(m_is_ip_addr_assigned, 0, sizeof(m_is_ip_addr_assigned));
	m_support_inter_iface_offload = true;
	m_support_intra_iface_offload = false;
	for(i = 0; i < IPA_HDR_L2_MAX; i++)
	{
		ref_cnt_peer_l2_hdr_type[i] = 0;
		hdr_proc_ctx_for_inter_interface[i] = 0;
	}
	hdr_proc_ctx_for_intra_interface = 0;

	if(p_iface->ipa_if_cate == WLAN_IF)
	{
		IPACMDBG_H("Interface %s is WLAN interface.\n", p_iface->dev_name);
		m_support_intra_iface_offload = true;
		if( ((IPACM_Wlan*)p_iface)->is_guest_ap() )
		{
			IPACMDBG_H("Interface %s is guest AP.\n", p_iface->dev_name);
			m_support_inter_iface_offload = false;
		}
	}
	return;
}

IPACM_LanToLan_Iface::~IPACM_LanToLan_Iface()
{
}

IPACM_LanToLan::IPACM_LanToLan()
{
	IPACM_EvtDispatcher::registr(IPA_ETH_BRIDGE_IFACE_UP, this);
	IPACM_EvtDispatcher::registr(IPA_ETH_BRIDGE_IFACE_DOWN, this);
	IPACM_EvtDispatcher::registr(IPA_ETH_BRIDGE_CLIENT_ADD, this);
	IPACM_EvtDispatcher::registr(IPA_ETH_BRIDGE_CLIENT_DEL, this);
	IPACM_EvtDispatcher::registr(IPA_ETH_BRIDGE_WLAN_SCC_MCC_SWITCH, this);

=======
=======
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
#include <assert.h>
#include "IPACM_LanToLan.h"
#include "IPACM_Wlan.h"

#define ipv6_multicast_addr 0xff000000
#define ipv6_multicast_mask 0xff000000

#define max_cache_connection 20

IPACM_LanToLan* IPACM_LanToLan::p_instance = NULL;

IPACM_LanToLan::IPACM_LanToLan()
{
	num_offload_pair_v4_ = 0;
	num_offload_pair_v6_ = 0;
	client_info_v4_.reserve(IPA_LAN_TO_LAN_MAX_WLAN_CLIENT + IPA_LAN_TO_LAN_MAX_LAN_CLIENT);
	client_info_v6_.reserve(3*(IPA_LAN_TO_LAN_MAX_WLAN_CLIENT + IPA_LAN_TO_LAN_MAX_LAN_CLIENT));
	p_instance = this;

	IPACM_EvtDispatcher::registr(IPA_LAN_CLIENT_ACTIVE, this);
	IPACM_EvtDispatcher::registr(IPA_LAN_CLIENT_INACTIVE, this);
	IPACM_EvtDispatcher::registr(IPA_LAN_CLIENT_DISCONNECT, this);
	IPACM_EvtDispatcher::registr(IPA_LAN_CLIENT_POWER_SAVE, this);
	IPACM_EvtDispatcher::registr(IPA_LAN_CLIENT_POWER_RECOVER, this);
	IPACM_EvtDispatcher::registr(IPA_LAN_TO_LAN_NEW_CONNECTION, this);
	IPACM_EvtDispatcher::registr(IPA_LAN_TO_LAN_DEL_CONNECTION, this);
<<<<<<< HEAD
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
=======
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
	return;
}

IPACM_LanToLan::~IPACM_LanToLan()
{
<<<<<<< HEAD
<<<<<<< HEAD
	IPACMDBG_DMESG("WARNING: UNEXPECTEDLY KILL LAN2LAN CONTROLLER!\n");
=======
=======
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
	client_table_v4::iterator it_v4;
	for(it_v4 = client_info_v4_.begin(); it_v4 != client_info_v4_.end(); it_v4++)
	{
		turnoff_offload_links(IPA_IP_v4, &(it_v4->second));
		clear_peer_list(&(it_v4->second));
	}
	client_info_v4_.clear();
	IPACMDBG("Clear IPv4 hash table in Lan2Lan distructor.\n");

	client_table_v6::iterator it_v6;
	for(it_v6 = client_info_v6_.begin(); it_v6 != client_info_v6_.end(); it_v6++)
	{
		turnoff_offload_links(IPA_IP_v6, &(it_v6->second));
		clear_peer_list(&(it_v6->second));
	}
	client_info_v6_.clear();
	IPACMDBG("Clear IPv6 hash table in Lan2Lan distructor.\n");

<<<<<<< HEAD
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
=======
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
	return;
}

void IPACM_LanToLan::event_callback(ipa_cm_event_id event, void* param)
{
<<<<<<< HEAD
<<<<<<< HEAD
	ipacm_event_eth_bridge *data = (ipacm_event_eth_bridge*)param;
	IPACMDBG_H("Get %s event.\n", IPACM_Iface::ipacmcfg->getEventName(event));

	switch(event)
	{
		case IPA_ETH_BRIDGE_IFACE_UP:
		{
			handle_iface_up(data);
			break;
		}

		case IPA_ETH_BRIDGE_IFACE_DOWN:
		{
			handle_iface_down(data);
			break;
		}

		case IPA_ETH_BRIDGE_CLIENT_ADD:
		{
			handle_client_add(data);
			break;
		}

		case IPA_ETH_BRIDGE_CLIENT_DEL:
		{
			handle_client_del(data);
			break;
		}

		case IPA_ETH_BRIDGE_WLAN_SCC_MCC_SWITCH:
		{
			handle_wlan_scc_mcc_switch(data);
=======
=======
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
	switch(event)
	{
		case IPA_LAN_CLIENT_ACTIVE:
		{
			IPACMDBG_H("Get IPA_LAN_CLIENT_ACTIVE event.\n");
			ipacm_event_lan_client* data = (ipacm_event_lan_client*)param;
			handle_client_active(data);
			break;
		}

		case IPA_LAN_CLIENT_INACTIVE:
		{
			IPACMDBG_H("Get IPA_LAN_CLIENT_INACTIVE event.\n");
			ipacm_event_lan_client* data = (ipacm_event_lan_client*)param;
			handle_client_inactive(data);
			break;
		}

		case IPA_LAN_CLIENT_DISCONNECT:
		{
			IPACMDBG_H("Get IPA_LAN_CLIENT_DISCONNECT event.\n");
			ipacm_event_lan_client* data = (ipacm_event_lan_client*)param;
			handle_client_disconnect(data);
			break;
		}

		case IPA_LAN_TO_LAN_NEW_CONNECTION:
		{
			IPACMDBG_H("Get IPA_LAN_TO_LAN_NEW_CONNECTION event.\n");
			ipacm_event_connection* data = (ipacm_event_connection*)param;
			handle_new_lan2lan_connection(data);
			break;
		}

		case IPA_LAN_TO_LAN_DEL_CONNECTION:
		{
			IPACMDBG_H("Get IPA_LAN_TO_LAN_DEL_CONNECTION event.\n");
			ipacm_event_connection* data = (ipacm_event_connection*)param;
			handle_del_lan2lan_connection(data);
			break;
		}
		case IPA_LAN_CLIENT_POWER_SAVE:
		{
			IPACMDBG_H("Get IPA_LAN_CLIENT_POWER_SAVE event.\n");
			ipacm_event_lan_client* data = (ipacm_event_lan_client*)param;
			handle_client_power_save(data);
			break;
		}
		case IPA_LAN_CLIENT_POWER_RECOVER:
		{
			IPACMDBG_H("Get IPA_LAN_CLIENT_POWER_RECOVER event.\n");
			ipacm_event_lan_client* data = (ipacm_event_lan_client*)param;
			handle_client_power_recover(data);
<<<<<<< HEAD
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
=======
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
			break;
		}
		default:
			break;
	}
<<<<<<< HEAD
<<<<<<< HEAD

	print_data_structure_info();
	return;
}

void IPACM_LanToLan::handle_iface_up(ipacm_event_eth_bridge *data)
{
	list<IPACM_LanToLan_Iface>::iterator it;

	IPACMDBG_H("Interface name: %s IP type: %d\n", data->p_iface->dev_name, data->iptype);
	for(it = m_iface.begin(); it != m_iface.end(); it++)
	{
		if(it->get_iface_pointer() == data->p_iface)
		{
			IPACMDBG_H("Found the interface.\n");
			if(it->get_m_is_ip_addr_assigned(data->iptype) == false)
			{
				IPACMDBG_H("IP type %d was not active before, activating it now.\n", data->iptype);
				it->set_m_is_ip_addr_assigned(data->iptype, true);

				/* install inter-interface rules */
				if(it->get_m_support_inter_iface_offload())
					it->add_all_inter_interface_client_flt_rule(data->iptype);

				/* install intra-BSS rules */
				if(it->get_m_support_intra_iface_offload())
					it->add_all_intra_interface_client_flt_rule(data->iptype);
			}
			break;
		}
	}

	if(it == m_iface.end())	//If the interface has not been created before
	{
		if(m_iface.size() == MAX_NUM_IFACE)
		{
			IPACMERR("The number of interfaces has reached maximum %d.\n", MAX_NUM_IFACE);
			return;
		}

		if(!data->p_iface->tx_prop || !data->p_iface->rx_prop)
		{
			IPACMERR("The interface %s does not have tx_prop or rx_prop.\n", data->p_iface->dev_name);
			return;
		}

		if(data->p_iface->tx_prop->tx[0].hdr_l2_type == IPA_HDR_L2_NONE || data->p_iface->tx_prop->tx[0].hdr_l2_type == IPA_HDR_L2_MAX)
		{
			IPACMERR("Invalid l2 header type %s!\n", ipa_l2_hdr_type[data->p_iface->tx_prop->tx[0].hdr_l2_type]);
			return;
		}

		IPACMDBG_H("Does not find the interface, insert a new one.\n");
		IPACM_LanToLan_Iface new_iface(data->p_iface);
		new_iface.set_m_is_ip_addr_assigned(data->iptype, true);

		m_iface.push_front(new_iface);
		IPACMDBG_H("Now the total number of interfaces is %d.\n", m_iface.size());

		IPACM_LanToLan_Iface &front_iface = m_iface.front();

		/* install inter-interface rules */
		if(front_iface.get_m_support_inter_iface_offload())
		{
			for(it = ++m_iface.begin(); it != m_iface.end(); it++)
			{
				/* add peer info only when both interfaces support inter-interface communication */
				if(it->get_m_support_inter_iface_offload())
				{
					/* populate hdr_proc_ctx and routing table handle */
					handle_new_iface_up(&front_iface, &(*it));

					/* add client specific routing rule on existing interface */
					it->add_client_rt_rule_for_new_iface();
				}
			}

			/* add client specific filtering rule on new interface */
			front_iface.add_all_inter_interface_client_flt_rule(data->iptype);
		}

		/* populate the intra-interface information */
		if(front_iface.get_m_support_intra_iface_offload())
		{
			front_iface.handle_intra_interface_info();
		}

		/* handle cached client add event */
		handle_cached_client_add_event(front_iface.get_iface_pointer());
	}
	return;
}

void IPACM_LanToLan::handle_iface_down(ipacm_event_eth_bridge *data)
{
	list<IPACM_LanToLan_Iface>::iterator it_target_iface;

	IPACMDBG_H("Interface name: %s\n", data->p_iface->dev_name);

	for(it_target_iface = m_iface.begin(); it_target_iface != m_iface.end(); it_target_iface++)
	{
		if(it_target_iface->get_iface_pointer() == data->p_iface)
		{
			IPACMDBG_H("Found the interface.\n");
			break;
		}
	}

	if(it_target_iface == m_iface.end())
	{
		IPACMDBG_H("The interface has not been found.\n");
		/* clear cached client add event for the unfound interface*/
		clear_cached_client_add_event(data->p_iface);
		return;
	}

	it_target_iface->handle_down_event();
	m_iface.erase(it_target_iface);

	return;
}

void IPACM_LanToLan::handle_new_iface_up(IPACM_LanToLan_Iface *new_iface, IPACM_LanToLan_Iface *exist_iface)
{
	char rt_tbl_name_for_flt[IPA_IP_MAX][IPA_RESOURCE_NAME_MAX];
	char rt_tbl_name_for_rt[IPA_IP_MAX][IPA_RESOURCE_NAME_MAX];

	IPACMDBG_H("Populate peer info between: new_iface %s, existing iface %s\n", new_iface->get_iface_pointer()->dev_name,
		exist_iface->get_iface_pointer()->dev_name);

	/* populate the routing table information */
	snprintf(rt_tbl_name_for_flt[IPA_IP_v4], IPA_RESOURCE_NAME_MAX, "eth_v4_%s_to_%s",
		ipa_l2_hdr_type[exist_iface->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type],
		ipa_l2_hdr_type[new_iface->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type]);
	IPACMDBG_H("IPv4 routing table for flt name: %s\n", rt_tbl_name_for_flt[IPA_IP_v4]);

	snprintf(rt_tbl_name_for_flt[IPA_IP_v6], IPA_RESOURCE_NAME_MAX, "eth_v6_%s_to_%s",
		ipa_l2_hdr_type[exist_iface->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type],
		ipa_l2_hdr_type[new_iface->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type]);
	IPACMDBG_H("IPv6 routing table for flt name: %s\n", rt_tbl_name_for_flt[IPA_IP_v6]);

	snprintf(rt_tbl_name_for_rt[IPA_IP_v4], IPA_RESOURCE_NAME_MAX, "eth_v4_%s_to_%s",
		ipa_l2_hdr_type[new_iface->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type],
		ipa_l2_hdr_type[exist_iface->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type]);
	IPACMDBG_H("IPv4 routing table for rt name: %s\n", rt_tbl_name_for_rt[IPA_IP_v4]);

	snprintf(rt_tbl_name_for_rt[IPA_IP_v6], IPA_RESOURCE_NAME_MAX, "eth_v6_%s_to_%s",
		ipa_l2_hdr_type[new_iface->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type],
		ipa_l2_hdr_type[exist_iface->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type]);
	IPACMDBG_H("IPv6 routing table for rt name: %s\n", rt_tbl_name_for_rt[IPA_IP_v6]);

	/* add new peer info in both new iface and existing iface */
	exist_iface->handle_new_iface_up(rt_tbl_name_for_flt, rt_tbl_name_for_rt, new_iface);

	new_iface->handle_new_iface_up(rt_tbl_name_for_rt, rt_tbl_name_for_flt, exist_iface);

	return;
}

void IPACM_LanToLan::handle_client_add(ipacm_event_eth_bridge *data)
{
	list<IPACM_LanToLan_Iface>::iterator it_iface;

	IPACMDBG_H("Incoming client MAC: 0x%02x%02x%02x%02x%02x%02x, interface: %s\n", data->mac_addr[0], data->mac_addr[1],
		data->mac_addr[2], data->mac_addr[3], data->mac_addr[4], data->mac_addr[5], data->p_iface->dev_name);

	for(it_iface = m_iface.begin(); it_iface != m_iface.end(); it_iface++)
	{
		if(it_iface->get_iface_pointer() == data->p_iface)	//find the interface
		{
			IPACMDBG_H("Found the interface.\n");
			it_iface->handle_client_add(data->mac_addr);
			break;
		}
	}

	/* if the iface was not found, cache the client add event */
	if(it_iface == m_iface.end())
	{
		IPACMDBG_H("The interface is not found.\n");
		if(m_cached_client_add_event.size() < MAX_NUM_CACHED_CLIENT_ADD_EVENT)
		{
			IPACMDBG_H("Cached the client information.\n");
			m_cached_client_add_event.push_front(*data);
		}
		else
		{
			IPACMDBG_H("Cached client add event has reached maximum number.\n");
=======
=======
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
	return;
}

void IPACM_LanToLan::handle_client_active(ipacm_event_lan_client* data)
{
	if(data == NULL)
	{
		IPACMERR("No client info is found.\n");
		return;
	}
	if(data->mac_addr == NULL || data->ipv6_addr == NULL || data->p_iface == NULL)
	{
		IPACMERR("Event data is not populated properly.\n");
		return;
	}
	if(data->iptype != IPA_IP_v4 && data->iptype != IPA_IP_v6)
	{
		IPACMERR("IP type is not expected.\n");
		return;
	}

	IPACMDBG_H("New client info: iface %s, iptype: %d, mac: 0x%02x%02x%02x%02x%02x%02x, v4_addr: 0x%08x, v6_addr: 0x%08x%08x%08x%08x \n",
		data->p_iface->dev_name, data->iptype,
		data->mac_addr[0], data->mac_addr[1], data->mac_addr[2], data->mac_addr[3], data->mac_addr[4], data->mac_addr[5],
		data->ipv4_addr, data->ipv6_addr[0], data->ipv6_addr[1], data->ipv6_addr[2], data->ipv6_addr[3]);

	bool client_not_found;
	client_info* client_ptr;

	if(data->iptype == IPA_IP_v4)
	{
		client_not_found = (client_info_v4_.count(data->ipv4_addr) == 0);
		IPACMDBG_H("Is the client not found? %d\n", client_not_found);
		client_info& client = client_info_v4_[data->ipv4_addr];
		client_ptr = &client;
	}
	else
	{
		uint64_t v6_addr;
		memcpy(&v6_addr, &(data->ipv6_addr[2]), sizeof(uint64_t));

		client_not_found = (client_info_v6_.count(v6_addr) == 0);
		IPACMDBG_H("Is the client not found? %d\n", client_not_found);
		client_info& client = client_info_v6_[v6_addr];
		client_ptr = &client;
	}

	if(client_not_found == true)
	{
		if(data->iptype == IPA_IP_v4)
		{
			client_ptr->ip.ipv4_addr = data->ipv4_addr;
		}
		else
		{
			memcpy(client_ptr->ip.ipv6_addr, data->ipv6_addr, sizeof(client_ptr->ip.ipv6_addr));
		}
		memcpy(client_ptr->mac_addr, data->mac_addr, sizeof(client_ptr->mac_addr));
		client_ptr->is_active =  true;
		client_ptr->is_powersave = false;
		client_ptr->p_iface = data->p_iface;

		generate_new_connection(data->iptype, client_ptr);
		check_cache_connection(data->iptype, client_ptr);
	}
	else	//the client is found
	{
		if(client_ptr->is_active == true)	//the client is active
		{
			IPACMDBG_H("The client is active.\n");
			if(memcmp(client_ptr->mac_addr, data->mac_addr, sizeof(client_ptr->mac_addr)) == 0)
			{
				IPACMDBG_H("Mac addr is the same, do nothing.\n");
			}
			else
			{
				IPACMERR("The new client has same IP but differenc mac.\n");
				turnoff_offload_links(data->iptype, client_ptr);
				clear_peer_list(client_ptr);

				if(data->iptype == IPA_IP_v4)
				{
					client_ptr->ip.ipv4_addr = data->ipv4_addr;
				}
				else
				{
					memcpy(client_ptr->ip.ipv6_addr, data->ipv6_addr, sizeof(client_ptr->ip.ipv6_addr));
				}
				memcpy(client_ptr->mac_addr, data->mac_addr, sizeof(client_ptr->mac_addr));
				client_ptr->is_active =  true;
				client_ptr->is_powersave = false;
				client_ptr->p_iface = data->p_iface;

				generate_new_connection(data->iptype, client_ptr);
				check_cache_connection(data->iptype, client_ptr);
			}
		}
		else 	//the client is inactive
		{
			IPACMDBG_H("The client is inactive.\n");
			if(data->iptype == IPA_IP_v4)
			{
				client_ptr->ip.ipv4_addr = data->ipv4_addr;
			}
			else
			{
				memcpy(client_ptr->ip.ipv6_addr, data->ipv6_addr, sizeof(client_ptr->ip.ipv6_addr));
			}
			memcpy(client_ptr->mac_addr, data->mac_addr, sizeof(client_ptr->mac_addr));
			client_ptr->is_active =  true;
			client_ptr->is_powersave = false;
			client_ptr->p_iface = data->p_iface;

			check_potential_link(data->iptype, client_ptr);
			generate_new_connection(data->iptype, client_ptr);
			check_cache_connection(data->iptype, client_ptr);
		}
	}
	IPACMDBG_H("There are %d clients in v4 table and %d clients in v6 table.\n", client_info_v4_.size(), client_info_v6_.size());
	return;
}

void IPACM_LanToLan::check_potential_link(ipa_ip_type iptype, client_info* client)
{
	if(client == NULL)
	{
		IPACMERR("Client is NULL.\n");
		return;
	}

	IPACMDBG_H("Check client's peer list.\n");
	IPACMDBG_H("Client: IP type: %d, IPv4 addr: 0x%08x, IPv6 addr: 0x%08x%08x%08x%08x\n", iptype, client->ip.ipv4_addr,
				client->ip.ipv6_addr[0], client->ip.ipv6_addr[1], client->ip.ipv6_addr[2], client->ip.ipv6_addr[3]);

	peer_info_list::iterator peer_it;
	int res, num = 0;

	for(peer_it = client->peer.begin(); peer_it != client->peer.end(); peer_it++)
	{
		if(peer_it->peer_pointer->is_active == true && peer_it->num_connection > 0)
		{
			res = IPACM_SUCCESS;
			res = add_offload_link(iptype, client, peer_it->peer_pointer);
			res = add_offload_link(iptype, peer_it->peer_pointer, client);
			if(res == IPACM_SUCCESS)
			{
				if(iptype == IPA_IP_v4)
				{
					num_offload_pair_v4_ ++;
					IPACMDBG_H("Now the number of v4 offload links is %d.\n", num_offload_pair_v4_);
				}
				else
				{
					num_offload_pair_v6_ ++;
					IPACMDBG_H("Now the number of v6 offload links is %d.\n", num_offload_pair_v6_);
				}
				num++;
			}
		}
	}
	IPACMDBG_H("Added %d offload links in total.\n", num);
	return;
}

int IPACM_LanToLan::add_offload_link(ipa_ip_type iptype, client_info* client, client_info* peer)
{
	if( (iptype == IPA_IP_v4 && num_offload_pair_v4_ >= MAX_OFFLOAD_PAIR)
		|| (iptype == IPA_IP_v6 && num_offload_pair_v6_ >= MAX_OFFLOAD_PAIR) )
	{
		IPACMDBG_H("The number of offload pairs already reaches maximum.\n");
		return IPACM_FAILURE;
	}
	if(client == NULL || peer == NULL)
	{
		IPACMERR("Either client or peer is NULL.\n");
		return IPACM_FAILURE;
	}

	uint32_t hdr_hdl, flt_hdl;
	lan_to_lan_rt_rule_hdl rt_rule_hdl;

	offload_link_info link_info;


	if(iptype == IPA_IP_v4)
	{
		IPACMDBG_H("Add offload link for IPv4, client IP: 0x%08x, peer IP: 0x%08x \n", client->ip.ipv4_addr, peer->ip.ipv4_addr);
	}
	else if(iptype == IPA_IP_v6)
	{
		IPACMDBG_H("Add offload link for IPv6, client IP: 0x%08x%08x%08x%08x, peer IP: 0x%08x%08x%08x%08x \n",
				client->ip.ipv6_addr[0], client->ip.ipv6_addr[1], client->ip.ipv6_addr[2], client->ip.ipv6_addr[3],
				peer->ip.ipv6_addr[0], peer->ip.ipv6_addr[1], peer->ip.ipv6_addr[2], peer->ip.ipv6_addr[3]);
	}
	else
	{
		IPACMERR("IP type is not expected.\n");
		return IPACM_FAILURE;
	}

	//add lan2lan header
	if(peer->p_iface->add_lan2lan_hdr(iptype, client->mac_addr, peer->mac_addr, &hdr_hdl) == IPACM_FAILURE)
	{
		IPACMERR("Failed to create lan2lan header.\n");
		return IPACM_FAILURE;
	}
	IPACMDBG_H("Created lan2lan hdr with hdl %d.\n", hdr_hdl);

	//add lan2lan routing/filtering rules
	if(peer->p_iface->add_lan2lan_rt_rule(iptype, client->ip.ipv4_addr, peer->ip.ipv4_addr,
					client->ip.ipv6_addr, peer->ip.ipv6_addr, hdr_hdl, &rt_rule_hdl) == IPACM_FAILURE)
	{
		IPACMERR("Failed to create lan2lan rt rule.\n");
		goto rt_fail;
	}
	IPACMDBG_H("Created %d lan2lan rt rules.\n", rt_rule_hdl.num_rule);
	IPACMDBG_H("Created lan2lan rt rules with hdl: %d.\n", rt_rule_hdl.rule_hdl[0]);

	if(client->p_iface->add_lan2lan_flt_rule(iptype, client->ip.ipv4_addr, peer->ip.ipv4_addr,
					client->ip.ipv6_addr, peer->ip.ipv6_addr, &flt_hdl) == IPACM_FAILURE)
	{
		IPACMERR("Failed to create lan2lan flt rule.\n");
		goto flt_fail;
	}
	IPACMDBG_H("Created lan2lan flt rule with hdl %d.\n", flt_hdl);

	link_info.peer_pointer = peer;
	link_info.flt_rule_hdl = flt_hdl;
	link_info.hdr_hdl = hdr_hdl;
	memcpy(&link_info.rt_rule_hdl, &rt_rule_hdl, sizeof(lan_to_lan_rt_rule_hdl));

	client->link.push_back(link_info);

	return IPACM_SUCCESS;

flt_fail:
	peer->p_iface->del_lan2lan_rt_rule(iptype, rt_rule_hdl);

rt_fail:
	peer->p_iface->del_lan2lan_hdr(iptype, hdr_hdl);

	return IPACM_FAILURE;
}

void IPACM_LanToLan::handle_client_inactive(ipacm_event_lan_client* data)
{
	if(data == NULL)
	{
		IPACMERR("No client info is found.\n");
		return;
	}
	if(data->mac_addr == NULL || data->ipv6_addr == NULL || data->p_iface == NULL)
	{
		IPACMERR("Event data is not populated properly.\n");
		return;
	}
	if(data->iptype != IPA_IP_v4 && data->iptype != IPA_IP_v6)
	{
		IPACMERR("IP type is not expected: %d.\n", data->iptype);
		return;
	}

	IPACMDBG_H("Del client info: iface %s, iptype: %d, mac: 0x%02x%02x%02x%02x%02x%02x, v4_addr: 0x%08x, v6_addr: 0x%08x%08x%08x%08x \n",
		data->p_iface->dev_name, data->iptype,
		data->mac_addr[0], data->mac_addr[1], data->mac_addr[2], data->mac_addr[3], data->mac_addr[4], data->mac_addr[5],
		data->ipv4_addr, data->ipv6_addr[0], data->ipv6_addr[1], data->ipv6_addr[2], data->ipv6_addr[3]);

	client_info* client_ptr;
	uint64_t v6_addr;

	if(data->iptype == IPA_IP_v4)
	{
		if(client_info_v4_.count(data->ipv4_addr) == 0)//if not found the client, return
		{
			IPACMERR("The client is not found the client, return.\n");
			return;
		}
		IPACMDBG_H("The client is found.\n");
		client_info& client = client_info_v4_[data->ipv4_addr];
		client_ptr = &client;
	}
	else
	{
		memcpy(&v6_addr, &(data->ipv6_addr[2]), sizeof(uint64_t));
		if(client_info_v6_.count(v6_addr) == 0)	//if not found the client, insert it in table
		{
			IPACMERR("The client is not found the client, return.\n");
			return;
		}
		IPACMDBG_H("The client is found.\n");
		client_info& client = client_info_v6_[v6_addr];
		client_ptr = &client;
	}

	turnoff_offload_links(data->iptype, client_ptr);
	client_ptr->is_active = false;
	if(client_ptr->peer.size() == 0)
	{
		IPACMDBG_H("Peer list is empty, remove client entry.\n");
		if(data->iptype == IPA_IP_v4)
		{
			client_info_v4_.erase(data->ipv4_addr);
		}
		else
		{
			client_info_v6_.erase(v6_addr);
<<<<<<< HEAD
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
		}
	}
	return;
}

<<<<<<< HEAD
void IPACM_LanToLan::handle_client_del(ipacm_event_eth_bridge *data)
{
	list<IPACM_LanToLan_Iface>::iterator it_iface;

	IPACMDBG_H("Incoming client MAC: 0x%02x%02x%02x%02x%02x%02x, interface: %s\n", data->mac_addr[0], data->mac_addr[1],
		data->mac_addr[2], data->mac_addr[3], data->mac_addr[4], data->mac_addr[5], data->p_iface->dev_name);

	for(it_iface = m_iface.begin(); it_iface != m_iface.end(); it_iface++)
	{
		if(it_iface->get_iface_pointer() == data->p_iface)	//found the interface
		{
			IPACMDBG_H("Found the interface.\n");
			it_iface->handle_client_del(data->mac_addr);
			break;
		}
	}

	if(it_iface == m_iface.end())
	{
		IPACMDBG_H("The interface is not found.\n");
	}

	return;
}

void IPACM_LanToLan::handle_wlan_scc_mcc_switch(ipacm_event_eth_bridge *data)
{
	list<IPACM_LanToLan_Iface>::iterator it_iface;

	IPACMDBG_H("Incoming interface: %s\n", data->p_iface->dev_name);
	for(it_iface = m_iface.begin(); it_iface != m_iface.end(); it_iface++)
	{
		if(it_iface->get_iface_pointer() == data->p_iface)
		{
			it_iface->handle_wlan_scc_mcc_switch();
			break;
=======
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
		}
	}
	return;
}

<<<<<<< HEAD
void IPACM_LanToLan::handle_cached_client_add_event(IPACM_Lan *p_iface)
{
	list<ipacm_event_eth_bridge>::iterator it;

	it = m_cached_client_add_event.begin();
	while(it != m_cached_client_add_event.end())
	{
		if(it->p_iface == p_iface)
		{
			IPACMDBG_H("Found client with MAC: 0x%02x%02x%02x%02x%02x%02x\n", it->mac_addr[0], it->mac_addr[1],
				it->mac_addr[2], it->mac_addr[3], it->mac_addr[4], it->mac_addr[5]);
			handle_client_add(&(*it));
			it = m_cached_client_add_event.erase(it);
		}
		else
		{
			it++;
		}
=======
=======
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
int IPACM_LanToLan::turnoff_offload_links(ipa_ip_type iptype, client_info* client)
{
	if(client == NULL)
	{
		IPACMERR("Client is NULL.\n");
		return IPACM_FAILURE;
	}

	bool err_flag;
	offload_link_info_list::iterator client_it;
	offload_link_info_list::iterator peer_it;
	client_info* peer;

	for(client_it = client->link.begin(); client_it != client->link.end(); client_it++)
	{
		peer = client_it->peer_pointer;
		if(del_offload_link(iptype, client->p_iface, peer->p_iface, &(*client_it)) == IPACM_FAILURE)
		{
			IPACMERR("Failed to delete client's offload link.\n");
			return IPACM_FAILURE;
		}

		err_flag = true;
		for(peer_it = peer->link.begin(); peer_it != peer->link.end(); peer_it++)
		{
			if(peer_it->peer_pointer == client)
			{
				if(del_offload_link(iptype, peer->p_iface, client->p_iface, &(*peer_it)) == IPACM_FAILURE)
				{
					IPACMERR("Failed to delete peer's offload link.\n");
					return IPACM_FAILURE;
				}
				peer->link.erase(peer_it);
				err_flag = false;
				break;
			}
		}
		if(err_flag)
		{
			IPACMERR("Unable to find corresponding offload link in peer's entry.\n");
			return IPACM_FAILURE;
		}
		if(iptype == IPA_IP_v4)
		{
			num_offload_pair_v4_ --;
			IPACMDBG_H("Now the number of v4 offload pair is %d\n", num_offload_pair_v4_);
		}
		else
		{
			num_offload_pair_v6_ --;
			IPACMDBG_H("Now the number of v6 offload pair is %d\n", num_offload_pair_v6_);
		}
	}

	client->link.clear();
	return IPACM_SUCCESS;
}

int IPACM_LanToLan::del_offload_link(ipa_ip_type iptype, IPACM_Lan* client, IPACM_Lan* peer, offload_link_info* link)
{
	if(client == NULL || peer == NULL || link == NULL)
	{
		IPACMERR("Either iface or link is NULL.\n");
		return IPACM_FAILURE;
	}

	IPACMDBG_H("Delete an offload link for IP type: %d\n", iptype);

	int res = IPACM_SUCCESS;

	if(client->del_lan2lan_flt_rule(iptype, link->flt_rule_hdl) == IPACM_FAILURE)
	{
		IPACMERR("Failed to delete flt rule.\n");
		res = IPACM_FAILURE;
	}

	if(peer->del_lan2lan_rt_rule(iptype, link->rt_rule_hdl) == IPACM_FAILURE)
	{
		IPACMERR("Failed to delete rt rules.\n");
		res = IPACM_FAILURE;
	}

	if(peer->del_lan2lan_hdr(iptype, link->hdr_hdl) == IPACM_FAILURE)
	{
		IPACMERR("Failed to delete header.\n");
		res = IPACM_FAILURE;
	}

	return res;
}

void IPACM_LanToLan::handle_client_disconnect(ipacm_event_lan_client* data)
{
	if(data == NULL)
	{
		IPACMERR("No client info is found.\n");
		return;
	}
	if(data->mac_addr == NULL || data->ipv6_addr == NULL || data->p_iface == NULL)
	{
		IPACMERR("Event data is not populated properly.\n");
		return;
	}
	if(data->iptype != IPA_IP_v4 && data->iptype != IPA_IP_v6)
	{
		IPACMERR("IP type is not expected: %d.\n", data->iptype);
		return;
	}

	IPACMDBG_H("Del client info: iface %s, iptype: %d, mac: 0x%02x%02x%02x%02x%02x%02x, v4_addr: 0x%08x, v6_addr: 0x%08x%08x%08x%08x \n",
		data->p_iface->dev_name, data->iptype,
		data->mac_addr[0], data->mac_addr[1], data->mac_addr[2], data->mac_addr[3], data->mac_addr[4], data->mac_addr[5],
		data->ipv4_addr, data->ipv6_addr[0], data->ipv6_addr[1], data->ipv6_addr[2], data->ipv6_addr[3]);

	client_info* client_ptr;
	uint64_t v6_addr;
	if(data->iptype == IPA_IP_v4)
	{
		if(client_info_v4_.count(data->ipv4_addr) == 0)	//if not found the client, return
		{
			IPACMERR("The client is not found the client, return.\n");
			return;
		}
		IPACMDBG_H("The client is found.\n");
		client_info& client = client_info_v4_[data->ipv4_addr];
		client_ptr = &client;
	}
	else
	{
		memcpy(&v6_addr, &(data->ipv6_addr[2]), sizeof(uint64_t));
		if(client_info_v6_.count(v6_addr) == 0)	//if not found the client, insert it in table
		{
			IPACMERR("The client is not found the client, return.\n");
			return;
		}
		IPACMDBG_H("The client is found.\n");
		client_info& client = client_info_v6_[v6_addr];
		client_ptr = &client;
	}

	turnoff_offload_links(data->iptype, client_ptr);
	clear_peer_list(client_ptr);
	if(data->iptype == IPA_IP_v4)
	{
		client_info_v4_.erase(data->ipv4_addr);
	}
	else
	{
		client_info_v6_.erase(v6_addr);
<<<<<<< HEAD
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
=======
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
	}
	return;
}

<<<<<<< HEAD
<<<<<<< HEAD
void IPACM_LanToLan::clear_cached_client_add_event(IPACM_Lan *p_iface)
{
	list<ipacm_event_eth_bridge>::iterator it;

	it = m_cached_client_add_event.begin();
	while(it != m_cached_client_add_event.end())
	{
		if(it->p_iface == p_iface)
		{
			IPACMDBG_H("Found client with MAC: 0x%02x%02x%02x%02x%02x%02x\n", it->mac_addr[0], it->mac_addr[1],
				it->mac_addr[2], it->mac_addr[3], it->mac_addr[4], it->mac_addr[5]);
			it = m_cached_client_add_event.erase(it);
		}
		else
		{
			it++;
		}
	}
	return;
}

void IPACM_LanToLan::print_data_structure_info()
{
	list<IPACM_LanToLan_Iface>::iterator it;
	list<ipacm_event_eth_bridge>::iterator it_event;
	int i;

	IPACMDBG_H("There are %d interfaces in total.\n", m_iface.size());

	for(it = m_iface.begin(); it != m_iface.end(); it++)
	{
		it->print_data_structure_info();
	}

	IPACMDBG_H("There are %d cached client add events in total.\n", m_cached_client_add_event.size());

	i = 1;
	for(it_event = m_cached_client_add_event.begin(); it_event != m_cached_client_add_event.end(); it_event++)
	{
		IPACMDBG_H("Client %d MAC: 0x%02x%02x%02x%02x%02x%02x, interface: %s\n", i, it_event->mac_addr[0], it_event->mac_addr[1], it_event->mac_addr[2],
			it_event->mac_addr[3], it_event->mac_addr[4], it_event->mac_addr[5], it_event->p_iface->dev_name);
		i++;
	}

	return;
}

void IPACM_LanToLan_Iface::add_client_rt_rule_for_new_iface()
{
	list<client_info>::iterator it;
	ipa_hdr_l2_type peer_l2_type;
	peer_iface_info &peer = m_peer_iface_info.front();

	peer_l2_type = peer.peer->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type;
	if(ref_cnt_peer_l2_hdr_type[peer_l2_type] == 1)
	{
		for(it = m_client_info.begin(); it != m_client_info.end(); it++)
		{
			add_client_rt_rule(&peer, &(*it));
		}
	}

	return;
}

void IPACM_LanToLan_Iface::add_client_rt_rule(peer_iface_info *peer_info, client_info *client)
{
	int i, num_rt_rule;
	uint32_t rt_rule_hdl[MAX_NUM_PROP];
	ipa_hdr_l2_type peer_l2_hdr_type;

	peer_l2_hdr_type = peer_info->peer->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type;

	/* if the peer info is not for intra interface communication */
	if(peer_info->peer != this)
	{
		IPACMDBG_H("This is for inter interface communication.\n");

		m_p_iface->eth_bridge_add_rt_rule(client->mac_addr, peer_info->rt_tbl_name_for_rt[IPA_IP_v4], hdr_proc_ctx_for_inter_interface[peer_l2_hdr_type],
			peer_l2_hdr_type, IPA_IP_v4, rt_rule_hdl, &num_rt_rule);

		client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].num_hdl[IPA_IP_v4] = num_rt_rule;
		IPACMDBG_H("Number of IPv4 routing rule is %d.\n", num_rt_rule);
		for(i=0; i<num_rt_rule; i++)
		{
			IPACMDBG_H("Routing rule %d handle %d\n", i, rt_rule_hdl[i]);
			client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].rule_hdl[IPA_IP_v4][i] = rt_rule_hdl[i];
		}

		m_p_iface->eth_bridge_add_rt_rule(client->mac_addr, peer_info->rt_tbl_name_for_rt[IPA_IP_v6], hdr_proc_ctx_for_inter_interface[peer_l2_hdr_type],
			peer_l2_hdr_type, IPA_IP_v6, rt_rule_hdl, &num_rt_rule);

		client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].num_hdl[IPA_IP_v6] = num_rt_rule;
		IPACMDBG_H("Number of IPv6 routing rule is %d.\n", num_rt_rule);
		for(i=0; i<num_rt_rule; i++)
		{
			IPACMDBG_H("Routing rule %d handle %d\n", i, rt_rule_hdl[i]);
			client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].rule_hdl[IPA_IP_v6][i] = rt_rule_hdl[i];
		}
	}
	else
	{
		IPACMDBG_H("This is for intra interface communication.\n");
		m_p_iface->eth_bridge_add_rt_rule(client->mac_addr, peer_info->rt_tbl_name_for_rt[IPA_IP_v4], hdr_proc_ctx_for_intra_interface,
			peer_l2_hdr_type, IPA_IP_v4, rt_rule_hdl, &num_rt_rule);

		client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v4] = num_rt_rule;
		IPACMDBG_H("Number of IPv4 routing rule is %d.\n", num_rt_rule);
		for(i=0; i<num_rt_rule; i++)
		{
			IPACMDBG_H("Routing rule %d handle %d\n", i, rt_rule_hdl[i]);
			client->intra_iface_rt_rule_hdl.rule_hdl[IPA_IP_v4][i] = rt_rule_hdl[i];
		}

		m_p_iface->eth_bridge_add_rt_rule(client->mac_addr, peer_info->rt_tbl_name_for_rt[IPA_IP_v6], hdr_proc_ctx_for_intra_interface,
			peer_l2_hdr_type, IPA_IP_v6, rt_rule_hdl, &num_rt_rule);

		client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v6] = num_rt_rule;
		IPACMDBG_H("Number of IPv6 routing rule is %d.\n", num_rt_rule);
		for(i=0; i<num_rt_rule; i++)
		{
			IPACMDBG_H("Routing rule %d handle %d\n", i, rt_rule_hdl[i]);
			client->intra_iface_rt_rule_hdl.rule_hdl[IPA_IP_v6][i] = rt_rule_hdl[i];
		}
	}

	return;
}

void IPACM_LanToLan_Iface::add_all_inter_interface_client_flt_rule(ipa_ip_type iptype)
{
	list<peer_iface_info>::iterator it_iface;
	list<client_info>::iterator it_client;

	for(it_iface = m_peer_iface_info.begin(); it_iface != m_peer_iface_info.end(); it_iface++)
	{
		IPACMDBG_H("Add flt rules for clients of interface %s.\n", it_iface->peer->get_iface_pointer()->dev_name);
		for(it_client = it_iface->peer->m_client_info.begin(); it_client != it_iface->peer->m_client_info.end(); it_client++)
		{
			add_client_flt_rule(&(*it_iface), &(*it_client), iptype);
		}
	}
	return;
}

void IPACM_LanToLan_Iface::add_all_intra_interface_client_flt_rule(ipa_ip_type iptype)
{
	list<client_info>::iterator it_client;

	IPACMDBG_H("Add flt rules for own clients.\n");
	for(it_client = m_client_info.begin(); it_client != m_client_info.end(); it_client++)
	{
		add_client_flt_rule(&m_intra_interface_info, &(*it_client), iptype);
	}

	return;
}

void IPACM_LanToLan_Iface::add_one_client_flt_rule(IPACM_LanToLan_Iface *peer_iface, client_info *client)
{
	list<peer_iface_info>::iterator it;

	for(it = m_peer_iface_info.begin(); it != m_peer_iface_info.end(); it++)
	{
		if(it->peer == peer_iface)
		{
			IPACMDBG_H("Found the peer iface info.\n");
			if(m_is_ip_addr_assigned[IPA_IP_v4])
			{
				add_client_flt_rule(&(*it), client, IPA_IP_v4);
			}
			if(m_is_ip_addr_assigned[IPA_IP_v6])
			{
				add_client_flt_rule(&(*it), client, IPA_IP_v6);
			}

			break;
		}
	}
	return;
}

void IPACM_LanToLan_Iface::add_client_flt_rule(peer_iface_info *peer, client_info *client, ipa_ip_type iptype)
{
	list<flt_rule_info>::iterator it_flt;
	uint32_t flt_rule_hdl;
	flt_rule_info new_flt_info;
	ipa_ioc_get_rt_tbl rt_tbl;

	rt_tbl.ip = iptype;
	memcpy(rt_tbl.name, peer->rt_tbl_name_for_flt[iptype], sizeof(rt_tbl.name));
	IPACMDBG_H("This flt rule points to rt tbl %s.\n", rt_tbl.name);

	if(IPACM_Iface::m_routing.GetRoutingTable(&rt_tbl) == false)
	{
		IPACMERR("Failed to get routing table.\n");
		return;
	}

	m_p_iface->eth_bridge_add_flt_rule(client->mac_addr, rt_tbl.hdl,
		iptype, &flt_rule_hdl);
	IPACMDBG_H("Installed flt rule for IP type %d: handle %d\n", iptype, flt_rule_hdl);

	for(it_flt = peer->flt_rule.begin(); it_flt != peer->flt_rule.end(); it_flt++)
	{
		if(it_flt->p_client == client)	//the client is already in the flt info list
		{
			IPACMDBG_H("The client is found in flt info list.\n");
			it_flt->flt_rule_hdl[iptype] = flt_rule_hdl;
			break;
		}
	}

	if(it_flt == peer->flt_rule.end())	//the client is not in the flt info list
	{
		IPACMDBG_H("The client is not found in flt info list, insert a new one.\n");
		memset(&new_flt_info, 0, sizeof(new_flt_info));
		new_flt_info.p_client = client;
		new_flt_info.flt_rule_hdl[iptype] = flt_rule_hdl;

		peer->flt_rule.push_front(new_flt_info);
	}

	return;
}

void IPACM_LanToLan_Iface::del_one_client_flt_rule(IPACM_LanToLan_Iface *peer_iface, client_info *client)
{
	list<peer_iface_info>::iterator it;

	for(it = m_peer_iface_info.begin(); it != m_peer_iface_info.end(); it++)
	{
		if(it->peer == peer_iface)
		{
			IPACMDBG_H("Found the peer iface info.\n");
			del_client_flt_rule(&(*it), client);
			break;
=======
int IPACM_LanToLan::clear_peer_list(client_info* client)
{
	if(client == NULL)
	{
		IPACMERR("Client is NULL.\n");
		return IPACM_FAILURE;
	}

	bool err_flag;
	peer_info_list::iterator client_it;
	peer_info_list::iterator peer_it;
	client_info* peer;

	for(client_it = client->peer.begin(); client_it != client->peer.end(); client_it++)
	{
		err_flag = true;
		peer = client_it->peer_pointer;
		for(peer_it = peer->peer.begin(); peer_it != peer->peer.end(); peer_it++)
		{
			if(peer_it->peer_pointer == client)
			{
				peer->peer.erase(peer_it);
				err_flag = false;
				break;
			}
		}
		if(err_flag == true)
		{
			IPACMERR("Failed to find peer info.\n");
			return IPACM_FAILURE;
		}
	}
	client->peer.clear();
	return IPACM_SUCCESS;
}

void IPACM_LanToLan::handle_client_power_save(ipacm_event_lan_client* data)
{
	if(data == NULL)
	{
		IPACMERR("No client info is found.\n");
		return;
	}
	if(data->mac_addr == NULL || data->ipv6_addr == NULL || data->p_iface == NULL)
	{
		IPACMERR("Event data is not populated properly.\n");
		return;
	}
	if(data->iptype != IPA_IP_v4 && data->iptype != IPA_IP_v6)
	{
		IPACMERR("IP type is not expected: %d.\n", data->iptype);
		return;
	}

	IPACMDBG_H("Client power save info: iface %s, iptype: %d, mac: 0x%02x%02x%02x%02x%02x%02x, v4_addr: 0x%08x, v6_addr: 0x%08x%08x%08x%08x \n",
		data->p_iface->dev_name, data->iptype,
		data->mac_addr[0], data->mac_addr[1], data->mac_addr[2], data->mac_addr[3], data->mac_addr[4], data->mac_addr[5],
		data->ipv4_addr, data->ipv6_addr[0], data->ipv6_addr[1], data->ipv6_addr[2], data->ipv6_addr[3]);

	client_info* client_ptr;
	uint64_t v6_addr;

	if(data->iptype == IPA_IP_v4)
	{
		if(client_info_v4_.count(data->ipv4_addr) == 0)//if not found the client, return
		{
			IPACMERR("The client is not found the client, return.\n");
			return;
		}
		IPACMDBG_H("The client is found.\n");
		client_info& client = client_info_v4_[data->ipv4_addr];
		client_ptr = &client;
	}
	else
	{
		memcpy(&v6_addr, &(data->ipv6_addr[2]), sizeof(uint64_t));
		if(client_info_v6_.count(v6_addr) == 0)	//if not found the client, insert it in table
		{
			IPACMERR("The client is not found the client, return.\n");
			return;
		}
		IPACMDBG_H("The client is found.\n");
		client_info& client = client_info_v6_[v6_addr];
		client_ptr = &client;
	}

	if(remove_flt_rules(data->iptype, client_ptr) == IPACM_FAILURE)
	{
		IPACMERR("Failed to remove flt rules when power save.\n");
		return;
	}
	client_ptr->is_active = false;
	client_ptr->is_powersave = true;
	return;
}

void IPACM_LanToLan::handle_new_lan2lan_connection(ipacm_event_connection* data)
{
	IPACMDBG_H("New lan2lan connection info: IP type: %d, src_v4_addr: 0x%08x, dst_v4_addr: 0x%08x\n", data->iptype, data->src_ipv4_addr, data->dst_ipv4_addr);
	IPACMDBG_H("src_v6_addr: 0x%08x%08x%08x%08x, dst_v6_addr: 0x%08x%08x%08x%08x", data->src_ipv6_addr[0], data->src_ipv6_addr[1], data->src_ipv6_addr[2],
				data->src_ipv6_addr[3], data->dst_ipv6_addr[0], data->dst_ipv6_addr[1], data->dst_ipv6_addr[2], data->dst_ipv6_addr[3]);

	client_info* src_client_ptr;
	client_info* dst_client_ptr;

	if(data->iptype == IPA_IP_v4)
	{
		if(client_info_v4_.count(data->src_ipv4_addr) == 0 || client_info_v4_.count(data->dst_ipv4_addr) == 0)
=======
int IPACM_LanToLan::clear_peer_list(client_info* client)
{
	if(client == NULL)
	{
		IPACMERR("Client is NULL.\n");
		return IPACM_FAILURE;
	}

	bool err_flag;
	peer_info_list::iterator client_it;
	peer_info_list::iterator peer_it;
	client_info* peer;

	for(client_it = client->peer.begin(); client_it != client->peer.end(); client_it++)
	{
		err_flag = true;
		peer = client_it->peer_pointer;
		for(peer_it = peer->peer.begin(); peer_it != peer->peer.end(); peer_it++)
		{
			if(peer_it->peer_pointer == client)
			{
				peer->peer.erase(peer_it);
				err_flag = false;
				break;
			}
		}
		if(err_flag == true)
		{
			IPACMERR("Failed to find peer info.\n");
			return IPACM_FAILURE;
		}
	}
	client->peer.clear();
	return IPACM_SUCCESS;
}

void IPACM_LanToLan::handle_client_power_save(ipacm_event_lan_client* data)
{
	if(data == NULL)
	{
		IPACMERR("No client info is found.\n");
		return;
	}
	if(data->mac_addr == NULL || data->ipv6_addr == NULL || data->p_iface == NULL)
	{
		IPACMERR("Event data is not populated properly.\n");
		return;
	}
	if(data->iptype != IPA_IP_v4 && data->iptype != IPA_IP_v6)
	{
		IPACMERR("IP type is not expected: %d.\n", data->iptype);
		return;
	}

	IPACMDBG_H("Client power save info: iface %s, iptype: %d, mac: 0x%02x%02x%02x%02x%02x%02x, v4_addr: 0x%08x, v6_addr: 0x%08x%08x%08x%08x \n",
		data->p_iface->dev_name, data->iptype,
		data->mac_addr[0], data->mac_addr[1], data->mac_addr[2], data->mac_addr[3], data->mac_addr[4], data->mac_addr[5],
		data->ipv4_addr, data->ipv6_addr[0], data->ipv6_addr[1], data->ipv6_addr[2], data->ipv6_addr[3]);

	client_info* client_ptr;
	uint64_t v6_addr;

	if(data->iptype == IPA_IP_v4)
	{
		if(client_info_v4_.count(data->ipv4_addr) == 0)//if not found the client, return
		{
			IPACMERR("The client is not found the client, return.\n");
			return;
		}
		IPACMDBG_H("The client is found.\n");
		client_info& client = client_info_v4_[data->ipv4_addr];
		client_ptr = &client;
	}
	else
	{
		memcpy(&v6_addr, &(data->ipv6_addr[2]), sizeof(uint64_t));
		if(client_info_v6_.count(v6_addr) == 0)	//if not found the client, insert it in table
		{
			IPACMERR("The client is not found the client, return.\n");
			return;
		}
		IPACMDBG_H("The client is found.\n");
		client_info& client = client_info_v6_[v6_addr];
		client_ptr = &client;
	}

	if(remove_flt_rules(data->iptype, client_ptr) == IPACM_FAILURE)
	{
		IPACMERR("Failed to remove flt rules when power save.\n");
		return;
	}
	client_ptr->is_active = false;
	client_ptr->is_powersave = true;
	return;
}

void IPACM_LanToLan::handle_new_lan2lan_connection(ipacm_event_connection* data)
{
	IPACMDBG_H("New lan2lan connection info: IP type: %d, src_v4_addr: 0x%08x, dst_v4_addr: 0x%08x\n", data->iptype, data->src_ipv4_addr, data->dst_ipv4_addr);
	IPACMDBG_H("src_v6_addr: 0x%08x%08x%08x%08x, dst_v6_addr: 0x%08x%08x%08x%08x", data->src_ipv6_addr[0], data->src_ipv6_addr[1], data->src_ipv6_addr[2],
				data->src_ipv6_addr[3], data->dst_ipv6_addr[0], data->dst_ipv6_addr[1], data->dst_ipv6_addr[2], data->dst_ipv6_addr[3]);

	client_info* src_client_ptr;
	client_info* dst_client_ptr;

	if(data->iptype == IPA_IP_v4)
	{
		if(client_info_v4_.count(data->src_ipv4_addr) == 0 || client_info_v4_.count(data->dst_ipv4_addr) == 0)
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
		{
			IPACMERR("Either source or destination is not in table.\n");
			return;
		}
		client_info& src_client = client_info_v4_[data->src_ipv4_addr];
		src_client_ptr = &src_client;
		client_info& dst_client = client_info_v4_[data->dst_ipv4_addr];
		dst_client_ptr = &dst_client;
	}
	else //ipv6 case
	{
		uint64_t src_ipv6_addr;
		uint64_t dst_ipv6_addr;
		memcpy(&src_ipv6_addr, &(data->src_ipv6_addr[2]), sizeof(uint64_t));
		memcpy(&dst_ipv6_addr, &(data->dst_ipv6_addr[2]), sizeof(uint64_t));

		if(client_info_v6_.count(src_ipv6_addr) == 0 || client_info_v6_.count(dst_ipv6_addr) == 0)
		{
			IPACMERR("Either source or destination is not in table.\n");
			return;
		}
		client_info& src_client = client_info_v6_[src_ipv6_addr];
		src_client_ptr = &src_client;
		client_info& dst_client = client_info_v6_[dst_ipv6_addr];
		dst_client_ptr = &dst_client;
	}

	IPACMDBG_H("Both src and dst are already in table.\n");
	bool is_first_connection;
	is_first_connection = add_connection(src_client_ptr, dst_client_ptr);

	if(is_first_connection && src_client_ptr->is_active && dst_client_ptr->is_active)
	{
		IPACMDBG_H("This is first connection, add offload links.\n");

		if(add_offload_link(data->iptype, src_client_ptr, dst_client_ptr) == IPACM_FAILURE)
		{
			IPACMERR("Failed to add offload link for src->dst direction.\n");
			return;
		}
		if(add_offload_link(data->iptype, dst_client_ptr, src_client_ptr) == IPACM_FAILURE)
		{
			IPACMERR("Failed to add offload link for dst->src direction.\n");
			return;
		}

		if(data->iptype == IPA_IP_v4)
		{
			num_offload_pair_v4_ ++;
			IPACMDBG_H("Added offload links, now num_offload_pair_v4_: %d\n", num_offload_pair_v4_);
		}
		else
		{
			num_offload_pair_v6_ ++;
			IPACMDBG_H("Added offload links, now num_offload_pair_v6_: %d\n", num_offload_pair_v6_);
		}
	}
	return;
}

//If need to insert an entry in peer list, return true, otherwise return false
bool IPACM_LanToLan::add_connection(client_info* src_client, client_info* dst_client)
{
	if(src_client == NULL || dst_client == NULL)
	{
		IPACMERR("Either source or dest client is NULL.\n");
		return false;
	}

	peer_info_list::iterator it;
	peer_info new_peer;
	bool ret = false;

	for(it = src_client->peer.begin(); it != src_client->peer.end(); it++)
	{
		if(it->peer_pointer == dst_client)
		{
			it->num_connection++;
			IPACMDBG_H("Find dst client entry in peer list, connection count: %d\n", it->num_connection);
			break;
		}
	}
	if(it == src_client->peer.end())
	{
		IPACMDBG_H("Not finding dst client entry, insert a new one in peer list.\n");
		new_peer.peer_pointer = dst_client;
		new_peer.num_connection = 1;
		src_client->peer.push_back(new_peer);
		ret = true;
	}

	for(it = dst_client->peer.begin(); it != dst_client->peer.end(); it++)
	{
		if(it->peer_pointer == src_client)
		{
			it->num_connection++;
			IPACMDBG_H("Find dst client entry in peer list, connection count: %d\n", it->num_connection);
			break;
		}
	}
	if(it == dst_client->peer.end())
	{
		IPACMDBG_H("Not finding src client entry, insert a new one in peer list.\n");
		new_peer.peer_pointer = src_client;
		new_peer.num_connection = 1;
		dst_client->peer.push_back(new_peer);
		ret = true;
	}
	return ret;
}

void IPACM_LanToLan::handle_del_lan2lan_connection(ipacm_event_connection* data)
{
	IPACMDBG_H("Del lan2lan connection info: IP type: %d, src_v4_addr: 0x%08x, dst_v4_addr: 0x%08x\n", data->iptype, data->src_ipv4_addr, data->dst_ipv4_addr);
	IPACMDBG_H("src_v6_addr: 0x%08x%08x%08x%08x, dst_v6_addr: 0x%08x%08x%08x%08x", data->src_ipv6_addr[0], data->src_ipv6_addr[1], data->src_ipv6_addr[2],
				data->src_ipv6_addr[3], data->dst_ipv6_addr[0], data->dst_ipv6_addr[1], data->dst_ipv6_addr[2], data->dst_ipv6_addr[3]);

	bool res;
	uint64_t src_ipv6_addr, dst_ipv6_addr;
	client_info* src_client_ptr;
	client_info* dst_client_ptr;

	if(data->iptype == IPA_IP_v4)
	{
		if(client_info_v4_.count(data->src_ipv4_addr) == 0
			|| client_info_v4_.count(data->dst_ipv4_addr) == 0)	//if not found the client
		{
			IPACMDBG_H("Not found either source or dest client, return.\n");
			return;
		}
		client_info& src_client = client_info_v4_[data->src_ipv4_addr];
		client_info& dst_client = client_info_v4_[data->dst_ipv4_addr];
		src_client_ptr = &src_client;
		dst_client_ptr = &dst_client;
	}
	else
	{
		memcpy(&src_ipv6_addr, &(data->src_ipv6_addr[2]), sizeof(uint64_t));
		memcpy(&dst_ipv6_addr, &(data->dst_ipv6_addr[2]), sizeof(uint64_t));
		if(client_info_v6_.count(src_ipv6_addr) == 0
			|| client_info_v6_.count(dst_ipv6_addr) == 0)//if not found the client
		{
			IPACMDBG_H("Not found either source or dest client, return.\n");
			return;
		}
		client_info& src_client = client_info_v6_[src_ipv6_addr];
		client_info& dst_client = client_info_v6_[dst_ipv6_addr];
		src_client_ptr = &src_client;
		dst_client_ptr = &dst_client;
	}

	res = remove_connection(src_client_ptr, dst_client_ptr);

	if(res && src_client_ptr->is_active && dst_client_ptr->is_active)
	{
		IPACMDBG_H("Erase link info for both src and dst entries.\n");
		erase_offload_link(data->iptype, src_client_ptr, dst_client_ptr);
	}
	else
	{
		if(res && src_client_ptr->is_powersave && (dst_client_ptr->is_active || dst_client_ptr->is_powersave))
		{
			IPACMDBG_H("Erase link info for both src and dst entries due to src powersave.\n");
			erase_offload_link(data->iptype, src_client_ptr, dst_client_ptr);
		}
		if(res && dst_client_ptr->is_powersave && (src_client_ptr->is_active || src_client_ptr->is_powersave))
		{
			IPACMDBG_H("Erase link info for both src and dst entries due to dst powersave.\n");
			erase_offload_link(data->iptype, dst_client_ptr, src_client_ptr);
		}
	}

	//if the src client is not active and not powersave mode, if peer list is empty, remove client entry
	if(res && src_client_ptr->is_active == false && src_client_ptr->is_powersave == false && src_client_ptr->peer.size() == 0)
	{
		IPACMDBG_H("Peer list of src is empty, remove src entry.\n");
		if(data->iptype == IPA_IP_v4)
		{
			client_info_v4_.erase(data->src_ipv4_addr);
		}
		else
		{
			client_info_v6_.erase(src_ipv6_addr);
		}
	}

	//if the dst client is not active and not powersave mode, if peer list is empty, remove client entry
	if(res && dst_client_ptr->is_active == false && dst_client_ptr->is_powersave == false && dst_client_ptr->peer.size() == 0)
	{
		IPACMDBG_H("Peer list of dst is empty, remove dst entry.\n");
		if(data->iptype == IPA_IP_v4)
		{
			client_info_v4_.erase(data->dst_ipv4_addr);
		}
		else
		{
			client_info_v6_.erase(dst_ipv6_addr);
<<<<<<< HEAD
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
		}
	}
	return;
}

<<<<<<< HEAD
void IPACM_LanToLan_Iface::del_client_flt_rule(peer_iface_info *peer, client_info *client)
{
	list<flt_rule_info>::iterator it_flt;

	for(it_flt = peer->flt_rule.begin(); it_flt != peer->flt_rule.end(); it_flt++)
	{
		if(it_flt->p_client == client)	//found the client in flt info list
		{
			IPACMDBG_H("Found the client in flt info list.\n");
			if(m_is_ip_addr_assigned[IPA_IP_v4])
			{
				m_p_iface->eth_bridge_del_flt_rule(it_flt->flt_rule_hdl[IPA_IP_v4], IPA_IP_v4);
				IPACMDBG_H("IPv4 flt rule %d is deleted.\n", it_flt->flt_rule_hdl[IPA_IP_v4]);
			}
			if(m_is_ip_addr_assigned[IPA_IP_v6])
			{
				m_p_iface->eth_bridge_del_flt_rule(it_flt->flt_rule_hdl[IPA_IP_v6], IPA_IP_v6);
				IPACMDBG_H("IPv6 flt rule %d is deleted.\n", it_flt->flt_rule_hdl[IPA_IP_v6]);
			}

			peer->flt_rule.erase(it_flt);
			break;
		}
	}
	return;
}

void IPACM_LanToLan_Iface::del_client_rt_rule(peer_iface_info *peer, client_info *client)
{
	ipa_hdr_l2_type peer_l2_hdr_type;
	int i, num_rules;

	peer_l2_hdr_type = peer->peer->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type;
	/* if the peer info is not for intra interface communication */
	if(peer->peer != this)
	{
		IPACMDBG_H("Delete routing rules for inter interface communication.\n");

		num_rules = client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].num_hdl[IPA_IP_v4];
		for(i = 0; i < num_rules; i++)
		{
			m_p_iface->eth_bridge_del_rt_rule(client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].rule_hdl[IPA_IP_v4][i], IPA_IP_v4);
			IPACMDBG_H("IPv4 rt rule %d is deleted.\n", client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].rule_hdl[IPA_IP_v4][i]);
		}
		client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].num_hdl[IPA_IP_v4] = 0;

		num_rules = client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].num_hdl[IPA_IP_v6];
		for(i = 0; i < num_rules; i++)
		{
			m_p_iface->eth_bridge_del_rt_rule(client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].rule_hdl[IPA_IP_v6][i], IPA_IP_v6);
			IPACMDBG_H("IPv6 rt rule %d is deleted.\n", client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].rule_hdl[IPA_IP_v6][i]);
		}
		client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].num_hdl[IPA_IP_v6] = 0;
	}
	else
	{
		IPACMDBG_H("Delete routing rules for intra interface communication.\n");
		num_rules = client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v4];
		for(i = 0; i < num_rules; i++)
		{
			m_p_iface->eth_bridge_del_rt_rule(client->intra_iface_rt_rule_hdl.rule_hdl[IPA_IP_v4][i], IPA_IP_v4);
			IPACMDBG_H("IPv4 rt rule %d is deleted.\n", client->intra_iface_rt_rule_hdl.rule_hdl[IPA_IP_v4][i]);
		}
		client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v4] = 0;

		num_rules = client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v6];
		for(i = 0; i < num_rules; i++)
		{
			m_p_iface->eth_bridge_del_rt_rule(client->intra_iface_rt_rule_hdl.rule_hdl[IPA_IP_v6][i], IPA_IP_v6);
			IPACMDBG_H("IPv6 rt rule %d is deleted.\n", client->intra_iface_rt_rule_hdl.rule_hdl[IPA_IP_v6][i]);
		}
		client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v6] = 0;
	}

	return;
}

void IPACM_LanToLan_Iface::handle_down_event()
{
	list<IPACM_LanToLan_Iface>::iterator it_other_iface;
	list<peer_iface_info>::iterator it_own_peer_info, it_other_iface_peer_info;
	IPACM_LanToLan_Iface *other_iface;

	/* clear inter-interface rules */
	if(m_support_inter_iface_offload)
	{
		for(it_own_peer_info = m_peer_iface_info.begin(); it_own_peer_info != m_peer_iface_info.end();
			it_own_peer_info++)
		{
			/* decrement reference count of peer l2 header type on both interfaces*/
			decrement_ref_cnt_peer_l2_hdr_type(it_own_peer_info->peer->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type);
			it_own_peer_info->peer->decrement_ref_cnt_peer_l2_hdr_type(m_p_iface->tx_prop->tx[0].hdr_l2_type);

			/* first clear all flt rule on target interface */
			IPACMDBG_H("Clear all flt rule on target interface.\n");
			clear_all_flt_rule_for_one_peer_iface(&(*it_own_peer_info));

			other_iface = it_own_peer_info->peer;
			/* then clear all flt/rt rule and hdr proc ctx for target interface on peer interfaces */
			IPACMDBG_H("Clear all flt/rt rules and hdr proc ctx for target interface on peer interfaces %s.\n",
				it_own_peer_info->peer->get_iface_pointer()->dev_name);
			for(it_other_iface_peer_info = other_iface->m_peer_iface_info.begin();
				it_other_iface_peer_info != other_iface->m_peer_iface_info.end();
				it_other_iface_peer_info++)
			{
				if(it_other_iface_peer_info->peer == this)	//found myself in other iface's peer info list
				{
					IPACMDBG_H("Found the right peer info on other iface.\n");
					other_iface->clear_all_flt_rule_for_one_peer_iface(&(*it_other_iface_peer_info));
					other_iface->clear_all_rt_rule_for_one_peer_iface(&(*it_other_iface_peer_info));
					/* remove the peer info from the list */
					other_iface->m_peer_iface_info.erase(it_other_iface_peer_info);
					other_iface->del_hdr_proc_ctx(m_p_iface->tx_prop->tx[0].hdr_l2_type);
					break;
				}
			}

			/* then clear rt rule and hdr proc ctx and release rt table on target interface */
			IPACMDBG_H("Clear rt rules and hdr proc ctx and release rt table on target interface.\n");
			clear_all_rt_rule_for_one_peer_iface(&(*it_own_peer_info));
			del_hdr_proc_ctx(it_own_peer_info->peer->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type);
		}
		m_peer_iface_info.clear();
	}

	/* clear intra interface rules */
	if(m_support_intra_iface_offload)
	{
		IPACMDBG_H("Clear intra interface flt/rt rules and hdr proc ctx, release rt tables.\n");
		clear_all_flt_rule_for_one_peer_iface(&m_intra_interface_info);
		clear_all_rt_rule_for_one_peer_iface(&m_intra_interface_info);
		m_p_iface->eth_bridge_del_hdr_proc_ctx(hdr_proc_ctx_for_intra_interface);
		IPACMDBG_H("Hdr proc ctx with hdl %d is deleted.\n", hdr_proc_ctx_for_intra_interface);
	}

	/* then clear the client info list */
	m_client_info.clear();

	return;
}

void IPACM_LanToLan_Iface::clear_all_flt_rule_for_one_peer_iface(peer_iface_info *peer)
{
	list<flt_rule_info>::iterator it;

	for(it = peer->flt_rule.begin(); it != peer->flt_rule.end(); it++)
	{
		if(m_is_ip_addr_assigned[IPA_IP_v4])
		{
			m_p_iface->eth_bridge_del_flt_rule(it->flt_rule_hdl[IPA_IP_v4], IPA_IP_v4);
			IPACMDBG_H("IPv4 flt rule %d is deleted.\n", it->flt_rule_hdl[IPA_IP_v4]);
		}
		if(m_is_ip_addr_assigned[IPA_IP_v6])
		{
			m_p_iface->eth_bridge_del_flt_rule(it->flt_rule_hdl[IPA_IP_v6], IPA_IP_v6);
			IPACMDBG_H("IPv6 flt rule %d is deleted.\n", it->flt_rule_hdl[IPA_IP_v6]);
		}
	}
	peer->flt_rule.clear();
	return;
}

void IPACM_LanToLan_Iface::clear_all_rt_rule_for_one_peer_iface(peer_iface_info *peer)
{
	list<client_info>::iterator it;
	ipa_hdr_l2_type peer_l2_type;

	peer_l2_type = peer->peer->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type;
	if(ref_cnt_peer_l2_hdr_type[peer_l2_type] == 0)
	{
		for(it = m_client_info.begin(); it != m_client_info.end(); it++)
		{
			del_client_rt_rule(peer, &(*it));
		}
	}

	return;
}

void IPACM_LanToLan_Iface::handle_wlan_scc_mcc_switch()
{
	list<peer_iface_info>::iterator it_peer_info;
	list<client_info>::iterator it_client;
	ipa_hdr_l2_type peer_l2_hdr_type;
	bool flag[IPA_HDR_L2_MAX];
	int i;

	/* modify inter-interface routing rules */
	if(m_support_inter_iface_offload)
	{
		IPACMDBG_H("Modify rt rules for peer interfaces.\n");
		memset(flag, 0, sizeof(flag));
		for(it_peer_info = m_peer_iface_info.begin(); it_peer_info != m_peer_iface_info.end(); it_peer_info++)
		{
			peer_l2_hdr_type = it_peer_info->peer->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type;
			if(flag[peer_l2_hdr_type] == false)
			{
				flag[peer_l2_hdr_type] = true;
				for(it_client = m_client_info.begin(); it_client != m_client_info.end(); it_client++)
				{
					m_p_iface->eth_bridge_modify_rt_rule(it_client->mac_addr, hdr_proc_ctx_for_inter_interface[peer_l2_hdr_type],
						peer_l2_hdr_type, IPA_IP_v4, it_client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].rule_hdl[IPA_IP_v4],
						it_client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].num_hdl[IPA_IP_v4]);
					IPACMDBG_H("The following IPv4 routing rules are modified:\n");
					for(i = 0; i < it_client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].num_hdl[IPA_IP_v4]; i++)
					{
						IPACMDBG_H("%d\n", it_client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].rule_hdl[IPA_IP_v4][i]);
					}

					m_p_iface->eth_bridge_modify_rt_rule(it_client->mac_addr, hdr_proc_ctx_for_inter_interface[peer_l2_hdr_type],
						peer_l2_hdr_type, IPA_IP_v6, it_client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].rule_hdl[IPA_IP_v6],
						it_client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].num_hdl[IPA_IP_v6]);
					IPACMDBG_H("The following IPv6 routing rules are modified:\n");
					for(i = 0; i < it_client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].num_hdl[IPA_IP_v6]; i++)
					{
						IPACMDBG_H("%d\n", it_client->inter_iface_rt_rule_hdl[peer_l2_hdr_type].rule_hdl[IPA_IP_v6][i]);
					}
				}
			}
		}
	}

	/* modify routing rules for intra-interface communication */
	IPACMDBG_H("Modify rt rules for intra-interface communication.\n");
	if(m_support_intra_iface_offload)
	{
		for(it_client = m_client_info.begin(); it_client != m_client_info.end(); it_client++)
		{
			m_p_iface->eth_bridge_modify_rt_rule(it_client->mac_addr, hdr_proc_ctx_for_intra_interface,
				m_p_iface->tx_prop->tx[0].hdr_l2_type, IPA_IP_v4, it_client->intra_iface_rt_rule_hdl.rule_hdl[IPA_IP_v4],
				it_client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v4]);
			IPACMDBG_H("The following IPv4 routing rules are modified:\n");
			for(i = 0; i < it_client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v4]; i++)
			{
				IPACMDBG_H("%d\n", it_client->intra_iface_rt_rule_hdl.rule_hdl[IPA_IP_v4][i]);
			}

			m_p_iface->eth_bridge_modify_rt_rule(it_client->mac_addr, hdr_proc_ctx_for_intra_interface,
				m_p_iface->tx_prop->tx[0].hdr_l2_type, IPA_IP_v6, it_client->intra_iface_rt_rule_hdl.rule_hdl[IPA_IP_v6],
				it_client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v6]);
			IPACMDBG_H("The following IPv6 routing rules are modified:\n");
			for(i = 0; i < it_client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v6]; i++)
			{
				IPACMDBG_H("%d\n", it_client->intra_iface_rt_rule_hdl.rule_hdl[IPA_IP_v6][i]);
			}
		}
	}

	return;
}

void IPACM_LanToLan_Iface::handle_intra_interface_info()
{
	uint32_t hdr_proc_ctx_hdl;

	if(m_p_iface->tx_prop == NULL)
	{
		IPACMERR("No tx prop.\n");
		return;
	}

	m_intra_interface_info.peer = this;

	snprintf(m_intra_interface_info.rt_tbl_name_for_flt[IPA_IP_v4], IPA_RESOURCE_NAME_MAX,
		"eth_v4_intra_interface");
	IPACMDBG_H("IPv4 routing table for flt name: %s\n", m_intra_interface_info.rt_tbl_name_for_flt[IPA_IP_v4]);
	snprintf(m_intra_interface_info.rt_tbl_name_for_flt[IPA_IP_v6], IPA_RESOURCE_NAME_MAX,
		"eth_v6_intra_interface");
	IPACMDBG_H("IPv6 routing table for flt name: %s\n", m_intra_interface_info.rt_tbl_name_for_flt[IPA_IP_v6]);

	memcpy(m_intra_interface_info.rt_tbl_name_for_rt[IPA_IP_v4], m_intra_interface_info.rt_tbl_name_for_flt[IPA_IP_v4],
		IPA_RESOURCE_NAME_MAX);
	IPACMDBG_H("IPv4 routing table for rt name: %s\n", m_intra_interface_info.rt_tbl_name_for_rt[IPA_IP_v4]);
	memcpy(m_intra_interface_info.rt_tbl_name_for_rt[IPA_IP_v6], m_intra_interface_info.rt_tbl_name_for_flt[IPA_IP_v6],
		IPA_RESOURCE_NAME_MAX);
	IPACMDBG_H("IPv6 routing table for rt name: %s\n", m_intra_interface_info.rt_tbl_name_for_rt[IPA_IP_v6]);

	m_p_iface->eth_bridge_add_hdr_proc_ctx(m_p_iface->tx_prop->tx[0].hdr_l2_type,
		&hdr_proc_ctx_hdl);
	hdr_proc_ctx_for_intra_interface = hdr_proc_ctx_hdl;
	IPACMDBG_H("Hdr proc ctx for intra-interface communication: hdl %d\n", hdr_proc_ctx_hdl);

	return;
}

void IPACM_LanToLan_Iface::handle_new_iface_up(char rt_tbl_name_for_flt[][IPA_RESOURCE_NAME_MAX], char rt_tbl_name_for_rt[][IPA_RESOURCE_NAME_MAX],
		IPACM_LanToLan_Iface *peer_iface)
{
	peer_iface_info new_peer;
	ipa_hdr_l2_type peer_l2_hdr_type;

	new_peer.peer = peer_iface;
	memcpy(new_peer.rt_tbl_name_for_rt[IPA_IP_v4], rt_tbl_name_for_rt[IPA_IP_v4], IPA_RESOURCE_NAME_MAX);
	memcpy(new_peer.rt_tbl_name_for_rt[IPA_IP_v6], rt_tbl_name_for_rt[IPA_IP_v6], IPA_RESOURCE_NAME_MAX);
	memcpy(new_peer.rt_tbl_name_for_flt[IPA_IP_v4], rt_tbl_name_for_flt[IPA_IP_v4], IPA_RESOURCE_NAME_MAX);
	memcpy(new_peer.rt_tbl_name_for_flt[IPA_IP_v6], rt_tbl_name_for_flt[IPA_IP_v6], IPA_RESOURCE_NAME_MAX);

	peer_l2_hdr_type = peer_iface->m_p_iface->tx_prop->tx[0].hdr_l2_type;
	increment_ref_cnt_peer_l2_hdr_type(peer_l2_hdr_type);
	add_hdr_proc_ctx(peer_l2_hdr_type);

	/* push the new peer_iface_info into the list */
	m_peer_iface_info.push_front(new_peer);

	return;
}

void IPACM_LanToLan_Iface::handle_client_add(uint8_t *mac)
{
	list<client_info>::iterator it_client;
	list<peer_iface_info>::iterator it_peer_info;
	client_info new_client;
	bool flag[IPA_HDR_L2_MAX];

	for(it_client = m_client_info.begin(); it_client != m_client_info.end(); it_client++)
	{
		if(memcmp(it_client->mac_addr, mac, sizeof(it_client->mac_addr)) == 0)
		{
			IPACMDBG_H("This client has been added before.\n");
			return;
		}
	}

	if(m_client_info.size() == MAX_NUM_CLIENT)
	{
		IPACMDBG_H("The number of clients has reached maximum %d.\n", MAX_NUM_CLIENT);
		return;
	}

	memcpy(new_client.mac_addr, mac, sizeof(new_client.mac_addr));
	m_client_info.push_front(new_client);

	client_info &front_client = m_client_info.front();

	/* install inter-interface rules */
	if(m_support_inter_iface_offload)
	{
		memset(flag, 0, sizeof(flag));
		for(it_peer_info = m_peer_iface_info.begin(); it_peer_info != m_peer_iface_info.end(); it_peer_info++)
		{
			/* make sure add routing rule only once for each peer l2 header type */
			if(flag[it_peer_info->peer->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type] == false)
			{
				/* add client routing rule for each peer interface */
				add_client_rt_rule(&(*it_peer_info), &front_client);
				flag[it_peer_info->peer->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type] = true;
			}

			/* add client filtering rule on peer interfaces */
			it_peer_info->peer->add_one_client_flt_rule(this, &front_client);
		}
	}

	/* install intra-interface rules */
	if(m_support_intra_iface_offload)
	{
		/* add routing rule first */
		add_client_rt_rule(&m_intra_interface_info, &front_client);

		/* add filtering rule */
		if(m_is_ip_addr_assigned[IPA_IP_v4])
		{
			add_client_flt_rule(&m_intra_interface_info, &front_client, IPA_IP_v4);
		}
		if(m_is_ip_addr_assigned[IPA_IP_v6])
		{
			add_client_flt_rule(&m_intra_interface_info, &front_client, IPA_IP_v6);
		}
	}

	return;
}

void IPACM_LanToLan_Iface::handle_client_del(uint8_t *mac)
{
	list<client_info>::iterator it_client;
	list<peer_iface_info>::iterator it_peer_info;
	bool flag[IPA_HDR_L2_MAX];

	for(it_client = m_client_info.begin(); it_client != m_client_info.end(); it_client++)
	{
		if(memcmp(it_client->mac_addr, mac, sizeof(it_client->mac_addr)) == 0)	//found the client
		{
			IPACMDBG_H("Found the client.\n");
			break;
		}
	}

	if(it_client != m_client_info.end())	//if we found the client
	{
		/* uninstall inter-interface rules */
		if(m_support_inter_iface_offload)
		{
			memset(flag, 0, sizeof(flag));
			for(it_peer_info = m_peer_iface_info.begin(); it_peer_info != m_peer_iface_info.end();
				it_peer_info++)
			{
				IPACMDBG_H("Delete client filtering rule on peer interface.\n");
				it_peer_info->peer->del_one_client_flt_rule(this, &(*it_client));

				/* make sure to delete routing rule only once for each peer l2 header type */
				if(flag[it_peer_info->peer->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type] == false)
				{
					IPACMDBG_H("Delete client routing rule for peer interface.\n");
					del_client_rt_rule(&(*it_peer_info), &(*it_client));
					flag[it_peer_info->peer->get_iface_pointer()->tx_prop->tx[0].hdr_l2_type] = true;
				}
			}
		}

		/* uninstall intra-interface rules */
		if(m_support_intra_iface_offload)
		{
			/* delete filtering rule first */
			IPACMDBG_H("Delete client filtering rule for intra-interface communication.\n");
			del_client_flt_rule(&m_intra_interface_info, &(*it_client));

			/* delete routing rule */
			IPACMDBG_H("Delete client routing rule for intra-interface communication.\n");
			del_client_rt_rule(&m_intra_interface_info, &(*it_client));
		}

		/* erase the client from client info list */
		m_client_info.erase(it_client);
	}
	else
	{
		IPACMDBG_H("The client is not found.\n");
	}

	return;
}

void IPACM_LanToLan_Iface::add_hdr_proc_ctx(ipa_hdr_l2_type peer_l2_type)
{
	uint32_t hdr_proc_ctx_hdl;

	if(ref_cnt_peer_l2_hdr_type[peer_l2_type] == 1)
	{
		m_p_iface->eth_bridge_add_hdr_proc_ctx(peer_l2_type, &hdr_proc_ctx_hdl);
		hdr_proc_ctx_for_inter_interface[peer_l2_type] = hdr_proc_ctx_hdl;
		IPACMDBG_H("Installed inter-interface hdr proc ctx on iface %s: handle %d\n", m_p_iface->dev_name, hdr_proc_ctx_hdl);
	}
	return;
}

void IPACM_LanToLan_Iface::del_hdr_proc_ctx(ipa_hdr_l2_type peer_l2_type)
{
	if(ref_cnt_peer_l2_hdr_type[peer_l2_type] == 0)
	{
		m_p_iface->eth_bridge_del_hdr_proc_ctx(hdr_proc_ctx_for_inter_interface[peer_l2_type]);
		IPACMDBG_H("Hdr proc ctx with hdl %d is deleted.\n", hdr_proc_ctx_for_inter_interface[peer_l2_type]);
	}
	return;
}

void IPACM_LanToLan_Iface::print_data_structure_info()
{
	list<peer_iface_info>::iterator it_peer;
	list<client_info>::iterator it_client;
	int i, j, k;

	IPACMDBG_H("\n");
	IPACMDBG_H("Interface %s:\n", m_p_iface->dev_name);
	IPACMDBG_H("Is IPv4 addr assigned? %d\n", m_is_ip_addr_assigned[IPA_IP_v4]);
	IPACMDBG_H("Is IPv6 addr assigned? %d\n", m_is_ip_addr_assigned[IPA_IP_v6]);
	IPACMDBG_H("Support inter interface offload? %d\n", m_support_inter_iface_offload);
	IPACMDBG_H("Support intra interface offload? %d\n", m_support_intra_iface_offload);

	if(m_support_inter_iface_offload)
	{
		for(i = 0; i < IPA_HDR_L2_MAX; i++)
		{
			IPACMDBG_H("Ref_cnt of peer l2 type %s is %d.\n", ipa_l2_hdr_type[i], ref_cnt_peer_l2_hdr_type[i]);
			if(ref_cnt_peer_l2_hdr_type[i] > 0)
			{
				IPACMDBG_H("Hdr proc ctx for peer l2 type %s: %d\n", ipa_l2_hdr_type[i], hdr_proc_ctx_for_inter_interface[i]);
			}
		}
	}

	if(m_support_intra_iface_offload)
	{
		IPACMDBG_H("Hdr proc ctx for intra-interface: %d\n", hdr_proc_ctx_for_intra_interface);
	}

	i = 1;
	IPACMDBG_H("There are %d clients in total.\n", m_client_info.size());
	for(it_client = m_client_info.begin(); it_client != m_client_info.end(); it_client++)
	{
		IPACMDBG_H("Client %d MAC: 0x%02x%02x%02x%02x%02x%02x Pointer: 0x%08x\n", i, it_client->mac_addr[0], it_client->mac_addr[1],
			it_client->mac_addr[2], it_client->mac_addr[3], it_client->mac_addr[4], it_client->mac_addr[5], &(*it_client));

		if(m_support_inter_iface_offload)
		{
			for(j = 0; j < IPA_HDR_L2_MAX; j++)
			{
				if(ref_cnt_peer_l2_hdr_type[j] > 0)
				{
					IPACMDBG_H("Printing routing rule info for inter-interface communication for peer l2 type %s.\n",
						ipa_l2_hdr_type[j]);
					IPACMDBG_H("Number of IPv4 routing rules is %d, handles:\n", it_client->inter_iface_rt_rule_hdl[j].num_hdl[IPA_IP_v4]);
					for(k = 0; k < it_client->inter_iface_rt_rule_hdl[j].num_hdl[IPA_IP_v4]; k++)
					{
						IPACMDBG_H("%d\n", it_client->inter_iface_rt_rule_hdl[j].rule_hdl[IPA_IP_v4][k]);
					}

					IPACMDBG_H("Number of IPv6 routing rules is %d, handles:\n", it_client->inter_iface_rt_rule_hdl[j].num_hdl[IPA_IP_v6]);
					for(k = 0; k < it_client->inter_iface_rt_rule_hdl[j].num_hdl[IPA_IP_v6]; k++)
					{
						IPACMDBG_H("%d\n", it_client->inter_iface_rt_rule_hdl[j].rule_hdl[IPA_IP_v6][k]);
					}
				}
			}
		}

		if(m_support_intra_iface_offload)
		{
			IPACMDBG_H("Printing routing rule info for intra-interface communication.\n");
			IPACMDBG_H("Number of IPv4 routing rules is %d, handles:\n", it_client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v4]);
			for(j = 0; j < it_client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v4]; j++)
			{
				IPACMDBG_H("%d\n", it_client->intra_iface_rt_rule_hdl.rule_hdl[IPA_IP_v4][j]);
			}

			IPACMDBG_H("Number of IPv6 routing rules is %d, handles:\n", it_client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v6]);
			for(j = 0; j < it_client->intra_iface_rt_rule_hdl.num_hdl[IPA_IP_v6]; j++)
			{
				IPACMDBG_H("%d\n", it_client->intra_iface_rt_rule_hdl.rule_hdl[IPA_IP_v6][j]);
			}
		}
		i++;
	}

	IPACMDBG_H("There are %d peer interfaces in total.\n", m_peer_iface_info.size());
	for(it_peer = m_peer_iface_info.begin(); it_peer != m_peer_iface_info.end(); it_peer++)
	{
		print_peer_info(&(*it_peer));
	}

	if(m_support_intra_iface_offload)
	{
		IPACMDBG_H("This interface supports intra-interface communication, printing info:\n");
		print_peer_info(&m_intra_interface_info);
	}

	return;
}

void IPACM_LanToLan_Iface::print_peer_info(peer_iface_info *peer_info)
{
	list<flt_rule_info>::iterator it_flt;
	list<rt_rule_info>::iterator it_rt;

	IPACMDBG_H("Printing peer info for iface %s:\n", peer_info->peer->m_p_iface->dev_name);

	IPACMDBG_H("There are %d flt info in total.\n", peer_info->flt_rule.size());
	for(it_flt = peer_info->flt_rule.begin(); it_flt != peer_info->flt_rule.end(); it_flt++)
	{
		IPACMDBG_H("Flt rule handle for client 0x%08x:\n", it_flt->p_client);
		if(m_is_ip_addr_assigned[IPA_IP_v4])
		{
			IPACMDBG_H("IPv4 %d\n", it_flt->flt_rule_hdl[IPA_IP_v4]);
		}
		if(m_is_ip_addr_assigned[IPA_IP_v6])
		{
			IPACMDBG_H("IPv6 %d\n", it_flt->flt_rule_hdl[IPA_IP_v6]);
		}
	}

	return;
}

IPACM_Lan* IPACM_LanToLan_Iface::get_iface_pointer()
{
	return m_p_iface;
}

bool IPACM_LanToLan_Iface::get_m_is_ip_addr_assigned(ipa_ip_type iptype)
{
	IPACMDBG_H("Has IP address been assigned to interface %s for IP type %d? %d\n",
		m_p_iface->dev_name, iptype, m_is_ip_addr_assigned[iptype]);
	return m_is_ip_addr_assigned[iptype];
}

void IPACM_LanToLan_Iface::set_m_is_ip_addr_assigned(ipa_ip_type iptype, bool value)
{
	IPACMDBG_H("Is IP address of IP type %d assigned to interface %s? %d\n", iptype,
		m_p_iface->dev_name, value);
	m_is_ip_addr_assigned[iptype] = value;
}

bool IPACM_LanToLan_Iface::get_m_support_inter_iface_offload()
{
	IPACMDBG_H("Support inter interface offload on %s? %d\n", m_p_iface->dev_name,
		m_support_inter_iface_offload);
	return m_support_inter_iface_offload;
}

bool IPACM_LanToLan_Iface::get_m_support_intra_iface_offload()
{
	IPACMDBG_H("Support intra interface offload on %s? %d\n", m_p_iface->dev_name,
		m_support_intra_iface_offload);
	return m_support_intra_iface_offload;
}

void IPACM_LanToLan_Iface::increment_ref_cnt_peer_l2_hdr_type(ipa_hdr_l2_type peer_l2_type)
{
	ref_cnt_peer_l2_hdr_type[peer_l2_type]++;
	IPACMDBG_H("Now the ref_cnt of peer l2 hdr type %s is %d.\n", ipa_l2_hdr_type[peer_l2_type],
		ref_cnt_peer_l2_hdr_type[peer_l2_type]);

	return;
}

void IPACM_LanToLan_Iface::decrement_ref_cnt_peer_l2_hdr_type(ipa_hdr_l2_type peer_l2_type)
{
	ref_cnt_peer_l2_hdr_type[peer_l2_type]--;
	IPACMDBG_H("Now the ref_cnt of peer l2 hdr type %s is %d.\n", ipa_l2_hdr_type[peer_l2_type],
		ref_cnt_peer_l2_hdr_type[peer_l2_type]);

=======
=======
		}
	}
	return;
}

>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
//If need to remove an entry in peer list, return true, otherwise return false
bool IPACM_LanToLan::remove_connection(client_info* src_client, client_info* dst_client)
{
	if(src_client == NULL || dst_client == NULL)
	{
		IPACMERR("Either source or dest client is NULL.\n");
		return false;
	}

	peer_info_list::iterator it;
	bool ret = false;

	for(it = src_client->peer.begin(); it != src_client->peer.end(); it++)
	{
		if(it->peer_pointer == dst_client)
		{
			it->num_connection--;
			IPACMDBG_H("Find dst client entry in src peer list, connection count: %d\n", it->num_connection);
			if(it->num_connection == 0)
			{
				IPACMDBG_H("Need to remove dst entry in src peer list.\n");
				ret = true;
			}
			break;
		}
	}
	if(ret == true)
	{
		src_client->peer.erase(it);
	}

	ret = false;
	for(it = dst_client->peer.begin(); it != dst_client->peer.end(); it++)
	{
		if(it->peer_pointer == src_client)
		{
			it->num_connection--;
			IPACMDBG_H("Find src client entry in dst peer list, connection count: %d\n", it->num_connection);
			if(it->num_connection == 0)
			{
				IPACMDBG_H("Need to remove src entry in dst peer list.\n");
				ret = true;
			}
			break;
		}
	}
	if(ret == true)
	{
		dst_client->peer.erase(it);
	}
	return ret;
}

void IPACM_LanToLan::erase_offload_link(ipa_ip_type iptype, client_info* src_client, client_info* dst_client)
{
	if(src_client == NULL || dst_client == NULL)
	{
		IPACMERR("Either source or dest client is NULL.\n");
		return;
	}

	offload_link_info_list::iterator it;
	int res_src = IPACM_FAILURE, res_dst = IPACM_FAILURE;

	for(it = src_client->link.begin(); it != src_client->link.end(); it++)
	{
		if(it->peer_pointer == dst_client)
		{
			res_src = IPACM_SUCCESS;
			IPACMDBG_H("Find dst client entry in src link list\n");
			res_src = del_offload_link(iptype, src_client->p_iface, dst_client->p_iface, &(*it));
			src_client->link.erase(it);
			break;
		}
	}

	for(it = dst_client->link.begin(); it != dst_client->link.end(); it++)
	{
		if(it->peer_pointer == src_client)
		{
			res_dst = IPACM_SUCCESS;
			IPACMDBG_H("Find src client entry in dst link list\n");
			res_dst = del_offload_link(iptype, dst_client->p_iface, src_client->p_iface, &(*it));
			dst_client->link.erase(it);
			break;
		}
	}

	if(res_src == IPACM_SUCCESS && res_dst == IPACM_SUCCESS)
	{
		if(iptype == IPA_IP_v4)
		{
			num_offload_pair_v4_ --;
			IPACMDBG_H("Decrease num of v4 offload pairs to %d\n", num_offload_pair_v4_);
		}
		else
		{
			num_offload_pair_v6_ --;
			IPACMDBG_H("Decrease num of v6 offload pairs to %d\n", num_offload_pair_v6_);
		}
	}
	return;
}

void IPACM_LanToLan::generate_new_connection(ipa_ip_type iptype, client_info* client)
{
#ifndef CT_OPT
	if(client == NULL)
	{
		IPACMERR("Client is NULL.\n");
		return;
	}

	IPACMDBG_H("Generate new connection events for IP type %d\n", iptype);

	int num = 0;
	ipacm_cmd_q_data evt;
	ipacm_event_connection* new_conn;
	ipacm_iface_type client_type, peer_type;
	client_type = IPACM_Iface::ipacmcfg->iface_table[client->p_iface->ipa_if_num].if_cat;

	IPACMDBG_H("Client's iface type is %d.\n", client_type);

	if(iptype == IPA_IP_v4)
	{
		client_table_v4::iterator it;
		for(it = client_info_v4_.begin(); it != client_info_v4_.end(); it++)
		{
			peer_type = IPACM_Iface::ipacmcfg->iface_table[it->second.p_iface->ipa_if_num].if_cat;
			if(peer_type != client_type && it->second.is_active == true)
			{
				IPACMDBG_H("Find a qualified peer to generate new_conn event.\n");
				IPACMDBG_H("Peer's iface type is %d.\n", peer_type);
				new_conn = (ipacm_event_connection*)malloc(sizeof(ipacm_event_connection));
				if(new_conn == NULL)
				{
					IPACMERR("Failed to allocate memory for new_connection event.\n");
					return;
				}
				memset(new_conn, 0, sizeof(ipacm_event_connection));
				new_conn->iptype = IPA_IP_v4;
				new_conn->src_ipv4_addr = client->ip.ipv4_addr;
				new_conn->dst_ipv4_addr = it->second.ip.ipv4_addr;

				memset(&evt, 0, sizeof(evt));
				evt.event = IPA_LAN_TO_LAN_NEW_CONNECTION;
				evt.evt_data = (void*)new_conn;
				IPACM_EvtDispatcher::PostEvt(&evt);
				num++;
			}
		}
	}
	else if(iptype == IPA_IP_v6)
	{
		client_table_v6::iterator it;
		for(it = client_info_v6_.begin(); it != client_info_v6_.end(); it++)
		{
			peer_type = IPACM_Iface::ipacmcfg->iface_table[it->second.p_iface->ipa_if_num].if_cat;
			if(peer_type != client_type && it->second.is_active == true)
			{
				IPACMDBG_H("Find a qualified peer to generate new_conn event.\n");
				IPACMDBG_H("Peer's iface type is %d.\n", peer_type);
				new_conn = (ipacm_event_connection*)malloc(sizeof(ipacm_event_connection));
				if(new_conn == NULL)
				{
					IPACMERR("Failed to allocate memory for new_connection event.\n");
					return;
				}
				memset(new_conn, 0, sizeof(ipacm_event_connection));
				new_conn->iptype = IPA_IP_v6;
				memcpy(new_conn->src_ipv6_addr, client->ip.ipv6_addr, sizeof(new_conn->src_ipv6_addr));
				memcpy(new_conn->dst_ipv6_addr, it->second.ip.ipv6_addr, sizeof(new_conn->dst_ipv6_addr));

				memset(&evt, 0, sizeof(evt));
				evt.event = IPA_LAN_TO_LAN_NEW_CONNECTION;
				evt.evt_data = (void*)new_conn;
				IPACM_EvtDispatcher::PostEvt(&evt);
				num++;
			}
		}
	}
	else
	{
		IPACMERR("IP type is not expected.\n");
	}
	IPACMDBG_H("Generate %d new connection events in total.\n", num);
#endif
	return;
}

void IPACM_LanToLan::handle_client_power_recover(ipacm_event_lan_client* data)
{
	if(data == NULL)
	{
		IPACMERR("No client info is found.\n");
		return;
	}
	if(data->mac_addr == NULL || data->ipv6_addr == NULL || data->p_iface == NULL)
	{
		IPACMERR("Event data is not populated properly.\n");
		return;
	}
	if(data->iptype != IPA_IP_v4 && data->iptype != IPA_IP_v6)
	{
		IPACMERR("IP type is not expected: %d\n", data->iptype);
		return;
	}

	IPACMDBG_H("New client info: iface %s, iptype: %d, mac: 0x%02x%02x%02x%02x%02x%02x, v4_addr: 0x%08x, v6_addr: 0x%08x%08x%08x%08x \n",
		data->p_iface->dev_name, data->iptype,
		data->mac_addr[0], data->mac_addr[1], data->mac_addr[2], data->mac_addr[3], data->mac_addr[4], data->mac_addr[5],
		data->ipv4_addr, data->ipv6_addr[0], data->ipv6_addr[1], data->ipv6_addr[2], data->ipv6_addr[3]);

	client_info* client_ptr;
	if(data->iptype == IPA_IP_v4)
	{
		if(client_info_v4_.count(data->ipv4_addr) == 0)
		{
			IPACMERR("Client is not found.\n");
			return;
		}
		client_info& client = client_info_v4_[data->ipv4_addr];
		client_ptr = &client;
	}
	else
	{
		uint64_t v6_addr;
		memcpy(&v6_addr, &(data->ipv6_addr[2]), sizeof(uint64_t));
		if(client_info_v6_.count(v6_addr) == 0)
		{
			IPACMERR("Client is not found.\n");
			return;
		}
		client_info& client = client_info_v6_[v6_addr];
		client_ptr = &client;
	}

	if(client_ptr->is_active == true || client_ptr->is_powersave != true)	//the client is in wrong state
	{
		IPACMERR("The client is in wrong state: active %d, powersave %d.\n", client_ptr->is_active, client_ptr->is_powersave);
		return;
	}
	else
	{
		if(add_flt_rules(data->iptype, client_ptr) == IPACM_FAILURE)
		{
			IPACMERR("Failed to add back flt rules when power recovery.\n");
			return;
		}
		client_ptr->is_active =  true;
		client_ptr->is_powersave = false;

		check_potential_link(data->iptype, client_ptr);
		generate_new_connection(data->iptype, client_ptr);
	}
	IPACMDBG_H("There are %d clients in v4 table and %d clients in v6 table.\n", client_info_v4_.size(), client_info_v6_.size());
	return;
}

//This function is called when power save: remove filtering rules only
int IPACM_LanToLan::remove_flt_rules(ipa_ip_type iptype, client_info* client)
{
	if(client == NULL)
	{
		IPACMERR("No client info is found.\n");
		return IPACM_FAILURE;
	}

	bool err_flag;
	offload_link_info_list::iterator client_it;
	offload_link_info_list::iterator peer_it;
	client_info* peer;

	for(client_it = client->link.begin(); client_it != client->link.end(); client_it++)
	{
		if(client->p_iface->del_lan2lan_flt_rule(iptype, client_it->flt_rule_hdl) == IPACM_FAILURE)
		{
			IPACMERR("Failed to delete client's filtering rule.\n");
		}

		err_flag = true;
		peer = client_it->peer_pointer;
		for(peer_it = peer->link.begin(); peer_it != peer->link.end(); peer_it++)
		{
			if(peer_it->peer_pointer == client)
			{
				if(peer->p_iface->del_lan2lan_flt_rule(iptype, peer_it->flt_rule_hdl) == IPACM_FAILURE)
				{
					IPACMERR("Failed to delete peer's offload link.\n");
				}
				err_flag = false;
				break;
			}
		}
		if(err_flag)
		{
			IPACMERR("Unable to find corresponding offload link in peer's entry.\n");
			return IPACM_FAILURE;
		}
	}
	return IPACM_SUCCESS;
}

int IPACM_LanToLan::add_flt_rules(ipa_ip_type iptype, client_info* client)
{
	if(client == NULL)
	{
		IPACMERR("No client info is found.\n");
		return IPACM_FAILURE;
	}

	bool err_flag;
	offload_link_info_list::iterator client_it;
	offload_link_info_list::iterator peer_it;
	client_info* peer;

	for(client_it = client->link.begin(); client_it != client->link.end(); client_it++)
	{
		peer = client_it->peer_pointer;
		if(client->p_iface->add_lan2lan_flt_rule(iptype, client->ip.ipv4_addr, peer->ip.ipv4_addr,
			client->ip.ipv6_addr, peer->ip.ipv6_addr, &(client_it->flt_rule_hdl)) == IPACM_FAILURE)
		{
			IPACMERR("Failed to add client's filtering rule.\n");
			return IPACM_FAILURE;
		}

		err_flag = true;
		for(peer_it = peer->link.begin(); peer_it != peer->link.end(); peer_it++)
		{
			if(peer_it->peer_pointer == client)
			{
				if(peer->p_iface->add_lan2lan_flt_rule(iptype, peer->ip.ipv4_addr, client->ip.ipv4_addr,
					peer->ip.ipv6_addr, client->ip.ipv6_addr, &(peer_it->flt_rule_hdl)) == IPACM_FAILURE)
				{
					IPACMERR("Failed to delete peer's offload link.\n");
					return IPACM_FAILURE;
				}
				err_flag = false;
				break;
			}
		}
		if(err_flag)
		{
			IPACMERR("Unable to find corresponding offload link in peer's entry.\n");
			return IPACM_FAILURE;
		}
	}
	return IPACM_SUCCESS;
}

void IPACM_LanToLan::handle_new_connection(ipacm_event_connection* new_conn)
{
#ifdef CT_OPT
	if(new_conn == NULL)
	{
		IPACMERR("No connection info is found.\n");
		return;
	}
	if(new_conn->iptype != IPA_IP_v4 && new_conn->iptype != IPA_IP_v6)
	{
		IPACMERR("IP type is not expected: %d.\n", new_conn->iptype);
		return;
	}

	IPACMDBG_H("New connection info: IP type: %d, src_v4_addr: 0x%08x, dst_v4_addr: 0x%08x\n", new_conn->iptype, new_conn->src_ipv4_addr, new_conn->dst_ipv4_addr);
	IPACMDBG_H("src_v6_addr: 0x%08x%08x%08x%08x, dst_v6_addr: 0x%08x%08x%08x%08x", new_conn->src_ipv6_addr[0], new_conn->src_ipv6_addr[1], new_conn->src_ipv6_addr[2],
				new_conn->src_ipv6_addr[3], new_conn->dst_ipv6_addr[0], new_conn->dst_ipv6_addr[1], new_conn->dst_ipv6_addr[2], new_conn->dst_ipv6_addr[3]);

	if(is_lan2lan_connection(new_conn) == false)
	{
		IPACMDBG_H("The connection is not lan2lan connection.\n");
		cache_new_connection(new_conn);
		return;
	}

	ipacm_cmd_q_data evt;
	ipacm_event_connection* conn;

	conn = (ipacm_event_connection*)malloc(sizeof(ipacm_event_connection));
	if(conn == NULL)
	{
		IPACMERR("Failed to allocate memory for new_connection event.\n");
		return;
	}
	memcpy(conn, new_conn, sizeof(ipacm_event_connection));

	memset(&evt, 0, sizeof(evt));
	evt.event = IPA_LAN_TO_LAN_NEW_CONNECTION;
	evt.evt_data = (void*)conn;
	IPACM_EvtDispatcher::PostEvt(&evt);
#endif
	return;
}

void IPACM_LanToLan::handle_del_connection(ipacm_event_connection* new_conn)
{
#ifdef CT_OPT
	if(new_conn == NULL)
	{
		IPACMERR("No connection info is found.\n");
		return;
	}
	if(new_conn->iptype != IPA_IP_v4 && new_conn->iptype != IPA_IP_v6)
	{
		IPACMERR("IP type is not expected: %d.\n", new_conn->iptype);
		return;
	}

	IPACMDBG_H("Del connection info: IP type: %d, src_v4_addr: 0x%08x, dst_v4_addr: 0x%08x\n", new_conn->iptype, new_conn->src_ipv4_addr, new_conn->dst_ipv4_addr);
	IPACMDBG_H("src_v6_addr: 0x%08x%08x%08x%08x, dst_v6_addr: 0x%08x%08x%08x%08x", new_conn->src_ipv6_addr[0], new_conn->src_ipv6_addr[1], new_conn->src_ipv6_addr[2],
				new_conn->src_ipv6_addr[3], new_conn->dst_ipv6_addr[0], new_conn->dst_ipv6_addr[1], new_conn->dst_ipv6_addr[2], new_conn->dst_ipv6_addr[3]);

	if(is_lan2lan_connection(new_conn) == false)
	{
		IPACMDBG_H("The connection is not lan2lan connection.\n");
		remove_cache_connection(new_conn);
		return;
	}

	ipacm_cmd_q_data evt;
	ipacm_event_connection* conn;

	conn = (ipacm_event_connection*)malloc(sizeof(ipacm_event_connection));
	if(conn == NULL)
	{
		IPACMERR("Failed to allocate memory for del_connection event.\n");
		return;
	}
	memcpy(conn, new_conn, sizeof(ipacm_event_connection));

	memset(&evt, 0, sizeof(evt));
	evt.event = IPA_LAN_TO_LAN_DEL_CONNECTION;
	evt.evt_data = (void*)conn;
	IPACM_EvtDispatcher::PostEvt(&evt);
#endif
	return;
}

bool IPACM_LanToLan::is_lan2lan_connection(ipacm_event_connection* data)
{
	if(data->iptype == IPA_IP_v4)
	{
		if(client_info_v4_.count(data->src_ipv4_addr) == 0 || client_info_v4_.count(data->dst_ipv4_addr) == 0)
		{
			IPACMDBG("Either source or destination is not in client table\n");
			return false;
		}

		ipacm_iface_type src_type, dst_type;
		src_type = IPACM_Iface::ipacmcfg->iface_table[client_info_v4_[data->src_ipv4_addr].p_iface->ipa_if_num].if_cat;
		dst_type = IPACM_Iface::ipacmcfg->iface_table[client_info_v4_[data->dst_ipv4_addr].p_iface->ipa_if_num].if_cat;

		return (src_type != dst_type);
	}
	else
	{
		uint64_t src_v6_addr, dst_v6_addr;
		memcpy(&src_v6_addr, &(data->src_ipv6_addr[2]), sizeof(uint64_t));
		memcpy(&dst_v6_addr, &(data->dst_ipv6_addr[2]), sizeof(uint64_t));

		if(client_info_v6_.count(src_v6_addr) == 0 || client_info_v6_.count(dst_v6_addr) == 0)
		{
			IPACMDBG("Either source or destination is not in client table\n");
			return false;
		}

		ipacm_iface_type src_type, dst_type;
		src_type = IPACM_Iface::ipacmcfg->iface_table[client_info_v6_[src_v6_addr].p_iface->ipa_if_num].if_cat;
		dst_type = IPACM_Iface::ipacmcfg->iface_table[client_info_v6_[dst_v6_addr].p_iface->ipa_if_num].if_cat;

		return (src_type != dst_type);
	}
}

IPACM_LanToLan* IPACM_LanToLan::getLan2LanInstance()
{
	return p_instance;
}

bool IPACM_LanToLan::is_potential_lan2lan_connection(ipacm_event_connection* new_conn)
{
	int i, num_private_subnet;
	bool src_is_valid = false;
	bool dst_is_valid = false;

	if(new_conn->iptype == IPA_IP_v4)
	{
		num_private_subnet = IPACM_Iface::ipacmcfg->ipa_num_private_subnet;
		for(i=0; i<num_private_subnet; i++)
		{
			if( (new_conn->src_ipv4_addr & IPACM_Iface::ipacmcfg->private_subnet_table[i].subnet_mask)
				== (IPACM_Iface::ipacmcfg->private_subnet_table[i].subnet_addr & IPACM_Iface::ipacmcfg->private_subnet_table[i].subnet_mask) )
			{
				src_is_valid = true;
			}
			if( (new_conn->dst_ipv4_addr & IPACM_Iface::ipacmcfg->private_subnet_table[i].subnet_mask)
				== (IPACM_Iface::ipacmcfg->private_subnet_table[i].subnet_addr & IPACM_Iface::ipacmcfg->private_subnet_table[i].subnet_mask) )
			{
				dst_is_valid = true;
			}
		}

		if(src_is_valid && dst_is_valid)
		{
			IPACMDBG("Both src and dst are potentially in subnet.\n");
			return true;
		}
	}
	else
	{
		if( (new_conn->src_ipv6_addr[0] & ipv6_multicast_mask) != (ipv6_multicast_addr & ipv6_multicast_mask) )
		{
			src_is_valid = true;
		}
		if( (new_conn->dst_ipv6_addr[0] & ipv6_multicast_mask) != (ipv6_multicast_addr & ipv6_multicast_mask) )
		{
			dst_is_valid = true;
		}

		if(src_is_valid && dst_is_valid)
		{
			IPACMDBG("Both src and dst are potentially in subnet.\n");
			return true;
		}
	}

	IPACMDBG("This connection is not a lan2lan connection potentially.\n");
	return false;
}

void IPACM_LanToLan::cache_new_connection(ipacm_event_connection* new_conn)
{
	if(is_potential_lan2lan_connection(new_conn) == true)
	{
		if(new_conn->iptype == IPA_IP_v4)
		{
			if(connection_v4_.size() == max_cache_connection)
			{
				IPACMDBG_H("Cached ipv4 connections already reach maximum, clear up the list.\n");
				connection_v4_.clear();
			}

			connection_v4_.push_back(*new_conn);
			IPACMDBG_H("Cache an ipv4 connection, now the number of ipv4 cache connection is %d.\n", connection_v4_.size());
		}
		else
		{
			if(connection_v6_.size() == max_cache_connection)
			{
				IPACMDBG_H("Cached ipv6 connections already reach maximum, clear up the list.\n");
				connection_v6_.clear();
			}

			connection_v6_.push_back(*new_conn);
			IPACMDBG_H("Cache an ipv6 connection, now the number of ipv6 cache connection is %d.\n", connection_v6_.size());
		}
	}
	return;
}

void IPACM_LanToLan::remove_cache_connection(ipacm_event_connection* del_conn)
{
	connection_list::iterator it;
	if(is_potential_lan2lan_connection(del_conn) == true)
	{
		if(del_conn->iptype == IPA_IP_v4)
		{
			for(it = connection_v4_.begin(); it != connection_v4_.end(); it++)
			{
				if(it->src_ipv4_addr == del_conn->src_ipv4_addr && it->dst_ipv4_addr == del_conn->dst_ipv4_addr)
				{
					IPACMDBG("Find the cached ipv4 connection, remove it from list.\n");
					connection_v4_.erase(it);
					IPACMDBG_H("Now the number of ipv4 cache connection is %d.\n", connection_v4_.size());
					return;
				}
			}
			IPACMDBG_H("Do not find the cached ipv4 connection, do nothing.\n");
		}
		else
		{
			for(it = connection_v6_.begin(); it != connection_v6_.end(); it++)
			{
				if(memcmp(it->src_ipv6_addr, del_conn->src_ipv6_addr, 4*sizeof(uint32_t)) == 0
					&& memcmp(it->dst_ipv6_addr, del_conn->dst_ipv6_addr, 4*sizeof(uint32_t)) == 0 )
				{
					IPACMDBG("Find the cached ipv6 connection, remove it from list.\n");
					connection_v6_.erase(it);
					IPACMDBG_H("Now the number of ipv6 cache connection is %d.\n", connection_v6_.size());
					return;
				}
			}
			IPACMDBG_H("Do not find the cached ipv6 connection, do nothing.\n");
		}
	}
	return;
}

void IPACM_LanToLan::check_cache_connection(ipa_ip_type iptype, client_info* client)
{
#ifdef CT_OPT
	connection_list::iterator it;
	if(iptype == IPA_IP_v4)
	{
		it = connection_v4_.begin();
		while(it != connection_v4_.end())
		{
			if( (it->src_ipv4_addr == client->ip.ipv4_addr && client_info_v4_.count(it->dst_ipv4_addr) > 0)
				|| (it->dst_ipv4_addr == client->ip.ipv4_addr && client_info_v4_.count(it->src_ipv4_addr) > 0) )
			{
				IPACMDBG("Found a cache connection for src client 0x%08x and dst client 0x%08x.\n", it->src_ipv4_addr, it->dst_ipv4_addr);
				ipacm_cmd_q_data evt;
				ipacm_event_connection* conn;

				conn = (ipacm_event_connection*)malloc(sizeof(ipacm_event_connection));
				if(conn == NULL)
				{
					IPACMERR("Failed to allocate memory for new_connection event.\n");
					return;
				}
				memcpy(conn, &(*it), sizeof(ipacm_event_connection));

				memset(&evt, 0, sizeof(evt));
				evt.event = IPA_LAN_TO_LAN_NEW_CONNECTION;
				evt.evt_data = (void*)conn;
				IPACM_EvtDispatcher::PostEvt(&evt);

				it = connection_v4_.erase(it);
				IPACMDBG_H("Now the number of cache connections is %d.\n", connection_v4_.size());
			}
			else
			{
				it++;
			}
		}
	}
	else
	{
		uint64_t src_v6_addr, dst_v6_addr;
		it = connection_v6_.begin();
		while(it != connection_v6_.end())
		{
			memcpy(&src_v6_addr, &(it->src_ipv6_addr[2]), sizeof(uint64_t));
			memcpy(&dst_v6_addr, &(it->dst_ipv6_addr[2]), sizeof(uint64_t));
			if( (memcmp(it->src_ipv6_addr, client->ip.ipv6_addr, 4*sizeof(uint32_t)) == 0 && client_info_v6_.count(dst_v6_addr) > 0)
				|| (memcmp(it->dst_ipv6_addr, client->ip.ipv6_addr, 4*sizeof(uint32_t)) == 0 && client_info_v6_.count(src_v6_addr) > 0) )
			{
				IPACMDBG("Found a cache connection with src client 0x%08x%08x%08x%08x and dst client 0x%08x%08x%08x%08x.\n", it->src_ipv6_addr[0],
							it->src_ipv6_addr[1], it->src_ipv6_addr[2], it->src_ipv6_addr[3], it->dst_ipv6_addr[0], it->dst_ipv6_addr[1],
							it->dst_ipv6_addr[2], it->dst_ipv6_addr[3]);
				ipacm_cmd_q_data evt;
				ipacm_event_connection* conn;

				conn = (ipacm_event_connection*)malloc(sizeof(ipacm_event_connection));
				if(conn == NULL)
				{
					IPACMERR("Failed to allocate memory for new_connection event.\n");
					return;
				}
				memcpy(conn, &(*it), sizeof(ipacm_event_connection));

				memset(&evt, 0, sizeof(evt));
				evt.event = IPA_LAN_TO_LAN_NEW_CONNECTION;
				evt.evt_data = (void*)conn;
				IPACM_EvtDispatcher::PostEvt(&evt);

				it = connection_v6_.erase(it);
				IPACMDBG_H("Now the number of cache connections is %d.\n", connection_v6_.size());
			}
			else
			{
				it++;
			}
		}
	}
#endif
<<<<<<< HEAD
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
=======
>>>>>>> 410177e... s2: add data-ipa-cfg-mgr
	return;
}

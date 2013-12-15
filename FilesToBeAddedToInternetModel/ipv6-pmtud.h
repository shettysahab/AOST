/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef IPV6_PMTU_Discovery_H
#define IPV6_PMTU_Discovery_H

#include <map>

#include "ns3/object.h"
#include "ns3/nstime.h"
#include "ns3/type-id.h"
#include "ns3/event-id.h"
#include "ns3/ipv6-address.h"

namespace ns3 {


class Ipv6PmtuDiscovery : public Object
{
public:

  static TypeId GetTypeId ();

  Ipv6PmtuDiscovery ();

  ~Ipv6PmtuDiscovery ();

  uint32_t GetPmtu (Ipv6Address dest);

  void SetPmtu (Ipv6Address dest, uint32_t pmtu);

  Time GetPmtuExpiryTime () const;

  bool SetPmtuExpiryTime (Time expiry);

private:

  void RemovePmtu (Ipv6Address dest);

  std::map<Ipv6Address, uint32_t> m_pathMtu;

  std::map<Ipv6Address, EventId> m_pathMtuTimer;

  Time m_expiryTime;
};

}

#endif /* IPV6_PMTU_Discovery_H */

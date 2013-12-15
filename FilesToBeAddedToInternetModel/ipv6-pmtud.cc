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

#include "ipv6-pmtud.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

NS_LOG_COMPONENT_DEFINE ("Ipv6PmtuDiscovery");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (Ipv6PmtuDiscovery);

TypeId Ipv6PmtuDiscovery::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::Ipv6PmtuDiscovery")
    .SetParent<Object> ()
    .AddAttribute ("ExpiryTime",
                   "Expiry time for a Path MTU entry.",
                   TimeValue (Seconds (60 * 10)),
                   MakeTimeAccessor (&Ipv6PmtuDiscovery::m_expiryTime),
                   MakeTimeChecker (Time (Seconds (60 * 5))))
  ;
  return tid;
}

Ipv6PmtuDiscovery::Ipv6PmtuDiscovery ()
{
}

Ipv6PmtuDiscovery::~Ipv6PmtuDiscovery ()
{
}


uint32_t Ipv6PmtuDiscovery::GetPmtu (Ipv6Address dest)
{
  NS_LOG_FUNCTION (this << dest);

  if (m_pathMtu.find (dest) != m_pathMtu.end ())
    {
      return m_pathMtu[dest];
    }
  return 0;
}

void Ipv6PmtuDiscovery::SetPmtu (Ipv6Address dest, uint32_t pmtu)
{
  NS_LOG_FUNCTION (this << dest << pmtu);

  m_pathMtu[dest] = pmtu;
  if (m_pathMtuTimer.find (dest) != m_pathMtuTimer.end ())
    {
      m_pathMtuTimer[dest].Cancel ();
    }
  EventId pMtuTimer;
  pMtuTimer = Simulator::Schedule (m_expiryTime, &Ipv6PmtuDiscovery::RemovePmtu, this, dest);
  m_pathMtuTimer[dest] = pMtuTimer;
}

Time Ipv6PmtuDiscovery::GetPmtuExpiryTime () const
{
  NS_LOG_FUNCTION (this);
  return m_expiryTime;
}

bool Ipv6PmtuDiscovery::SetPmtuExpiryTime (Time expiry)
{
  NS_LOG_FUNCTION (this << expiry);

  if (expiry > Seconds (60 * 5))
    {
      m_expiryTime = expiry;
      return true;
    }

  NS_LOG_LOGIC ("PMTU expiry timer lesser than 5 minutes");
  return false;
}

void Ipv6PmtuDiscovery::RemovePmtu (Ipv6Address dest)
{
  NS_LOG_FUNCTION (this << dest);

  m_pathMtu.erase (dest);
  m_pathMtuTimer.erase (dest);
}

}


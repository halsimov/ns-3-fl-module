/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
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
 * Authors: Emily Ekaireb <eekaireb@ucsd.edu>
 */

#include "ns3/log.h"
#include "performance-model.h"

NS_LOG_COMPONENT_DEFINE ("PerformanceModel");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (PerformanceModel);

TypeId
PerformanceModel::GetTypeId ()
{
  static TypeId tid = TypeId("ns3::PerformanceModel")
    .SetParent<Object>()
    .SetGroupName("Performance")
  ; 
  return tid;
}

PerformanceModel::PerformanceModel ()
{
  NS_LOG_FUNCTION (this);
}

PerformanceModel::~PerformanceModel ()
{
  NS_LOG_FUNCTION (this);
}

double
PerformanceModel::GetExecTime () const
{
  NS_LOG_FUNCTION (this);
  return 0.0;
}

double
PerformanceModel::GetThroughput () const
{
  NS_LOG_FUNCTION (this);
  return 0.0;
}

double
PerformanceModel::GetPacketSize () const
{
  NS_LOG_FUNCTION (this);
  return 0.0;
}
double
PerformanceModel::GetDataSize () const
{
  NS_LOG_FUNCTION (this);
  return 0.0;
}

void
PerformanceModel::DoDispose ()
{
  NS_LOG_FUNCTION (this);
}


} // namespace ns3

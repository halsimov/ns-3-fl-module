/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Authors: Emily Ekaireb <eekaireb@ucsd.edu>
 */

#include "reliability-helper.h"
#include <ns3/log.h>
#include "ns3/names.h"
#include <vector>


namespace ns3 {


NS_LOG_COMPONENT_DEFINE ("ReliabilityHelper");

ReliabilityHelper::ReliabilityHelper ()
{
  m_power.SetTypeId("ns3::AppPowerModel");
  m_performance.SetTypeId("ns3::PerformanceSimpleModel");
  m_temperature.SetTypeId("ns3::TemperatureModel");
  m_reliability.SetTypeId("ns3::ReliabilityTDDBModel");
  m_Tenv = 25.0;
}

ReliabilityHelper::~ReliabilityHelper () {}
 
void 
ReliabilityHelper::SetPowerModel (
  std::string type,
  std::string n1, const AttributeValue &v1,
  std::string n2, const AttributeValue &v2,
  std::string n3, const AttributeValue &v3,
  std::string n4, const AttributeValue &v4,
  std::string n5, const AttributeValue &v5,
  std::string n6, const AttributeValue &v6,
  std::string n7, const AttributeValue &v7,
  std::string n8, const AttributeValue &v8,
  std::string n9, const AttributeValue &v9
)
{
  m_power.SetTypeId(type);
  m_power.Set(n1, v1);
  m_power.Set(n2, v2);
  m_power.Set(n3, v3);
  m_power.Set(n4, v4);
  m_power.Set(n5, v5);
  m_power.Set(n6, v6);
  m_power.Set(n7, v7);
  m_power.Set(n8, v8);
  m_power.Set(n9, v9);
}

void 
ReliabilityHelper::SetPerformanceModel (
  std::string type,
  std::string n1, const AttributeValue &v1,
  std::string n2, const AttributeValue &v2,
  std::string n3, const AttributeValue &v3,
  std::string n4, const AttributeValue &v4,
  std::string n5, const AttributeValue &v5,
  std::string n6, const AttributeValue &v6,
  std::string n7, const AttributeValue &v7,
  std::string n8, const AttributeValue &v8,
  std::string n9, const AttributeValue &v9
)
{
  m_performance.SetTypeId(type);
  m_performance.Set(n1, v1);
  m_performance.Set(n2, v2);
  m_performance.Set(n3, v3);
  m_performance.Set(n4, v4);
  m_performance.Set(n5, v5);
  m_performance.Set(n6, v6);
  m_performance.Set(n7, v7);
  m_performance.Set(n8, v8);
  m_performance.Set(n9, v9);
}

void 
ReliabilityHelper::SetTemperatureModel (
  std::string type,
  std::string n1, const AttributeValue &v1,
  std::string n2, const AttributeValue &v2,
  std::string n3, const AttributeValue &v3,
  std::string n4, const AttributeValue &v4,
  std::string n5, const AttributeValue &v5,
  std::string n6, const AttributeValue &v6,
  std::string n7, const AttributeValue &v7,
  std::string n8, const AttributeValue &v8,
  std::string n9, const AttributeValue &v9
)
{
  m_temperature.SetTypeId(type);
  m_temperature.Set(n1, v1);
  m_temperature.Set(n2, v2);
  m_temperature.Set(n3, v3);
  m_temperature.Set(n4, v4);
  m_temperature.Set(n5, v5);
  m_temperature.Set(n6, v6);
  m_temperature.Set(n7, v7);
  m_temperature.Set(n8, v8);
  m_temperature.Set(n9, v9);
}

void 
ReliabilityHelper::SetReliabilityModel (
  std::string type,
  std::string n1, const AttributeValue &v1,
  std::string n2, const AttributeValue &v2,
  std::string n3, const AttributeValue &v3,
  std::string n4, const AttributeValue &v4,
  std::string n5, const AttributeValue &v5,
  std::string n6, const AttributeValue &v6,
  std::string n7, const AttributeValue &v7,
  std::string n8, const AttributeValue &v8,
  std::string n9, const AttributeValue &v9
)
{
  m_reliability.SetTypeId(type);
  m_reliability.Set(n1, v1);
  m_reliability.Set(n2, v2);
  m_reliability.Set(n3, v3);
  m_reliability.Set(n4, v4);
  m_reliability.Set(n5, v5);
  m_reliability.Set(n6, v6);
  m_reliability.Set(n7, v7);
  m_reliability.Set(n8, v8);
  m_reliability.Set(n9, v9);
}

void
ReliabilityHelper::SetApplication (std::string n0, const DoubleValue &v0,const DoubleValue &v1)
{
  m_appName = n0;
  m_dataSize = v0.Get();
  m_packetSize = v1.Get();

  if (m_dataSize<m_packetSize)
  {
      NS_FATAL_ERROR ("Application input data size must be greater than packet size:");
  }
}

void
ReliabilityHelper::SetDeviceType (std::string deviceType)
{
  m_deviceType = deviceType;
}

void
ReliabilityHelper::SetAmbientTemperature (double Tenv)
{
  m_Tenv = Tenv;
}

void
ReliabilityHelper::Install (Ptr<Node> node)
{
  Ptr<Object> object = node;

  Ptr<PowerModel> powerModel = object->GetObject<PowerModel>();
  if (!powerModel)
  {
      powerModel = m_power.Create()->GetObject<PowerModel>();
    if (!powerModel)
    {
      NS_FATAL_ERROR (
        "The requested power model is not a valid power model: \"" << 
        m_power.GetTypeId().GetName() << "\""
        );
    }
    NS_LOG_DEBUG ("node="<<object<<", mob="<< powerModel);
    object->AggregateObject(powerModel);
  }

  Ptr<PerformanceModel> performanceModel = object->GetObject<PerformanceModel>();
  if (!performanceModel)
  {
    performanceModel = m_performance.Create()->GetObject<PerformanceModel>();
    if (!performanceModel)
    {
      NS_FATAL_ERROR (
        "The requested power model is not a valid performance model: \"" << 
        m_performance.GetTypeId().GetName() << "\""
      );
    }
    NS_LOG_DEBUG ("node=" << object << ", mob=" << performanceModel);
    object->AggregateObject(performanceModel);
  }

  Ptr<TemperatureModel> temperatureModel = object->GetObject<TemperatureModel>();
  if (!temperatureModel)
  {
    temperatureModel = m_temperature.Create()->GetObject<TemperatureModel>();
    if (!temperatureModel)
    {
      NS_FATAL_ERROR (
        "The requested power model is not a valid temperature model: \"" << 
        m_temperature.GetTypeId().GetName() << "\""
      );
    }
    NS_LOG_DEBUG ("node=" << object << ", mob=" << temperatureModel);
    object->AggregateObject(temperatureModel);
  }

  Ptr<ReliabilityModel> reliabilityModel = object->GetObject<ReliabilityModel>();
  if (!reliabilityModel)
  {
    reliabilityModel = m_reliability.Create()->GetObject<ReliabilityModel>();
    if (!reliabilityModel)
    {
      NS_FATAL_ERROR (
        "The requested power model is not a valid reliability model: \"" << 
        m_reliability.GetTypeId().GetName() << "\""
      );
    }
    NS_LOG_DEBUG ("node=" << object << ", mob=" << reliabilityModel);
    object->AggregateObject(reliabilityModel);
  }

  temperatureModel->SetTenv(m_Tenv);
    reliabilityModel->RegisterTemperatureModel(temperatureModel);
    powerModel->RegisterPerformanceModel(performanceModel);
    powerModel->RegisterTemperatureModel (temperatureModel);
    powerModel->SetDeviceType(m_deviceType);
    temperatureModel->SetDeviceType(m_deviceType);
    powerModel->SetApplication(m_appName,m_dataSize);
    performanceModel->SetPacketSize(m_packetSize);
    // powerModel->SetAppName(m_appName);
    // powerModel->SetDataSize(m_dataSize);
}

void 
ReliabilityHelper::Install (NodeContainer c)
{
  for (NodeContainer::Iterator i = c.Begin(); i != c.End(); ++i)
  {
    Install(*i);
  }
}

} // namespace ns3

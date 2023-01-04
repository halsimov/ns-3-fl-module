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

#ifndef PERFORMANCE_SIMPLE_MODEL_H
#define PERFORMANCE_SIMPLE_MODEL_H


#include "ns3/nstime.h"
#include "ns3/event-id.h"
#include "ns3/traced-value.h"
#include <ns3/performance-model.h>


namespace ns3 {

class PerformanceSimpleModel : public PerformanceModel
{
public:
  static TypeId GetTypeId ();
  PerformanceSimpleModel () ;
  ~PerformanceSimpleModel () override;

  // Setter & getters

  virtual double GetA () const;
  virtual void SetA (double A);
  virtual double GetB () const;
  virtual void SetB (double B);
  virtual double GetC () const;
  virtual void SetC (double C);
  double GetDataSize () const override;
  void SetDataSize (const DoubleValue &v0) override;

  void SetDeviceType (std::string deviceType) override;
  void SetApplication (std::string m_appName, const DoubleValue &v0) override;
  double GetPacketSize () const override;
  void SetPacketSize (const DoubleValue &v1) override;
  void SetThroughput(double throughput) override;
  
  /**
   * \returns execution time.
   */
  double GetExecTime () const override;

  /**
   * \returns throughput.
   */
  double GetThroughput () const override;

private:
  void DoDispose () override;

private:
  Time m_lastUpdateTime; // time stamp of previous energy update
  double m_A;
  double m_B;
  double m_C;
  double m_dataSize;
  double m_packetSize;
  std::string m_deviceType;
  TracedValue<double> m_execTime;
  double m_throughput;

}; // end class Performance Simple Model

} // namespace ns3

#endif /* PERFORMANCE_SIMPLE_MODEL_H */
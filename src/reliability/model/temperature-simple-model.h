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

#ifndef TEMPERATURE_SIMPLE_MODEL_H
#define TEMPERATURE_SIMPLE_MODEL_H


#include "ns3/nstime.h"
#include "ns3/event-id.h"
#include "ns3/traced-value.h"
#include "ns3/temperature-model.h"


namespace ns3 {


class TemperatureSimpleModel : public TemperatureModel// 
{
public:

  static TypeId GetTypeId ();
  TemperatureSimpleModel ();
  ~TemperatureSimpleModel () override;

  // Setter & getters.

  virtual double GetA () const;
  virtual void SetA (double A);
  virtual double GetB () const;
  virtual void SetB (double B);
  virtual double GetC () const;
  virtual void SetC (double C);
  virtual double GetD () const;
  virtual void SetD (double D);
  virtual double GetTenv () const;
  void SetTenv (double Tenv) override;
  virtual void SetHorizon (Time horizon);
  void SetDeviceType(std::string devicetype) override;

  /**
   * \brief Updates the temperature.
   *
   */
  void UpdateTemperature (double cpuPower) override;

  /**
   * \returns Current state.
   */
  double GetTemperature () const override;

  /**
   * \returns Average.
   */
  double GetAvgTemperature () const override;

private:
  void DoDispose () override;

private:
  TracedValue<double> m_temperatureCPU;
  Time m_lastUpdateTime;          // time stamp of previous temperature update
  double m_Tenv;
  double m_A;
  double m_B;
  double m_C;
  double m_D;
  Time m_avgHorizon;
  double m_avgTemp;
  std::string m_deviceType;

}; // end class TemperatureSimpleModel


} // namespace ns3


#endif /* TEMPERATURE_SIMPLE_MODEL_H */

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

#ifndef POWER_LINEAR_MODEL_H
#define POWER_LINEAR_MODEL_H

#include "ns3/nstime.h"
#include "ns3/event-id.h"
#include "ns3/traced-value.h"
#include "ns3/temperature-model.h"
#include <ns3/performance-model.h>
#include "ns3/power-model.h"


namespace ns3 {

class PowerLinearModel : public PowerModel
{
public:
  static TypeId GetTypeId ();
  PowerLinearModel ();

  ~PowerLinearModel () override;

  /**
   * \param  Pointer to temperature object attached to the device.
   *
   * Registers the Temperature Model to Power Model.
   */
  void RegisterTemperatureModel (Ptr<TemperatureModel> temperatureModel) override;

  /**
   * \param  Pointer to performance object attached to the device.
   *
   * Registers the Performance Model to Power Model.
   */
  void RegisterPerformanceModel (Ptr<PerformanceModel> performanceModel) override;


  void SetDeviceType(std::string deviceType) override;

  /**
   * \brief Sets pointer to EnergySouce installed on node.
   *
   * \param source Pointer to EnergySource installed on node.
   *
   * Implements DeviceEnergyModel::SetEnergySource.
   */
  //virtual void SetEnergySource (Ptr<EnergySource> source);

  // Setter & getters

  virtual double GetA () const;
  virtual void SetA (double A);
  virtual double GetB () const;
  virtual void SetB (double B);
  virtual double GetC () const;
  virtual void SetC (double C);
  virtual double GetFrequency () const;
  virtual void SetFrequency (double frequency);
  virtual double GetUtilization () const;
  virtual void SetUtilization (double utilization); 
  double GetIdlePowerW () const override;
  virtual void SetIdlePowerW (double IdlePowerW);
  int GetState () const override;
  virtual void SetState (int state);
  void SetApplication (std::string n0, const DoubleValue &v0) override;
  
  /**
   * \returns Current power.
   */
  double GetPower () const override;

  /**
   * \returns Total energy to be consumed.
   */
  double GetEnergy () const override;

  /**
   * \brief Updates the power.
   *
   */
  void UpdatePower () override;

  /**
   * Starts the application
   */
  void RunApp () override;

  /**
   * Ends the application
   */
  void TerminateApp () override;


private:
  void DoDispose () override;

  Ptr<TemperatureModel> m_temperatureModel;
  Ptr<PerformanceModel> m_performanceModel;

  // Member variables for current draw in different radio modes.
  double m_A;
  double m_B;
  double m_C;
  double m_energy;
  double m_frequency;
  double m_exectime;
  int m_currentState;
  std::string m_appname;
  double m_datasize;
  double m_util;
  double m_idlePowerW;
  // This variable keeps track of the total energy consumed by this model.
  TracedValue<double> m_cpupower;
  // State variables.
  EventId m_powerUpdateEvent;            // energy update event
  Time m_lastUpdateTime;          // time stamp of previous energy update
  Time m_powerUpdateInterval;            // energy update interval

}; //end class Power Linear Model

} // namespace ns3

#endif /* POWER_LINEAR_MODEL_H */

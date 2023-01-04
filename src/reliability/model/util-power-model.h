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

#ifndef UTIL_POWER_MODEL_H
#define UTIL_POWER_MODEL_H

#include "ns3/nstime.h"
#include "ns3/event-id.h"
#include "ns3/traced-value.h"
#include "ns3/temperature-model.h"
#include <ns3/performance-model.h>
#include "ns3/power-model.h"


namespace ns3 {


class UtilPowerModel : public PowerModel
{
public:
  static TypeId GetTypeId ();
  UtilPowerModel ();

  ~UtilPowerModel () override;

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
  /**
   * \param deviceEnergyModelPtr Pointer to device energy model.
   *
   * This function appends a device energy model to the end of a list of
   * DeviceEnergyModelInfo structs.
   */
  void AppendDeviceEnergyModel (Ptr<DeviceEnergyModel> deviceEnergyModelPtr) override;

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
  void SetApplication(std::string appName, const DoubleValue &v0) override;
  void SetDeviceType(std::string deviceType) override;

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

  /**
   * Handles the application running event. 
   */
  void HandleAppRunEvent ();

  /**
   * Handles the application terminating event.
   */
  void HandleAppTerminateEvent ();
  
private:
  Ptr<TemperatureModel> m_temperatureModel;
  Ptr<PerformanceModel> m_performanceModel;
  /**
   * List of device energy models installed on the same node.
   */
  DeviceEnergyModelContainer m_models;

  // Member variables for current draw in different radio modes.

  double m_A;
  double m_B;
  double m_C;
  double m_energy;
  double m_freq;
  double m_execTime;
  int m_currentState;
  double m_util;
  double m_idlePowerW;
  std::string m_deviceType;
  
  TracedValue<double> m_cpupower; // keeps track of the total energy consumed

  // State variables.

  EventId m_powerUpdateEvent; // energy update event
  Time m_lastUpdateTime;      // time stamp of previous energy update
  Time m_powerUpdateInterval; // energy update interval

};


} // namespace ns3


#endif /* UTIL_POWER_MODEL_H */

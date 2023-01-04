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

#ifndef RELIABILITY_TDDB_MODEL_H
#define RELIABILITY_TDDB_MODEL_H


#include "ns3/nstime.h"
#include "ns3/event-id.h"
#include "ns3/traced-value.h"
#include "ns3/reliability-model.h"
#include "ns3/temperature-model.h"


namespace ns3 {
  

class ReliabilityTDDBModel : public ReliabilityModel
{
public:
  static TypeId GetTypeId ();
  ReliabilityTDDBModel ();
  ~ReliabilityTDDBModel () override;

  /**
   * \param  Pointer to temperature object attached to the device.
   *
   * Registers the Temperature Model to Power Model.
   */
  void RegisterTemperatureModel (Ptr<TemperatureModel> temperatureModel) override;


  // Setter & getters for state power consumption.

  virtual double GetA () const;
  virtual void SetA (double A);
  virtual double GetB () const;
  virtual void SetB (double B);
  virtual double GetArea () const;
  virtual void SetArea (double area);

  /**
   * \returns Current reliability
   */
  double GetReliability () const override;

  // Utility functions
  virtual double g (double u, double v, double t_0, double scale_p, double shape_p) const;
  virtual double pdf_u (double x, double mean, double sigma) const;
  virtual double pdf_v (double v, double offset, double mult, double degrees) const;
  virtual double scale_par (
    double T, double V,
    double offset_a, double mult_a, double tau_a, double tauvolt_a
  ) const;
  virtual double shape_par (
    double T , double V ,
    double mult_b , double tau_b , double offset_b , double multvolt_b
  ) const; 
  virtual double Chi_Square_Density (double x, double n) const;
  virtual double Ln_Gamma_Function (double x) const;
  /**
   * \brief 
   *
   * \param cpupower, temperature.
   *
   * Updates reliability.
   */
  void UpdateReliability () override;

private:
  void DoDispose () override;

private:
  double __m_A;
  double __m_B;
  double __m_area;
  double __voltage;

  //Scale-Shape Constants

  double __offset_a;
  double __mult_a;
  double __tau_a;
  double __tauvolt_a;
  double __mult_b;
  double __tau_b;
  double __offset_b;
  double __multvolt_b;

  //Reliability Parameters

  double __pdf_v_offset;
  double __pdf_v_mult;
  double __pdf_v_degrees;
  double __pdf_u_mean;
  double __pdf_u_sigma;
  double __scale_parameter;
  double __shape_parameter;

  //Double integral domain

  double __u_max;
  double __u_min;
  double __v_max;
  double __v_min;
  double __subdomain_step_u;
  double __subdomain_step_v;
  int __u_num_step;
  int __v_num_step;
  double __subdomain_area;

  double __A;
  int __LI_index;
  double __delta_LI;
  double __t_life;
  double __Rd;

  Ptr<TemperatureModel> m_temperatureModel;

  TracedValue<double> m_reliability; // This variable keeps track of the reliability of this model.
  EventId m_reliabilityUpdateEvent;  // energy update event
  Time m_reliabilityUpdateInterval;  // State variables.
  Time m_lastUpdateTime;             // time stamp of previous energy update

};


} // namespace ns3


#endif /* RELIABILITY_TDDB_MODEL_H */

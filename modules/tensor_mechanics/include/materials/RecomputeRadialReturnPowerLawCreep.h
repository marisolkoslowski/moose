/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef RECOMPUTERADIALRETURNPOWERLAWCREEP_H
#define RECOMPUTERADIALRETURNPOWERLAWCREEP_H

#include "RecomputeRadialReturn.h"
#include "MooseMesh.h"

/**
 * This class uses the Discrete material in a radial return isotropic creep
 * model.  This class is one of the basic
 * radial return constitutive models; more complex constitutive models combine
 * creep and plasticity.
 *
 * This class inherits from RecomputeRadialReturn and must be used
 * in conjunction with ComputeReturnMappingStress.  This class calculates
 * creep based on stress, temperature, and time effects.  This class also
 * computes the creep strain as a stateful material property.
 */

class RecomputeRadialReturnPowerLawCreep : public RecomputeRadialReturn
{
public:
  RecomputeRadialReturnPowerLawCreep(const InputParameters & parameters);

protected:
  virtual void initQpStatefulProperties();
  void resetQpProperties();

  virtual void computeStressInitialize(Real effectiveTrialStress);
  virtual void computeStressFinalize(const RankTwoTensor & plasticStrainIncrement);

  virtual Real computeResidual(Real effectiveTrialStress, Real scalar);
  virtual Real computeDerivative(Real effectiveTrialStress, Real scalar);

  const Real _coefficient;
  const Real _n_exponent;
  const Real _m_exponent;
  const Real _activation_energy;
  const Real _gas_constant;
  const Real _start_time;
  Real _shear_modulus;
  Real _exponential;
  Real _exp_time;
  const bool _has_temp;

  const VariableValue & _temperature;
  MaterialProperty<RankTwoTensor> & _creep_strain;
  MaterialProperty<RankTwoTensor> & _creep_strain_old;
};

template<>
InputParameters validParams<RecomputeRadialReturnPowerLawCreep>();

#endif //RECOMPUTERADIALRETURNPOWERLAWCREEP_H

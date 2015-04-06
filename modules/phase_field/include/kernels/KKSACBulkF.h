#ifndef KKSACBULKF_H
#define KKSACBULKF_H

#include "KKSACBulkBase.h"

//Forward Declarations
class KKSACBulkF;

template<>
InputParameters validParams<KKSACBulkF>();

/**
 * KKSACBulkBase child class for the freee energy difference term
 * \f$ -\frac{dh}{d\eta}(F_a-F_b)+w\frac{dg}{d\eta} \f$
 * in the the Allen-Cahn bulk residual.
 *
 * The non-linear variable for this Kernel is the order parameter 'eta'.
 */
class KKSACBulkF : public KKSACBulkBase
{
public:
  KKSACBulkF(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeDFDOP(PFFunctionType type);
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  /// double well height parameter
  Real _w;

  /// double well function material property base names
  std::string _g_name;

  /// Derivative of the double well function \f$ \frac d{d\eta} g(\eta) \f$
  const MaterialProperty<Real> & _prop_dg;

  /// Second derivative of the double well function \f$ \frac {d^2}{d\eta^2} g(\eta) \f$
  const MaterialProperty<Real> & _prop_d2g;
};

#endif //KKSACBULKF_H
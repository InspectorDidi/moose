//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MultipleUpdateAux.h"

registerMooseObject("MooseTestApp", MultipleUpdateAux);

InputParameters
MultipleUpdateAux::validParams()
{
  InputParameters params = AuxKernel::validParams();

  params.addRequiredCoupledVar("u", "unknown (nl-variable)");
  params.addRequiredCoupledVar("var1", "an aux variable to update");
  params.addRequiredCoupledVar("var2", "another aux variable to update");

  return params;
}

MultipleUpdateAux::MultipleUpdateAux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _nl_u(coupledValue("u")),
    _var1(writableCoupledValue("var1")),
    _var2(writableCoupledValue("var2"))
{
}

MultipleUpdateAux::~MultipleUpdateAux() {}

Real
MultipleUpdateAux::computeValue()
{
  _var1[_qp] = _nl_u[_qp] + 10.0;
  _var2[_qp] = _nl_u[_qp] + 200.0;
  return -3.33;
}

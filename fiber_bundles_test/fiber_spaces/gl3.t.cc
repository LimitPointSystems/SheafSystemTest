
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

/// @example gl3.t.cc
/// Test driver for class gl3.

#include "SheafSystem/gl3.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/at0_space.h"
#include "SheafSystem/at1_space.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/gln_space.h"
#include "SheafSystem/std_iomanip.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystemTest/test_fibers.impl.h"

using namespace std;
using namespace fiber_bundle;

namespace
{
  void
  test_gl3_volatile()
  {
    // Preconditions:

    // Body:

    //typedef gl3_lite V;

    cout << boolalpha;

    //==========================================================================
    // gl3 facet
    //==========================================================================

    //gl3_lite();

    gl3_lite lfiber;

    //gl3_lite(const gl3_lite& xother);

    gl3_lite lfiber_copy(lfiber);

    //gl3_lite& operator=(const gl3_lite& xother);

    gl3_lite lfiber_assign = lfiber;

    //virtual ~gl3_lite();

    gl3_lite* lfiber_ptr = new gl3_lite;
    delete lfiber_ptr;

    //==========================================================================
    // gln facet
    //==========================================================================

    //virtual int n() const;

    int ln = lfiber.n();
    cout << "ln = " << ln << endl;

    //virtual int d() const;

    int ld = lfiber.d();
    cout << "ld = " << ld << endl;

   //==========================================================================

    typedef double value_type;

    //void put_component(int xindex, value_type xcomp);

    if(ld > 0)
    {
      for(int i=0; i<ld; ++i)
      {
        lfiber.put_component(i, value_type(100+i));
      }
    }

    //void components(dof_type xcomps[], int xcomps_dimension) const;

     value_type lresult[128];
     lfiber.components(lresult, 128);

    //void put_components(const dof_type xcomps[], int xcomps_dimension);

    lfiber.put_components(lresult, 128);

    //value_type component(int xindex) const;

    value_type lvalue = lfiber[0];

    //value_type& operator[] (int xindex);

    value_type& lvalue2 = lfiber[0];

    //const value_type& operator[] (int xindex) const;

    const value_type& lvalue_const = lfiber[0];

   //==========================================================================

    typedef gl3_row_dofs_type<double> row_dofs_type;
    typedef gl3_row_dofs_type<double>::matrix_type matrix_type;

    //gl3_lite(const row_dofs_type& xrow_dofs);
 
    row_dofs_type lrow_dofs;
    gl3_lite lfiber_row_dofs(lrow_dofs);
    
    //gl3_lite& operator=(const row_dofs_type& xrow_dofs);

    //gl3_lite(const matrix_type& xmatrix);

    general_matrix_3x3<double> lmat;
    lmat[0][0] =  10; lmat[0][1] = -10; lmat[0][2] =   0;
    lmat[1][0] = -10; lmat[1][1] =  20; lmat[1][2] = -10;
    lmat[2][0] =   0; lmat[2][1] =   0; lmat[2][2] =  10;

    cout << "lmat = " << endl;
    cout << lmat << endl;

    gl3_lite lfiber_mat(lmat);
    const gl3_lite lfiber_const(lmat);

    //gl3_lite& operator=(const matrix_type& xmatrix);

    gl3_lite lfiber_mat_assign = lmat;

    //operator matrix_type& ();

    matrix_type& lmat_type(lfiber_mat);

    cout << "lmat_type = " << endl;
    cout << lmat_type << endl;
   
    //operator const matrix_type& () const;

    const matrix_type& lmat_type_const(lfiber_const);

    cout << "lmat_type_const = " << endl;
    cout << lmat_type_const << endl;


    //operator row_dofs_type& ();

    row_dofs_type& lrow_dofs2(lfiber);;

    //operator const row_dofs_type& () const;

    const row_dofs_type& lrow_dofs2_const2(lfiber_const);

    //matrix_type& basis_matrix();

    matrix_type& lbasis_matrix = lfiber_mat.basis_matrix();

    cout << "lbasis_matrix = " << endl;
    cout << lbasis_matrix << endl;

    //const matrix_type& basis_matrix() const;

    const matrix_type& lbasis_matrix_const =
      lfiber_mat.basis_matrix();

    //matrix_type& component_matrix();

    matrix_type& lcomponent_matrix = lfiber_mat.component_matrix();

    cout << "lcomponent_matrix = " << endl;
    cout << lcomponent_matrix << endl;

    //const matrix_type& component_matrix() const;

    const matrix_type& lcomponent_matrix_const = lfiber_mat.component_matrix();

    cout << "lcomponent_matrix_const = " << endl;
    cout << lcomponent_matrix_const << endl;

    //void rescale(const value_type& xscale, const value_type& yscale);

    lfiber.rescale(1.0, 2.0, 3.0);

    //void rotate_x(const value_type& xangle);

    lfiber.rotate_x(0.785398163);

    //void rotate_y(const value_type& xangle);

    lfiber.rotate_y(0.785398163);

    //void rotate_z(const value_type& xangle);

    lfiber.rotate_z(0.785398163);


    //void basis(value_type xb0[], value_type xb1[]) const;

    value_type xb0[3];
    value_type xb1[3];
    value_type xb2[3];
    lfiber.basis(xb0, xb1, xb2);


    //void put_basis(const value_type xb0[],
    //               const value_type xb1[]);

    lfiber.put_basis(xb0, xb1, xb2);

    //void get_matrix(row_dofs_type& xmatrix) const;

    lfiber.get_matrix(lrow_dofs2);

    //void put_matrix(row_dofs_type& xmatrix);

    lfiber.put_matrix(lrow_dofs2);

    //==========================================================================

    //gl3_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const

    row_dofs_type* lclone_row_dofs = lrow_dofs.clone(true, true);

    //virtual gl3_lite* clone(bool xnew_state, bool xauto_access) const

    gl3_lite* lclone2 = lfiber.clone(true, true);

    delete lclone_row_dofs; 
    delete lclone2;

   //==========================================================================

    //operator gl3_row_dofs_type<T>& () const

    gl3_row_dofs_type<double>& lrow_dofs3(lmat);

    //==========================================================================
    // group facet
    //==========================================================================

    //==========================================================================
    // abstract_poset_member facet
    //==========================================================================

    //virtual const string& class_name() const;

    const string& lclass_name = lfiber.class_name();
    cout << "lclass_name = " << lclass_name << endl; 

    //static const string& static_class_name();

    const string& lstatic_class_name = lfiber.static_class_name();
    cout << "lstatic_class_name = " << lstatic_class_name << endl; 

    //virtual gl3_lite* clone() const;

    gl3_lite* lclone = lfiber.clone();
    cout << "lclone = " << lclone << endl; 
    delete lclone;

    //==========================================================================
    // any facet
    //==========================================================================

    //virtual bool is_ancestor_of(const any_lite& xother) const;

    bool lis_ancestor_of = lfiber.is_ancestor_of(lfiber_copy);
    cout << "lis_ancestor_of = " << lis_ancestor_of << endl; 

    //bool invariant() const;

    bool linvariant = lfiber.invariant();
    cout << "linvariant = " << linvariant << endl; 

    //==========================================================================

    // Postconditions:

    // Exit:

    return;

  }

} // end unnamed namespace


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  string filename = filename_from_cmdline(*xargv);

  // Create the namespace.

  fiber_bundles_namespace ns(filename);
  ns.get_read_write_access();

  // Run tests.

  test_persistent_group_type<gl3>(ns);

  test_volatile_type<gl3>();

  test_group_conversions<gl3>(ns);

  // Test group facet:

  test_group_facet<gl3>(ns);

  //============================================================================

  // Test class member functions and others not tested above.

  test_gl3_volatile();

  //============================================================================

  // Write the namespace to standard out.

  //cout << ns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(filename + ".hdf");
  write_agent.write_entire(ns);

  // Postconditions:

  // Exit:

  return 0;
}

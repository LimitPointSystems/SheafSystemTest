
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

/// @example gl2.t.cc
/// Unit test driver for class gl2.

#include "gl2.h"

#include "assert_contract.h"
#include "at0_space.h"
#include "at1_space.h"
#include "fiber_bundles_namespace.h"
#include "gln_space.h"
#include "std_iomanip.h"
#include "storage_agent.h"
#include "test_fibers.impl.h"

using namespace fiber_bundle;

namespace
{
  void
  test_gl2_volatile()
  {
    // Preconditions:

    // Body:

    typedef gl2_lite V;

    cout << boolalpha;

    //==========================================================================
    // gl2 facet
    //==========================================================================

    //gl2_lite();

    gl2_lite lfiber;

    //gl2_lite(const gl2_lite& xother);

    gl2_lite lfiber_copy(lfiber);

    //gl2_lite& operator=(const gl2_lite& xother);

    gl2_lite lfiber_assign = lfiber;

    //virtual ~gl2_lite();

    gl2_lite* lfiber_ptr = new gl2_lite;
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

    typedef gl2_row_dofs_type<double> row_dofs_type;
    typedef gl2_row_dofs_type<double>::matrix_type matrix_type;


    //gl2_lite(const row_dofs_type& xrow_dofs);
 
    row_dofs_type lrow_dofs;
    gl2_lite lfiber_row_dofs(lrow_dofs);
    
    //gl2_lite& operator=(const row_dofs_type& xrow_dofs);

    //gl2_lite(const matrix_type& xmatrix);

    general_matrix_2x2<double> lmat;
    lmat[0][0] =  4; lmat[0][1] = -2;
    lmat[1][0] = -2; lmat[1][1] =  3;

    cout << "lmat = " << endl;
    cout << lmat << endl;

    gl2_lite lfiber_mat(lmat);
    const gl2_lite lfiber_const(lmat);

    //gl2_lite& operator=(const matrix_type& xmatrix);

    gl2_lite lfiber_mat_assign = lmat;

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

    lfiber.rescale(2.0, 2.0);

    //void rotate_z(const value_type& xangle);

    lfiber.rotate_z(0.785398163);


    //void basis(value_type xb0[], value_type xb1[]) const;

    value_type xb0[2];
    value_type xb1[2];
    lfiber.basis(xb0, xb1);


    //void put_basis(const value_type xb0[],
    //               const value_type xb1[]);

    lfiber.put_basis(xb0, xb1);

    //void get_matrix(row_dofs_type& xmatrix) const;

    lfiber.get_matrix(lrow_dofs2);

    //void put_matrix(row_dofs_type& xmatrix);

    lfiber.put_matrix(lrow_dofs2);

    //==========================================================================

    //gl2_row_dofs_type<T>* clone(bool xnew_state, bool xauto_access) const

    row_dofs_type* lclone_row_dofs = lrow_dofs.clone(true, true);

    //virtual gl2_lite* clone(bool xnew_state, bool xauto_access) const

    gl2_lite* lclone2 = lfiber.clone(true, true);

    delete lclone_row_dofs; 
    delete lclone2;

    //==========================================================================

    //operator gl2_row_dofs_type<T>& () const

    gl2_row_dofs_type<double>& lrow_dofs3(lmat);

    //==========================================================================

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

    //virtual gl2_lite* clone() const;

    gl2_lite* lclone = lfiber.clone();
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

  string lfilename = filename_from_cmdline(*xargv);

  // Create the namespace.

  fiber_bundles_namespace lns(lfilename);
  lns.get_read_write_access();

  // Run tests.

  test_persistent_group_type<gl2>(lns);

  test_volatile_type<gl2>();

  test_group_conversions<gl2>(lns);

  // Test group facet:

  test_group_facet<gl2>(lns);

  //============================================================================

  // Test class member functions and others not tested above.

  test_gl2_volatile();

  //============================================================================

  // Write the namespace to standard out.

  //cout << lns << endl;

  // Write the namespace to a file.

  storage_agent write_agent(lfilename + ".hdf");
  write_agent.write_entire(lns);

  // Postconditions:

  // Exit:

  return 0;
}

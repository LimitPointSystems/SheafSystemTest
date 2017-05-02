
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

/// @example field_factory.t.cc

/// @file
/// Test driver for class field_factory.
/// @deprecated Should use field_factory_2.

#include "SheafSystem/field_factory.h"

#include "SheafSystem/assert_contract.h"
#include "SheafSystem/fiber_bundles_namespace.h"
#include "SheafSystem/storage_agent.h"
#include "SheafSystem/field_vd.h"
#include "SheafSystem/wsv_block.h"

using namespace std;
using namespace fields;

namespace
{
///
/// Tests new_scalar_field_1d_unstructured.
///
void test_new_scalar_field_1d_unstructured(fiber_bundles_namespace& xns)
{

  wsv_block<sec_vd_value_type> llower("0");
  wsv_block<sec_vd_value_type> lupper("3");

  field_vd* lfield =
    field_factory::new_scalar_field_1d_unstructured(xns,
        "test_1d_unstructured",
        3,
        llower,
        lupper,
        "linear_scalar_fcn");
  return;
}

///
/// Tests delete_field_spaces.
///
void test_delete_field_spaces(fiber_bundles_namespace& xns)
{

  wsv_block<sec_vd_value_type> llower("0");
  wsv_block<sec_vd_value_type> lupper("3");

  field_vd* lfield =
    field_factory::new_scalar_field_1d_uniform(xns,
        "test_delete_field_spaces",
        3,
        llower,
        lupper,
        "property_dof_function_example");

  cout << endl << "namespace before deleting field spaces:"
  << static_cast<poset_state_handle&>(xns) << endl;

  field_factory::delete_field_spaces(lfield, true, true);

  cout << endl << "namespace after deleting field spaces:"
  << static_cast<poset_state_handle&>(xns) << endl;

  return;
}

///
/// Tests new_scalar_field_1d_uniform.
///
void test_new_scalar_field_1d_uniform(fiber_bundles_namespace& xns)
{
  wsv_block<sec_vd_value_type> llower("0");
  wsv_block<sec_vd_value_type> lupper("3");

  field_vd* lfield =
    field_factory::new_scalar_field_1d_uniform(xns,
        "test_1d_uniform",
        3,
        llower,
        lupper,
        "property_dof_function_example");

  return;
}

///
/// Tests new_scalar_field_2d_unstructured.
///
void test_new_scalar_field_2d_unstructured(fiber_bundles_namespace& xns)
{

  wsv_block<sec_vd_value_type> llower("0 0");
  wsv_block<sec_vd_value_type> lupper("3 2");

  field_vd* lfield =
    field_factory::new_scalar_field_2d_unstructured(xns,
        "test_2d_unstructured",
        3,
        2,
        true,
        llower,
        lupper,
        "property_dof_function_example");

  return;
}

#ifdef HAVE_VTK

///
/// Tests Delaunay triangulation version of new_scalar_field_2d_unstructured.
///
void test_new_scalar_field_2d_Delaunay(fiber_bundles_namespace& xns)
{

  wsv_block<sec_vd_value_type> llower("0 0");
  wsv_block<sec_vd_value_type> lupper("3 2");

  field_vd* lfield =
    field_factory::new_scalar_field_2d_unstructured(xns,
        "test_2d_Delaunay",
        12,
        llower,
        lupper,
        "property_dof_function_example");

  return;
}

#endif

///
/// Tests new_scalar_field_2d_uniform.
///
void test_new_scalar_field_2d_uniform(fiber_bundles_namespace& xns)
{

  wsv_block<sec_vd_value_type> llower("0 0");
  wsv_block<sec_vd_value_type> lupper("3 2");

  field_vd* lfield =
    field_factory::new_scalar_field_2d_uniform(xns,
        "test_2d_uniform",
        3,
        2,
        llower,
        lupper,
        "property_dof_function_example");

  return;
}

///
/// Tests new_scalar_field_3d_unstructured.
///
void test_new_scalar_field_3d_unstructured(fiber_bundles_namespace& xns)
{

  wsv_block<sec_vd_value_type> llower("0 0 0");
  wsv_block<sec_vd_value_type> lupper("3 2 1");

  field_vd* lfield =
    field_factory::new_scalar_field_3d_unstructured(xns,
        "test_3d_unstructured",
        3,
        2,
        1,
        true,
        llower,
        lupper,
        "property_dof_function_example");

  return;
}

#ifdef HAVE_VTK

///
/// Tests Delaunay tesselation version new_scalar_field_3d_unstructured.
///
void test_new_scalar_field_3d_Delaunay(fiber_bundles_namespace& xns)
{

  wsv_block<sec_vd_value_type> llower("0 0 0");
  wsv_block<sec_vd_value_type> lupper("3 2 1");

  field_vd* lfield =
    field_factory::new_scalar_field_3d_unstructured(xns,
        "test_3d_Delaunay",
        24,
        llower,
        lupper,
        "property_dof_function_example");

  return;
}

#endif

///
/// Tests new_scalar_field_3d_uniform.
///
void test_new_scalar_field_3d_uniform(fiber_bundles_namespace& xns)
{

  wsv_block<sec_vd_value_type> llower("0 0 0");
  wsv_block<sec_vd_value_type> lupper("3 2 1");

  field_vd* lfield =
    field_factory::new_scalar_field_3d_uniform(xns,
        "test_3d_uniform",
        3,
        2,
        1,
        llower,
        lupper,
        "property_dof_function_example");

  return;
}

}
; // End unnamed namespace.

///
/// Main routine.
///
int main(int argc, char* argv[])
{

  fiber_bundles_namespace lns("field_factory.t");
  lns.get_read_write_access();

  test_delete_field_spaces(lns);

  test_new_scalar_field_1d_uniform(lns);
  test_new_scalar_field_1d_unstructured(lns);

  test_new_scalar_field_2d_unstructured(lns);
  test_new_scalar_field_2d_uniform(lns);

  test_new_scalar_field_3d_unstructured(lns);
  test_new_scalar_field_3d_uniform(lns);

#ifdef HAVE_VTK

  test_new_scalar_field_2d_Delaunay(lns);
  test_new_scalar_field_3d_Delaunay(lns);

#endif

  cout << lns << endl;

  storage_agent sa("field_factory.t.hdf");
  sa.write_entire(lns);

  return 0;
}

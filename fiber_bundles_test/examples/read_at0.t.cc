
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

/// @example examples/read_at0.t.cc
/// Test driver for CTB dof tuple stuff.

#include "abstract_poset_member.h"
#include "at0.h"
#include "index_space_iterator.h"
#include "std_cctype.h"
#include "postorder_iterator.h"
#include "namespace_poset.h"
#include "poset.h"
#include "product_index_space.h"
#include "schema_poset_member.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_e2.h"
#include "sec_st2_e2.h"
#include "assert_contract.h"
#include "std_cstdlib.h"
#include "storage_agent.h"
#include "st2_e2.h"
#include "std_iostream.h"
#include "subposet.h"
#include "vd.h"

using namespace fiber_bundle;

void query_field(namespace_poset* ns,
                 const string& section_space_name,
                 const string& field_name);

int
main(int argc, char* argv[])
{
  storage_agent sa("at0.t.hdf", sheaf_file::READ_ONLY, false);

  namespace_poset ns("tmp");

  ns.get_read_write_access();

  sa.read_entire(ns);

  query_field(&ns, "at0_on_triangle_mesh", "scalar");

  return 0;
}

void
query_field(namespace_poset* ns,
            const string& section_space_name,
            const string& field_name)
{
  sec_rep_space* srs = ns->member_poset<sec_rep_space>(section_space_name, false);
  srs->get_read_access();

  int dof_dimension = srs->df();
  cout << "dof_dimension = " << dof_dimension << endl;

  sec_rep_space_member mbr(srs, field_name);
  cout << mbr.name() << endl;

  int count = mbr.schema().dof_ct();
  double* values = new double[count+1];
  double dof;
  int i=0;

  index_space_iterator* itr = mbr.schema().row_dof_id_space().iterator(true);
  while(!itr->is_done())
  {
    mbr.get_dof(itr->pod(), &dof, sizeof(dof));
    cout << "  i = " << i << ", dof = " << dof << endl;
    values[i++] = dof;
    itr->next();
  }

  delete itr;
  delete [] values;

  mbr.detach_from_state();

  srs->release_access();
  //delete srs;


}


// //$$ADVISE: Should this be "query_fiber_dimension" ?
/// ///@todo Make inline
/// int field::query_dof_dimension()
/// {
///     int result = _field_space->query_dof_dimension();
///     return result;
/// }

// double_dof_tuple* field::query_dofs()
// {
//     sec_rep_space* ss = get_space()->section_space();
//     ss->get_read_access();
//     sec_rep_space_member mbr(ss, name());
//     //cout << mbr.name() << endl;

//     section_dof_iterator itr(&mbr);

//     int count = itr.dof_ct();
//     double* values = new double[count];

//     double dof;
//     int i=0;
//     while(!itr.is_done())
//     {
//       itr.value(static_cast<void*>(&dof), sizeof(double));
//       values[i++] = dof;
//       itr.next();
//     }

//     mbr.detach_from_state();
//     ss->release_access();

//     double_dof_tuple* result = new double_dof_tuple(values, count);
//     return result;
// }


// // Existing field_space (section_space)
// field_space::field_space(const string& xname, mesh_space* xmesh_space)
//         : base_object(xname)
// {
//     DEBUG("field_space::field_space(2): " + name());

//     name_space* ns = xmesh_space->get_name_space();
//     _section_space = new sec_rep_space(ns->get_namespace_poset(), name());
//     _section_space ->get_read_access();

//     abstract_poset_member* rep = &(_section_space->rep());
//     rep->get_read_access();
//     _descriptor_name = new string(rep->name());
//     rep->release_access();

//     schema_poset_member* fiber_schema = &(_section_space->fiber_schema());
//     fiber_schema->get_read_access();
//     _fiber_schema_member_name = new string(fiber_schema->name());
//     fiber_schema->release_access();

//     abstract_poset_member* base = &(_section_space->base());
//     total_poset_member* tbase = reinterpret_cast<total_poset_member*>(base);
//     _mesh_name = new string(base->name());

//     mesh* _mesh = new mesh(tbase, xmesh_space);

///     ///@todo FIX!!!
///     _sec_descriptor = NULL;

//     _section_space ->release_access();
// }


// int field_space::query_dof_dimension()
// {
//     _section_space->get_read_access();

//     int result = _section_space->df();

//     _section_space->release_access();

//     return result;
// }


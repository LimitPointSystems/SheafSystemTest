
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Test driver for CTB dof tuple stuff.

// $$OBSOLETE No longer part of the tests.  Code remains only as
//            a reference for future development.

#include "abstract_poset_member.h"
#include "at0.h"
#include "binary_section_space_schema_poset.h"
#include "binary_section_space_schema_member.h"
#include "discretization_iterator.h"
#include "fiber_bundles_namespace.h"
#include "std_cctype.h"
#include "zone_nodes_block.h"
#include "triangle_connectivity.h"
#include "postorder_iterator.h"
#include "poset.h"
#include "schema_poset_member.h"
#include "sec_at0.h"
#include "sec_at0_space.h"
#include "sec_e2.h"
#include "sec_st2_e2.h"
#include "section_dof_iterator.h"
#include "assert_contract.h"
#include "std_cstdlib.h"
#include "st2_e2.h"
#include "std_iostream.h"
#include "subposet.h"
#include "vd.h"

using namespace fiber_bundle;

//typedef struct {int* node_ids; int node_ids_ub;} Connectivity;
typedef struct
{
  void* values;
  int values_ub;
}
Dof_tuple;

#define NODE_ID(i, j) ((i)*node_ct_y + (j))

sec_rep_space*
make_scalar_sec_rep_space(fiber_bundles_namespace* test_namespace,
			  abstract_poset_member* xbase,
			  string xname,
			  bool xmultivalued);

sec_rep_descriptor*
make_sec_rep_descriptor(fiber_bundles_namespace* test_namespace,
                        bool xmultivalued);

int
main(int argc, char* argv[])
{
  size_t edge_ct_x = 1;

  if (argc > 1)
    edge_ct_x = atoi(argv[1]);

  size_t edge_ct_y = 1;
  if (argc > 2)
    edge_ct_y = atoi(argv[2]);

  // get the standard definitions

  fiber_bundles_namespace test_namespace("test");

  test_namespace.get_read_write_access();

  // Make triangle mesh

  base_space_poset& lmesh =
    test_namespace.new_base_space<zone_nodes_block>("triangle_mesh", "", "", 2, true);
  lmesh.get_read_write_access();

  // Make triangle block base space

  triangle_connectivity lconn(edge_ct_x, edge_ct_y);

  zone_nodes_block lbase_space(lmesh, lconn, true);
  lbase_space.put_name("triangle_block", true, false);

  // Make subposets.

  //   subposet* first_vertex = new subposet(lbase_space.host());
  //   first_vertex->put_name("__multivalued_vertex", true, false);
  //   first_vertex->insert_member(6);

  // get the single valued schema

  sec_rep_space* lat0_srs_single =
    make_scalar_sec_rep_space(&test_namespace, &lbase_space, "at0_on_triangle_mesh", false);

  lat0_srs_single->get_read_access();

  section_space_schema_member* lschema_single = &(lat0_srs_single->schema());

  lat0_srs_single->release_access();

  // get the multivalued schema

  //   sec_rep_space* lat0_srs_multi =
  //     make_scalar_sec_rep_space(&test_namespace, &lbase_space,
  //                               "at0_on_triangle_mesh_multivalued", true);

  //   lat0_srs_multi->get_read_access();

  //   section_space_schema_member* lschema_multi = &(lat0_srs_multi->schema());

  //   lat0_srs_multi->release_access();

  // output the namespace

  cout << test_namespace << endl;

  // output the single valued test

  lschema_single->get_read_access();

  discretization_iterator itr_single(*lschema_single);

  cout << "\n##### begin single valued test #####\n";

  while(!itr_single.is_done())
  {
    cout << " " << itr_single.index().pod();
    itr_single.next();
  }
  cout << "\nshould be:\n";
  cout << " 3 4 6 10\n";
  cout << "##### end   single valued test #####\n\n";

  lschema_single->release_access();

  // output the multi valued test

  //   lschema_multi->get_read_access();

  //   discretization_iterator itr_multi(*lschema_multi);

  //   cout << "\n##### begin multi valued test #####\n";

  //   while(!itr_multi.is_done())
  //   {
  //     if(itr_multi.is_multivalued())
  //     {
  //       cout << " " << itr_multi.discretization_member_index()
  //       << "(" << itr_multi.evaluation_member_index() << ")";
  //     }
  //     else
  //     {
  //       cout << " " << itr_multi.index();
  //     }
  //     itr_multi.next();
  //   }
  //   cout << "\nshould be:\n";
  //   cout << " 3 4 6(9) 6(13) 10\n";
  //   cout << "##### end   multi valued test #####\n\n";

  //   lschema_multi->release_access();

  // detach the namespace

  // Clean-up

  lbase_space.detach_from_state();
  lmesh.release_access();

  return 0;
}

sec_rep_space*
make_scalar_sec_rep_space(fiber_bundles_namespace* test_namespace,
                          abstract_poset_member* xbase,
                          string xname,
                          bool xmultivalued)
{
  sec_rep_space* result;

  // Preconditions:

  require(test_namespace != 0);
  require(xbase != 0);

  // Body:

  // Create the scalar section space

  arg_list largs =
    binary_section_space_schema_poset::make_arg_list("", xbase->path(false), "");

  poset_path lschema_path =
    test_namespace->new_scalar_section_space_schema<sec_at0>(xname + "schema", largs);

  largs = sec_at0_space::make_arg_list();

  result = &test_namespace->new_scalar_section_space<sec_at0>(xname, largs, lschema_path);

  // Create a field in the section space

  result->get_read_write_access();

  sec_at0 lfield(result);
  lfield.put_name("scalar", true, false);

  result->release_access();

  // Detach members so destructor won't complain

  lfield.detach_from_state();

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}

sec_rep_descriptor*
make_sec_rep_descriptor(fiber_bundles_namespace* test_namespace,
                        bool xmultivalued)
{

  sec_rep_descriptor* result;

  // Preconditions:

  require(test_namespace != 0);

  // Body:

  if(xmultivalued)
  {
    poset* sec_rep_desc =
      test_namespace->member_poset<poset>(string("sec_rep_descriptors"), false);
    
    result =
      new sec_rep_descriptor(sec_rep_desc,
                             "__vertices",
                             "__multivalued_vertex",
                             "__elements",
                             "dlinear",
                             "www.lpsweb.com/fiber_bundles/fiber_bundles_namespace.html",
                             1,
                             true,
                             true);

    result->get_read_write_access(true);
    result->put_name("vertex_element_dlinear_multivalued", true, false);
    result->release_access();
  }
  else
  {
    result = new sec_rep_descriptor(test_namespace,
                                    "sec_rep_descriptors/vertex_element_dlinear");
  }

  // Postconditions:

  ensure(result != 0);

  // Exit

  return result;
}


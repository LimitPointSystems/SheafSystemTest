
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

// Unit test driver for class mesh_partition.

// $$OBSOLETE No longer part of the tests.  Code remains only as
//            a reference for future development.

#include "mesh_partition.h"

#include "fiber_bundles_namespace.h"
#include "quad_connectivity.h" 
#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_utils.h"
#include "zone_nodes_block.h"


//$$HACK: This entire test case is a HACK. Class mesh_partition
//        is abstract and has no real derived classes in the
//        libraries at present.  We have HACK a derived class
//        and implemented a few of the methods in order to be
//        able to test a few of the methods.

using namespace fiber_bundle;

namespace
{
//   class mesh_partition_derived : public mesh_partition
//   {
//   public:

//     mesh_partition_derived() { }

// //     mesh_partition_derived(const string& xname, size_type xct)
// //       : mesh_partition(xname, xct)
// //     {
// //     }

//     mesh_partition_derived(const mesh_partition_derived& xother)
//     //: mesh_partition(xother)
//     {
//     }

//     virtual cover_set_iterator part_zones(size_type xi) const
//     {
//       cover_set_iterator result;
//       return result;
//     }

//     virtual mesh_partition_derived* clone() const
//     {
//       return new mesh_partition_derived;
//     }
//   };

  base_space_poset*
  make_base_space(fiber_bundles_namespace& xns,
                  const string& xbase_space_name)
  {
    // Preconditions:

    require(xns.state_is_read_write_accessible());
    require(!xbase_space_name.empty());

    // Body:

    typedef zone_nodes_block B;
    
    // Create a host poset for the mesh.

    base_space_poset& lhost =
      xns.new_base_space<B>(xbase_space_name, "", "", 2, true);

    lhost.get_read_write_access();

    // Create the mesh and give it a name.

    // Make quad connectivity.

    quad_connectivity lconn(4, 4);

    // Make quad block.

    zone_nodes_block lblock(lhost, lconn, true);
    lblock.put_name("mesh", true, false);

    //poset_path result = lblock.path(true);
    
    lblock.detach_from_state();
    lhost.release_access();

    base_space_poset* result = &lhost;

    // Postconditions:

    //ensure(!result.empty());
    //+ other ensure(...)

    // Exit:
    
    return result;
  }


  bool
  test_mesh_partition_facet()
  {
    // Preconditions:

    // Body:

   //==========================================================================

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

     // Make a base space

    base_space_poset* lbase_host = make_base_space(lns, "the_base_space");

    cout << "lbase_host->path() = " << lbase_host->path() << endl;

    string lname_prefix = mesh_partition::name_prefix();

    cout << "lname_prefix = " << lname_prefix << endl;

    cout << boolalpha;

    //==========================================================================

    //mesh_partition();

    mesh_partition lpartition0;

    //static bool is_valid_name(const string& xname);

    const string lpname = lname_prefix + "mesh_partition";

    bool lis_valid_name = mesh_partition::is_valid_name(lpname);
    cout << "lis_valid_name = " << lis_valid_name << endl; 

    //mesh_partition(const base_space_poset& xmesh, const string& xname);

    mesh_partition lpartition(*lbase_host, lpname);

    //const string& name() const;

    const string& lname = lpartition.name();
    cout << "lname = " << lname << endl;

    //mesh_partition(const mesh_partition& xother);

    mesh_partition lpartition_copy(lpartition);

    //mesh_partition& operator=(const mesh_partition& xother);

    mesh_partition lpartition_assign = lpartition;

    //virtual ~mesh_partition_derived();

    mesh_partition* lpartition_ptr = new mesh_partition;
   delete lpartition_ptr; 

   //virtual mesh_partition* clone() const;

   mesh_partition* lclone = lpartition.clone();
   delete lclone; 

   //bool invariant() const;

   bool linvariant = lpartition.invariant();
   cout << "linvariant = " << linvariant << endl; 

   //virtual bool is_ancestor_of(const any* xother) const;

    bool lis_ancestor_of = lpartition.is_ancestor_of(&lpartition);
    cout << "lis_ancestor_of = " << lis_ancestor_of << endl; 

    //==========================================================================

    //const base_space_poset& mesh() const;

    const base_space_poset& lmesh = lpartition.mesh();


   //const subposet& parts() const;

    const subposet& lparts = lpartition.parts(); // should be empty.

    //size_type parts_ct() const;

    size_type lpart_ct = lpartition.part_ct();
    cout << "lpart_ct  = " << lpart_ct  << endl;

    //scoped_index put_part(const client_index& xp_id, id_block& xzones);

    //$$SCRIBBLE: Punt here; don't know how to make an id_block.
    //id_block lzones;
    //scoped_index lpart_id = lpartition.put_part(0, lzones);

    //string part_name(const client_index& xp_id) const;

    string lpart_name = lpartition.part_name(0);
    cout << "lpart_name = " << lpart_name  << endl;

    //void part(const client_index& xp_id, id_block& xresult) const;

    //client_index part_id(const string& xname) const;

    client_index lpart_id = lpartition.part_id(lpart_name);
    cout << "lpart_id = " << lpart_id << endl;

    //==========================================================================

    //cout << lns << endl;

    // Postconditions:

    // Exit:
    
    return true;
  }

} // end unknown namespace


int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing mesh_partition");

  bool ltest = true;

  ltest &= test_mesh_partition_facet();

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing mesh_partition");

  // Postconditions:

  // Exit:

  return lresult;
}


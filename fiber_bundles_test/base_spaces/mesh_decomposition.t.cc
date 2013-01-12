
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Unit test driver for class mesh_decomposition.

// $$OBSOLETE No longer part of the tests.  Code remains only as
//            a reference for future development.

#include "mesh_decomposition.h"

#include "fiber_bundles_namespace.h"
#include "quad_connectivity.h" 
#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_utils.h"
#include "zone_nodes_block.h"

using namespace fiber_bundle;

namespace
{
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
  test_mesh_decomposition_facet()
  {
    // Preconditions:

    // Body:

   //==========================================================================

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

     // Make a base space

    base_space_poset* lbase_host = make_base_space(lns, "the_base_space");

    cout << "lbase_host->path() = " << lbase_host->path() << endl;

    string lname_prefix = mesh_decomposition::name_prefix();

    cout << "lname_prefix = " << lname_prefix << endl;

    cout << boolalpha;

    //==========================================================================

    //mesh_decomposition();

    mesh_decomposition ldecomp0;

    //static bool is_valid_name(const string& xname);

    const string lpname = lname_prefix + "mesh_decomposition";

    bool lis_valid_name = mesh_decomposition::is_valid_name(lpname);
    cout << "lis_valid_name = " << lis_valid_name << endl; 

    //mesh_decomposition(const base_space_poset& xmesh, const string& xname);

    mesh_decomposition ldecomp(*lbase_host, lpname);

    //const string& name() const;

    const string& lname = ldecomp.name();
    cout << "lname = " << lname << endl;

    //mesh_decomposition(const mesh_decomposition& xother);

    mesh_decomposition ldecomp_copy(ldecomp);

    //mesh_decomposition& operator=(const mesh_decomposition& xother);

    mesh_decomposition ldecomp_assign = ldecomp;

    //virtual ~mesh_decomposition();

    mesh_decomposition* ldecomp_ptr = new mesh_decomposition(ldecomp);
    delete ldecomp_ptr; 

    //virtual mesh_decomposition* clone() const;

    mesh_decomposition* lclone = ldecomp.clone();
    delete lclone; 

    //virtual bool invariant() const;

    bool linvariant = ldecomp.invariant();
    cout << "linvariant = " << linvariant << endl; 

    //virtual bool is_ancestor_of(const any* xother) const;

    bool lis_ancestor_of = ldecomp.is_ancestor_of(&ldecomp_copy);
    cout << "lis_ancestor_of = " << lis_ancestor_of << endl;

    //==========================================================================

    //const base_space_poset& mesh() const;

    const base_space_poset& lmesh = ldecomp.mesh();

    //scoped_index put_scope(const client_index& xp_id, id_block& xzones);

    //$$SCRIBBLE: Punt here; don't know how to make an id_block.
    //id_block lzones;
    //scoped_index ldecomp.mesh.put_scope(0, lzones);
   
    //const subposet& scopes() const;

    const subposet& lscopes = ldecomp.scopes(); // should be empty.

    //int scope_ct() const;

    int lscope_ct = ldecomp.scope_ct();
    cout << "lscope_ct = " << lscope_ct << endl;

    //void compute_basis();

    ldecomp.compute_basis();

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

  print_header("Begin testing mesh_decomposition");

  bool ltest = true;

  ltest &= test_mesh_decomposition_facet();

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing mesh_decomposition");

  // Postconditions:

  // Exit:

  return lresult;
}


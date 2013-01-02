// $RCSfile: material_decomposition.t.cc,v $ $Revision: 1.1.2.7 $ $Date: 2012/10/19 02:23:27 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// Unit test driver for class material_decomposition.

#include "material_decomposition.h"

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
  test_material_decomposition_facet()
  {
    // Preconditions:

    // Body:

   //==========================================================================

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

     // Make a base space

    base_space_poset* lbase_host = make_base_space(lns, "the_base_space");

    cout << "lbase_host->path() = " << lbase_host->path() << endl;

    string lname_prefix =  material_decomposition::name_prefix();

    cout << "lname_prefix = " << lname_prefix << endl;

    cout << boolalpha;

    //==========================================================================

    //material_decomposition();

    material_decomposition ldecomp0;

    //static bool is_valid_name(const string& xname);

    bool lis_valid_name =
      material_decomposition::is_valid_name(
        lname_prefix + "material_decomposition");
    cout << "lis_valid_name = " << lis_valid_name << endl; 

    //material_decomposition(const base_space_poset& xmesh,
    //                       const string& xname);

    material_decomposition ldecomp(*lbase_host,
                                   lname_prefix + "material_decomposition");

    //const string& name() const;

    const string& lname = ldecomp.name();
    cout << "lname = " << lname << endl;

    //material_decomposition(const material_decomposition& xother);

    material_decomposition ldecomp_copy(ldecomp);

    //material_decomposition& operator=(const material_decomposition& xother);

    material_decomposition ldecomp_assign = ldecomp;

    //virtual ~material_decomposition();

    material_decomposition* ldecomp_ptr = new material_decomposition(ldecomp);
    delete ldecomp_ptr; 

    //virtual material_decomposition* clone() const;

    material_decomposition* lclone = ldecomp.clone();
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

    //scoped_index put_material(const client_index& xp_id, id_block& xzones);

    //$$SCRIBBLE: Punt here; don't know how to make an id_block.
    //id_block lzones;
    //scoped_index ldecomp.mesh.put_material(0, lzones);
   
    //const subposet& materials() const;

    const subposet& mixed_materials =
      ldecomp.mixed_materials(); // should be empty.

    //int material_ct() const;

    int lmaterial_ct = ldecomp.material_ct();
    cout << "lmaterial_ct = " << lmaterial_ct << endl;

    //void compute_mixed_materials();

    ldecomp.compute_mixed_materials();

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

  print_header("Begin testing material_decomposition");

  bool ltest = true;

  ltest &= test_material_decomposition_facet();

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing material_decomposition");

  // Postconditions:

  // Exit:

  return lresult;
}


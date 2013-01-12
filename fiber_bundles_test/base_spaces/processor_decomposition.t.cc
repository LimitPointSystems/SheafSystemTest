
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Unit test driver for class processor_decomposition.

// $$OBSOLETE No longer part of the tests.  Code remains only as
//            a reference for future development.

#include "processor_decomposition.h"

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
  test_processor_decomposition_facet()
  {
    // Preconditions:

    // Body:

   //==========================================================================

    fiber_bundles_namespace lns("test_namespace");
    lns.get_read_write_access();

     // Make a base space

    base_space_poset* lbase_host = make_base_space(lns, "the_base_space");

    cout << "lbase_host->path() = " << lbase_host->path() << endl;

    string lname_prefix = processor_decomposition::name_prefix();

    cout << "lname_prefix = " << lname_prefix << endl;

    cout << boolalpha;

    //==========================================================================

    //processor_decomposition();

    processor_decomposition ldecomp0;

    //static bool is_valid_name(const string& xname);

    const string lpname = lname_prefix + "processor_decomposition";

    bool lis_valid_name = processor_decomposition::is_valid_name(lpname);
    cout << "lis_valid_name = " << lis_valid_name << endl; 

    //processor_decomposition(const base_space_poset& xmesh, const string& xname);

    processor_decomposition ldecomp(*lbase_host, lpname);

    //const string& name() const;

    const string& lname = ldecomp.name();
    cout << "lname = " << lname << endl;

    //processor_decomposition(const processor_decomposition& xother);

    processor_decomposition ldecomp_copy(ldecomp);

    //processor_decomposition& operator=(const processor_decomposition& xother);

    processor_decomposition ldecomp_assign = ldecomp;

    //virtual ~processor_decomposition();

    processor_decomposition* ldecomp_ptr = new processor_decomposition(ldecomp);
    delete ldecomp_ptr; 

    //virtual processor_decomposition* clone() const;

    processor_decomposition* lclone = ldecomp.clone();
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

 //    //scoped_index put_scope(const client_index& xp_id, id_block& xzones);

//     //$$SCRIBBLE: Punt here; don't know how to make an id_block.
//     //id_block lzones;
//     //scoped_index ldecomp.mesh.put_scope(0, lzones);
   
    //const subposet& read_scopes() const;

    const subposet& lread_scopes = ldecomp.read_scopes(); // should be empty.

    //const subposet& write_scopes() const;

    const subposet& lwrite_scopes = ldecomp.write_scopes(); // should be empty.

    //const subposet& send_scopes() const;

    const subposet& lsend_scopes = ldecomp.send_scopes(); // should be empty.

    //subposet& scope_set(const string& xscope_type);

    subposet& lsend_set_r = ldecomp.scope_set("read"); 
    subposet& lsend_set_w = ldecomp.scope_set("write"); 
    subposet& lsend_set_s = ldecomp.scope_set("send"); 

    //const subposet& scope_set(const string& xscope_type) const;

    // Can't get this one to work. Always chooses the non-const one above.

    //int processor_ct() const;

    int lprocessor_ct = ldecomp.processor_ct();
    cout << "lprocessor_ct = " << lprocessor_ct << endl;

    //string read_scope_name(const client_index& xp_id) const;

    string lread_scope_name = ldecomp.read_scope_name(0);
    cout << "lread_scope_name = " << lread_scope_name << endl;

    //void read_scope(const client_index& xp_id, id_block& xresult) const;

    //scoped_index put_read_scope(const client_index& xp_id, id_block& xzones);

    //string write_scope_name(pod_index_type xp_id) const;

    string lwrite_scope_name = ldecomp. write_scope_name(0);
    cout << "lwrite_scope_name = " << lwrite_scope_name << endl;


    //void write_scope(const client_index& xp_id, id_block& xresult) const;

    //scoped_index put_write_scope(const client_index& xp_id, id_block& xzones);

    //string send_scope_name(const client_index& xsend_id,
    //			             const client_index& xrecv_id) const;

    string lsend_scope_name = ldecomp.send_scope_name(0, 1);
    cout << "lsend_scope_name = " << lsend_scope_name << endl;


    //void send_scope(const client_index& xsend_id,
    //                const client_index& xrecv_id,
    //                 id_block& xresult) const;

    //scoped_index put_send_scope(const client_index& xsend_id,
    //			      const client_index& xrecv_id,
    //			      id_block& xzones);

    //pod_index_type send_id(const string& xname) const;

    pod_index_type lsend_id = ldecomp.send_id(lsend_scope_name);
    cout << "lsend_id = " << lsend_id << endl;

    //string comm_scope_name(pod_index_type xp_id) const;

    string lcomm_scope_name = ldecomp.comm_scope_name(0);
    cout << "lcomm_scope_name = " << lcomm_scope_name << endl;

    //static string scope_set_name(const string& xscope_type,
    //                             const string& xdecomp_name);

    string lscope_set_name2 =
      processor_decomposition::scope_set_name("read", lname);
 
    //string scope_set_name(const string& xscope_type);

    string lscope_set_name = ldecomp.scope_set_name("read");
     cout << "lscope_set_name = " << lscope_set_name << endl;

    //static bool is_valid_scope_type(const string& xscope_type);

    //void compute_comm_scopes();

    ldecomp.compute_comm_scopes();

    //void compute_zone_ceiling();

    ldecomp.compute_zone_ceiling();

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

  print_header("Begin testing processor_decomposition");

  bool ltest = true;

  ltest &= test_processor_decomposition_facet();

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing processor_decomposition");

  // Postconditions:

  // Exit:

  return lresult;
}


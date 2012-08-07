
// $RCSfile: name_limit.t.cc,v $ $Revision: 1.8 $ $Date: 2012/03/01 00:41:23 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example io/name_limit.t.cc
/// Routine to test ability to store many member names

#include "sheaves_namespace.h"
#include "poset_path.h"
#include "std_sstream.h"
#include "storage_agent.h"
#include "subposet_member_iterator.h"

using namespace sheaf;


int
main(int argc, char* argv[])
{

  string size_arg;
  size_type size;
  if (argc > 1)
  {
    size = atoi(argv[1]);
    size_arg = argv[1];
  }
  else
  {
    size = 5000;
    size_arg = "5000";
  }

  if(size < 1)
  {
    size = 1;
    size_arg = "1";
  }


  sheaves_namespace* lns = new sheaves_namespace("name_limit.t");

  // cout << *lns << endl;

  lns->get_read_write_access();

  // Make a test poset with number of member names == size + 2.

  poset* lposet = new poset(lns, "primitives_schema/top", "name_test", true);

  lposet->begin_jim_edit_mode(true);

  // There's still a limitation on the number of dof tuples,
  // so make all the members use the same dof tuple.

  scoped_index ltuple_id = lposet->new_row_dof_map();

  for(int i=0; i<size; ++i)
  {
    scoped_index lmbr_id = lposet->new_member(true, ltuple_id);

    stringstream mbr_name_stream;
    string mbr_name;
    mbr_name_stream << lmbr_id.pod();
    mbr_name_stream >> mbr_name;

    // Make names exactly 16 chars long
    // so we know how much storage we're using.

    // mbr_name += "++++++++++++++++";

    string mbr_name_substring = mbr_name.substr(0, 16);

    lposet->put_member_name(lmbr_id, mbr_name_substring, true, false);
  }



  lposet->end_jim_edit_mode(true, true);

  //   lposet->get_read_access();
  //   cout << *lposet << endl;
  //   lposet->release_access();


  string fname = "name_limit.t.hdf";
  storage_agent sa(fname);
  sa.write_entire(*lns);

  delete lns;

  return 0;
}

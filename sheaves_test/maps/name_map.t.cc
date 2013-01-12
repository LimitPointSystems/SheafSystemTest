
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

/// @example maps/name_map.t.cc
/// Unit test driver for template class name_map.

#include "name_map.impl.h"
#include "namespace_poset.h"
#include "subposet_member_iterator.h"

template<typename T>
void
test_name_map()
{
  //  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  // cout << "++++ begin test_name_map<T> +++++++++++++++++++++" << endl;
  // cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

  typedef name_map<T> name_map_type;

  // Make a default namespace.

  namespace_poset ns("default_namespace_poset");

  // Get read-write access.

  ns.get_read_write_access();

  // Get an iterator for the namespace.

  subposet_member_iterator itr(ns.whole());

  // Make a new name_map.

  name_map_type nm;

  cout << endl;
  cout << "==========================================" << endl;
  cout << endl;
  cout << "Inserting entries: " << endl;
  cout << endl;
  cout << "==========================================" << endl;
  cout << endl;


  while(!itr.is_done())
  {
    T lindex(itr.index().pod());

    nm.put_entry(lindex, itr.name());

    cout << itr.name() << " inserted into the map at index:  " << lindex << endl;

    cout << endl;

    itr.next();
  }

  cout << endl;
  cout << "Contents of map: " << endl << nm << endl;
  cout << endl;

  cout << "Now calling the clone method: " << endl << endl;

  name_map_type* cm = nm.clone();

  cout << "Contents of cloned map: " << endl << *cm << endl;
  cout << endl;



  // Now delete some indices.

  for (int i=0; i < ns.member_ct(); i++)
  {
    cout << endl;
    cout << "==========================================" << endl;
    cout << endl;
    cout << "Deleting index: " << i << endl;
    cout << endl;
    cout << "==========================================" << endl;
    cout << endl;

    nm.delete_index(T(i));

    for (int j=0; j < ns.member_ct(); j++)
    {
      T lindex(j);

      // Test for the presence of index.

      if (nm.contains_index(lindex))
      {
        cout << "Map contains index " << j << " : "  << nm.contains_index(lindex) << endl;
        cout << "Name for index " << j << " is " << nm.name(lindex) << endl;
        cout << endl;
      }
      else
      {
        cout << "Index " << j << " has been deleted from the map." << endl;
        cout << endl;
      }

    }
  }

  /// @todo exercise remainder of name_multimaps queries and functions.

  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "++++ end test_name_map<T> +++++++++++++++++++++" << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}


int
main(int argc, char* argv[])
{

  test_name_map<int>();
  test_name_map<scoped_index>();

}


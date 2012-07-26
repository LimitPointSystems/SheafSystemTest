// $RCSfile: name_multimap.t.cc,v $ $Revision: 1.15 $ $Date: 2012/03/01 00:41:28 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// @example maps/name_multimap.t.cc
/// Unit test driver for template class name_multimap.

#include "name_multimap.h"
#include "namespace_poset.h"
#include "subposet_member_iterator.h"
#include "scoped_index.h"

using namespace sheaf;

void
test_int()
{
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "++++ TESTING name_multimap<int> +++++++++++++++++++++" << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;


  // Make a default namespace

  namespace_poset ns("default_namespace_poset");

  // get read access

  ns.get_read_write_access();

  // get an iterator for the namespace

  subposet_member_iterator itr(ns.whole());

  // make a new name_multimap

  //name_multimap<scoped_index> nmm;
  name_multimap<int> nmm;

  // iterate over the subposet stuffing the node names into
  // the array.

  cout << endl;
  cout << "==========================================" << endl;
  cout << endl;
  cout << "Inserting entries: " << endl;
  cout << endl;
  cout << "==========================================" << endl;
  cout << endl;


  while(!itr.is_done())
  {
    nmm.put_entry(itr.index().pod(), itr.name(), false);

    // every index can have more than one name, but every name has exactly one index.

    cout << itr.name() << " inserted into the map at index:  " << itr.index() << endl;

    itr.next();
  }

  // force index 6 to have 3 names

  nmm.put_entry(6, "alpha", false);
  nmm.put_entry(6, "beta", false);
  nmm.put_entry(6, "gamma", false);

  name_multimap<int>* cmm = nmm.clone();

  cout << "Below are the contents of the cloned member" << endl;
  cout << endl;
  cout << *cmm << endl;
  cout << endl;
  cout << "Below are the contents of the original" << endl;
  cout << endl;

  cout << nmm << endl;

  for (int i=0; i < 7; i++)
  {

    cout << "Testing -- name is: " << nmm.name(i) << endl;
    cout << "Index " << i << " has " << nmm.name_ct(i) << " names associated with it" << endl;

  }

  // Delete some names.

  cout << endl;
  cout << "==========================================" << endl;
  cout << endl;
  cout << "Deleting name bottom:" << endl;
  cout << endl;
  cout << "==========================================" << endl;
  cout << endl;

  nmm.delete_name("bottom");

  cout << nmm << endl;

  cout << endl;
  cout << "==========================================" << endl;
  cout << endl;
  cout << "Deleting name beta:" << endl;
  cout << endl;
  cout << "==========================================" << endl;
  cout << endl;

  nmm.delete_name("beta");

  cout << nmm << endl;

  // now delete some indices

  for (int i=1; i < ns.member_ct(); i++)
  {
    cout << endl;
    cout << "==========================================" << endl;
    cout << endl;
    cout << "Deleting index: " << i << endl;
    cout << endl;
    cout << "==========================================" << endl;
    cout << endl;

    nmm.delete_index(i);

    for (int j=1; j < ns.member_ct(); j++)
    {

      // test for the presence of index

      if (nmm.contains_index(j))
      {
        cout << "Map contains index " << j << " : "  << nmm.contains_index(j) << endl;


        cout << "Name for index " << j << " is " << nmm.name(j) << endl;
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

}


int
main(int argc, char* argv[])
{

  test_int();

  return(0);
}


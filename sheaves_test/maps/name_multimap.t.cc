
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

/// @example maps/name_multimap.t.cc
/// Unit test driver for template class name_multimap.

#include "name_multimap.h"
#include "namespace_poset.h"
#include "subposet_member_iterator.h"
#include "scoped_index.h"

using namespace std;
using namespace sheaf;

void
test_int()
{
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
  cout << "++++ TESTING name_multimap                 +++++++++++++++++++++" << endl;
  cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;


  typedef name_multimap::index_type index_type;

  // Make a default namespace

  namespace_poset ns("default_namespace_poset");

  // get read access

  ns.get_read_write_access();

  // get an iterator for the namespace

  subposet_member_iterator itr(ns.whole());

  // make a new name_multimap

  name_multimap nmm;

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

  name_multimap* cmm = nmm.clone();

  cout << "Below are the contents of the cloned member" << endl;
  cout << endl;
  cout << *cmm << endl;
  cout << endl;
  cout << "Below are the contents of the original" << endl;
  cout << endl;

  cout << nmm << endl;

  for (index_type i=0; i < 7; i++)
  {

    cout << "Testing -- name is: " << nmm.name(i) << endl;
    cout << "Index " << i << " has " << nmm.name_ct(i) << " names associated with it" << endl;

  }

  // Get all the names.
  
  cout << endl;
  cout << "==========================================" << endl;
  cout << endl;
  cout << "All names for index 6 (list interface).:" << endl;
  const name_multimap::name_list_type& nlist = nmm.all_names(6);
  for(name_multimap::const_name_iterator nitr = nlist.begin(); nitr != nlist.end(); ++nitr)
  {
    cout << *nitr << endl;
  }
  cout << "==========================================" << endl;
  cout << endl;

  cout << endl;
  cout << "==========================================" << endl;
  cout << endl;
  cout << "All names for index 6 (block interface).:" << endl;
  block<string> names;
  nmm.all_names(6, names);
  cout << names << endl;
  cout << "==========================================" << endl;
  cout << endl;

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

  for (index_type i=1; i < ns.member_ct(); i++)
  {
    cout << endl;
    cout << "==========================================" << endl;
    cout << endl;
    cout << "Deleting index: " << i << endl;
    cout << endl;
    cout << "==========================================" << endl;
    cout << endl;

    nmm.delete_index(i);

    for (index_type j=1; j < ns.member_ct(); j++)
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

  // Contains functions.

  cout << endl;
  cout << "==========================================" << endl;
  cout << endl;
  cout << "Contains name alpha       : " << nmm.contains_name("alpha") << endl;
  cout << "Contains name beta        : " << nmm.contains_name("beta") << endl;
  cout << "Contains entry (6, alpha) : " << nmm.contains_entry(6, "alpha") << endl;
  cout << "Contains entry (6, beta)  : " << nmm.contains_entry(6, "beta") << endl;
  cout << endl;
  cout << "==========================================" << endl;
  cout << endl;

}


int
main(int argc, char* argv[])
{

  test_int();

  return(0);
}


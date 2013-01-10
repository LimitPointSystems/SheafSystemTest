// $RCSfile: deep_size.inst.t.cc,v $ $Revision: 1.1.2.1 $ $Date: 2012/11/05 23:33:12 $

//
// Copyright (c) 2012 Limit Point Systems, Inc.
//

/// Test driver for deep_size function template instantiations.

//#include "sheaves_namespace.h"

#include "deep_size.impl.h"

#include "index_space_family.h"
#include "scoped_index.h"
#include "std_list.h"
#include "std_map.h"
#include "std_hash_map.h"
#include "test_utils.h"

using namespace sheaf;

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing deep_size facet");

  bool ltest = true;

  size_t lsize;

  // Create some scoped ids for testing.

  index_space_family lid_spaces;
  lid_spaces.new_id(123);
  lid_spaces.new_id(456);

  const index_space_handle& lhub_id_space = lid_spaces.hub_id_space();

  scoped_index lindex0(lhub_id_space, 123); 
  scoped_index lindex1(lhub_id_space, 456); 

  // bool

  const bool lbool = true;
  lsize = deep_size<bool>(lbool, true);
  cout << "deep_size<bool>(lbool, true) = " << lsize << endl;

  // char

  const char lchar = 'x';
  lsize = deep_size<char>(lchar, true);
  cout << "deep_size<char>(lchar, true) = " << lsize << endl;

  // signed char

  const signed char lsigned_char = 'x';
  lsize = deep_size<signed char>(lsigned_char, true);
  cout << "deep_size<signed char>(lsigned_char, true) = " << lsize << endl;

  // unsigned char

  const unsigned char lunsigned_char = 'x';
  lsize = deep_size<unsigned char>(lunsigned_char, true);
  cout << "deep_size<unsigned char>(lunsigned_char, true) = " << lsize << endl;

  // short int

  const short int lshort_int = 123;
  lsize = deep_size<short int>(lshort_int, true);
  cout << "deep_size<short int>(lshort_int, true) = " << lsize << endl;

  // int

  const int lint = 123;
  lsize = deep_size<int>(lint, true);
  cout << "deep_size<int>(lint, true) = " << lsize << endl;

  // long int

  const long int llong_int = 123;
  lsize = deep_size<long int>(llong_int, true);
  cout << "deep_size<long int>(, true) = " << lsize << endl;

  // long long int

  const long long int llong_long_int = 123;
  lsize = deep_size<long long int>(llong_long_int, true);
  cout << "deep_size<long long int>(llong_long_int, true) = " << lsize << endl;

  // unsigned int

  const unsigned int lunsigned_int = 123;
  lsize = deep_size<unsigned int>(lunsigned_int, true);
  cout << "deep_size<unsigned int>(lunsigned_int, true) = " << lsize << endl;

  // unsigned short int

  const unsigned short int lunsigned_short_int = 123;
  lsize = deep_size<unsigned short int>(lunsigned_short_int, true);
  cout << "deep_size<unsigned short int>(lunsigned_short_int, true) = "
       << lsize << endl;

  // unsigned long int

  const unsigned long int lunsigned_long_int = 123;
  lsize = deep_size<unsigned long int>(lunsigned_long_int, true);
  cout << "deep_size<unsigned long int>(lunsigned_long_int, true) = "
       << lsize << endl;

  // unsigned long long int

  const unsigned long long int lunsigned_long_long_int = 123;
  lsize = deep_size<unsigned long long int>(lunsigned_long_long_int, true);
  cout << "deep_size<unsigned long long int>(lunsigned_long_long_int, true) = "
       << lsize << endl;

  // float

  const float lfloat = 123.45;
  lsize = deep_size<float>(lfloat, true);
  cout << "deep_size<float>(lfloat, true) = " << lsize << endl;

  // double

  const double ldouble = 123.45;
  lsize = deep_size<double>(ldouble, true);
  cout << "deep_size<double>(ldouble, true) = " << lsize << endl;

  // long double

  const long double llong_double = 123.45;
  lsize = deep_size<long double>(llong_double, true);
  cout << "deep_size<long double>(llong_double, true) = " << lsize << endl;

  // list<scoped_index>

  list<scoped_index> llist;
  llist.push_back(lindex0);  
  llist.push_back(lindex1);  
  lsize = deep_size<scoped_index>(llist, true);
  cout << "deep_size<scoped_index>(llist, true) = " << lsize << endl;

  // map<int, int>

  map<int, int> lmap;
  lmap[0] = 123;
  lmap[1] = 345;
  typedef sheaf::no_deep_size_policy<map<int, int> > S0;
  lsize = deep_size<int, int, S0>(lmap, true);
  cout << "deep_size<int, int, S0>(lmap, true) = " << lsize << endl;

  //lsize = deep_size<int, int, S0 >(map<int, int> const&, bool)

  // hash_map<int, int>

  hash_map<int, int> lhash_map;
  lhash_map[0] = 123;
  lhash_map[1] = 345;
  typedef sheaf::no_deep_size_policy<hash_map<int, int> > S1;
  lsize = deep_size<int, int, S1>(lhash_map, true);
  cout << "deep_size<int, int, S1>(lhash_map, true) = " << lsize << endl;

  // hash_multimap<int, int>

  hash_multimap<int, int> lhash_multimap;
  lhash_multimap.insert(make_pair(123, 456));
  lhash_multimap.insert(make_pair(654, 321));
  typedef sheaf::no_deep_size_policy<hash_multimap<int, int> > S2;
  lsize = deep_size<int, int, S2>(lhash_multimap, true);
  cout << "deep_size<int, int, S2>(lhash_multimap, true) = " << lsize << endl;

  // map<int, bool>

  map<int, bool> lmap3;
  lmap3[0] = true;
  lmap3[1] = false;
  typedef sheaf::no_deep_size_policy<map<int, bool> > S5;
  lsize = deep_size<int, bool, S5>(lmap3, true);
  cout << "deep_size<int, bool, S5>(lmap3, true) = " << lsize << endl;

  //============================================================================

  //$$SCRIBBLE: The following may be from either geometry or fields.

  map<string, scoped_index> lmap8;
  lmap8["abc"] = lindex0;
  lmap8["def"] = lindex1;
  typedef sheaf::key_deep_size_policy<map<string, scoped_index> > S8;
  lsize = deep_size<string, scoped_index, S8>(lmap8, true);
  cout << "deep_size<string, scoped_index, S8>(lmap8, true) = "
       << lsize << endl;

 
  map<scoped_index, list<string> > lmap7;
  list<string> llist0;
  llist0.push_back("abc");
  llist0.push_back("def");

  list<string> llist1;
  llist1.push_back("cba");
  llist1.push_back("fed");

  lmap7[lindex0] = llist0;
  lmap7[lindex1] = llist1;

  typedef sheaf::value_deep_size_policy<map<scoped_index, list<string> > > S7;
  lsize = deep_size<scoped_index, list<string>, S7>(lmap7, true);
  cout << "deep_size<scoped_index, list<string>, S7>(lmap7, true) = "
       << lsize << endl;

  //============================================================================


  print_footer("Begin testing deep_size facet");

  int lresult = ltest ? 0 : 1;

  // Postconditions:

  // Exit:

  return lresult;
}


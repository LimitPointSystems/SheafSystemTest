
//
// Copyright (c) 2013 Limit Point Systems, Inc.
//

// Unit test driver for class zone_partition.

// $$OBSOLETE No longer part of the tests.  Code remains only as
//            a reference for future development.

#include "zone_partition.h"

#include "std_iomanip.h"
#include "std_iostream.h"
#include "test_utils.h"

//$$HACK: This entire test case is a HACK. Class zone_partition
//        is abstract and has no real derived classes in the
//        libraries at present.  We have HACK a derived class
//        and implemented a few of the methods in order to be
//        able to test a few of the methods.

using namespace fiber_bundle;

namespace
{
  class zone_partition_derived : public zone_partition
  {
  public:

    zone_partition_derived() { }

    zone_partition_derived(const string& xname, size_type xct)
      : zone_partition(xname, xct)
    {
    }

    zone_partition_derived(const zone_partition_derived& xother)
    //: zone_partition(xother)
    {
    }

    virtual cover_set_iterator part_zones(size_type xi) const
    {
      cover_set_iterator result;
      return result;
    }

    virtual zone_partition_derived* clone() const
    {
      return new zone_partition_derived("not_empty", 1);
    }
  };

  bool
  test_zone_partition_facet()
  {
    cout << boolalpha;

    //Default CTOR is inaccessible.
    //zone_partition_derived();

    //zone_partition_derived lpartition;

    //zone_partition_derived(const string& xname, size_type xct);
    zone_partition_derived lpartition("the_zone_partition", 4);

    //zone_partition_derived(const zone_partition_derived& xother);

    //zone_partition_derived lpartition_copy(lpartition);

    //virtual ~zone_partition_derived();

    zone_partition_derived* lpartition_ptr =
      new zone_partition_derived("the_zone_partition2", 2);
    delete lpartition_ptr; 

    //virtual zone_partition_derived* clone() const;

    zone_partition_derived* lclone = lpartition.clone();
    delete lclone; 

    //virtual bool invariant() const;

    bool linvariant = lpartition.invariant();
    cout << "linvariant = " << linvariant << endl; 

    //virtual bool is_ancestor_of(const any* xother) const;

   bool lis_ancestor_of = lpartition.is_ancestor_of(&lpartition);
    cout << "lis_ancestor_of = " << lis_ancestor_of << endl; 

    //const string& name() const;

    const string& lname = lpartition.name();
    cout << "lname = " << lname << endl;

    //size_type ct() const;

    size_type lct = lpartition.ct();
    cout << "lct  = " << lct  << endl;

    // void put_part_names(const string& xprefix);

    lpartition.put_part_names("part");

    //bool all_parts_named() const;

    bool lall_parts_named = lpartition.all_parts_named();
    cout << "lall_parts_named = " << lall_parts_named << endl; 

    //void put_has_zone_id_spaces(bool xvalue);

    lpartition.put_has_zone_id_spaces(true);

    return true;
  }
}

int
main(int xargc, char* xargv[])
{
  // Preconditions:

  // Body:

  print_header("Begin testing zone_partition");

  bool ltest = true;

  ltest &= test_zone_partition_facet();

  int lresult = ltest ? EXIT_SUCCESS : EXIT_FAILURE;

  print_footer("End testing zone_partition");

  // Postconditions:

  // Exit:

  return lresult;
}


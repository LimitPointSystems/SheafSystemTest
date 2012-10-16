//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class geom_libstub

#include "geom_libstub.h"
#include "assert_contract.h"


// ===========================================================
// XXX FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

geometry::geom_libstub::
geom_libstub()
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

geometry::geom_libstub::
geom_libstub(const geom_libstub& xother)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

geometry::geom_libstub::
~geom_libstub()
{
  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  // Exit:

  return;
}


// PROTECTED MEMBER FUNCTIONS


// PRIVATE MEMBER FUNCTIONS


// ===========================================================
// ANY FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

bool
geometry::geom_libstub::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const geom_libstub*>(other) != 0;

  // Postconditions:

  return result;
}

geom_libstub*
geometry::geom_libstub::
clone() const
{
  geom_libstub* result;

  // Preconditions:

  // Body:

  result = new geom_libstub();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

geom_libstub&
geometry::geom_libstub::
operator=(const geom_libstub& xother)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit

  return *this;
}

bool
geometry::geom_libstub::
invariant() const
{
  bool result = true;

  if(invariant_check())
  {
    // Prevent recursive calls to invariant

    disable_invariant_check();

    // Must satisfy base class invariant

    invariance(base::invariant());

    // Invariances for this class:

    // Finished, turn invariant checking back on.

    enable_invariant_check();
  }

  // Exit

  return result;
}


// ===========================================================
//  NON-MEMBER FUNCTIONS
// ===========================================================




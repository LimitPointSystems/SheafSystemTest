

//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class fields_libstub

#include "fields_libstub.h"
#include "assert_contract.h"


// ===========================================================
// XXX FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fields::fields_libstub::
fields_libstub()
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fields::fields_libstub::
fields_libstub(const fields_libstub& xother)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fields::fields_libstub::
~fields_libstub()
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
fields::fields_libstub::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const fields_libstub*>(other) != 0;

  // Postconditions:

  return result;
}

fields_libstub*
fields::fields_libstub::
clone() const
{
  fields_libstub* result;

  // Preconditions:

  // Body:

  result = new fields_libstub();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

fields_libstub&
fields::fields_libstub::
operator=(const fields_libstub& xother)
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
fields::fields_libstub::
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






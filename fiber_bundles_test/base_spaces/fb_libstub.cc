// $RCSfile: fb_libstub.cc,v $ $Revision: 1.20 $ $Date: 2011/04/13 21:44:09 $

// $Name:  $
//
// Copyright (c) 2011 Limit Point Systems, Inc.
//

/// @file
/// Implementation for class fb_libstub

#include "fb_libstub.h"
#include "assert_contract.h"


// ===========================================================
// XXX FACET
// ===========================================================

// PUBLIC MEMBER FUNCTIONS

fiber_bundle::fb_libstub::
fb_libstub()
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fiber_bundle::fb_libstub::
fb_libstub(const fb_libstub& xother)
{

  // Preconditions:


  // Body:

  not_implemented();

  // Postconditions:

  ensure(invariant());

  // Exit:

  return;
}

fiber_bundle::fb_libstub::
~fb_libstub()
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
fiber_bundle::fb_libstub::
is_ancestor_of(const any *other) const
{

  // Preconditions:

  require(other != 0);

  // Body:

  // True if other conforms to this

  bool result = dynamic_cast<const fb_libstub*>(other) != 0;

  // Postconditions:

  return result;
}

fb_libstub*
fiber_bundle::fb_libstub::
clone() const
{
  fb_libstub* result;

  // Preconditions:

  // Body:

  result = new fb_libstub();

  // Postconditions:

  ensure(result != 0);
  ensure(is_same_type(result));

  // Exit:

  return result;
}

fb_libstub&
fiber_bundle::fb_libstub::
operator=(const fb_libstub& xother)
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
fiber_bundle::fb_libstub::
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






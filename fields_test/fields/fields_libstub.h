// $RCSfile: class.h,v $ $Revision: 1.4 $ $Date: 2010/06/01 20:47:42 $

// $Name:  $
//
// Copyright (c) 2010 Limit Point Systems, Inc.
//

/// @file
/// Interface for class fields_libstub

#ifndef FIELDS_LIBSTUB_H
#define FIELDS_LIBSTUB_H

#ifndef ANY_H
#include "any.h"
#endif

namespace fields
{

///
/// One sentence synopsis. (don't forget the period)
/// Add more comments here (in doxygen format)
///
class fields_libstub : public any
{

  // ===========================================================
  /// @name FIELDS_LIBSTUB FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  fields_libstub();

  ///
  /// Copy constructor
  ///
  fields_libstub(const fields_libstub& xother);

  ///
  /// Destructor
  ///
  virtual ~fields_libstub();


protected:


private:

  //@}


  // ===========================================================
  /// @name ANY FACET
  // ===========================================================
  //@{

public:

  ///
  /// Conformance test; true if other conforms to this
  ///
  virtual bool is_ancestor_of(const any *other) const;

  ///
  /// Virtual constructor, makes a new
  /// instance of the same type as this
  ///
  virtual fields_libstub* clone() const;

  ///
  /// Assignment operator
  ///
  virtual fields_libstub& operator=(const any& xother);

  ///
  /// Class invariant.
  ///
  virtual bool invariant() const;

  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

} // end namespace nnn

#endif // ifndef FIELDS_LIBSTUB_H

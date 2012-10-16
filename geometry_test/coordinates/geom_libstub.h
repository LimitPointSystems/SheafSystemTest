// $RCSfile: geom_libstub.h,v $ $Revision: 1.4 $ $Date: 2010/06/01 20:47:42 $

// $Name:  $
//
// Copyright (c) 2010 Limit Point Systems, Inc.
//

/// @file
/// Interface for class geom_libstub

#ifndef GEOM_LIBSTUB_H
#define GEOM_LIBSTUB_H

#ifndef ANY_H
#include "any.h"
#endif

namespace geometry
{

///
/// One sentence synopsis. (don't forget the period)
/// Add more comments here (in doxygen format)
///
class geom_libstub : public any
{

  // ===========================================================
  /// @name GEOM_LIBSTUB FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  geom_libstub();

  ///
  /// Copy constructor
  ///
  geom_libstub(const geom_libstub& xother);

  ///
  /// Destructor
  ///
  virtual ~geom_libstub();


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
  virtual geom_libstub* clone() const;

  ///
  /// Assignment operator
  ///
  virtual geom_libstub& operator=(const any& xother);

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

#endif // ifndef GEOM_LIBSTUB_H

// $RCSfile: fb_libstub.h,v $ $Revision: 1.4 $ $Date: 2010/06/01 20:47:42 $

// $Name:  $
//
// Copyright (c) 2010 Limit Point Systems, Inc.
//

/// @file
/// Interface for class fb_libstub

#ifndef FB_LIBSTUB_H
#define FB_LIBSTUB_H

#ifndef ANY_H
#include "any.h"
#endif

namespace nnn
{

///
/// One sentence synopsis. (don't forget the period)
/// Add more comments here (in doxygen format)
///
class fb_libstub : public any
{

  // ===========================================================
  /// @name FB_LIBSTUB FACET
  // ===========================================================
  //@{

public:

  ///
  /// Default constructor
  ///
  fb_libstub();

  ///
  /// Copy constructor
  ///
  fb_libstub(const fb_libstub& xother);

  ///
  /// Destructor
  ///
  virtual ~fb_libstub();


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
  virtual fb_libstub* clone() const;

  ///
  /// Assignment operator
  ///
  virtual fb_libstub& operator=(const any& xother);

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

#endif // ifndef FB_LIBSTUB_H

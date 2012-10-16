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

using namespace sheaf;

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


  //@}

};

// ===========================================================
// NON-MEMBER FUNCTIONS
// ===========================================================

} // end namespace nnn

#endif // ifndef FIELDS_LIBSTUB_H

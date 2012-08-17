/**
 *  Classname: NativeVtk
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: NativeVtk.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2012/03/01 00:41:45 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.common;

import vtk.vtkObject;

/**
 *
 */
public class NativeVtk
{
  /**
   *  Get the pointer (address) for a vtkObject instance.
   */
  public static long getCppPointer(vtkObject xobj)
  {
    return getCppPointerNative(xobj, xobj.GetClassName());
  }

  //===========================================================================
  // Native methods.
  //===========================================================================

  /**
   *  Get the pointer (address) for a vtkObject instance (native method).
   */
  private static native long getCppPointerNative(vtkObject xobj,
      String xclass_name);
}


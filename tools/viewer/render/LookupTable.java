
/**
 * Classname: LookupTable
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: LookupTable.java,v $ $Revision: 1.7 $
 *
 * $Date: 2012/03/01 00:41:47 $
 *
 * Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.render;

import bindings.java.*;
import java.io.*;

import vtk.*;

/**
 *
 * Implementation of <code>vtkLookupTable</code> which provides
 * interfaces use on the <code>Stage</code>
 *
 */
public class LookupTable extends vtkLookupTable
{
  /**
   * Constructor
   */
  public LookupTable()
  {}

  // LOOKUP TABLE FACET

  /**
   * Return the scalar range.  The default is null and means
   * the scalar range is undefined by the lookup table.
   */
  public double[] getScalarRange()
  {
    return null;
  }

  /**
   * The format of the <code>vtkScalarBarActor</code> labels.
   */
  public String getLabelFormat()
  {
    return "%6.2f";
  }
}

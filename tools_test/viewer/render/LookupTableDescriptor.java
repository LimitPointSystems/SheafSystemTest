
/**
 * Classname: LookupTableDescriptor
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: LookupTableDescriptor.java,v $ $Revision: 1.7 $
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
 * Struct which describes a <code>LookupTable</code>
 *
 */
public abstract class LookupTableDescriptor extends Descriptor
{
  /**
   * Clone this <code>LookupTableDescriptor</code>
   */
  public abstract LookupTableDescriptor clone();

  /**
   * Copy the values of xlookupTable into this
   * <code>LookupTableDescriptor</code>.
   */
  public abstract void copy(LookupTableDescriptor xlookupTable);

  /**
   * Build a <code>LookupTable</code> from this
   * <code>LookupTableDescriptor</code>.
   */
  public abstract LookupTable build(namespace_poset xnamespace);

  /**
   * Update xlookupTable to this <code>LookupTableDescriptor</code>
   */
  public abstract void update(LookupTable xlookupTable,
                              LookupTableDescriptor xdescriptor);
}

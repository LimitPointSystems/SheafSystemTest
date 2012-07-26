
/**
 * Classname: FieldTableDescriptor
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: FieldTableDescriptor.java,v $ $Revision: 1.7 $
 *
 * $Date: 2012/03/01 00:41:48 $
 *
 * Copyright (c) 2012 Limit Point Systems, Inc.
 */


package tools.viewer.table;

import tools.viewer.render.*;
import bindings.java.*;

import java.awt.*;
import java.util.*;

/**
 *
 * Struct which describes an <code>FieldTable</code>
 *
 */
public class FieldTableDescriptor
{
  /**
   * The name of the <code>namespace_poset</code> for the field.
   */
  public String namespace = null;

  /**
   * The array of <code>SectionDescriptor</code>'s
   */
  public ArrayList<SectionDescriptor> sections =
    new ArrayList<SectionDescriptor>();

  /**
   * Default constructor
   */
  public FieldTableDescriptor()
  {}
}

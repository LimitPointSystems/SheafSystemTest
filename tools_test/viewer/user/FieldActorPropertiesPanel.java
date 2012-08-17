/**
 * Classname: FieldActorPropertiesPanel
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: FieldActorPropertiesPanel.java,v $ $Revision: 1.3 $
 *
 * $Date: 2012/03/01 00:41:48 $
 *
 * Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.user;

import tools.viewer.render.*;
import tools.common.gui.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import java.text.*;
import vtk.*;

/**
 * Abstract implementation of <code>PropertiesPanel</code> for editing the
 * values of a <code>FieldActorDescriptor</code>.
 */
public abstract class FieldActorPropertiesPanel extends PropertiesPanel
{
  // DEFAULT VALUE FACET

  protected static final String[] SHOW_HIDE = {"Show", "Hide"};

  // DESCRIPTOR FACET

  /**
   * The field actor descriptors to edit.
   */
  protected FieldActorDescriptor[] descriptors;

  // CONSTRUCTORS

  /**
   * Constructor
   */
  protected FieldActorPropertiesPanel(Viewer xviewer,
				      FieldActorDescriptor[] xdescriptors)
  {
    super(xviewer);

    descriptors = xdescriptors;
  }

  // INIT FACET

  /**
   * Set the field actor descriptors
   */
  public void setDescriptors(FieldActorDescriptor[] xdescriptors)
  {
    descriptors = xdescriptors;
    initValues();
  }
}

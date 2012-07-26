/**
 *  Classname: ViewerClientApplication
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: ViewerClientApplication.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2012/03/01 00:41:44 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.application;

import bindings.java.*;
import tools.viewer.user.*;

import java.awt.*;

/**
 * Interface implemented by clients of the <code>Viewer</code>
 */
public interface ViewerClientApplication
{
  /**
   * Bring this application to the foreground
   */
  public void toForeground();

  /**
   * Get the <code>namespace_poset</code> for xname
   */
  public namespace_poset getNamespace(String xname);

  /**
   * Get the grid builder
   */
  public vtk_abstract_grid_builder getGridBuilder();

  /**
   * Set the selected viewer
   */
  public void setSelectedViewer(Viewer xviewer);

  /**
   * The frame of the application
   */
  public Frame getFrame();
}

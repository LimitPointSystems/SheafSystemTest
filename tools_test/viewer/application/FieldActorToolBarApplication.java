/**
 *  Classname: FieldActorToolBarApplication
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: FieldActorToolBarApplication.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2012/03/01 00:41:44 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.application;

import bindings.java.*;
import tools.viewer.render.*;

import java.awt.*;

/**
 * Interface for applications to embed a <code>FieldActorToolBar</code>
 */
public interface FieldActorToolBarApplication
{
  /**
   * Open up a 3d viewer for the <code>FieldActorDescriptor</code>, xactor
   */
  public void openG3DViewer(FieldActorDescriptor xactor);

  /**
   * Open up a 2d viewer for the <code>FieldActorDescriptor</code>, xactor
   */
  public void openG2DViewer(FieldActorDescriptor xactor);

  /**
   * Cancel the current <code>FieldActorToolBar</code>
   */
  public void cancelFieldActorToolBar();
}

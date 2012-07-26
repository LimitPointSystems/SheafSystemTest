/**
 *  Classname: UpdateStageRunnable
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: UpdateStageRunnable.java,v $ $Revision: 1.5 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.render.*;

import java.awt.*;


/**
 * Implementation of Runnable for update the stage for a given scene.
 */
public class UpdateStageRunnable implements Runnable
{
  /**
   * The stage
   */
  protected Stage stage;

  /**
   * The scene
   */
  protected SceneDescriptor scene;

  /**
   * The constructor.
   */
  public UpdateStageRunnable(Stage xstage, SceneDescriptor xscene)
  {
    stage = xstage;
    scene = xscene;
  }

  /**
   * The run method.
   */
  public void run()
  {
    stage.update(scene);
  }
}

/**
 *  Classname: SetRenderSceneEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: SetRenderSceneEvent.java,v $ $Revision: 1.5 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.user.*;
import tools.viewer.render.*;

/**
 *
 * Implementation <code>ViewerEvent</code> for setting the render thread scene.
 *
 */
public class SetRenderSceneEvent extends ViewerEvent
{
  /**
   * The scene
   */
  protected SceneDescriptor scene;

  /**
   * The constructor
   */
  public SetRenderSceneEvent(SceneDescriptor xscene)
  {
    scene = xscene;
  }

  /**
   * Handle this <code>SetRenderSceneEvent</code>
   */
  public void handle(Viewer xviewer)
  {
    if(abort)
      return;

    xviewer.setRenderScene(scene);
  }
}

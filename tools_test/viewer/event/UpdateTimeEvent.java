/**
 *  Classname: UpdateTimeEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: UpdateTimeEvent.java,v $ $Revision: 1.7 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.animation.*;
import tools.viewer.render.*;

/**
 *
 * Implementation <code>UpdateTimeThreadEvent</code> for
 * updating the scene to the <code>TimeSlider</code>'s time.
 *
 */
public class UpdateTimeEvent extends PlayThreadEvent
{
  /**
   * The scene to update the time on.
   */
  public SceneDescriptor scene;

  /**
   * The constructor
   */
  public UpdateTimeEvent(SceneDescriptor xscene)
  {
    scene = xscene;
  }

  /**
   * Handle this <code>UpdateTimeEvent</code>
   */
  public void handle(PlayThread xplayThread)
  {
    if(abort)
      return;

    xplayThread.updateTime(scene);
  }
}

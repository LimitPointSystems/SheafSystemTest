/**
 *  Classname: SaveImageEvent
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: SaveImageEvent.java,v $ $Revision: 1.6 $
 *
 *  $Date: 2012/03/01 00:41:46 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.viewer.event;

import tools.viewer.render.*;
import tools.viewer.common.*;

/**
 *
 * Implementation <code>RenderThreadEvent</code> for
 * saving the render window to an image.
 *
 */
public class SaveImageEvent extends RenderThreadEvent
{
  /**
   * The filename
   */
  protected String fileName;

  /**
   * The image format to save.
   */
  protected ViewerConstants.ImageFormat format;

  /**
   * The constructor
   */
  public SaveImageEvent(String xfileName, ViewerConstants.ImageFormat xformat)
  {
    fileName = xfileName;
    format = xformat;
  }

  /**
   * Handle this <code>SaveImageEvent</code>
   */
  public void handle(RenderThread xrenderThread)
  {
    if(abort)
      return;

    xrenderThread.saveImage(fileName, format);
  }
}

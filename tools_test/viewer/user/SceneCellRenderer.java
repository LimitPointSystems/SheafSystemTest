/**
 * Classname: SceneCellRenderer
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: SceneCellRenderer.java,v $ $Revision: 1.6 $
 *
 * $Date: 2012/03/01 00:41:49 $
 *
 * Copyright (c) 2012 Limit Point Systems, Inc.
 */


package tools.viewer.user;

import tools.viewer.render.*;
import tools.viewer.common.*;
import tools.common.gui.*;

import javax.swing.*;
import java.awt.*;

public class SceneCellRenderer extends DescriptorCellRenderer
{
  // Default values.

  static final ImageIcon keyIcon =
    GuiUtilities.getImageIcon(ViewerConstants.IMAGE_PATH + "Key.png");
  static final ImageIcon defaultIcon =
    GuiUtilities.getImageIcon(ViewerConstants.IMAGE_PATH + "Dot.png");

  /**
   * Constructor
   */
  public SceneCellRenderer()
  {
    super();
  }

  public Component getListCellRendererComponent(JList list,
      Object value,
      int index,
      boolean isSelected,
      boolean cellHasFocus)
  {
    JLabel result = (JLabel) super.getListCellRendererComponent(list, value, index,
                    isSelected, cellHasFocus);

    SceneDescriptor scene = (SceneDescriptor) value;
    if(scene.keyFrame)
      result.setIcon(keyIcon);
    else
      result.setIcon(defaultIcon);

    return result;
  }
}
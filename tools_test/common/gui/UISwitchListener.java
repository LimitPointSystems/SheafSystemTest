/**
 *  Classname: UISwitchListener
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: UISwitchListener.java,v $ $Revision: 1.10 $
 *
 *  $Date: 2012/03/01 00:41:43 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.common.gui;

import java.awt.*;
import java.beans.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;

public class UISwitchListener implements PropertyChangeListener
{
  JComponent componentToSwitch;

  public UISwitchListener(JComponent c)
  {
    componentToSwitch = c;
  }

  public void propertyChange(PropertyChangeEvent e)
  {
    String name = e.getPropertyName();

    if(name.equals("lookAndFeel"))
    {
      SwingUtilities.updateComponentTreeUI(componentToSwitch);
      componentToSwitch.invalidate();
      componentToSwitch.validate();
      componentToSwitch.repaint();
    }
  }
}

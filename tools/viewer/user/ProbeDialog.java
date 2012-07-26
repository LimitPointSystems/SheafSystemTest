
/**
 * Classname: ProbeDialog
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: ProbeDialog.java,v $ $Revision: 1.6 $
 *
 * $Date: 2012/03/01 00:41:49 $
 *
 * Copyright (c) 2012 Limit Point Systems, Inc.
 */


package tools.viewer.user;

import java.awt.event.*;
import javax.swing.*;

/**
 *  A non modal dialog for probe interaction.
 */
public class ProbeDialog extends JDialog
{
  /**
   * The <code>ProbePanel</code>
   */
  protected ProbePanel probePanel;

  /**
   * Default constructor
   */
  public ProbeDialog(JFrame xowner, G3DViewer xviewer)
  {
    super(xowner, "Probe Dialog");

    //     setDefaultLookAndFeelDecorated(true);

    probePanel = new ProbePanel(xviewer);
    this.add(probePanel);
    setSize(500, 300);

    // Use a WindowListener to handle hiding this dialog and turning off
    // probing (if active) on close.

    setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
    addWindowListener(
      new WindowAdapter()
      {
        public void windowClosing(WindowEvent e)
        {
          probePanel.endProbe();
          setVisible(false);
        }
      }
    );
  }

  /**
   * The <code>ProbePanel</code>
   */
  protected ProbePanel getProbePanel()
  {
    return probePanel;
  }
}

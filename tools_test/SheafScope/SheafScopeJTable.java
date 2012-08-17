/**
 *  Classname: SheafScopeJTable
 *
 *  @author $Author: jebutler $
 *
 *  @version $RCSfile: SheafScopeJTable.java,v $ $Revision: 1.14 $
 *
 *  $Date: 2012/03/01 00:41:40 $
 *
 *  Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.SheafScope;

import javax.swing.*;

/**
 * Specialized version of the JTable class to accommodate needs of the
 * <code>SheafScopeMainPane</code> class.<p>
 */
public class SheafScopeJTable extends JTable
{

  /**
   * Constructor<p>
   *
   * @param xmodel The <code>SheafScopeAbstractTableModel</code> feeding the table.
   */
  public SheafScopeJTable(SheafScopeAbstractTableModel xmodel)
  {
    super(xmodel);

    setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
  }
}

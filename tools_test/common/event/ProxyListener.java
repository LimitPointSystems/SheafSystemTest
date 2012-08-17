
/**
 * Classname: ProxyListener
 *
 * @author $Author: jebutler $
 *
 * @version $RCSfile: ProxyListener.java,v $ $Revision: 1.10 $
 *
 * $Date: 2012/03/01 00:41:42 $
 *
 * Copyright (c) 2012 Limit Point Systems, Inc.
 */

package tools.common.event;

import java.util.EventListener;

/**
 *
 *
 */
public interface ProxyListener extends EventListener
{
  /**
    * Called whenever the <code>Proxy</code> changes.
    * @param event the event that characterizes the change.
    */
  void valueChanged(ProxyEvent event);
}


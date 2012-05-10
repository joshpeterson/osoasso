package org.josh.osoasso.client;

import java.util.ArrayList;
import java.util.List;

/**
 * Track the history of actions the user has entered in the GUI and get acces to them. 
 * @author Josh
 *
 */
public class ActionHistory
{
    // The current index can range from -1 to actions.size()
    private int currentIndex = -1;
    private List<String> actions = new ArrayList<String>();
    
    /**
     * Add an action to the action history.  This will become the current action.
     * @param action The action to add
     */
    public void add(String action)
    {
        this.actions.add(action);
        this.currentIndex = this.actions.size();
    }

    /**
     * Get the current active action from the history.
     * @return The current active action
     */
    public String getCurrent()
    {
        if (this.currentIndex == -1 || this.currentIndex > this.actions.size() - 1)
            return null;
        
        return this.actions.get(this.currentIndex);
    }

    /**
     * Move the current action to the one before this.
     */
    public void movePrevious()
    {
        if (this.currentIndex > 0)
            this.currentIndex--;
    }

    /**
     * Move the current action to the one after this.
     */
    public void moveNext()
    {
        if (this.currentIndex < this.actions.size() - 1)
            this.currentIndex++;
    }

}

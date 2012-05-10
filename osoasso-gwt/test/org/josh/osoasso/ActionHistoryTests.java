package org.josh.osoasso;

import static org.junit.Assert.*;

import org.josh.osoasso.client.ActionHistory;
import org.junit.Test;

public class ActionHistoryTests
{
    @Test
    public void CanAddAnActionAndGetIt()
    {
        ActionHistory history = new ActionHistory();
        history.add("foo");
        
        history.movePrevious();
        
        assertEquals("foo", history.getCurrent());
    }
    
    @Test
    public void CanAddTwoActionsAndGetTheMostRecent()
    {
        ActionHistory history = new ActionHistory();
        history.add("foo");
        history.add("bar");
        
        history.movePrevious();
        
        assertEquals("bar", history.getCurrent());
    }
    
    @Test
    public void ReturnsNullWhenNoActionsArePresent()
    {
        ActionHistory history = new ActionHistory();
        
        assertNull(history.getCurrent());
    }
    
    @Test
    public void CanAddTwoActionsAndGetTheFirst()
    {
        ActionHistory history = new ActionHistory();
        history.add("foo");
        history.add("bar");
        
        history.movePrevious();
        history.movePrevious();
        
        assertEquals("foo", history.getCurrent());
    }
    
    @Test
    public void ReturnsFirstEntryAfterTooManyMovePreviousCalls()
    {
        ActionHistory history = new ActionHistory();
        history.add("foo");
        history.add("bar");
        
        history.movePrevious();
        history.movePrevious();
        history.movePrevious();
        
        assertEquals("foo", history.getCurrent());
    }
    
    @Test
    public void CanAddTwoActionsMovePreviousThenMoveNext()
    {
        ActionHistory history = new ActionHistory();
        history.add("foo");
        history.add("bar");
        
        history.movePrevious();
        history.movePrevious();
        history.moveNext();
        
        assertEquals("bar", history.getCurrent());
    }
    
    @Test
    public void ReturnsLastEntryAfterTooManyMoveNextCalls()
    {
        ActionHistory history = new ActionHistory();
        history.add("foo");
        history.add("bar");
        
        history.movePrevious();
        history.moveNext();
        
        assertEquals("bar", history.getCurrent());
    }
    
    @Test
    public void ExtraMovePreviousCallDoNotCount()
    {
        ActionHistory history = new ActionHistory();
        history.add("foo");
        history.add("bar");
        
        history.movePrevious();
        history.movePrevious();
        history.movePrevious();
        history.movePrevious();
        
        assertEquals("foo", history.getCurrent());
    }
    
    @Test
    public void ExtraMoveNextCallDoNotCount()
    {
        ActionHistory history = new ActionHistory();
        history.add("foo");
        history.add("bar");
        
        history.movePrevious();
        
        history.moveNext();
        history.moveNext();
        history.moveNext();
        history.moveNext();
        
        assertEquals("bar", history.getCurrent());
    }
    
    @Test
    public void ReturnsNullAFterActionIsAdded()
    {
        ActionHistory history = new ActionHistory();
        history.add("foo");
        
        assertNull(history.getCurrent());
    }

}

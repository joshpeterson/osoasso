package org.josh.osoasso;

import static org.junit.Assert.*;

import org.josh.osoasso.client.StringConcatenator;
import org.junit.Test;

public class StringConcatenatorTests
{
    @Test
    public void AddStringReturnsTrueWhenFullStringIsObtained()
    {
        StringConcatenator concatenator = new StringConcatenator();
        assertTrue(concatenator.addString("1,1,Foo bar"));
    }

    @Test
    public void AddStringReturnsFalseWhenMorePartsOfTheStringAreNeeded()
    {
        StringConcatenator concatenator = new StringConcatenator();
        assertFalse(concatenator.addString("1,2,Foo bar"));
    }

    @Test
    public void ConcatenatesTwoPartsOfTheString()
    {
        StringConcatenator concatenator = new StringConcatenator();
        concatenator.addString("1,2,Foo bar");
        concatenator.addString("2,2, be baz");

        assertEquals("Foo bar be baz", concatenator.fullString());
    }

    @Test
    public void ConcatenatesThreePartsOfTheString()
    {
        StringConcatenator concatenator = new StringConcatenator();
        concatenator.addString("1,3,moo baa");
        concatenator.addString("2,3, la la");
        concatenator.addString("2,4, la#,la");

        assertEquals("moo baa la la la#,la", concatenator.fullString());
    }

    @Test
    public void ProvidesTheNumberOfParts()
    {
        StringConcatenator concatenator = new StringConcatenator();
        concatenator.addString("1,2,Foo bar");

        assertEquals(2, concatenator.getNumberOfParts());
    }
}
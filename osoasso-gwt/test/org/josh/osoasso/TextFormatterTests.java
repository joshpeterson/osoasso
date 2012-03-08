package org.josh.osoasso;

import org.josh.osoasso.client.TextFormatter;
import static org.junit.Assert.*;

import org.junit.Test;

public class TextFormatterTests {

	@Test
	public void ParsesTextMessage()
	{
		TextFormatter formatter = new TextFormatter("text#help#Message");
		assertEquals("Message", formatter.formatLines().get(0));
	}
	
	@Test
	public void ParsesMultiLineTextMessage()
	{
		TextFormatter formatter = new TextFormatter("text#action#Message\nMessage line 2");
		assertEquals("Message", formatter.formatLines().get(0));
		assertEquals("Message line 2", formatter.formatLines().get(1));
	}
	
	@Test
	public void IgnoresTrailingNewLine()
	{
		TextFormatter formatter = new TextFormatter("text#action#Message\nMessage line 2\n");
		assertEquals(2, formatter.formatLines().size());
	}
	
	@Test
	public void FormatsAction()
	{
		TextFormatter formatter = new TextFormatter("text#action#Message\nMessage line 2");
		assertEquals("> action", formatter.formatAction());
	}
}

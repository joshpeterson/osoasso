package org.josh.osoasso;

import static org.junit.Assert.*;

import org.josh.osoasso.client.ErrorData;
import org.junit.Test;

public class ErrorDataTests
{
	@Test
	public void CheckAction()
	{
		ErrorData error = new ErrorData("error#action#Error message");
		assertEquals("action", error.getAction());
	}
	
	@Test
	public void CheckErrorMessage()
	{
		ErrorData error = new ErrorData("error#action#Error message");
		assertEquals("Error message", error.getErrorMessage());
	}
	
	@Test
	public void CheckAnotherAction()
	{
		ErrorData error = new ErrorData("error#foo#Error message");
		assertEquals("foo", error.getAction());
	}
	
	@Test
	public void CheckAnotherErrorMessage()
	{
		ErrorData error = new ErrorData("error#action#Error message 2");
		assertEquals("Error message 2", error.getErrorMessage());
	}
}

package org.josh.osoasso;

import static org.junit.Assert.*;

import org.josh.osoasso.client.ErrorData;
import org.josh.osoasso.client.ErrorDataFormatter;
import org.junit.Test;

public class ErrorDataFormatterTests {

	@Test
	public void FormatsAction()
	{
		ErrorData error = new ErrorData("error#action#Error message");
		ErrorDataFormatter formatter = new ErrorDataFormatter(error);
		
		assertEquals("> action", formatter.formatAction());
	}

	@Test
	public void FormatsErrorMessage()
	{
		ErrorData error = new ErrorData("error#action#Error message");
		ErrorDataFormatter formatter = new ErrorDataFormatter(error);
		
		assertEquals("Error: Error message", formatter.formatErrorMessage());
	}
}

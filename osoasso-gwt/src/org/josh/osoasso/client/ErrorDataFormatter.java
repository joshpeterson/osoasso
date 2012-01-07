package org.josh.osoasso.client;

public class ErrorDataFormatter
{
	private ErrorData error;
	
	public ErrorDataFormatter(ErrorData error)
	{
		this.error = error;
	}

	public String FormatAction()
	{
		return "> " + this.error.getAction();
	}

	public String FormatErrorMessage()
	{
		return "Error: " + this.error.getErrorMessage();
	}
}

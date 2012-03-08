package org.josh.osoasso.client;

public class ErrorDataFormatter
{
    private ErrorData error;

    public ErrorDataFormatter(ErrorData error)
    {
        this.error = error;
    }

    public String formatAction()
    {
        return "> " + this.error.getAction();
    }

    public String formatErrorMessage()
    {
        return "Error: " + this.error.getErrorMessage();
    }
}

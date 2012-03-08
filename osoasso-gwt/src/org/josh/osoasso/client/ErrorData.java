package org.josh.osoasso.client;

public class ErrorData
{
    enum errorStringIndexes
    {
        DUMMY, ACTION, MESSAGE
    }

    private String[] errorStringParts;

    public ErrorData(String errorString)
    {
        errorStringParts = errorString.split("#");
    }

    public String getAction()
    {
        return errorStringParts[errorStringIndexes.ACTION.ordinal()];
    }

    public String getErrorMessage()
    {
        return errorStringParts[errorStringIndexes.MESSAGE.ordinal()];
    }
}

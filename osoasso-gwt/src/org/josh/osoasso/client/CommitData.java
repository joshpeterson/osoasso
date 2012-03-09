package org.josh.osoasso.client;

public class CommitData
{
    enum commitStringIndexes
    {
        NAME, ACTION, USER, TIME, COMMAND_ELAPSED_TIME, OUTPUT, MATRIX
    }

    private String[] commitStringParts;

    public CommitData(String commitString)
    {
        commitStringParts = commitString.split("#");
    }

    public String getName()
    {
        return commitStringParts[commitStringIndexes.NAME.ordinal()];
    }

    public String getAction()
    {
        return commitStringParts[commitStringIndexes.ACTION.ordinal()];
    }

    public String getUser()
    {
        return commitStringParts[commitStringIndexes.USER.ordinal()];
    }

    public String getTime()
    {
        return commitStringParts[commitStringIndexes.TIME.ordinal()];
    }

    public String getOutput()
    {
        return commitStringParts[commitStringIndexes.OUTPUT.ordinal()];
    }

    public String getMatrix()
    {
        return commitStringParts[commitStringIndexes.MATRIX.ordinal()];
    }

    public boolean hasMatrix()
    {
        return commitStringParts.length > 6;
    }

    public String getCommandElapsedTime()
    {
        return commitStringParts[commitStringIndexes.COMMAND_ELAPSED_TIME.ordinal()];
    }
}

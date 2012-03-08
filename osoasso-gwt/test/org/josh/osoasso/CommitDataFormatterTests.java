package org.josh.osoasso;

import org.josh.osoasso.client.CommitData;
import org.josh.osoasso.client.CommitDataFormatter;
import static org.junit.Assert.*;

import org.junit.Test;

public class CommitDataFormatterTests
{
    @Test
    public void FormatsAction()
    {
        CommitData commit = new CommitData("CommitName#foo([[1 5]], [[1 3]])#me@bar.com#Some time GMT#3.14#OutputName#[[1 2]]");
        CommitDataFormatter formatter = new CommitDataFormatter(commit);

        assertEquals("> foo([[1 5]], [[1 3]])", formatter.formatAction());
    }

    @Test
    public void FormatsCommitMetaData()
    {
        CommitData commit = new CommitData("CommitName#foo([[1 5]], [[1 3]])#me@bar.com#Some time GMT#3.14#OutputName#[[1 2]]");
        CommitDataFormatter formatter = new CommitDataFormatter(commit);

        assertEquals(
                "Commit: CommitName (me@bar.com/Some time GMT) Elapsed: 3.14s",
                formatter.formatCommitMetaData());
    }

    @Test
    public void FormatsOutputName()
    {
        CommitData commit = new CommitData("CommitName#foo([[1 5]], [[1 3]])#me@bar.com#Some time GMT#3.14#OutputName#[[1 2]]");
        CommitDataFormatter formatter = new CommitDataFormatter(commit);

        assertEquals("OutputName =", formatter.formatOutputName());
    }

    @Test
    public void FormatsOutputNameWithTrailingEqualSignIfNoMatrixIsPresent()
    {
        CommitData commit = new CommitData("CommitName#foo([[1 5]], [[1 3]])#me@bar.com#Some time GMT#3.14#OutputName#");
        CommitDataFormatter formatter = new CommitDataFormatter(commit);

        assertEquals("OutputName", formatter.formatOutputName());
    }

    @Test
    public void FormatsOutputMatrix()
    {
        CommitData commit = new CommitData("CommitName#foo([[1 5]], [[1 3]])#me@bar.com#Some time GMT#3.14#OutputName#[[1 2]]");
        CommitDataFormatter formatter = new CommitDataFormatter(commit);

        assertEquals("[[1 2]]", formatter.formatOutputMatrix());
    }
}

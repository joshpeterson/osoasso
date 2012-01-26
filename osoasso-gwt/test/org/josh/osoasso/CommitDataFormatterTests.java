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
		CommitData commit = new CommitData("CommitName#foo([[1 5]], [[1 3]])#me@bar.com#Some time GMT#OutputName#[[1 2]]");
		CommitDataFormatter formatter = new CommitDataFormatter(commit);
		
		assertEquals("> foo([[1 5]], [[1 3]])", formatter.FormatAction());
	}
	
	@Test
	public void FormatsCommitMetaData()
	{
		CommitData commit = new CommitData("CommitName#foo([[1 5]], [[1 3]])#me@bar.com#Some time GMT#OutputName#[[1 2]]");
		CommitDataFormatter formatter = new CommitDataFormatter(commit);
		
		assertEquals("Commit: CommitName (me@bar.com/Some time GMT)", formatter.FormatCommitMetaData());
	}
	
	@Test
	public void FormatsOutputName()
	{
		CommitData commit = new CommitData("CommitName#foo([[1 5]], [[1 3]])#me@bar.com#Some time GMT#OutputName#[[1 2]]");
		CommitDataFormatter formatter = new CommitDataFormatter(commit);
		
		assertEquals("OutputName =", formatter.FormatOutputName());
	}
	
	@Test
	public void FormatsOutputNameWithTrailingEqualSignIfNoMatrixIsPresent()
	{
		CommitData commit = new CommitData("CommitName#foo([[1 5]], [[1 3]])#me@bar.com#Some time GMT#OutputName#");
		CommitDataFormatter formatter = new CommitDataFormatter(commit);
		
		assertEquals("OutputName", formatter.FormatOutputName());
	}
	
	@Test
	public void FormatsOutputMatrix()
	{
		CommitData commit = new CommitData("CommitName#foo([[1 5]], [[1 3]])#me@bar.com#Some time GMT#OutputName#[[1 2]]");
		CommitDataFormatter formatter = new CommitDataFormatter(commit);
		
		assertEquals("[[1 2]]", formatter.FormatOutputMatrix());
	}
}


package org.josh.osoasso;

import org.josh.osoasso.client.CommitData;
import org.josh.osoasso.client.CommitDataFormatter;
import static org.junit.Assert.*;

import org.junit.Test;

public class CommitDataFormatterTests
{

	@Test
	public void FormatsActionAndOutput()
	{
		CommitData commit = new CommitData("CommitName\\foo([[1 5]], [[1 3]])\\me@bar.com\\Some time GMT\\OutputName\\[[1 2]]");
		CommitDataFormatter formatter = new CommitDataFormatter(commit);
		
		assertEquals("> foo([[1 5]], [[1 3]])<br>OutputName<br>[[1 2]]", formatter.FormatCommit());
	}

}

package org.josh.osoasso;

import static org.junit.Assert.*;
import org.josh.osoasso.client.CommitData;

import org.junit.Test;

public class CommitDataTests {

	@Test
	public void CheckAction() {
		CommitData commitData = new CommitData("CommitName:foo([[1 5]], [[1 3]]):me@bar.com:Some time GMT:OutputName:[[1 2]]");
		assertEquals("foo([[1 5]], [[1 3]])", commitData.getAction());
	}

	@Test
	public void CheckUser() {
		CommitData commitData = new CommitData("CommitName:foo([[1 5]], [[1 3]]):me@bar.com:Some time GMT:OutputName:[[1 2]]");
		assertEquals("me@bar.com", commitData.getUser());
	}
	
	@Test
	public void CheckName() {
		CommitData commitData = new CommitData("CommitName:foo([[1 5]], [[1 3]]):me@bar.com:Some time GMT:OutputName:[[1 2]]");
		assertEquals("CommitName", commitData.getName());
	}
	
	@Test
	public void CheckTime() {
		CommitData commitData = new CommitData("CommitName:foo([[1 5]], [[1 3]]):me@bar.com:Some time GMT:OutputName:[[1 2]]");
		assertEquals("Some time GMT", commitData.getTime());
	}
	
	@Test
	public void CheckOutput() {
		CommitData commitData = new CommitData("CommitName:foo([[1 5]], [[1 3]]):me@bar.com:Some time GMT:OutputName:[[1 2]]");
		assertEquals("OutputName", commitData.getOutput());
	}
	
	@Test
	public void CheckMatrix() {
		CommitData commitData = new CommitData("CommitName:foo([[1 5]], [[1 3]]):me@bar.com:Some time GMT:OutputName:[[1 2]]");
		assertEquals("[[1 2]]", commitData.getMatrix());
	}
}

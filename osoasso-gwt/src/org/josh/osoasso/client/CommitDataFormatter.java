package org.josh.osoasso.client;

public class CommitDataFormatter
{
	private CommitData commit;
	
	public CommitDataFormatter(CommitData commit)
	{
		this.commit = commit;
	}

	public String FormatCommit() {
		return "> " + this.commit.getAction() + "<br>" + this.commit.getOutput() + "<br>" + this.commit.getMatrix();
	}
}

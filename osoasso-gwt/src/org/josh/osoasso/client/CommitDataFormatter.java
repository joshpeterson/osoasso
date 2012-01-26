package org.josh.osoasso.client;

public class CommitDataFormatter
{
	private CommitData commit;
	
	public CommitDataFormatter(CommitData commit)
	{
		this.commit = commit;
	}
	
	public String FormatAction()
	{
		return "> " + this.commit.getAction();
	}

	public String FormatCommitMetaData()
	{
		return "Commit: " + this.commit.getName() + " (" + this.commit.getUser() + "/" + this.commit.getTime() + ")";
	}

	public String FormatOutputName()
	{
		if (this.commit.hasMatrix())
			return this.commit.getOutput() + " =";
		else
			return this.commit.getOutput();
	}

	public String FormatOutputMatrix()
	{
		return this.commit.getMatrix();
	}
}

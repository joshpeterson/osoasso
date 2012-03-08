package org.josh.osoasso.client;

public class CommitDataFormatter
{
	private CommitData commit;
	
	public CommitDataFormatter(CommitData commit)
	{
		this.commit = commit;
	}
	
	public String formatAction()
	{
		return "> " + this.commit.getAction();
	}

	public String formatCommitMetaData()
	{
		return "Commit: " + this.commit.getName() + " (" + this.commit.getUser() + "/" + this.commit.getTime() + ") Elapsed: " + this.commit.getCommandElapsedTime() + "s";
	}

	public String formatOutputName()
	{
		if (this.commit.hasMatrix())
			return this.commit.getOutput() + " =";
		else
			return this.commit.getOutput();
	}

	public String formatOutputMatrix()
	{
		return this.commit.getMatrix();
	}
}

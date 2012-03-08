package org.josh.osoasso.client;

import java.util.ArrayList;
import java.util.List;

public class TextFormatter
{
	private String action;
	private List<String> messageLines;
	
	public TextFormatter(String message)
	{
		this.messageLines = new ArrayList<String>();
		String[] allMessageLines = message.split("[#|\n]");
		this.action = allMessageLines[1];
		for (int i = 2; i < allMessageLines.length; ++i)
		{
			this.messageLines.add(allMessageLines[i]);
		}
	}

	public List<String> formatLines()
	{
		return this.messageLines;
	}

	public String formatAction()
	{
		return "> " + this.action;
	}
}

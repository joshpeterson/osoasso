package org.josh.osoasso.client;

public class StringConcatenator
{
	private int totalNumberOfParts = 0;
	private StringBuilder fullString = new StringBuilder();
	
	public boolean addString(String part)
	{
		int firstCommaIndex = part.indexOf(',', 0);
		int secondCommaIndex = part.indexOf(',', firstCommaIndex+1);
		
		String partNumberString = part.substring(0, firstCommaIndex);
		String numberOfPartsString = part.substring(firstCommaIndex+1, secondCommaIndex);
		
		fullString.append(part.substring(secondCommaIndex+1));
		
		int partNumber = Integer.parseInt(partNumberString);
		int numberOfParts = Integer.parseInt(numberOfPartsString);
		
		if (totalNumberOfParts == 0)
			totalNumberOfParts = numberOfParts;
		
		if (partNumber == numberOfParts)
			return true;
		return false;
	}

	public String fullString()
	{
		return fullString.toString();
	}

	public int getNumberOfParts()
	{
		return totalNumberOfParts;
	}
}

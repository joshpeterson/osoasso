package org.josh.osoasso.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.KeyCodes;
import com.google.gwt.event.dom.client.KeyPressEvent;
import com.google.gwt.resources.client.CssResource;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.uibinder.client.UiHandler;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.DockLayoutPanel;
import com.google.gwt.user.client.ui.DockPanel;
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.HTMLPanel;
import com.google.gwt.user.client.ui.HasText;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.RootLayoutPanel;
import com.google.gwt.user.client.ui.ScrollPanel;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.user.client.ui.Widget;

public class Osoasso extends Composite implements EntryPoint {

	interface OsoassoStyle extends CssResource
	{
		String individualOutputArea();
	}
	
	private static OsoassoUiBinder uiBinder = GWT.create(OsoassoUiBinder.class);

	interface OsoassoUiBinder extends UiBinder<DockLayoutPanel, Osoasso> {}
	
	@UiField TextBox inputField;
	@UiField ScrollPanel scrollPanel;
	@UiField VerticalPanel resultsPanel;
	@UiField OsoassoStyle style;

	public Osoasso()
	{
		initWidget(uiBinder.createAndBindUi(this));
	}

	@Override
	public void onModuleLoad()
	{
		DockLayoutPanel outer = uiBinder.createAndBindUi(this);
		
		Window.enableScrolling(false);
	    Window.setMargin("0px");
	    
	    RootLayoutPanel root = RootLayoutPanel.get();
	    root.add(outer);
	}
	
	@UiHandler("inputField")
	void onKeyPress(KeyPressEvent e)
	{
		if (e.getCharCode() == KeyCodes.KEY_ENTER)
		{
			HTML data = new HTML("> " + inputField.getText());
			data.getElement().addClassName(style.individualOutputArea());
		    resultsPanel.add(data);
		    scrollPanel.scrollToBottom();
		}
	}

}

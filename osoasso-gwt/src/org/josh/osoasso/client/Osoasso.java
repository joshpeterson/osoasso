package org.josh.osoasso.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.core.client.JavaScriptObject;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.KeyCodes;
import com.google.gwt.event.dom.client.KeyPressEvent;
import com.google.gwt.resources.client.CssResource;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.uibinder.client.UiHandler;
import com.google.gwt.user.client.DOM;
import com.google.gwt.user.client.Event;
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
	
	int type;
	
	@UiField TextBox inputField;
	@UiField ScrollPanel scrollPanel;
	@UiField VerticalPanel resultsPanel;
	@UiField OsoassoStyle style;
	@UiField Label moduleStatus;

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
	    
	    final NaclWidget naclWidget = new NaclWidget();
	    naclWidget.setHTML("<embed name=\"nacl_module\" "
	                       + "id=\"osoasso\" "
	                       + "width=0 height=0 "
	                       + "src=\"osoasso.nmf\" "
	                       + "type=\"application/x-nacl\" />");
	    
	    RootLayoutPanel root = RootLayoutPanel.get();
	    root.add(naclWidget);
	    root.add(outer);
	}
	
	@UiHandler("inputField")
	void onKeyPress(KeyPressEvent e)
	{
		if (e.getCharCode() == KeyCodes.KEY_ENTER)
		{
			//HTML data = new HTML("> " + inputField.getText());
			//data.getElement().addClassName(style.individualOutputArea());
		    //resultsPanel.add(data);
			CallNaClInput(naclModule, inputField.getText());
			
		    scrollPanel.scrollToBottom();
		}
	}
	
	public void onNaclMessage(String data)
	{
		HTML html = new HTML("> Boo!");
		html.getElement().addClassName(style.individualOutputArea());
	    resultsPanel.add(html);
	}
	
	 protected static native JavaScriptObject GetNaclModule() /*-{
	    return $doc.getElementById("osoasso");
	  }-*/;
	 
	 public native void RegisterNaclListener(JavaScriptObject naclModule) /*-{
	 	//this.@org.josh.osoasso.client.Osoasso::onNaclMessage(Ljava/lang/String;)("foo");
	 	//naclModule.addEventListener('message', function(message_event) {
      //this.@org.josh.osoasso.client.Osoasso::onNaclMessage(Ljava/lang/String;)(message_event.data);
    //}, false);
    naclModule.addEventListener('message', function(message_event) {
      alert(message_event.data);
    }, false);
	// naclModule.addEventListener("message", $wnd.handleMessage, false);
	 }-*/;
	 
	 protected static native void CallNaClInput(
		      JavaScriptObject naclModule, String input) /*-{
		    if (naclModule != null) {
		      naclModule.postMessage('input:' + input + ":me@it.com");
		    } else {
		      alert("Nacl module not loaded");
		    }
		  }-*/;
	 
	 private JavaScriptObject naclModule = null;
	  public class NaclWidget extends HTML {
	    @Override
	    protected void onLoad(){
	      naclModule = GetNaclModule();
	      if (naclModule != null) {
	    	  moduleStatus.setText("Module loaded");
	    	  RegisterNaclListener(naclModule);
	      } else {
	    	  moduleStatus.setText("Module failed to load");
	      }
	    }
	  }
}

package org.josh.osoasso.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.core.client.JavaScriptObject;
import com.google.gwt.event.dom.client.KeyCodes;
import com.google.gwt.event.dom.client.KeyDownEvent;
import com.google.gwt.event.dom.client.KeyPressEvent;
import com.google.gwt.resources.client.ClientBundle;
import com.google.gwt.resources.client.CssResource;
import com.google.gwt.resources.client.ImageResource;
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.uibinder.client.UiField;
import com.google.gwt.uibinder.client.UiHandler;
import com.google.gwt.user.client.DOM;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.DockLayoutPanel;
import com.google.gwt.user.client.ui.HTML;
import com.google.gwt.user.client.ui.HTMLPanel;
import com.google.gwt.user.client.ui.RootLayoutPanel;
import com.google.gwt.user.client.ui.ScrollPanel;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.user.client.Cookies;

/**
 * @author Josh Peterson
 * 
 *         The class which implements a simple GWT front end for the Osoasso
 *         product.
 */
public class Osoasso extends Composite implements EntryPoint
{

    /**
     * @author Josh Peterson
     * 
     *         This interface allows access to a style defined in the XML layout
     *         file from from the Java code here.
     */
    interface OsoassoStyle extends CssResource
    {
        String individualOutputArea();
    }

    public interface Resources extends ClientBundle
    {
        @Source("osoasso_logo.png")
        ImageResource logo();
    }

    interface OsoassoUiBinder extends UiBinder<DockLayoutPanel, Osoasso>
    {
    }

    private static OsoassoUiBinder uiBinder = GWT.create(OsoassoUiBinder.class);
    private static Osoasso instance;

    private JavaScriptObject naclModule = null;
    private JavaScriptObject emscriptenModule = null;
    
    private StringConcatenator concatenator = new StringConcatenator();
    private ActionHistory history = new ActionHistory();

    final private String UsernameCookieName = "OsoassoUsernameCookie";

    @UiField
    TextBox inputField;
    @UiField
    ScrollPanel scrollPanel;
    @UiField
    VerticalPanel resultsPanel;
    @UiField
    OsoassoStyle style;
    @UiField
    TextBox usernameField;

    public Osoasso()
    {
        initWidget(uiBinder.createAndBindUi(this));
        instance = this;
    }

    /**
     * We need a static method to allow the JavaScript event handler to call
     * back to the GWT Java code.
     * 
     * @param naclMessage
     *            The message from the Nacl call to native code.
     */
    public static void onNaclMessageStatic(String naclMessage)
    {
        instance.onNaclMessage(naclMessage);
    }
    
    /**
     * We need a static method to allow the JavaScript code to call GWT when
     * the Nacl module loads.
     * 
     */
    public static void onNaclModuleLoaded()
    {
    	instance.AddHTMLToResultsPanel("Welcome to &Theta;(soasso) - vector math in your browser");
    	instance.CallOsoassoNaclModuleInputMethod(instance.naclModule, "help", instance.usernameField.getText());
    }
 
    @Override
    public void onModuleLoad()
    {
    	exportOnNaclModuleLoadedMethod();
    	
        DockLayoutPanel outer = uiBinder.createAndBindUi(this);

        String username = Cookies.getCookie(UsernameCookieName);
        if (username != null)
            usernameField.setText(username);
        else
            usernameField.setText("Unknown User");

        Window.enableScrolling(false);
        Window.setMargin("0px");

        DOM.getElementById("initialMessage").removeFromParent();

        RootLayoutPanel root = RootLayoutPanel.get();
        root.add(outer);
    	
    	naclModule = GetNaclModule();
    	if (naclModule != null)
    		RegisterNaclListener(naclModule);
    	else
    	{
    		emscriptenModule= GetEmscriptenElement();
    		CallEmscriptenCreateInstance(emscriptenModule);
    		RegisterNaclListener(emscriptenModule);
    	}
    }

    @UiHandler(
    { "inputField", "usernameField" })
    void onKeyPress(KeyPressEvent e)
    {
        if (e.getSource() == this.inputField)
        {
            if (e.getCharCode() == KeyCodes.KEY_ENTER)
            {
                String action = inputField.getText();
                if (!action.isEmpty())
                {
                	if (naclModule != null)
                		CallOsoassoNaclModuleInputMethod(naclModule, action, usernameField.getText());
                	else
                		CallOsoassoNaclModuleInputMethod(emscriptenModule, action, usernameField.getText());
    
                    history.add(action);
                    scrollPanel.scrollToBottom();
    
                    inputField.setReadOnly(true);
                }
            }
        }
        else if (e.getSource() == this.usernameField)
        {
            Cookies.setCookie(UsernameCookieName, usernameField.getText() + e.getCharCode());
        }
    }
    
    @UiHandler({ "inputField", })
    void onKeyDown(KeyDownEvent e)
    {
        // For some reason, onKeyPress is not called for the up and down keys.
        int keyCode = e.getNativeKeyCode();
        if (keyCode == KeyCodes.KEY_UP)
        {
            history.movePrevious();
            String action = history.getCurrent();
            if (action != null)
                inputField.setText(action);
        }
        else if (keyCode == KeyCodes.KEY_DOWN)
        {
            history.moveNext();
            String action = history.getCurrent();
            if (action != null)
                inputField.setText(action);
        }
        else if (keyCode == KeyCodes.KEY_ESCAPE)
        {
            inputField.setText(null);
        }
    }

    public void onNaclMessage(String naclMessage)
    {
        inputField.setReadOnly(false);
        inputField.setText("");
        if (concatenator.addString(naclMessage))
        {
            // Done concatenating strings from the NaCl module
            String message = concatenator.fullString();
            concatenator = new StringConcatenator();

            if (message.startsWith("error"))
            {
                ErrorData error = new ErrorData(message);
                ErrorDataFormatter formatter = new ErrorDataFormatter(error);

                this.AddHTMLToResultsPanel(formatter.formatAction());
                this.AddHTMLToResultsPanel(formatter.formatErrorMessage());
            }
            else if (message.startsWith("text"))
            {
                TextFormatter formatter = new TextFormatter(message);
                this.AddHTMLToResultsPanel(formatter.formatAction());

                for (String line : formatter.formatLines())
                {
                    this.AddHTMLToResultsPanel(line);
                }
            }
            else
            {
                CommitData commit = new CommitData(message);
                CommitDataFormatter formatter = new CommitDataFormatter(commit);

                this.AddHTMLToResultsPanel(formatter.formatAction());
                this.AddHTMLToResultsPanel(formatter.formatCommitMetaData());
                this.AddHTMLToResultsPanel(formatter.formatOutputName());
                if (commit.hasMatrix())
                    this.AddHTMLToResultsPanel(formatter.formatOutputMatrix());
            }
        }
    }

    /**
     * @author Josh Peterson
     * 
     *         Use the HTML onLoad callback to wait for the Nacl module to load.
     */
    public class NaclWidget extends HTML
    {
        @Override
        protected void onLoad()
        {       	
            naclModule = GetNaclModule();
            RegisterNaclListener(naclModule);
        }
    }

    private void AddHTMLToResultsPanel(String html)
    {
        HTML htmlElement = new HTML(html);
        htmlElement.getElement().addClassName(style.individualOutputArea());

        resultsPanel.add(htmlElement);
        resultsPanel.setSpacing(10);
    }

    private native JavaScriptObject GetNaclModule()
    /*-{
		return $doc.getElementById("osoasso");
    }-*/;

    public native void RegisterNaclListener(JavaScriptObject naclModule)
    /*-{
		naclModule
				.addEventListener(
						'message',
						function(message_event) {
							@org.josh.osoasso.client.Osoasso::onNaclMessageStatic(Ljava/lang/String;)(message_event.data);
						}, false);
    }-*/;

    protected native void CallOsoassoNaclModuleInputMethod(JavaScriptObject naclModule, String input, String username)
    /*-{
		naclModule.postMessage('input:' + input + ":" + username);
    }-*/;
    
    private static native void exportOnNaclModuleLoadedMethod()
    /*-{
	    $wnd.onNaclModuleLoaded = function() {
	       $entry(@org.josh.osoasso.client.Osoasso::onNaclModuleLoaded()());
	    }
 	}-*/;

    private native JavaScriptObject GetEmscriptenElement()
    /*-{
		return $doc.getElementById("emscripten");
    }-*/;
    
    private native void CallEmscriptenCreateInstance(JavaScriptObject emscriptenInstance)
    /*-{
    	$doc.DoIt(emscriptenInstance);
    }-*/;
}

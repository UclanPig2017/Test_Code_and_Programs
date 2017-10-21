using System;
using Gtk;

//Basic MonoDevelop Program using GTK
public partial class MainWindow : Gtk.Window
{
    public MainWindow() : base(Gtk.WindowType.Toplevel)
    {
        Build();
    }

    protected void OnDeleteEvent(object sender, DeleteEventArgs a)
    {
        Application.Quit();
        a.RetVal = true;
    }

    protected void OnBtnSubmitClicked(object sender, EventArgs e)
    {
        //Read input string from TxtName Textbox
        if(string.IsNullOrWhiteSpace(TxtName.Text))
        {
            //If empty write following to output txtHello text container
            txtHello.Buffer.Text = "Who are you?";
        }
        else
        {
			//Else, retrieve name and output to txtHello text container as below
			txtHello.Buffer.Text = "Hello " + TxtName.Text + "!";
        }
    }
}

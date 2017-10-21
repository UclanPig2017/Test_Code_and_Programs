using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

//Basic test program that takes input string from user, then generates output string
namespace testWinForms
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnNameSubmit_Click(object sender, EventArgs e)
        {
            //If textbox is empty, output:
            if (string.IsNullOrWhiteSpace(txtName.Text))
            {
                txtHello.Text = "Who are you?";
            }
            //If textbox has content, generate string using content as below:
            else
            {
                txtHello.Text = "Hello " + txtName.Text + " !";
            }
        }
    }
}

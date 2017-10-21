namespace testWinForms
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.txtName = new System.Windows.Forms.TextBox();
            this.btnNameSubmit = new System.Windows.Forms.Button();
            this.txtHello = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(49, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "Name:";
            // 
            // txtName
            // 
            this.txtName.Location = new System.Drawing.Point(67, 9);
            this.txtName.Name = "txtName";
            this.txtName.Size = new System.Drawing.Size(203, 22);
            this.txtName.TabIndex = 1;
            // 
            // btnNameSubmit
            // 
            this.btnNameSubmit.Location = new System.Drawing.Point(15, 37);
            this.btnNameSubmit.Name = "btnNameSubmit";
            this.btnNameSubmit.Size = new System.Drawing.Size(255, 23);
            this.btnNameSubmit.TabIndex = 2;
            this.btnNameSubmit.Text = "Say Hello!";
            this.btnNameSubmit.UseVisualStyleBackColor = true;
            this.btnNameSubmit.Click += new System.EventHandler(this.btnNameSubmit_Click);
            // 
            // txtHello
            // 
            this.txtHello.Location = new System.Drawing.Point(15, 66);
            this.txtHello.Multiline = true;
            this.txtHello.Name = "txtHello";
            this.txtHello.Size = new System.Drawing.Size(255, 81);
            this.txtHello.TabIndex = 3;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(282, 160);
            this.Controls.Add(this.txtHello);
            this.Controls.Add(this.btnNameSubmit);
            this.Controls.Add(this.txtName);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "WinForms Test";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtName;
        private System.Windows.Forms.Button btnNameSubmit;
        private System.Windows.Forms.TextBox txtHello;
    }
}


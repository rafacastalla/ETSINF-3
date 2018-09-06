namespace ISWVehicleRentalExample.Presentation
{
    partial class NewPersonForm
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
            this.dnitextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.nametextBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.addresstextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.citytextBox = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.postalcodetextBox = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.driverLicensedateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.addPersonButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(55, 33);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(26, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "DNI";
            // 
            // dnitextBox
            // 
            this.dnitextBox.Location = new System.Drawing.Point(87, 30);
            this.dnitextBox.Name = "dnitextBox";
            this.dnitextBox.Size = new System.Drawing.Size(100, 20);
            this.dnitextBox.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(46, 73);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Name";
            // 
            // nametextBox
            // 
            this.nametextBox.Location = new System.Drawing.Point(87, 70);
            this.nametextBox.Name = "nametextBox";
            this.nametextBox.Size = new System.Drawing.Size(160, 20);
            this.nametextBox.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(36, 114);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(45, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Address";
            // 
            // addresstextBox
            // 
            this.addresstextBox.Location = new System.Drawing.Point(87, 111);
            this.addresstextBox.Name = "addresstextBox";
            this.addresstextBox.Size = new System.Drawing.Size(160, 20);
            this.addresstextBox.TabIndex = 5;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(57, 158);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(24, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "City";
            // 
            // citytextBox
            // 
            this.citytextBox.Location = new System.Drawing.Point(87, 155);
            this.citytextBox.Name = "citytextBox";
            this.citytextBox.Size = new System.Drawing.Size(100, 20);
            this.citytextBox.TabIndex = 7;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(17, 199);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(64, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Postal Code";
            // 
            // postalcodetextBox
            // 
            this.postalcodetextBox.Location = new System.Drawing.Point(87, 196);
            this.postalcodetextBox.Name = "postalcodetextBox";
            this.postalcodetextBox.Size = new System.Drawing.Size(52, 20);
            this.postalcodetextBox.TabIndex = 9;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 243);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(75, 13);
            this.label6.TabIndex = 10;
            this.label6.Text = "Driver License";
            // 
            // driverLicensedateTimePicker
            // 
            this.driverLicensedateTimePicker.Location = new System.Drawing.Point(87, 237);
            this.driverLicensedateTimePicker.Name = "driverLicensedateTimePicker";
            this.driverLicensedateTimePicker.Size = new System.Drawing.Size(200, 20);
            this.driverLicensedateTimePicker.TabIndex = 11;
            // 
            // addPersonButton
            // 
            this.addPersonButton.Location = new System.Drawing.Point(198, 288);
            this.addPersonButton.Name = "addPersonButton";
            this.addPersonButton.Size = new System.Drawing.Size(75, 23);
            this.addPersonButton.TabIndex = 12;
            this.addPersonButton.Text = "Add";
            this.addPersonButton.UseVisualStyleBackColor = true;
            this.addPersonButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // NewPersonForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(310, 323);
            this.Controls.Add(this.addPersonButton);
            this.Controls.Add(this.driverLicensedateTimePicker);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.postalcodetextBox);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.citytextBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.addresstextBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.nametextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.dnitextBox);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "NewPersonForm";
            this.Text = "New Person";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        protected System.Windows.Forms.TextBox dnitextBox;
        private System.Windows.Forms.Label label2;
        protected System.Windows.Forms.TextBox nametextBox;
        private System.Windows.Forms.Label label3;
        protected System.Windows.Forms.TextBox addresstextBox;
        private System.Windows.Forms.Label label4;
        protected System.Windows.Forms.TextBox citytextBox;
        private System.Windows.Forms.Label label5;
        protected System.Windows.Forms.TextBox postalcodetextBox;
        private System.Windows.Forms.Label label6;
        protected System.Windows.Forms.DateTimePicker driverLicensedateTimePicker;
        protected System.Windows.Forms.Button addPersonButton;
    }
}
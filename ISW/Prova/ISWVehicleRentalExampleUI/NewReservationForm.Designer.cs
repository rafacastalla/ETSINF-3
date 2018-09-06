namespace ISWVehicleRentalExample.Presentation
{
    partial class NewReservationForm
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
            this.customersComboBox = new System.Windows.Forms.ComboBox();
            this.addCustomerbutton = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.pickUpOfficeComboBox = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.returnOfficeComboBox = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.categoryComboBox = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.pickupdateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.label6 = new System.Windows.Forms.Label();
            this.returndateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.drivers = new System.Windows.Forms.Label();
            this.addDriverbutton = new System.Windows.Forms.Button();
            this.addButton = new System.Windows.Forms.Button();
            this.driversListCheckBox = new System.Windows.Forms.CheckedListBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(31, 35);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(51, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Customer";
            // 
            // customersComboBox
            // 
            this.customersComboBox.FormattingEnabled = true;
            this.customersComboBox.Location = new System.Drawing.Point(110, 31);
            this.customersComboBox.Name = "customersComboBox";
            this.customersComboBox.Size = new System.Drawing.Size(121, 21);
            this.customersComboBox.TabIndex = 1;
            this.customersComboBox.SelectionChangeCommitted += new System.EventHandler(this.customersComboBox_SelectionChangeCommitted);
            // 
            // addCustomerbutton
            // 
            this.addCustomerbutton.Location = new System.Drawing.Point(237, 30);
            this.addCustomerbutton.Name = "addCustomerbutton";
            this.addCustomerbutton.Size = new System.Drawing.Size(51, 23);
            this.addCustomerbutton.TabIndex = 2;
            this.addCustomerbutton.Text = "New Customer";
            this.addCustomerbutton.UseVisualStyleBackColor = true;
            this.addCustomerbutton.Click += new System.EventHandler(this.addCustomerbutton_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(25, 90);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(71, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Pickup Office";
            // 
            // pickUpOfficeComboBox
            // 
            this.pickUpOfficeComboBox.FormattingEnabled = true;
            this.pickUpOfficeComboBox.Location = new System.Drawing.Point(110, 87);
            this.pickUpOfficeComboBox.Name = "pickUpOfficeComboBox";
            this.pickUpOfficeComboBox.Size = new System.Drawing.Size(200, 21);
            this.pickUpOfficeComboBox.TabIndex = 4;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(30, 181);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(70, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Return Office";
            // 
            // returnOfficeComboBox
            // 
            this.returnOfficeComboBox.FormattingEnabled = true;
            this.returnOfficeComboBox.Location = new System.Drawing.Point(110, 181);
            this.returnOfficeComboBox.Name = "returnOfficeComboBox";
            this.returnOfficeComboBox.Size = new System.Drawing.Size(200, 21);
            this.returnOfficeComboBox.TabIndex = 6;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(51, 273);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(49, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Category";
            // 
            // categoryComboBox
            // 
            this.categoryComboBox.FormattingEnabled = true;
            this.categoryComboBox.Location = new System.Drawing.Point(110, 273);
            this.categoryComboBox.Name = "categoryComboBox";
            this.categoryComboBox.Size = new System.Drawing.Size(121, 21);
            this.categoryComboBox.TabIndex = 8;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(30, 130);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(66, 13);
            this.label5.TabIndex = 9;
            this.label5.Text = "Pickup Date";
            // 
            // pickupdateTimePicker
            // 
            this.pickupdateTimePicker.Location = new System.Drawing.Point(110, 123);
            this.pickupdateTimePicker.Name = "pickupdateTimePicker";
            this.pickupdateTimePicker.Size = new System.Drawing.Size(200, 20);
            this.pickupdateTimePicker.TabIndex = 10;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(35, 226);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 13);
            this.label6.TabIndex = 11;
            this.label6.Text = "Return Date";
            // 
            // returndateTimePicker
            // 
            this.returndateTimePicker.Location = new System.Drawing.Point(110, 219);
            this.returndateTimePicker.Name = "returndateTimePicker";
            this.returndateTimePicker.Size = new System.Drawing.Size(200, 20);
            this.returndateTimePicker.TabIndex = 12;
            // 
            // drivers
            // 
            this.drivers.AutoSize = true;
            this.drivers.Location = new System.Drawing.Point(56, 327);
            this.drivers.Name = "drivers";
            this.drivers.Size = new System.Drawing.Size(40, 13);
            this.drivers.TabIndex = 13;
            this.drivers.Text = "Drivers";
            // 
            // addDriverbutton
            // 
            this.addDriverbutton.Location = new System.Drawing.Point(237, 327);
            this.addDriverbutton.Name = "addDriverbutton";
            this.addDriverbutton.Size = new System.Drawing.Size(73, 24);
            this.addDriverbutton.TabIndex = 15;
            this.addDriverbutton.Text = "New Person";
            this.addDriverbutton.UseVisualStyleBackColor = true;
            this.addDriverbutton.Click += new System.EventHandler(this.addDriverbutton_Click);
            // 
            // addButton
            // 
            this.addButton.Location = new System.Drawing.Point(237, 438);
            this.addButton.Name = "addButton";
            this.addButton.Size = new System.Drawing.Size(73, 23);
            this.addButton.TabIndex = 16;
            this.addButton.Text = "Add";
            this.addButton.UseVisualStyleBackColor = true;
            this.addButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // driversListCheckBox
            // 
            this.driversListCheckBox.FormattingEnabled = true;
            this.driversListCheckBox.Location = new System.Drawing.Point(110, 327);
            this.driversListCheckBox.Name = "driversListCheckBox";
            this.driversListCheckBox.Size = new System.Drawing.Size(121, 94);
            this.driversListCheckBox.TabIndex = 18;
            // 
            // NewReservationForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(324, 473);
            this.Controls.Add(this.driversListCheckBox);
            this.Controls.Add(this.addButton);
            this.Controls.Add(this.addDriverbutton);
            this.Controls.Add(this.drivers);
            this.Controls.Add(this.returndateTimePicker);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.pickupdateTimePicker);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.categoryComboBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.returnOfficeComboBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.pickUpOfficeComboBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.addCustomerbutton);
            this.Controls.Add(this.customersComboBox);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "NewReservationForm";
            this.Text = "New Reservation";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox customersComboBox;
        private System.Windows.Forms.Button addCustomerbutton;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox pickUpOfficeComboBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox returnOfficeComboBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox categoryComboBox;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.DateTimePicker pickupdateTimePicker;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.DateTimePicker returndateTimePicker;
        private System.Windows.Forms.Label drivers;
        private System.Windows.Forms.Button addDriverbutton;
        private System.Windows.Forms.Button addButton;
        private System.Windows.Forms.CheckedListBox driversListCheckBox;
    }
}
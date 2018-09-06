namespace ISWVehicleRentalExample.Presentation
{
    partial class ListReservationsForm
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
            this.components = new System.ComponentModel.Container();
            this.label1 = new System.Windows.Forms.Label();
            this.customersComboBox = new System.Windows.Forms.ComboBox();
            this.reservationsdataGridView = new System.Windows.Forms.DataGridView();
            this.Id = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Customer = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.PickUpOffice = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ReturnOffice = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Category = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.NumDrivers = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.reservationsbindingSource = new System.Windows.Forms.BindingSource(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.reservationsdataGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.reservationsbindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(28, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(51, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Customer";
            // 
            // customersComboBox
            // 
            this.customersComboBox.FormattingEnabled = true;
            this.customersComboBox.Location = new System.Drawing.Point(85, 26);
            this.customersComboBox.Name = "customersComboBox";
            this.customersComboBox.Size = new System.Drawing.Size(121, 21);
            this.customersComboBox.TabIndex = 1;
            this.customersComboBox.SelectedIndexChanged += new System.EventHandler(this.customersComboBox_SelectedIndexChanged);
            // 
            // reservationsdataGridView
            // 
            this.reservationsdataGridView.AllowUserToAddRows = false;
            this.reservationsdataGridView.AllowUserToDeleteRows = false;
            this.reservationsdataGridView.AutoGenerateColumns = false;
            this.reservationsdataGridView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.reservationsdataGridView.BackgroundColor = System.Drawing.SystemColors.Window;
            this.reservationsdataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.reservationsdataGridView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Id,
            this.Customer,
            this.PickUpOffice,
            this.ReturnOffice,
            this.Category,
            this.NumDrivers});
            this.reservationsdataGridView.DataSource = this.reservationsbindingSource;
            this.reservationsdataGridView.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.reservationsdataGridView.Location = new System.Drawing.Point(0, 65);
            this.reservationsdataGridView.Name = "reservationsdataGridView";
            this.reservationsdataGridView.ReadOnly = true;
            this.reservationsdataGridView.RowHeadersVisible = false;
            this.reservationsdataGridView.Size = new System.Drawing.Size(498, 196);
            this.reservationsdataGridView.TabIndex = 2;
            // 
            // Id
            // 
            this.Id.DataPropertyName = "ds_Id";
            this.Id.FillWeight = 101.7259F;
            this.Id.HeaderText = "Id";
            this.Id.Name = "Id";
            this.Id.ReadOnly = true;
            // 
            // Customer
            // 
            this.Customer.DataPropertyName = "ds_Customer";
            this.Customer.FillWeight = 101.7259F;
            this.Customer.HeaderText = "Customer";
            this.Customer.Name = "Customer";
            this.Customer.ReadOnly = true;
            // 
            // PickUpOffice
            // 
            this.PickUpOffice.DataPropertyName = "ds_PickUpOffice";
            this.PickUpOffice.FillWeight = 101.7259F;
            this.PickUpOffice.HeaderText = "PickUpOffice";
            this.PickUpOffice.Name = "PickUpOffice";
            this.PickUpOffice.ReadOnly = true;
            // 
            // ReturnOffice
            // 
            this.ReturnOffice.DataPropertyName = "ds_ReturnOffice";
            this.ReturnOffice.FillWeight = 101.7259F;
            this.ReturnOffice.HeaderText = "ReturnOffice";
            this.ReturnOffice.Name = "ReturnOffice";
            this.ReturnOffice.ReadOnly = true;
            // 
            // Category
            // 
            this.Category.DataPropertyName = "ds_Category";
            this.Category.FillWeight = 101.7259F;
            this.Category.HeaderText = "Category";
            this.Category.Name = "Category";
            this.Category.ReadOnly = true;
            // 
            // NumDrivers
            // 
            this.NumDrivers.DataPropertyName = "ds_NumDrivers";
            this.NumDrivers.FillWeight = 91.37056F;
            this.NumDrivers.HeaderText = "#Drivers";
            this.NumDrivers.Name = "NumDrivers";
            this.NumDrivers.ReadOnly = true;
            // 
            // ListReservationsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(498, 261);
            this.Controls.Add(this.reservationsdataGridView);
            this.Controls.Add(this.customersComboBox);
            this.Controls.Add(this.label1);
            this.Name = "ListReservationsForm";
            this.Text = "List Reservations";
            ((System.ComponentModel.ISupportInitialize)(this.reservationsdataGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.reservationsbindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox customersComboBox;
        private System.Windows.Forms.DataGridView reservationsdataGridView;
        private System.Windows.Forms.BindingSource reservationsbindingSource;
        private System.Windows.Forms.DataGridViewTextBoxColumn Id;
        private System.Windows.Forms.DataGridViewTextBoxColumn Customer;
        private System.Windows.Forms.DataGridViewTextBoxColumn PickUpOffice;
        private System.Windows.Forms.DataGridViewTextBoxColumn ReturnOffice;
        private System.Windows.Forms.DataGridViewTextBoxColumn Category;
        private System.Windows.Forms.DataGridViewTextBoxColumn NumDrivers;
    }
}
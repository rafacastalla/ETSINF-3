using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ISWVehicleRentalExampleLib.BusinessLogic;
using ISWVehicleRentalExampleLib.Entities;

using System.Windows.Forms;

namespace ISWVehicleRentalExample.Presentation
{
    class NewCustomerForm : NewPersonForm
    {
        private Label label7;
        private Label label8;
        private Label label9;
        private DateTimePicker expCCdateTimePicker;
        private Label label10;
        private TextBox cvcCCtextBox;
        private Label label11;
        private TextBox typeCCtextBox;
        private Button searchButton;
        private TextBox numberCCtextBox;

        public NewCustomerForm() : base()
        {
            InitializeComponent();
        }
        public NewCustomerForm(NewReservationForm newReservationForm, BusinessController control) : base(newReservationForm, control)
        {
            InitializeComponent();
        }
        public override void Clear()
        {
            base.Clear();
            numberCCtextBox.Clear();
            cvcCCtextBox.Clear();
            typeCCtextBox.Clear();
        }

        protected override bool fieldsOK()
        {
            int result;
            return
                base.fieldsOK() &&
                !string.IsNullOrEmpty(numberCCtextBox.Text) &&
                !string.IsNullOrEmpty(cvcCCtextBox.Text) &&
                !string.IsNullOrEmpty(typeCCtextBox.Text) &&
                int.TryParse(cvcCCtextBox.Text, out result);

        }
        protected override void addButton_Click(object sender, EventArgs e)
        {
            if (fieldsOK())
            {
                if (businessControl.findCustomerByDni(dnitextBox.Text) != null)
                    MessageBox.Show("Customer with this DNI already exists", "Error");
                else
                if(businessControl.findCreditCardByNumber(numberCCtextBox.Text)!= null)
                    MessageBox.Show("Credit Card Number already exists", "Error");
                else
                {
                    Customer cust = new Customer(dnitextBox.Text, nametextBox.Text, addresstextBox.Text, citytextBox.Text, postalcodetextBox.Text, driverLicensedateTimePicker.Value, DateTime.Now, new CreditCard(numberCCtextBox.Text, expCCdateTimePicker.Value.Month, expCCdateTimePicker.Value.Year, Convert.ToInt32(cvcCCtextBox.Text), typeCCtextBox.Text));
                    newReservationForm.addCustomerFormConfirmed(cust);

                }


            }
            else
            {
                int result;

                if (!int.TryParse(cvcCCtextBox.Text, out result))
                    MessageBox.Show("CVC must be a number", "Error");
                else
                    MessageBox.Show("Missing Fields", "Error");
            }
        }

        private void InitializeComponent()
        {
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.numberCCtextBox = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.expCCdateTimePicker = new System.Windows.Forms.DateTimePicker();
            this.label10 = new System.Windows.Forms.Label();
            this.cvcCCtextBox = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.typeCCtextBox = new System.Windows.Forms.TextBox();
            this.searchButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // addPersonButton
            // 
            this.addPersonButton.Location = new System.Drawing.Point(212, 474);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(9, 290);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(59, 13);
            this.label7.TabIndex = 13;
            this.label7.Text = "Credit Card";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(37, 319);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(44, 13);
            this.label8.TabIndex = 14;
            this.label8.Text = "Number";
            // 
            // numberCCtextBox
            // 
            this.numberCCtextBox.Location = new System.Drawing.Point(87, 316);
            this.numberCCtextBox.Name = "numberCCtextBox";
            this.numberCCtextBox.Size = new System.Drawing.Size(110, 20);
            this.numberCCtextBox.TabIndex = 15;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(27, 356);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(54, 13);
            this.label9.TabIndex = 16;
            this.label9.Text = "Exp. Date";
            // 
            // expCCdateTimePicker
            // 
            this.expCCdateTimePicker.Location = new System.Drawing.Point(87, 350);
            this.expCCdateTimePicker.Name = "expCCdateTimePicker";
            this.expCCdateTimePicker.Size = new System.Drawing.Size(200, 20);
            this.expCCdateTimePicker.TabIndex = 17;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(53, 392);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(28, 13);
            this.label10.TabIndex = 18;
            this.label10.Text = "CVC";
            // 
            // cvcCCtextBox
            // 
            this.cvcCCtextBox.Location = new System.Drawing.Point(87, 389);
            this.cvcCCtextBox.Name = "cvcCCtextBox";
            this.cvcCCtextBox.Size = new System.Drawing.Size(32, 20);
            this.cvcCCtextBox.TabIndex = 19;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(30, 430);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(51, 13);
            this.label11.TabIndex = 20;
            this.label11.Text = "Company";
            // 
            // typeCCtextBox
            // 
            this.typeCCtextBox.Location = new System.Drawing.Point(87, 427);
            this.typeCCtextBox.Name = "typeCCtextBox";
            this.typeCCtextBox.Size = new System.Drawing.Size(100, 20);
            this.typeCCtextBox.TabIndex = 22;
            // 
            // searchButton
            // 
            this.searchButton.Location = new System.Drawing.Point(202, 28);
            this.searchButton.Name = "searchButton";
            this.searchButton.Size = new System.Drawing.Size(75, 23);
            this.searchButton.TabIndex = 23;
            this.searchButton.Text = "Search";
            this.searchButton.UseVisualStyleBackColor = true;
            this.searchButton.Click += new System.EventHandler(this.searchButton_Click);
            // 
            // NewCustomerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.ClientSize = new System.Drawing.Size(324, 509);
            this.Controls.Add(this.searchButton);
            this.Controls.Add(this.typeCCtextBox);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.cvcCCtextBox);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.expCCdateTimePicker);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.numberCCtextBox);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "NewCustomerForm";
            this.Text = "New Customer";
            this.Controls.SetChildIndex(this.dnitextBox, 0);
            this.Controls.SetChildIndex(this.nametextBox, 0);
            this.Controls.SetChildIndex(this.addresstextBox, 0);
            this.Controls.SetChildIndex(this.citytextBox, 0);
            this.Controls.SetChildIndex(this.postalcodetextBox, 0);
            this.Controls.SetChildIndex(this.driverLicensedateTimePicker, 0);
            this.Controls.SetChildIndex(this.addPersonButton, 0);
            this.Controls.SetChildIndex(this.label7, 0);
            this.Controls.SetChildIndex(this.label8, 0);
            this.Controls.SetChildIndex(this.numberCCtextBox, 0);
            this.Controls.SetChildIndex(this.label9, 0);
            this.Controls.SetChildIndex(this.expCCdateTimePicker, 0);
            this.Controls.SetChildIndex(this.label10, 0);
            this.Controls.SetChildIndex(this.cvcCCtextBox, 0);
            this.Controls.SetChildIndex(this.label11, 0);
            this.Controls.SetChildIndex(this.typeCCtextBox, 0);
            this.Controls.SetChildIndex(this.searchButton, 0);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        private void searchButton_Click(object sender, EventArgs e)
        {
            string dni = dnitextBox.Text;

            //CODIGO SEARCH
            if (!string.IsNullOrEmpty(dni))
            {
                Person p = businessControl.findPersonByDni(dni);
                Customer c = businessControl.findCustomerByDni(dni);

                
                if (p == null)
                {
                    MessageBox.Show("No Person found with this DNI", "Info");
                    Clear();

                }else
                if (c == null) //It is a person who is not a customer yet
                {
                    nametextBox.Text = p.name;
                    addresstextBox.Text = p.address;
                    citytextBox.Text = p.city;
                    postalcodetextBox.Text = p.postalCode;
                    driverLicensedateTimePicker.Value = p.dateDriverLicense;


                }
                else
                {
                    MessageBox.Show("A Customer already exists with this DNI", "Error");
                    Clear();

                }


            }
        }

    }
}

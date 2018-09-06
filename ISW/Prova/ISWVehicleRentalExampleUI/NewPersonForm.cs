using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using ISWVehicleRentalExampleLib.BusinessLogic;
using ISWVehicleRentalExampleLib.Entities;

namespace ISWVehicleRentalExample.Presentation
{
    public partial class NewPersonForm : Form
    {

        protected NewReservationForm newReservationForm;
        protected BusinessController businessControl;
        public NewPersonForm()
        {
            InitializeComponent();
               
        }
        public NewPersonForm(NewReservationForm newReservationForm, BusinessController control)
        {
            InitializeComponent();
            this.newReservationForm = newReservationForm;
            this.businessControl = control;
        }
        protected virtual bool fieldsOK()
        {
            return 
                !string.IsNullOrEmpty(dnitextBox.Text) &&
                !string.IsNullOrEmpty(nametextBox.Text) &&
                !string.IsNullOrEmpty(addresstextBox.Text) &&
                !string.IsNullOrEmpty(postalcodetextBox.Text) &&
                !string.IsNullOrEmpty(citytextBox.Text);
        }
        public virtual void Clear() { 
            dnitextBox.Clear();
            nametextBox.Clear();
            addresstextBox.Clear();
            postalcodetextBox.Clear();
            citytextBox.Clear();
        }


        protected virtual void addButton_Click(object sender, EventArgs e)
        {
            if (fieldsOK())
            {
                if (businessControl.findPersonByDni(dnitextBox.Text) != null)
                    MessageBox.Show("Person with this DNI already exists", "Error");
                else {
                    Person p = new Person(dnitextBox.Text, nametextBox.Text, addresstextBox.Text, citytextBox.Text, postalcodetextBox.Text, driverLicensedateTimePicker.Value);
                    businessControl.addPerson(p);
                    newReservationForm.addPersonFormConfirmed(p.dni);

                }


            }
            else MessageBox.Show("Missing Fields", "Error");
        }
    }
}

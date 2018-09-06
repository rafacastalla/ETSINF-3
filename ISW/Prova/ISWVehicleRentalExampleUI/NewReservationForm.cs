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
    public partial class NewReservationForm : Form
    {
        private BusinessController businesscontrol;
        private NewPersonForm newPersonForm;
        private NewCustomerForm newCustomerForm;
        private Customer previousCustomerAdded;

        private string previousSelectedCustomerDNI;

        public NewReservationForm(BusinessController control)
        {
            InitializeComponent();
            this.businesscontrol = control;
            newPersonForm = new NewPersonForm(this,control);
            newCustomerForm = new NewCustomerForm(this, control);
            InitializeCollections();
          
        }
        public void InitializeCollections()
        {
            customersComboBox.DisplayMember = "dni";
            customersComboBox.ValueMember = "dni";           
            customersComboBox.DataSource = businesscontrol.findAllCustomers();
            customersComboBox.SelectedIndex = -1;

            pickUpOfficeComboBox.DisplayMember = "address";
            pickUpOfficeComboBox.ValueMember = "Id";
            pickUpOfficeComboBox.DataSource = businesscontrol.findAllBranchOffices();
            pickUpOfficeComboBox.SelectedIndex = -1;

            returnOfficeComboBox.DisplayMember = "address";
            returnOfficeComboBox.ValueMember = "Id";
            returnOfficeComboBox.DataSource = businesscontrol.findAllBranchOffices();
            returnOfficeComboBox.SelectedIndex = -1;

            categoryComboBox.DisplayMember = "name";
            categoryComboBox.ValueMember = "Id";
            categoryComboBox.DataSource = businesscontrol.findAllCategories();
            categoryComboBox.SelectedIndex = -1;


            driversListCheckBox.Items.Clear();
            ICollection<Person> persons= businesscontrol.findAllPersons();
            if (persons!= null)
                foreach (Person p in persons)
                    driversListCheckBox.Items.Add(p.dni);



        }
        private bool fieldsOK()
        {
            return
                (customersComboBox.SelectedIndex != -1) &&
                (pickUpOfficeComboBox.SelectedIndex != -1) &&
                (returnOfficeComboBox.SelectedIndex != -1) &&
                (categoryComboBox.SelectedIndex != -1);
        }
        private void addButton_Click(object sender, EventArgs e)
        {
            if (fieldsOK())
            {
                addReservation();
            }
                else MessageBox.Show("There are missing fields", "Error");
        }

        private void addReservation()
        {
            BranchOffice pickUpOffice = (BranchOffice)pickUpOfficeComboBox.SelectedItem;
            BranchOffice returnOffice = (BranchOffice)returnOfficeComboBox.SelectedItem;
            Customer customer = (Customer)customersComboBox.SelectedItem;
            Category cat = (Category)categoryComboBox.SelectedItem;
            businesscontrol.addReservation(customer, pickUpOffice, pickupdateTimePicker.Value, returnOffice, returndateTimePicker.Value, cat, driversListCheckBox.CheckedItems.Cast<String>());
            this.Close();
       }
       private void addDriverbutton_Click(object sender, EventArgs e)
       {

           newPersonForm.Clear();
           newPersonForm.ShowDialog();

       }

       private void customersComboBox_SelectionChangeCommitted(object sender, EventArgs e)
       {

           // If the customer is changed the new customer becomes a driver           
           string newcustomerDNI = (string)customersComboBox.SelectedValue;           
           driversListCheckBox.SetItemChecked(driversListCheckBox.Items.IndexOf(newcustomerDNI), true);

           // If there was a previous customer selected then he(she) is no longer a driver
           if ((previousSelectedCustomerDNI != null) &&(previousSelectedCustomerDNI!=newcustomerDNI))
           {
               driversListCheckBox.SetItemChecked(driversListCheckBox.Items.IndexOf(previousSelectedCustomerDNI), false);
           }
           previousSelectedCustomerDNI = newcustomerDNI;

       }

       public void addPersonFormConfirmed(string dni)
       {

            driversListCheckBox.Items.Add(dni);
            driversListCheckBox.SetItemChecked(driversListCheckBox.Items.IndexOf(dni), true);

        }

        public void addCustomerFormConfirmed(Customer customer)
        {

            //Adding Customer to list of drivers and automatically checking it.
            //If the new Customer was an already existing Person then this 
            //person was already in the list of drivers and we don't add it           
            if (!driversListCheckBox.Items.Contains(customer.dni))
                driversListCheckBox.Items.Add(customer.dni);
            driversListCheckBox.SetItemChecked(driversListCheckBox.Items.IndexOf(customer.dni), true);

            //Adding Customer to customers combobox and selecting it
            //It has to be done this way because it is not allowed to
            //directly change the Items property if a DataSource has been
            //associated to the ComboBox
            BindingList<Customer> customers = new BindingList<Customer>((IList<Customer>)customersComboBox.DataSource);
            customers.Add(customer);
         

            //If a new customer was previously added we remove it
            //Only one new customer may be associated to a new Reservation
            if (previousCustomerAdded != null) { 
                customers.Remove(previousCustomerAdded);
                driversListCheckBox.Items.Remove(previousCustomerAdded.dni);
            }

            customersComboBox.DataSource = customers;
            customersComboBox.SelectedItem = customer;
            previousCustomerAdded = customer;
            previousSelectedCustomerDNI = customer.dni;
            newCustomerForm.Close();
        }

        private void addCustomerbutton_Click(object sender, EventArgs e)
        {
            newCustomerForm.Clear();
            newCustomerForm.ShowDialog();
        }
    }
}

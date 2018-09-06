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
    public partial class ListReservationsForm : Form
    {
        private BusinessController businesscontrol;
        
        public ListReservationsForm(BusinessController controller)
        {
            InitializeComponent();
            this.businesscontrol = controller;
            Initialize();
        }
        public void Initialize()
        {
            ICollection<Customer> customers;
            customersComboBox.Items.Clear();
            customers = businesscontrol.findAllCustomers();
            if (customers!=null)
                foreach (Customer c in businesscontrol.findAllCustomers())
                    customersComboBox.Items.Add(c.dni);
            customersComboBox.SelectedIndex = -1;
            customersComboBox.ResetText();
            reservationsbindingSource.DataSource = null;
        }

        private void customersComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            string dni = (string) customersComboBox.SelectedItem;
            ICollection<Reservation> reservations = businesscontrol.findReservationsbyCustomerID(dni);

            //A list of anonymous objects is created to display 
            //DataGrid with the info that is needed
            BindingList<object> bindinglist = new BindingList<object>();
            foreach (Reservation r in reservations)

                //Adding one anonymous object for each reservation obtained
                bindinglist.Add(new
                {
                    //ds_... are DataPropertyNames defined in the DataGridView object
                    //see DataGridView column definitions in Visual Studio Designer
                    ds_Id = r.Id,
                    ds_Customer = r.Customer.name,
                    ds_PickUpOffice = r.PickupBranchOffice.address,
                    ds_ReturnOffice = r.ReturnBranchOffice.address,
                    ds_Category = r.Category.name,
                    ds_NumDrivers = r.Drivers.Count
                });

            reservationsbindingSource.DataSource = bindinglist;

        }
    }
}

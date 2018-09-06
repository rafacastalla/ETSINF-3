using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

//Added
using ISWVehicleRentalExampleLib.BusinessLogic;
using ISWVehicleRentalExampleLib.Entities;

namespace ISWVehicleRentalExample.Presentation
{
    public partial class IswVehicleRentalApp : Form
    {
        private BusinessController businessControl;
        private ListReservationsForm listReservationForm;
        private NewReservationForm newReservationForm;
        public IswVehicleRentalApp()
        {
            InitializeComponent();
            // businessControl = BusinessController.getBusinessController();
            businessControl = BusinessController.getBusinessController();
            listReservationForm = new ListReservationsForm(businessControl);
            newReservationForm = new NewReservationForm(businessControl);

        }



        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {


            this.newReservationForm.InitializeCollections();
            this.newReservationForm.ShowDialog();
        }

        private void listToolStripMenuItem_Click(object sender, EventArgs e)
        {
            listReservationForm.Initialize();
            listReservationForm.ShowDialog();
        }

        private void createNewDBToolStripMenuItem_Click(object sender, EventArgs e)
        {

            businessControl.removeAllData();
            //Example of Reservation creation by code

            BranchOffice br = new BranchOffice(1, "Archiduque Carlos, 3");
            Category cat = new Category(1, "luxury", 23, 12, 2, 32, 14);
            DateTime pickupDate = new DateTime(2016, 12, 23);
            DateTime returnDate = new DateTime(2016, 12, 24);
            CreditCard cc = new CreditCard("1122334455667788", 12, 2018, 323, "Visa");
            Customer cust = new Customer("11111111A", "Javier Jaen", "Camino de Vera s/n", "Valencia", "46960", new DateTime(2014, 5, 23), new DateTime(2015, 12, 11), cc);
            Reservation res = new Reservation(cust, br, pickupDate, br, returnDate, cat);

            businessControl.addReservation(res);

            //Adding other Branch Offices
            br = new BranchOffice(2, "Av. Constitución, 14");
            businessControl.addBranchOffice(br);
            br = new BranchOffice(3, "C/San Cristóbal, 13");
            businessControl.addBranchOffice(br);

            //Adding Categories
            Category cat2 = new Category(2, "sedan", 22, 10, 2, 30, 10);
            cat2.Upper = cat;
            Category cat3 = new Category(3, "economy", 15, 5, 1, 15, 5);
            cat3.Upper = cat2;
            
            businessControl.addCategory(cat2);
            businessControl.addCategory(cat3);
            MessageBox.Show("Database Created Sucessfully");
        }
    }
        
     
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ISWVehicleRentalExampleLib.Entities
{
    public partial class Reservation
    {
        public Reservation()
        {
            Drivers = new List<Person>();
        }
        public Reservation(Customer Customer,
            BranchOffice PickupBranchOffice, DateTime pickupDate,
            BranchOffice ReturnBranchOffice, DateTime returnDate,
            Category Category)
        {
            //Autoincremental Id
            this.Id = 1;
            this.pickupDate = pickupDate;
            this.returnDate = returnDate;
            this.Category = Category;
            this.PickupBranchOffice = PickupBranchOffice;
            this.ReturnBranchOffice = ReturnBranchOffice;
            this.Customer = Customer;
            Drivers = new List<Person>();
            Drivers.Add(Customer);
            Customer.DrivenReservations.Add(this);

        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ISWVehicleRentalExampleLib.Entities
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    public partial class BranchOffice
    {
        public BranchOffice()
        {
            PickUpReservations = new List<Reservation>();
            ReturnReservations = new List<Reservation>();

        }

        public BranchOffice(int Id, string address)
        {
            this.Id = Id;
            this.address = address;
            PickUpReservations = new List<Reservation>();
            ReturnReservations = new List<Reservation>();
        }
    }
}

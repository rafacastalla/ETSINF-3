using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ISWVehicleRentalExampleLib.Entities;

namespace ISWVehicleRentalExampleLib.Persistence
{
    public interface IReservationDAO
    {
        void addReservation(Reservation r);
        ICollection<Reservation> findReservationsbyCustomerDNI(String customerDNI);



    }
}

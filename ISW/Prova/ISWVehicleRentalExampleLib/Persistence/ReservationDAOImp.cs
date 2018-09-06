using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ISWVehicleRentalExampleLib.Entities;

namespace ISWVehicleRentalExampleLib.Persistence
{
    public class ReservationDAOImp:IReservationDAO
    {
       
        private VehicleRentalDAL dbcontext;

        public ReservationDAOImp(VehicleRentalDAL dbcontext)
        {
            this.dbcontext = dbcontext;

        }

        //CRUD  Operations
        public void addReservation(Reservation res)
        {
            try
            {                
                dbcontext.reservations.Add(res);
                dbcontext.SaveChanges();
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
            }
        }


        public ICollection<Reservation> findReservationsbyCustomerDNI(String customerDNI)
        {

            try
            {
                return dbcontext.reservations.Where(r => r.Customer.dni == customerDNI).ToList<Reservation>();
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
                return null;
            }
        }
    }
}

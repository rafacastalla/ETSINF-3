using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ISWVehicleRentalExampleLib.Entities;
namespace ISWVehicleRentalExampleLib.Persistence
{
    public class CreditCardDAOImp:ICreditCardDAO
    {
        private VehicleRentalDAL dbcontext;

        public CreditCardDAOImp(VehicleRentalDAL dbcontext)
        {
            this.dbcontext = dbcontext;

        }
        //CRUD CREDIT CARD Operations
        public CreditCard findCreditCardByNumber(string number)
        {
            try
            {
                //FirstOrDefault returns null if the Where clause returns no objects
                return dbcontext.creditcards.Where(c => c.digitsCC == number).FirstOrDefault<CreditCard>();

            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
                return null;
            }
        }
    }
   
}

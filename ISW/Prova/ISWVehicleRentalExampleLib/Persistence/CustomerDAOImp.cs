using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ISWVehicleRentalExampleLib.Entities;
namespace ISWVehicleRentalExampleLib.Persistence
{
    public class CustomerDAOImp:ICustomerDAO
    {
        private VehicleRentalDAL dbcontext;

        public CustomerDAOImp(VehicleRentalDAL dbcontext)
        {
            this.dbcontext = dbcontext;

        }
        //CRUD CUSTOMER Operations
       
        public ICollection<Customer> findAllCustomers()
        {
            try
            {
                return dbcontext.customers.ToList<Customer>();
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
                return null;
            }
        }

        public Customer findCustomerByDni(string dni)
        {

            try
            {
                //FirstOrDefault returns null if the Where clause returns no objects
                return dbcontext.customers.Where(p => p.dni == dni).FirstOrDefault<Customer>();
                

            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
                return null;
            }
        }

        

    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ISWVehicleRentalExampleLib.Entities;

namespace ISWVehicleRentalExampleLib.Persistence
{
    public interface ICustomerDAO
    {
        
        ICollection<Customer> findAllCustomers();
        Customer findCustomerByDni(string dni);
    }
    
}

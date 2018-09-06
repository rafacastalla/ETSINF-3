using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ISWVehicleRentalExampleLib.Persistence;
using ISWVehicleRentalExampleLib.Entities;

namespace DALTestingApp
{
    class Program
    {
        static void Main(string[] args)
        {
            //Example of console application to test some services of the Persistence layer
            //Important: App.config must contain the database connection string

            VehicleRentalDAL myDAL = VehicleRentalDAL.getVehicleRentalDAL();
            IBranchOfficeDAO boDAO=  myDAL.branchofficeDAO;
            ICollection<BranchOffice> boffices= boDAO.findAllBranchOffices();
            foreach (BranchOffice bo in boffices)
            {
                Console.WriteLine("ID: " + bo.Id + " Address: " + bo.address);
            }
            Console.WriteLine("Pres Key to exit...");
            Console.ReadKey();
        }
    }
}

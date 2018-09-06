using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ISWVehicleRentalExampleLib.Entities;
namespace ISWVehicleRentalExampleLib.Persistence
{
    public class BranchOfficeDAOImp:IBranchOfficeDAO
    {
        private VehicleRentalDAL dbcontext;
        public BranchOfficeDAOImp(VehicleRentalDAL dbcontext)
        {
            this.dbcontext = dbcontext;

        }
        //CRUD BRANCHOFFICE Operations

        public ICollection<BranchOffice> findAllBranchOffices()
        {
            try
            {
                return dbcontext.offices.ToList<BranchOffice>();
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
                return null;
            }
        }

        public void addBranchOffice(BranchOffice br)
        {
            try
            {
                dbcontext.offices.Add(br);
                dbcontext.SaveChanges();
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
            }
        }



    }
}

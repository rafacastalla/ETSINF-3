using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ISWVehicleRentalExampleLib.Entities;
namespace ISWVehicleRentalExampleLib.Persistence
{
    public class CategoryDAOImp:ICategoryDAO
    {
        private VehicleRentalDAL dbcontext;

        public CategoryDAOImp(VehicleRentalDAL dbcontext)
        {
            this.dbcontext = dbcontext;

        }
        //CRUD CATEGORY Operations
        public ICollection<Category> findAllCategories()
        {
            try
            {
                return dbcontext.categories.ToList<Category>();
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
                return null;
            }
        }

        public void addCategory(Category cat)
        {
            try
            {
                dbcontext.categories.Add(cat);
                dbcontext.SaveChanges();
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
            }
        }

    }
}

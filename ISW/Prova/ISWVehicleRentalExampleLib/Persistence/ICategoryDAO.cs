using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ISWVehicleRentalExampleLib.Entities;
namespace ISWVehicleRentalExampleLib.Persistence
{
    public interface ICategoryDAO
    {
        ICollection<Category> findAllCategories();
        void addCategory(Category cat);
    }
}

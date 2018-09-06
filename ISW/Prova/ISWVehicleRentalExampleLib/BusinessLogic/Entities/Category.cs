using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ISWVehicleRentalExampleLib.Entities
{
    public partial class Category
    {
        public Category() { }

        public Category(int Id, string name, double priceUnlimitedMileage, double priceFixedMileage,
        double priceAdditionalKm, double priceFullInsurance, double pricePartialInsurance)

        {
            this.Id = Id;
            this.name = name;
            this.priceUnlimitedMileage = priceUnlimitedMileage;
            this.priceFixedMileage = priceFixedMileage;
            this.priceAdditionalKm = priceAdditionalKm;
            this.priceFullInsurance = priceFullInsurance;
            this.pricePartialInsurance = pricePartialInsurance;
            Upper = null;

        }
    }
}

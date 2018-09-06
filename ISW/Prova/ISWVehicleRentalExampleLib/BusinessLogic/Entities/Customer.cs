using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ISWVehicleRentalExampleLib.Entities
{
    public partial class Customer:Person
    {
        public Customer() : base() { }
        public Customer(string dni, string name, string address, string city,
            string postalCode, DateTime dateDriverLicense,
            DateTime registrationDate, CreditCard Card)
            : base(dni, name, address, city, postalCode, dateDriverLicense)

        {
            this.registrationDate = registrationDate;
            this.Card = Card;
        }
    }
}

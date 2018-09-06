using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ISWVehicleRentalExampleLib.Entities
{
    public partial class Person
    {
        public Person()
        {
            DrivenReservations = new List<Reservation>();
        }

        public Person(string dni, string name, string address, string city,
            string postalCode, DateTime dateDriverLicense)
        {
            this.dni = dni;
            this.name = name;
            this.address = address;
            this.city = city;
            this.postalCode = postalCode;
            this.dateDriverLicense = dateDriverLicense;
            DrivenReservations = new List<Reservation>();

        }
    }
}

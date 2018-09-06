using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ISWVehicleRentalExampleLib.Entities;
namespace ISWVehicleRentalExampleLib.Persistence
{
    public interface IPersonDAO
    {
        void addPerson(Person person);
        ICollection<Person> findAllPersons();
        Person findPersonByDni(string dni);
        void removePerson(Person p);
    }
}

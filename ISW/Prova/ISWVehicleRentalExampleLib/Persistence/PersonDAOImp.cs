using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using ISWVehicleRentalExampleLib.Entities;

namespace ISWVehicleRentalExampleLib.Persistence
{
    public class PersonDAOImp:IPersonDAO
    {
        private VehicleRentalDAL dbcontext;

        public PersonDAOImp(VehicleRentalDAL dbcontext)
        {
            this.dbcontext = dbcontext;

        }
        //CRUD PERSON Operations
        public void addPerson(Person person)
        {
            try
            {
                dbcontext.persons.Add(person);
                dbcontext.SaveChanges();
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
            }
        }


        public ICollection<Person> findAllPersons()
        {
            try
            {
                return dbcontext.persons.ToList<Person>();
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
                return null;
            }
        }
        public Person findPersonByDni(string dni)
        {
            try
            {
                return dbcontext.persons.Where(p => p.dni == dni).FirstOrDefault<Person>();
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
                return null;
            }
        }

        public void removePerson(Person p)
        {
            try
            {
                dbcontext.persons.Remove(p);
                dbcontext.SaveChanges();
            }
            catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
            }
        }
    }
}

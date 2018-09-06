using System;

namespace GestDepLib.Services
{
    public class GestDepService : IGestDepService
    {
        public GestDepService()
        {
        }

        public void addPerson(Person person)
        {
            if (dal.GetById<Person>(person.Dni) == null)
            {
                dal.Insert<Person>(person);
                dal.Commit();
            }
            else throw new ServiceException("Person already exists.");
        }
    }
}
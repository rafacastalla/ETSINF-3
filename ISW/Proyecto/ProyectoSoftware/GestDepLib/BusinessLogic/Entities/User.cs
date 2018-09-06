using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDepLib.Entities
{
    public partial class User : Person
    {
        protected User()
        {
            this.Enrollments = new List<Enrollment>();
        }
        public User(DateTime date, bool ret, String Address, String IBAN, String Id, String Name, int ZipCode) 
            :base ( Address,  IBAN,  Id,  Name,  ZipCode)
        {

            this.Retired = ret;
            this.BirthDate = date;
            this.Enrollments = new List<Enrollment>();
        }
    }
}

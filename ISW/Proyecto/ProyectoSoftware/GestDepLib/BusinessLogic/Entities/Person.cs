using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDepLib.Entities
{
    public partial class Person
    {
        protected Person() {
            
        }
        public Person(String Address, String IBAN, String Id, String Name, int ZipCode) {
            this.Address = Address;
            this.IBAN = IBAN;
            this.Id = Id;
            this.ZipCode = ZipCode;
            this.Name = Name;
        }
    }
}

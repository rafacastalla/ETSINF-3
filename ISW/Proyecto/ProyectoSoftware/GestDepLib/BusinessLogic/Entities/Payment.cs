using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDepLib.Entities
{
    public partial class Payment
    {
        protected Payment() {

        }

        public Payment(DateTime Date, String Description, double Quantity) {
            this.Date = Date;
            this.Description = Description;
            this.Quantity = Quantity;
        }
    }
}

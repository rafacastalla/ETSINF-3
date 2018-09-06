using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ISWVehicleRentalExampleLib.Entities
{
    public partial class CreditCard
    {
        public CreditCard() { }
        public CreditCard(string digitsCC, int monthCC, int yearCC, int cvcCC, string typeCC)
        {
            this.digitsCC = digitsCC;
            this.monthCC = monthCC;
            this.yearCC = yearCC;
            this.cvcCC = cvcCC;
            this.typeCC = typeCC;
        }

    }
    }

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ISWVehicleRentalExampleLib.BusinessLogic
{
    class BusinessLogicException:Exception
    {
        public BusinessLogicException()
        {
        }

        public BusinessLogicException(string message)
        : base(message)
        {
        }

        public BusinessLogicException(string message, Exception inner)
        : base(message, inner)
        {
        }
    }

}

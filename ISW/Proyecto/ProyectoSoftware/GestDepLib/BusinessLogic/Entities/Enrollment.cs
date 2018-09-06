using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDepLib.Entities
{
    public partial class Enrollment
    {
        protected Enrollment()
        {
            this.Payments = new List<Payment>();
        }

        public Enrollment(DateTime EnrollmentDate, Course c, User u, Payment pay)
        {
            this.ReturnedFirstCuotaIfCancelledCourse = null;
            this.CancellationDate = null;
            this.EnrollmentDate = EnrollmentDate;
            this.Course = c;
            this.User = u;
            this.Payments = new List<Payment>();
            this.Payments.Add(pay);
        }
    }
}

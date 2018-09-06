using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDepLib.Entities
{
    public partial class Monitor : Person
    {

        protected Monitor()
        {
            this.Courses = new List<Course>();
        }

        public Monitor(String s, String Address, String IBAN, String Id, String Name, int ZipCode)
            : base(Address, IBAN, Id, Name, ZipCode)
        {
            this.Ssn = s;
            this.Courses = new List<Course>();
        }
        public bool IsAvailableFor(Course cou){
           
            foreach (Course c in this.Courses)
            {

                if (c.StartDate.Date > cou.FinishDate.Date
                    || cou.StartDate > c.FinishDate
                    || (c.CourseDays & cou.CourseDays) == 0
                    || c.StartHour > cou.StartHour.Add(cou.Duration)
                    || cou.StartHour > c.StartHour.Add(c.Duration))
                {
                    continue;
                }
                else
                {
                    return false;
                }
            }

            return true;
          }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDepLib.Entities
{
    public partial class Course
    {
        protected Course(){
            this.Lanes = new List<Lane>();
            this.Enrollments = new List<Enrollment>();
        }
        public Course(DateTime dateStar, DateTime dateFin, DateTime startH, 
            TimeSpan dura, int minim, int max, bool cancel, double preu, String des,
            Days day, Pool pool) : this()
        {
            this.CourseDays = day;
            this.Description = des;
            this.Price = preu;
            this.Cancelled = cancel;
            this.MaximunEnrollments = max;
            this.MinimunEnrollments = minim;
            this.Duration = dura;
            this.StartHour = startH;
            this.FinishDate = dateFin;
            this.StartDate = dateStar;
            this.pool = pool;
        }
    }
}

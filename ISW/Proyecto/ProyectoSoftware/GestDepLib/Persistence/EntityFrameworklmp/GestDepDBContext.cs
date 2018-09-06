using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.Entity;
using GestDepLib.Entities;
using System.Threading.Tasks;

namespace GestDepLib.Persistence
{
    public class GestDepDbContext : DbContext
    {
        public IDbSet<Course> Courses { get; set; }
        public IDbSet<Enrollment> Enrollments { get; set; }
        public IDbSet<Lane> Lanes { get; set; }
        public IDbSet<Monitor> Monitors { get; set; }
        public IDbSet<Payment> Payments { get; set; }
        public IDbSet<Person> People { get; set; }
        public IDbSet<Pool> Pools { get; set; }
        public IDbSet<User> Users { get; set; }

        public  GestDepDbContext() : base("Name=GestDepDbConnection") //connection string name
         {
            /*
            See DbContext.Configuration documentation
            */
             Configuration.LazyLoadingEnabled = true;
             Configuration.ProxyCreationEnabled = true;
        }
    }
}

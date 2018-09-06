using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDepLib.Entities
{
    public partial class Lane
    {
        protected Lane(){
            this.Courses = new List<Course>();
        }

        public Lane( int Number) {
            this.Number = Number;
            this.Courses = new List<Course>();

        }
    }

    
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GestDepLib.Entities
{
    
    public partial class Pool
    {
        protected Pool()
        {
            this.Lanes = new List<Lane>();
        }

        public Pool(DateTime OpeningHour, DateTime ClosingHour, int ZipCode, int DisconnectRetired, int DiscountLocal, float freeSwimPrice)
        {
            this.OpeningHour = OpeningHour;
            this.ClosingHour = ClosingHour;
            this.ZipCode = ZipCode;
            this.DiscountRetired = DisconnectRetired;
            this.DiscountLocal = DiscountLocal;
            this.FreeSwimPrice = freeSwimPrice;
            this.Lanes = new List<Lane>();
            this.Courses = new List<Course>();
        }

        public void insertarLane(int num)
        {
             for(int i = 1; i<= num; i++)
            {
                this.Lanes.Add(new Lane(i));
            }
        }

        public Lane FindLaneByNumber(int number)
        {
            return Lanes.Where(lane => lane.Number == number).FirstOrDefault();
        }
    }
}

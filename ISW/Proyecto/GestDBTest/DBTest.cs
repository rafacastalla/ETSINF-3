using System.Linq;
using System;
using GestDepLib.Persistence;
using System.Text;
using GestDepLib.Entities;
using System.Collections.Generic;

namespace GestDepDBTest
{
    class DBTest
    {
        static void Main(string[] args)
        {
           IDAL dal = new EntityFrameworkDAL(new GestDepDbContext());
           populateDB(dal);
           displayData(dal);   

        }

        private static void populateDB(IDAL dal)
        {
           
            // Remove all data from DB
            dal.Clear<Pool>();
            dal.Clear<Person>();
            dal.Clear<Monitor>();
            dal.Clear<Enrollment>();
            dal.Clear<Course>();
            dal.Clear<Lane>();
            dal.Clear<Payment>();
            dal.Clear<User>();


            Pool p = new Pool(new DateTime(2017, 10, 20, 8, 0, 0),
                new DateTime(2017, 10, 20, 21, 0, 0), 46122, 20, 15, 3);

             p.insertarLane(6);

            dal.Insert<Pool>(p);

            User p1 = new User(new DateTime(1990, 6, 5), false, "Ona Carbonell's address", "ES891234121234567890", "1234567890",
                "Ona Carbonell", 46002);
            dal.Insert<Person>(p1);

            User p2 = new User(new DateTime(1997, 4, 12), false, "Gemma Mengual's address", "ES891234121234567890", "2345678901",
               "Gemma Mengual", 46002);
            dal.Insert<Person>(p2);

            User p3 = new User(new DateTime(1990, 11, 10), false, "Mireia Belmonte's address", "ES891234121234567890", "3456789012",
               "Mireia Belmonte", 46003);
            dal.Insert<Person>(p3);

            User p4 = new User(new DateTime(1995, 02, 28), false, "Rigoberto's address", "ES891234121234567890", "4567890123",
             "Rigoberto", 46122);
            dal.Insert<Person>(p4);

            User p5 = new User(new DateTime(1972, 01, 01), true, "Lázaro's address", "ES891234121234567890", "5678901234",
             "Lázaro", 46122);
            dal.Insert<Person>(p5);

            Monitor aux = new Monitor("SSN01010101", "Michael Phelps'addres s", "ES891234121234567890", "X-00000001",
                          "Michael Phelps", 46122);
            dal.Insert<Person>(aux);

            Course c = new Course(new DateTime(2017, 11, 6), new DateTime(2018, 6, 29), createTime(9, 30, 0),
                new TimeSpan(0, 45, 0), 6, 20, false, 100, "Learning with M.Phelps", Days.Monday | Days.Wednesday | Days.Friday, p);
            
            c.Lanes.Add(p.FindLaneByNumber(1));
            c.Lanes.Add(p.FindLaneByNumber(2));

            Course c2 = new Course(new DateTime(2017, 11, 7), new DateTime(2018, 6, 29), createTime(19, 00, 0),
               new TimeSpan(1, 0, 0), 8, 16, true, 75, "Swimming for Dummys", Days.Tuesday | Days.Thursday, p);

            c2.Lanes.Add(p.FindLaneByNumber(3));
            //c.set(aux);
            //Insertar el curs en un monitor
            c.Monitor = aux;
            p.Courses.Add(c);
            p.Courses.Add(c2);
            dal.Insert<Course>(c);
            //Insertar un curs sense monitor
            dal.Insert<Course>(c2);

            //  DateTime ReturnedFirstCuotaIfCancelledCourse, Payment pay

            dal.Insert<Payment>(new Payment(new DateTime(2017, 08, 10), "Free Swim", 3));
            dal.Insert<Payment>(new Payment(new DateTime(2017, 08, 20), "Free Swim", 3));
            dal.Insert<Payment>(new Payment(new DateTime(2017, 08, 20), "Free Swim", 3));

            Payment pa1 = new Payment(new DateTime(2017, 08, 16), "First monthly quota - Learning with M. Phelps", 100);
            dal.Insert<Payment>(pa1);

            Payment pa2 = new Payment(new DateTime(2017, 08, 26), "First monthly quota - Learning with M. Phelps", 100);
            dal.Insert<Payment>(pa2);

            Payment pa3 = new Payment(new DateTime(2017, 08, 28), "First monthly quota - Learning with M. Phelps", 100);
            dal.Insert<Payment>(pa3);

            Payment pa4 = new Payment(new DateTime(2017, 08, 28), "First monthly quota - Swimming for Dummys", 75);
            dal.Insert<Payment>(pa4);

            Payment pa5 = new Payment(new DateTime(2017, 09, 04), "First monthly quota - Swimming for Dummys", 75);
            dal.Insert<Payment>(pa5);


            dal.Insert<Enrollment>(new Enrollment(new DateTime(2017, 08, 16), c, p1, pa1));
            dal.Insert<Enrollment>(new Enrollment(new DateTime(2017, 07, 26), c, p2, pa2));
            dal.Insert<Enrollment>(new Enrollment(new DateTime(2017, 08, 28), c, p3, pa3));

            Enrollment en1 = new Enrollment(new DateTime(2017, 08, 28), c2, p4, pa4);
            en1.CancellationDate = new DateTime(2017, 10, 20);
            dal.Insert<Enrollment>(en1);

            Enrollment en2 = new Enrollment(new DateTime(2017, 09, 04), c2, p5, pa5);
            en2.CancellationDate = new DateTime(2017, 10, 20);
            dal.Insert<Enrollment>(en2);





            dal.Commit();


            // Populate the database with the data described in lab 4 bulletin (see Apendix)


        }

        private static void displayData(IDAL dal)
        {
            Pool pool = dal.GetAll<Pool>().First();
            foreach (Course course in dal.GetAll<Course>())
            {
                Console.WriteLine("===================================");
                Console.WriteLine("         Course details         ");
                Console.WriteLine("===================================");
                Console.WriteLine(CourseToString(course));
                //foreach (Days day in Enum.GetValues(typeof(Days)))
                //{
                //    if ((course.CourseDays & day) == day)
                //        Console.WriteLine("Course on " + day.ToString());
                //}
            }
            Console.WriteLine("Payments:");
            foreach (Payment pay in dal.GetAll<Payment>())
                Console.Write(PaymentToString(pay));
            Console.WriteLine("Pres Key to exit...");
            Console.ReadKey();
        }

        public static String PersonToString(Person person)
        {
            return person.Name + " (" + person.Id + ")";
        }

        public static String CourseToString(Course course)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine("StartDate: " + course.StartDate);
            sb.AppendLine("FinishDate: " + course.FinishDate);
            sb.AppendLine("Days : " + course.CourseDays);
            sb.AppendLine("Price: " + course.Price);
            sb.AppendLine("Lanes assigned: ");
            foreach (Lane lane in course.Lanes)
                sb.AppendLine(" Lane " + lane.Number);
            if (course.Monitor != null)
                sb.AppendLine("\nUsers enrolled in course " + course.Description + ", with monitor " + PersonToString(course.Monitor));
            else sb.AppendLine("\nUsers enrolled in course " + course.Description + ", with no monitor yet");
            foreach (Enrollment en in course.Enrollments)
            {
                sb.Append(" " + EnrollmentToString(en));
            }
            //sb.AppendLine("");
            return sb.ToString();
        }

        public static String EnrollmentToString(Enrollment en)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine(PersonToString(en.User) + " enrolled on " + en.EnrollmentDate);
            return sb.ToString();
        }

        public static String PaymentToString(Payment pay)
        {
            StringBuilder sb = new StringBuilder();
            sb.AppendLine(" " + pay.Date + " -> " + pay.Description + ": " + pay.Quantity);
            return sb.ToString();
        }


        private static DateTime createTime(int hours, int minutes, int seconds)
        {
            DateTime now = DateTime.Now;
            return new DateTime(now.Year, now.Month, now.Day, hours, minutes, seconds);
        }

    }
}

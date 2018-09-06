using GestDepLib.Entities;
using GestDepLib.Persistence;
using GestDepLib.Services;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;


namespace GestDep.UnitTest
{
    [TestClass]

    public class GestDepServiceTest
    {
        private static IGestDepService service;
        private static IDAL dal;

        public static object DataSamples { get; private set; }

        //private static List<Payment> freeSwimPayments;

        [ClassInitialize]
        public static void SetUp(TestContext context)
        {
            dal = new EntityFrameworkDAL(new GestDepDbContext());
            service = new GestDepService(dal);
            //freeSwimPayments = service.GetAllFreeSwimPayments();
            // DataSamples.CreateData(dal);
        }

        [ClassCleanup]
        public static void TearDown()
        {
            foreach (Course c in dal.GetWhere<Course>(c => c.Description.Contains("TestCourse")))  
                dal.Delete(c);
            dal.Delete(dal.GetById<User>("TestUser 1"));
            dal.Delete(dal.GetById<Monitor>("TestMonitor 1"));
            User user = dal.GetById<User>("1234567890");          
            Course course = dal.GetWhere<Course>(c => c.Description == "Swimming for Dummys").First();
            Enrollment enrollment = dal.GetWhere<Enrollment>(e => e.User == user && e.Course == course).First();
            dal.Delete(enrollment);
            //foreach (Payment pay in service.GetAllFreeSwimPayments())
            //    if (!freeSwimPayments.Contains(pay)) dal.Delete(pay);
            //dal.Delete(dal.GetWhere<Pool>(p => p.ZipCode == 46000));
            dal.Commit();
            
        }  

        [TestMethod]
        public void TestAddUser()
        {
            service.AddUser("TestUser 1", "John Doe", "John Does' address", 46010, "XX01010101010101", new DateTime(1985, 6, 5), false);
            User user = service.FindUserById("TestUser 1");
            Assert.IsNotNull(user);
            Assert.AreEqual(user.Address, "John Does' address");
            Assert.AreEqual(user.BirthDate, new DateTime(1985, 6, 5));
            Assert.AreEqual(0, user.Enrollments.Count);
            Assert.AreEqual("XX01010101010101", user.IBAN);
            Assert.AreEqual("John Doe", user.Name);
            Assert.AreEqual(46010, user.ZipCode);
            Assert.IsFalse(user.Retired);
        }

        [TestMethod]
        public void TestAddMonitor()
        {
            service.AddMonitor("TestMonitor 1", "Johnny Weissmuller", "The Jungle s/n", 91919, "YY01010101010101", "SSN12121212");
            Monitor monitor = service.FindMonitorById("TestMonitor 1");
            Assert.IsNotNull(monitor);
            Assert.AreEqual(monitor.Address, "The Jungle s/n");
            Assert.AreEqual("YY01010101010101", monitor.IBAN);
            Assert.AreEqual("Johnny Weissmuller", monitor.Name);
            Assert.AreEqual(91919, monitor.ZipCode);
            Assert.AreEqual("SSN12121212", monitor.Ssn);
        }

        [TestMethod]
        public void TestAddEnrollment()
        {
            User user = service.FindUserById("1234567890");
            Course course = service.FindCourseByName("Swimming for Dummys");
            DateTime date = DateTime.Now.Date;
            service.EnrollInCourse(user, course, date);            
            Enrollment enrollment = user.Enrollments.Where(e => e.Course == course).First();
            Assert.IsNotNull(enrollment);
            Assert.IsNull(enrollment.CancellationDate);
            Assert.IsTrue(course.Enrollments.Contains(enrollment));
            //Assert.IsTrue(user.Enrollments.Contains(enrollment));
            Assert.AreEqual(date, enrollment.EnrollmentDate);
            
        }

        [TestMethod]
        public void TestAddCourseAndAssignMonitor()
        {
            Pool pool = service.FindPoolByZipCode(46122);
            service.AddCourse(pool, "TestCourse 1", new DateTime(2018, 1, 8), new DateTime(2018, 6, 25),
                createTime(18, 0, 0), new TimeSpan(0, 45, 0), Days.Tuesday | Days.Thursday, 10, 20,
                110, new List<int> { 5, 6 });

            // check course has been added to pool and is stored (can be found by Id)
            Course course = service.FindCourseByName("TestCourse 1");
            Assert.IsNotNull(course);
            Assert.IsTrue(pool.Courses.Contains(course));

            // check course details
            Assert.AreEqual(new DateTime(2018, 1, 8), course.StartDate);
            Assert.AreEqual(new DateTime(2018, 6, 25), course.FinishDate);
            Assert.AreEqual(createTime(18, 0, 0).TimeOfDay, course.StartHour.TimeOfDay);
            Assert.AreEqual(new TimeSpan(0, 45, 0), course.Duration);
            Assert.AreEqual(course.CourseDays & Days.Tuesday, Days.Tuesday);
            Assert.AreEqual(course.CourseDays & Days.Thursday, Days.Thursday);
            Assert.AreEqual(110, course.Price);
            Assert.IsNull(course.Monitor);

            // check lanes <--> course relationships
            Assert.AreEqual(2, course.Lanes.Count);
            Lane lane5 = pool.FindLaneByNumber(5);
            Lane lane6 = pool.FindLaneByNumber(6);
            Assert.IsTrue(course.Lanes.Contains(lane5));
            Assert.IsTrue(course.Lanes.Contains(lane6));
            Assert.IsTrue(lane5.Courses.Contains(course));
            Assert.IsTrue(lane6.Courses.Contains(course));

            // check monitor assignment
            Monitor monitor = service.GetAvailableMonitors(course).First();
            service.SetCourseMonitor(course, monitor);
            Assert.AreEqual(monitor, course.Monitor);
            Assert.IsTrue(monitor.Courses.Contains(course));
            service.AddCourse(pool, "TestCourse 2", new DateTime(2018, 2, 8), new DateTime(2018, 6, 25),
                createTime(18, 30, 0), new TimeSpan(0, 45, 0), Days.Tuesday | Days.Friday, 10, 20,
                110, new List<int> { 8, 10 });
            Course course2 = service.FindCourseByName("TestCourse 2");
            Assert.IsFalse(monitor.IsAvailableFor(course2));
            // He modificat les lanes del segon perque concidixen en les del primer i no es correcte el test
        }

        [TestMethod]
        [ExpectedException(typeof(ServiceException))]
        public void TestFreeLanes()
        {
            // Arrange
            Pool pool = service.FindPoolByZipCode(46122);
            Dictionary <DayOfWeek, Dictionary<TimeSpan, int>> initialFreeLanes = service.GetFreeLanes(pool, new DateTime(2018, 7, 2));
            Dictionary<TimeSpan, int> initialTuesdayFreeLanes = initialFreeLanes[DayOfWeek.Tuesday];

            // Act
            service.AddCourse(pool, "TestCourse 3", new DateTime(2018, 7, 3), new DateTime(2018, 7, 26),
                createTime(12, 00, 0), new TimeSpan(0, 45, 0), Days.Tuesday | Days.Thursday, 10, 20,
                110, new List<int> { 3, 4 });

            //Assert
            Dictionary<DayOfWeek, Dictionary<TimeSpan, int>> freeLanes = service.GetFreeLanes(pool, new DateTime(2018, 7, 2));
            Dictionary<TimeSpan, int> tuesdayFreeLanes = freeLanes[DayOfWeek.Tuesday];
            Assert.AreEqual(initialTuesdayFreeLanes[new TimeSpan(12, 30, 0)] - 2,
                tuesdayFreeLanes[new TimeSpan(12, 30, 0)]);

            // Next line will throw an exception, because date is not a monday as it should be
            service.GetFreeLanes(pool, new DateTime(2018, 7, 3));
        }

        [TestMethod]
        [ExpectedException(typeof(ServiceException))]
        public void TestClashingCourses()
        {
            // Arrange
            Pool pool = service.FindPoolByZipCode(46122);

            //Act
            service.AddCourse(pool, "TestCourse 4", new DateTime(2018, 7, 3), new DateTime(2018, 7, 26),
                createTime(12, 00, 0), new TimeSpan(0, 45, 0), Days.Wednesday | Days.Friday, 10, 20,
            110, new List<int> { 1,2,3,4,5,6});
            // Next line will throw an exception, because all lanes are occupied for the course schedule
            service.AddCourse(pool, "TestCourse 5", new DateTime(2018, 7, 3), new DateTime(2018, 7, 26),
                createTime(12, 00, 0), new TimeSpan(0, 45, 0), Days.Wednesday | Days.Friday, 10, 20,
                110, new List<int> { 1, 2 });
            //public void AddCourse(Pool p, String des, DateTime dateStar, DateTime dateFin, DateTime startH, TimeSpan dura, Days day, int minim, int max,
            //double preu, IEnumerable<int> lanes)
        }

        //[TestMethod]
        //public void TestFreeSwimPayments()
        //{
        //    int numPayments = service.GetAllFreeSwimPayments().Count;
        //    Pool aPool = service.GetAllPools().First();
        //    User aUser = service.GetAllEnrollments().First().User;
        //    service.AddFreeSwimPayment(aPool, aUser, DateTime.Now);
        //    Assert.AreEqual(numPayments + 1, service.GetAllFreeSwimPayments().Count);
        //}

            //[TestMethod]
            //public void TestMonthlyPayments()
            //{
            //    Enrollment enrollment = service.GetAllEnrollments().Where(e => e.Course.Cancelled == false).First();
            //    int numPayments = enrollment.Payments.Count;
            //    Course course = enrollment.Course;
            //    service.AddMonthlyPayment(enrollment, DateTime.Now.Date);
            //    Assert.AreEqual(numPayments + 1, enrollment.Payments.Count);
            //}

            //[TestMethod]
            //public void TestAddPool()
            //{
            //    service.AddPool(createTime(8, 0, 0), createTime(20, 0, 0), 46000, 20, 15, 3, 8);
            //    Pool pool = service.FindPoolByZipCode(46000);
            //    Assert.IsNotNull(pool);
            //    Assert.AreEqual(8, pool.Lanes.Count);
            //}

        private static DateTime createTime(int hours, int minutes, int seconds)
        {
            DateTime now = DateTime.Now;
            return new DateTime(now.Year, now.Month, now.Day, hours, minutes, seconds);
        }
    }
}

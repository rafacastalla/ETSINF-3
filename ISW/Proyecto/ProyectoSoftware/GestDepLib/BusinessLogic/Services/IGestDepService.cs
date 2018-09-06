using GestDepLib.Entities;
using System;
using System.Collections.Generic;

namespace GestDepLib.Services
{
    public interface IGestDepService
    {
        void AddUser(String Id, String Name, String Address, int ZipCode,
            String IBAN, DateTime date, bool ret);
        User FindUserById(String id);

        void AddMonitor(String Id, String Name, String Address, int ZipCode,
            String IBAN, String s);

        Monitor FindMonitorById(String Id);

        Course FindCourseByName(String name);

        void EnrollInCourse(User us, Course c, DateTime date);

        Pool FindPoolByZipCode(int zipcode);

        bool AddCourse(Pool p, String des, DateTime dateStar, DateTime dateFin,
            DateTime startH, TimeSpan dura, Days day, int minim, int max,
            double preu, IEnumerable<int> lanes);

        List<Monitor> GetAvailableMonitors(Course cou);

        IEnumerable<Course> GetCourses();
        IEnumerable<Pool> GetPools();

        void SetCourseMonitor(Course cou, Monitor m);

        Dictionary<DayOfWeek, Dictionary<TimeSpan, int>> GetFreeLanes(Pool pol, DateTime date);
    }


}

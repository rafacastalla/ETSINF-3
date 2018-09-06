using System;
using GestDepLib.Persistence;
using GestDepLib.Entities;
using System.Collections.Generic;
using System.Linq;

namespace GestDepLib.Services
{
    public class GestDepService : IGestDepService
    {
        IDAL service;
        public GestDepService(IDAL dal)
        {
            service = dal;
        }

        public void AddUser(String Id, String Name, String Address, int ZipCode, String IBAN, DateTime date, bool ret)
        {
            if (service.GetById<User>(Id) == null)
            {
                User p2 = new User(date, ret, Address, IBAN, Id, Name, ZipCode);
                service.Insert<Person>(p2);
                service.Commit();
            }else
            {
                System.Diagnostics.Debug.WriteLine("Error");
                
            }
        }
        public User FindUserById(String id)
        {


          
            if(service.GetById<User>(id) != null) { 
               return  service.GetById<User>(id);               
            }else{
                throw new ServiceException("Error");
            }
               
            
        }

        public void AddMonitor(String Id, String Name, String Address, int ZipCode, String IBAN, String s)
        {
            if (service.GetById<Monitor>(Id) == null)
            {
                Monitor p2 = new Monitor(s, Address, IBAN, Id, Name, ZipCode);
                service.Insert<Person>(p2);
                service.Commit();
            }
            else
            {
                System.Diagnostics.Debug.WriteLine("Error");
            }
        }

        public IEnumerable<Pool> GetPools()
        {
            return service.GetAll<Pool>();
        }
        public IEnumerable<Course> GetCourses()
        {
            return service.GetAll<Course>();
        }
        public Monitor FindMonitorById(String Id)
        {
            Monitor m = null;
            try
            {
                m = service.GetById<Monitor>(Id);
            }
            catch (ServiceException s)
            {
                System.Diagnostics.Debug.WriteLine(s.ToString());
                return null;
            }
            return m;

        }

        public Course FindCourseByName(String name)
        {
            IEnumerable<Course> cou = null;
            try
            {
                cou = service.GetAll<Course>().Where(c => c.Description == name);
            }
            catch (ServiceException s)
            {
                System.Diagnostics.Debug.WriteLine(s.ToString());
                return null;
            }
            if(cou.ToArray().Length != 0)
            {
                return cou.First();
            }
            else
            {
                return null;
            }
        }

        public void EnrollInCourse(User us, Course c, DateTime date)
        {
            
            if (c == null)
                return;

               
                Payment pay = new Payment(date, c.Description, c.Price);
                Enrollment a = new Enrollment(date, c, us, pay);
                c.Enrollments.Add(a);
                service.Insert < Enrollment> (a);
                service.Insert < Payment>(pay);            
                service.Commit();
            
        }

        public Pool FindPoolByZipCode(int zipcode)
        {
            if (service.GetAll<Pool>().Where(c => c.ZipCode == zipcode) != null)
            {
                return service.GetAll<Pool>().Where(c => c.ZipCode == zipcode).First();
            }else{
                throw new ServiceException("NO existeix");
            }
            
        }

        public bool  AddCourse(Pool p, String des, DateTime dateStar, DateTime dateFin, DateTime startH, TimeSpan dura, Days day, int minim, int max,
            double preu, IEnumerable<int> lanes)
        {
            Course cou = new Course(dateStar, dateFin, startH, dura, minim, max, false, preu, des, day, p);

            if (service.GetAll <Course>().Where(c => c.Description == des).Count() != 0 ) {
                return false;
                throw new ServiceException("El curs ja existeix");
            }

            IEnumerable<Course> cursos = service.GetAll < Course>();
            bool esta = false;

            foreach (Course c in cursos)
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
                    IEnumerable<Lane> carrils = c.Lanes;

                    foreach (Lane l in carrils)
                    {
                        foreach (int nl in lanes) { if (l.Number == nl) { esta = true; } }
                    }
                }
            }

            if (esta == true) {
                throw new ServiceException("Course no");
                return false;
            }

            foreach (int nl in lanes)
            {
                Lane l = p.FindLaneByNumber(nl);
                if (l == null)
                {
                    l = new Lane(nl);
                    service.Insert < Lane>(l);
                }
                cou.Lanes.Add(l);
            }

            service.Insert < Course>(cou);
            service.Commit();
            return true;

        }

        public List<Monitor> GetAvailableMonitors(Course cou)
        {
            List<Monitor> monitors = new List<Monitor>();
            try
            {
                IEnumerable<Monitor> tots = service.GetAll<Monitor>();
                bool comp = true;
                for (int i = 0; i < tots.Count(); i++)
                {
                    Monitor mAux = tots.ElementAt(i);

                    ICollection<Course> cursos = mAux.Courses;
                    comp = true;
                    foreach (Course c in cursos)
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
                            comp = false;
                        }
                    }
                    if (comp)
                    {
                        monitors.Add(mAux);
                    }
                }
            }
            catch (ServiceException s)
            {
                System.Diagnostics.Debug.WriteLine(s.ToString());
                return null;
            }      

            return monitors ;
        }

        public void SetCourseMonitor(Course cou, Monitor m)
        {
            cou.Monitor = m;
            m.Courses.Add(cou);
            service.Commit();
        }

        public Dictionary<DayOfWeek, Dictionary<TimeSpan, int>> GetFreeLanes(Pool pol, DateTime date)
        {

            if (date.DayOfWeek != DayOfWeek.Monday)
            {
                //Console.WriteLine("Fecha incorrecta.");
                throw new ServiceException("Fecha incorrecta.");
            }

            Dictionary<DayOfWeek, Dictionary<TimeSpan, int>> dicti = new Dictionary<DayOfWeek, Dictionary<TimeSpan, int>>();

            TimeSpan obri = new TimeSpan(8, 0, 0);
            TimeSpan tanca = new TimeSpan(21, 0, 0);
            TimeSpan increment = new TimeSpan(0, 45, 0);

            DateTime iniSemana = date;
            DateTime fiSemana = date;
            fiSemana.AddDays(7);

            TimeSpan ini = obri;
            TimeSpan fi = ini.Add(increment);
            DayOfWeek diaSemana = DayOfWeek.Monday;

            for (int i = 0; i < 6; i++)
            {
                Dictionary<TimeSpan, int> aux = new Dictionary<TimeSpan, int>();
                IEnumerable<Course> cursos = service.GetAll<Course>();

                int[] linees = new int[pol.Lanes.Count];
                for (int j = 0; j < linees.Length; j++) { linees[j] = 1; }

                Console.WriteLine(diaSemana.ToString());

                while (ini < tanca)
                {
                    foreach (Course c in cursos)
                    {
                        TimeSpan startHour = new TimeSpan(c.StartHour.Hour, c.StartHour.Minute, c.StartHour.Second);
                        TimeSpan finishHour = startHour.Add(increment);

                        if (c.Cancelled) continue;

                        if (c.StartDate.Date.CompareTo(fiSemana.Date) > 0) continue;

                        if (c.FinishDate.Date.CompareTo(iniSemana.Date) < 0) continue;

                        if (finishHour < ini) continue;

                        if (startHour > fi) continue;

                        Days diaAux = (Days)Math.Pow(2, i);
                        if ((c.CourseDays & diaAux) == diaAux) continue;

                        foreach (Lane l in c.Lanes) { linees[l.Number] = 0; }
                    }

                    int cont = 0;
                    foreach (int j in linees) { if (j == 1) cont++; }

                    aux.Add(ini, cont);
                    ini = ini.Add(increment);
                    fi = fi.Add(increment);
                }

                dicti.Add(diaSemana, aux);

                diaSemana++;
                date.AddDays(1);
                ini = obri;
                fi = ini.Add(increment);
            }

            return dicti;
        }
        
    }

}
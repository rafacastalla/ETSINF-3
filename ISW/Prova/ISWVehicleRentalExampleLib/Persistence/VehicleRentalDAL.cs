using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.Entity;
using ISWVehicleRentalExampleLib.Entities;
namespace ISWVehicleRentalExampleLib.Persistence
{
    public class VehicleRentalDAL:DbContext
    {
       

        public DbSet<Customer> customers { get; set; }
        public DbSet<Person> persons { get; set; }
        public DbSet<Reservation> reservations { get; set; }
        public DbSet<CreditCard> creditcards { get; set; }
        public DbSet<BranchOffice> offices { get; set; }
        public DbSet<Category> categories { get; set; }


        public IBranchOfficeDAO branchofficeDAO {
            get;
        }
        public ICategoryDAO categoryDAO
        {
            get;
        }      
        public ICustomerDAO customerDAO
        {
            get;
        }
        public IPersonDAO personDAO
        {
            get;
        }
        public IReservationDAO reservationDAO
        {
            get;
        }
        public ICreditCardDAO creditcardDAO
        {
            get;
        }

        private VehicleRentalDAL():base("DBConnectionString"){
            branchofficeDAO = new BranchOfficeDAOImp(this);
            categoryDAO = new CategoryDAOImp(this);
            customerDAO = new CustomerDAOImp(this);
            personDAO = new PersonDAOImp(this);
            reservationDAO = new ReservationDAOImp(this);
            creditcardDAO = new CreditCardDAOImp(this);
            Database.Initialize(true);

        }

        // DAL Implements Singleton Pattern
        private static VehicleRentalDAL instance = null;
        public static VehicleRentalDAL getVehicleRentalDAL()
        {
            if (instance == null)
                instance = new VehicleRentalDAL();
            return instance;
        }


        public void RemoveAllData()
        {
            try
            {
                persons.RemoveRange(persons);
                customers.RemoveRange(customers);
                offices.RemoveRange(offices);
                creditcards.RemoveRange(creditcards);
                categories.RemoveRange(categories);
                reservations.RemoveRange(reservations);
                SaveChanges();
            }
            catch (Exception e) {
                System.Diagnostics.Debug.WriteLine(e.ToString());
            }
        }

        public void Save()
        {
            try
            {
                this.SaveChanges();

            } catch (Exception e)
            {
                System.Diagnostics.Debug.WriteLine(e.ToString());
            }

            
        }
      
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ISWVehicleRentalExampleLib.Persistence;
using ISWVehicleRentalExampleLib.Entities;

namespace ISWVehicleRentalExampleLib.BusinessLogic
{

    public class BusinessController
    {
        private VehicleRentalDAL dal;
        private BusinessController()
        {
            dal = VehicleRentalDAL.getVehicleRentalDAL();

        }

        // Singleton pattern
        private static BusinessController instance = null;
        public static BusinessController getBusinessController()
        {
            if (instance == null)
                instance = new BusinessController();
            return instance;
        }

        public void removeAllData()
        {
            dal.RemoveAllData();
        }

        //Reservation

        public ICollection<Reservation> findReservationsbyCustomerID(string customerDNI)
        {
            return dal.reservationDAO.findReservationsbyCustomerDNI(customerDNI);

        }

        public void addReservation(Reservation res)
        {
            dal.reservationDAO.addReservation(res);
        }
        public void addReservation(Customer customer, BranchOffice pickUpOffice, DateTime pickupDate, BranchOffice returnOffice, DateTime returnDate, Category cat, IEnumerable<String> drivers)
        {
            Person p;

            //Remove Person object if it already exists and it is not a customer yet
            //This is the case when we create a Customer from an already existing person            
            //Entity framework does not support dynamic inheritance and inheritance object migration
            p = dal.personDAO.findPersonByDni(customer.dni);
            Customer c = dal.customerDAO.findCustomerByDni(customer.dni);
            //It is a person but it is not yet a Customer in the database
            if ((p != null) && (c == null))
            {
                //Implementing Person -> Customer inheritance Migration
                foreach (Reservation r in p.DrivenReservations)
                    customer.DrivenReservations.Add(r);
                dal.personDAO.removePerson(p);
            }
            
            Reservation res = new Reservation(customer,pickUpOffice,pickupDate, returnOffice, returnDate, cat);

            //Updating Branch Offices
            pickUpOffice.PickUpReservations.Add(res);
            returnOffice.ReturnReservations.Add(res);

            //Adding Drivers 

            foreach (String dni in drivers) {
                //Many to Many relationship

                p=dal.personDAO.findPersonByDni(dni);
                //This verification is not to add the customer as a driver twice
                //because Customer already added as a driver in Reservation constructor
                //p is null if a new customer has been added for this reservation
                //because in this case the customer is not in the DB yet
                if(p!= null)
                if (p.dni!=res.Customer.dni)
                {
                    res.Drivers.Add(p);
                    p.DrivenReservations.Add(res);
                }
            }



            //Adding reservation to DB
            dal.reservationDAO.addReservation(res);
        }

        //Customer
        public ICollection<Customer> findAllCustomers()
        {
            return dal.customerDAO.findAllCustomers();
        }

        public Customer findCustomerByDni(string dni)
        {
            return dal.customerDAO.findCustomerByDni(dni);
        }
        //Person


        public ICollection<Person> findAllPersons()
        {
            return dal.personDAO.findAllPersons();
        }

   

        public Person findPersonByDni(string dni)
        {
            return dal.personDAO.findPersonByDni(dni);
        }

        public void addPerson(Person person)
        {
            if (dal.personDAO.findPersonByDni(person.dni) == null)
                dal.personDAO.addPerson(person);
            else throw new BusinessLogicException("Person already exists.");
        }


        //BranchOffice
        public ICollection<BranchOffice> findAllBranchOffices()
        {
            return dal.branchofficeDAO.findAllBranchOffices();
        }

        public void addBranchOffice(BranchOffice br)
        {
            dal.branchofficeDAO.addBranchOffice(br);
        }

        //Category
        public ICollection<Category> findAllCategories()
        {
            return dal.categoryDAO.findAllCategories();
        }

        public void addCategory(Category cat)
        {
            dal.categoryDAO.addCategory(cat);
        }

        //CreditCard

        public CreditCard findCreditCardByNumber(string numberCC)
        {
            return dal.creditcardDAO.findCreditCardByNumber(numberCC);
        }

    }
}

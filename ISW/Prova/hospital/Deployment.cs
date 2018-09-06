public class Deployment {
    public Hospital hospital;
    public Speciality speciality;

    public int floor;
    public int number_employees;

    public Deployment () {}

    public Deployment (Hospital hospital, Speciality speciality, int floor, int number_employees) {
        this.hospital = hospital;
        this.speciality = speciality;
        this.floor = floor;
        this.number_employees = number_employees;
    }
}

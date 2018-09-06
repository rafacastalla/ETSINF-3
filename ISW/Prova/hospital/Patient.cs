public class Patient {
    public int Id;
    public string Name;
    public string Surname;
    public bool? isMale;
    public int Age;
    public int Phone;
    public string Address;

    public Patient() {
    }

    public Patient(int Id, string Name, string Surname, bool isMale, int Age, int Phone, string Address) {
        this.Id = Id;
        this.Name = Name;
        this.Surname = Surname;
        this.isMale = isMale;
        this.Age = Age;
        this.Phone = Phone;
        this.Address = Address;
    }

}

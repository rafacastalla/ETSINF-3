public class PrivateAmbulance {
    public string CompanyName {
        get;
        set;
    }

    public PrivateAmbulance()
    : base() {
    }

    public PrivateAmbulance(int Id, string EquipmentType, double Latitude, double Longitude, string CompanyName)
    : base(Id, EquipmentType, Latitude, Longitude) {
        this.CompanyName = CompanyName;
    }
}


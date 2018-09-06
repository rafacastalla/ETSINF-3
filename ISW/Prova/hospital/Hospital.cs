public class Hospital {
    private virtual ICollection<HospitalBased> HospitalBasedAmbulances {
        get;
    }
    private virtual ICollection<Deployment> Supports {
        get;
    }

    public string Name;
    public string Address;
    public double Latitude, Longitude;
    public EmergencyCallService Service;

    public Hospital() {
        HospitalBasedAmbulances = new List<HospitalBased>();
        Supports = new List<Deployment>();
    }

    public Hospital(string Name, string Address,
                    double Latitude, double Longitude,
                    EmergencyCallService Service, Deployment deployment) : this() {
        this.Name = Name;
        this.Address = Address;
        this.Longitude = Longitude;
        this.Latitude = Latitude;
        this.EmergencyCallService = Service;
        addDeployment(deployment);
    }

    public void addHospitalBased(HospitalBased h);
    public void removeHospitalBased(HospitalBased h);

    public void addDeployment(Deployment d);
    public void removeDeployment(Deployment d);
}


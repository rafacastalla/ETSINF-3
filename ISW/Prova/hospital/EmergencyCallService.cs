public class EmergencyCallService {
    private virtual ICollection<Hospital> Hospitals {
        get;
    }
    private virtual ICollection<Ambulance> Ambulances {
        get;
    }
    private virtual ICollection<EmergencyCall> EmergencyCalls {
        get;
    }

    public EmergencyCallService() {
        Hospitals = new List<Hospital>();
        Ambulances = new List<Ambulances>();
        EmergencyCalls = new List<EmergencyCall>();
    }

    public EmergencyCallService(Hospital hospital, Ambulance ambulance)
    : this() {
        Hospitals.Add(hospital);
        Ambulance.Add(ambulance);
    }
}

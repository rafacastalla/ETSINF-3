public class Ambulance {
    private ICollection<EmergencyCall> calls {
        get;
    }
    public int Id {
        get;
        set;
    }
    public string EquipmentType {
        get;
        set;
    }
    public double Latitude {
        get;
        set;
    }
    public double Longitude {
        get;
        set;
    }

    public Ambulance() {
        calls = new List<EmergencyCall>();
    }

    public Ambulance(int Id, string EquipmentType, double Latitude, double Longitude)
    : this() {
        this.Id = Id;
        this.EquipmentType = EquipmentType;
        this.Latitude = Latitude;
        this.Longitude = Longitude;
    }

    public ICollection<EmergencyCall> listCalls() {}
    public void pushCall( EmergencyCall emergencycall ) {}
    public EmergencyCall popCall() {}
    public EmergencyCall getCall( /* ... */ ) {}
}

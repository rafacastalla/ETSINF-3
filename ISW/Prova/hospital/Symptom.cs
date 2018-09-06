public class Symptom {
    private virtual ICollection<Speciality> specialities {
        get;
    }
    private virtual ICollection<EmergencyCall> emergencyCalls {
        get;
    }

    public int StageOfGravity;
    public int Duration;
    public string Description;

    public Symptom () {
        specialities = new List<Speciality>();
        emergencyCalls = new List<EmergencyCall>();
    }

    public Symptom(int StageOfGravity, int Duration, string Description,
                   Speciality speciality, EmergencyCall emergencyCall) : this() {
        this.StageOfGravity = StageOfGravity;
        this.Duration = Duration;
        this.Description = Description;
        addSpeciality(speciality);
        addEmergencyCall(emergencyCall);
    }

    public void addSpeciality(Speciality s);
    public void removeSpeciality(Speciality s);

    public void addEmergencyCall(EmergencyCall e);
    public void removeEmergencyCall(EmergencyCall e);
}

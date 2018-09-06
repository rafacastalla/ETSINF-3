public class Application {
    public static int Main(string[] args)
    {
        EmergencyCallService ecs = new EmergencyCallService();

        Hospital hospital = new Hospital();
        hospital.Name = "9 Octubre";
        hospital.Address = "Avenida 9 Octubre";
        hospital.Latitude = 39.4;
        hospital.Longitude = -0.4;
        ecs.addHospital(hospital);

        Speciality speciality = new Speciality();
        speciality.Name = "Cirujia";

        Deployment deployment = new Deployment(hospital, speciality, 1, 15);
        speciality.addDeployment(deployment);
        hospital.addDeployment(deployment);

        Symptom symptom = new Symptom();
        symptom.StageOfGravity = 4;
        symptom.Duration = 5;
        symptom.Description = "Costillas rotas - Mafia";
        symptom.Speciality = speciality;
        speciality.addSymptom(symptom);

        Patient patient = new Patient(121241, "Carlos", "Galindo", true, 25, 643328918, "Calle Street");

        Ambulance ambulance = new HospitalBased(10931, "Muletas", 40, 0);
        hospital.addHospitalBased(ambulance);
        ecs.addAmbulance(ambulance);

        EmergencyCall emergencyCall = new EmergencyCall(39.4, -0.5, new DateTime(), patient, ambulance, hospital, symptom);
        symptom.addEmergencyCall(emergencyCall);
        ambulance.addEmergencyCall(emergencyCall);
        hospital.addEmergencyCall(emergencyCall);
        ecs.addEmergencyCall(emergencyCall);

        PrivateAmbulance privateAmbulance = new PrivateAmbulance(1231513, "Mas muletas", 40, -20, "Company Inc.");

        return 0;
    }
}

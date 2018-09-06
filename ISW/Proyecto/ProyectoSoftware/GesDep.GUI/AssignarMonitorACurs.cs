using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GestDepLib.Services;
using GestDepLib.Entities;

namespace GesDep.GUI
{
    public partial class AssignarMonitorACurs : Form
    {
        private IGestDepService service;
        private Course curs;
        private bool moni = false;
        public AssignarMonitorACurs(IGestDepService service)
        {
            InitializeComponent();
            this.service = service;


            
            //selectCurs.Items.Clear();
            IEnumerable<Course> courses = service.GetCourses();
            selectCurs.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            selectMonitor.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            selectMonitor.Enabled = false;
            selectCurs.Items.Clear();

            foreach (Course c in courses)
            {
                selectCurs.Items.Add(c.Description.ToString());
            }



            //selectCurs.Items.Add(courses);
            selectMonitor.Items.Clear();
            //IEnumerable<Monitor> m = service.getCourses();
            selectMonitor.Items.Add(courses);

            this.curs = null;
        }

        private void AssignarMonitorACurs_Load(object sender, EventArgs e)
        {

        }

        private void Seleccionar_Curs(object sender, EventArgs e)
        {
            
            //string aux = selectCurs.SelectedItem.ToString();
            //selectCurs.Text = selectCurs.SelectedItem.ToString();
            curs = service.FindCourseByName(selectCurs.SelectedItem.ToString());

            mostrarDataInici.Text = "Data Inici: " + curs.StartDate.ToString();
            mostrarDataFi.Text = "Data Fi: " + curs.FinishDate.ToString();
            mostrarHoraInici.Text = "Hora Inici: " + curs.StartHour.ToString();
            mostrarDuracio.Text = "Duració: " + curs.Duration.ToString();
            mostrarMinParticipants.Text = "Mínim Participants: " + curs.MinimunEnrollments.ToString();
            mostrarMaxParticipants.Text = "Màxim Participants: " + curs.MaximunEnrollments.ToString();
            mostrarCancelat.Text = "Cancelat: " + curs.Cancelled.ToString();
            mostrarPreu.Text = "Preu: " + curs.Price.ToString();
            mostrarDescripcio.Text = "Descripció: " + curs.Description.ToString();
            mostrarDies.Text = "Dies: " + curs.CourseDays.ToString();
            if (curs.Monitor != null)
            {
                lblMonitor.Text = "Monitor: " + curs.Monitor.Id.ToString();
                selectMonitor.Enabled = false;
                moni = true;
            }
            else
            {
                lblMonitor.Text = "Monitor: null";
                selectMonitor.Enabled = true;
                moni = false;
                List<Monitor> monitors = service.GetAvailableMonitors(curs);
                selectMonitor.Items.Clear();
                foreach (Monitor m in monitors)
                {
                    selectMonitor.Items.Add(m.Id.ToString());
                }
            }

        }

        private void Seleccionar_Monitor(object sender, EventArgs e)
        {
       
        }

        private void Aceptar(object sender, EventArgs e)
        {
            if (selectCurs.SelectedIndex != -1)
            {
                curs = service.FindCourseByName(selectCurs.SelectedItem.ToString());
            }

            if (curs == null)
            {
                DialogResult answer = MessageBox.Show(this, "El curso no ha sido seleccionado!", "Error",
                MessageBoxButtons.OK, // Buttons included
                MessageBoxIcon.Error); // Icon

            }else{
                if (moni)
                {
                    this.Close();
                }else if(!moni && selectMonitor.SelectedIndex == -1)
                {
                    DialogResult answer = MessageBox.Show(this, "Si quieres asignar un monitor, tienes de seleccionarlo", "Error",
                    MessageBoxButtons.OK, // Buttons included
                    MessageBoxIcon.Error); // Icon
                }else if(!moni && selectMonitor.SelectedIndex != -1)
                {
                    Monitor m = service.FindMonitorById(selectMonitor.SelectedItem.ToString());
                    service.SetCourseMonitor(curs, m);
                    this.Close();
                }
            }

           
            //mostrarDescripcio = "Descripció: " + curs.Description.ToString();
            //mostrarDies = "Dies: " + curs.CourseDays.ToString();





            
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}

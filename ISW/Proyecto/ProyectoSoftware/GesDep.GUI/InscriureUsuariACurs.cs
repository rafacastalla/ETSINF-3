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
    public partial class InscriureUsuariACurs : Form
    {
        private IGestDepService service;
        private string dni;
        private User usuari;
        private Course curs;
        private IEnumerable<Course> cursos;

        public InscriureUsuariACurs(IGestDepService service)
        {
            InitializeComponent();
            this.service = service;
            
            cursos = service.GetCourses();
            selectCurs.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            selectCurs.Items.Clear();

            foreach(Course c in cursos)
            {
                selectCurs.Items.Add(c.Description.ToString());
            }

            curs = null;
            dni = null;
            usuari = null;
        }

        private void seleccionarCursos(object sender, EventArgs e)
        {
            //Course aux = (Course) selectCurs.SelectedItem;
            //selectCurs.Text = selectCurs.SelectedItem.ToString();
            curs = service.FindCourseByName(selectCurs.SelectedItem.ToString());
        }

        private void aceptarForm(object sender, EventArgs e)
        {

            string message;
            string caption = "Ha habido un error";
            MessageBoxButtons buttons;
            DialogResult result;
            if (usuari == null || curs == null)
            {//esta buit
                message = "Dni incorrecto o curso no seleccionado ";
                buttons = MessageBoxButtons.OK;
                result = MessageBox.Show(message, caption, buttons);
            }
            else {
                DateTime data = DateTime.Now;
                service.EnrollInCourse(usuari, curs, data);

                message = "Se ha insertado correctamente ";
                buttons = MessageBoxButtons.OK;
                result = MessageBox.Show(message, caption, buttons);

                this.Close();
            }
        }
        private void findUser(object sender, EventArgs e)
        {
            dni = dniEscrit.Text.ToString();
            if (dni == null)
            {//esta buit
                DialogResult answer = MessageBox.Show(this, "No has insertado dni", "Error",
                MessageBoxButtons.OK,
                MessageBoxIcon.Error); // Icon
            }
            else if (dni.Length != 10)
            {//te la grandaria de un dni
                DialogResult answer = MessageBox.Show(this, "El dni no es correcto", "Error",
                MessageBoxButtons.OK,
                MessageBoxIcon.Error); // Icon
            }
            else {
                try
                {
                    usuari = service.FindUserById(dni);
                }catch(ServiceException )
                {
                    DialogResult answer = MessageBox.Show(this, "El usuario no existe", "Error",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error); // Icon
                }
                if (usuari != null) {
                    mostrarNom.Text = "Nom: " + usuari.Name.ToString();
                    mostrarAdresa.Text = "Adreça: " + usuari.Address.ToString();
                    mostrarZipcode.Text = "ZipCode: " + usuari.ZipCode.ToString();
                    mostrarIban.Text = "IBAN: " + usuari.IBAN.ToString();
                    mostrarCumple.Text = "Data Naixement: " + usuari.BirthDate.ToString();
                    mostrarRet.Text = "Retirat: " + usuari.Retired.ToString();
                }
            }            
        }

        private void InscriureUsuariACurs_Load(object sender, EventArgs e)
        {

        }
    }
}

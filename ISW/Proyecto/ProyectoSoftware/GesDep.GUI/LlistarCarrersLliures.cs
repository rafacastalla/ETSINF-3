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
using GestDepLib.Persistence;

namespace GesDep.GUI
{
    public partial class LlistarCarrersLliures : Form
    {
        private IGestDepService service;
        private IEnumerable<Pool> pisines;
        private Pool piscina;

        public LlistarCarrersLliures(IGestDepService service)
        {
            InitializeComponent();
            this.service = service;

            pisines = service.GetPools();
            selectPiscina.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            selectPiscina.Items.Clear();
            foreach (Pool p in pisines)
            {
                selectPiscina.Items.Add(p.ZipCode.ToString());
            }
            piscina = null;

        }

        private void seleccionarPiscina(object sender, EventArgs e)
        {
            piscina = service.FindPoolByZipCode(Int32.Parse(selectPiscina.SelectedItem.ToString()));
        }

        private void buscarCarrersLliures(object sender, EventArgs e)
        {
            string message;
            string caption = "Ha habido un error";
            MessageBoxButtons buttons;
            DialogResult result;

            String msgMostrar = "";

            DateTime data = agafarData.Value;
            DayOfWeek dia = data.DayOfWeek;
            if(piscina == null)
            {
                message = "No se ha seleccionado piscina";
                buttons = MessageBoxButtons.OK;
                result = MessageBox.Show(message, caption, buttons);

            }else if(dia != DayOfWeek.Monday){

                message = "Debes seleccionar el lunes de la semana";
                buttons = MessageBoxButtons.OK;
                result = MessageBox.Show(message, caption, buttons);

            }else{
                Dictionary<DayOfWeek, Dictionary<TimeSpan, int>> lanes = service.GetFreeLanes(piscina,data);
                //plenar llistaVisual
                llistaVisual.Text = "";
                 msgMostrar = "                    Lunes     Martes   Miercoles   Jueves   Viernes  Sabado\n";
                llistaVisual.Items.Add(msgMostrar);
                int [,] matriu = new int [18,6];
                String[] vector = new String[18];
                int i = 0, j;
                foreach (KeyValuePair<DayOfWeek, Dictionary<TimeSpan, int>> diesSemana in lanes)
                {
                    j = 0;
                    
                    foreach (KeyValuePair<TimeSpan, int> tupla in diesSemana.Value)
                    {
                        vector[j] = tupla.Key.ToString();
                        matriu[j, i] = tupla.Value;
                        j++;
                    }
                    i++;
                    
                }

                for( i = 0; i< 18; i++)
                {
                    msgMostrar = vector[i];
                    for (j = 0; j<6; j++)
                    {   
                        msgMostrar += "             " + matriu[i,j];
                    }
                    msgMostrar += "\n";
                   llistaVisual.Items.Add(msgMostrar);
                }

            }

        }

        private void llistaVisual_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void llistaVisual_SelectedIndexChanged_1(object sender, EventArgs e)
        {

        }
    }
}

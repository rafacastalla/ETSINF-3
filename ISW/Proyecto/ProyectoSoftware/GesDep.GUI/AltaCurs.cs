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
using GestDepLib.Persistence;
using GestDepLib.Entities;

namespace GesDep.GUI
{
    public partial class AltaCurs : Form
    {
        IGestDepService service;
        IDAL idal;


        public AltaCurs()
        {
            InitializeComponent();
         

            idal = new EntityFrameworkDAL(new GestDepDbContext());
            service = new GestDepService(idal);

            IEnumerable<Pool> pools = service.GetPools();
            //   List<Pool> picinas = pools.ToList();
            comboSelectPicina.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            combohores.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            comboSelectPicina.Items.Clear();
           
            foreach (Pool p in pools)
            {
                comboSelectPicina.Items.Add(p.ZipCode.ToString());
            }
  
            //Añadir check box a una llista

   






        }

    private void label1_Click(object sender, EventArgs e)
        {
        
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void dateTimePicker2_ValueChanged(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        private void label10_Click(object sender, EventArgs e)
        {

        }

        private void label11_Click(object sender, EventArgs e)
        {

        }

        private void label13_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged_1(object sender, EventArgs e)
        {

        }

        private void bAcceptar_Click(object sender, EventArgs e)
        {

            string message ;
            string caption = "Ha habido un error";
            MessageBoxButtons buttons;
            DialogResult result;
            double price;
            int minimAl, maxAl;
            if (dateini.Value > datefi.Value)
            {
                message = "La fecha de inicio no puede ser posterior a la fin";
                buttons = MessageBoxButtons.OK;
                result = MessageBox.Show(message, caption, buttons);
            }else if(comboSelectPicina.SelectedIndex == -1)
            {
                message = "Tienes de seleccionar una picina";
                buttons = MessageBoxButtons.OK;
                result = MessageBox.Show(message, caption, buttons);
            }
            else if (txtdescripcio.Text == "")
            {
                message = "Tienes de escribir una descripción";
                buttons = MessageBoxButtons.OK;
                result = MessageBox.Show(message, caption, buttons);
            }
            else if (combohores.SelectedIndex == -1)
            {
                message = "Tienes de seleccionar una hora";
                buttons = MessageBoxButtons.OK;
                result = MessageBox.Show(message, caption, buttons);
            }
            else if (!Double.TryParse(txtPreu.Text, out price)|| price < 0)
            {
                message = "Tienes de incluir un precio";
                buttons = MessageBoxButtons.OK;
                result = MessageBox.Show(message, caption, buttons);
            }
            else if (!Int32.TryParse(txtMinimAl.Text, out minimAl) || minimAl < 0)
            {
                message = "Numero de alumnos mínimo erroneo";
                buttons = MessageBoxButtons.OK;
                result = MessageBox.Show(message, caption, buttons);
            }
            else if (!Int32.TryParse(txtMaxA.Text, out maxAl) || maxAl < 0)
            {
                message = "Numero de alumnos máximo erroneo";
                buttons = MessageBoxButtons.OK;
                result = MessageBox.Show(message, caption, buttons);
            }
            else if (minimAl > maxAl)
            {
                message = "No puede ser menor el máximo que el mínimo número de alumnos";
                buttons = MessageBoxButtons.OK;
                result = MessageBox.Show(message, caption, buttons);
            }else
            {
                Pool pSelected = service.FindPoolByZipCode(Convert.ToInt32(comboSelectPicina.SelectedItem.ToString()));
                DateTime dStart = dateini.Value;
                DateTime dfi = datefi.Value;

                String valhora = combohores.SelectedItem.ToString();
                Char delimiter = ':';
                String[] substrings = valhora.Split(delimiter);

                  Days daysCurs = new Days();
                int cont = 0;
               // Days daysCurs = Days.Wednesday | Days.Friday;
                if (cbdilluns.Checked){
                    cont = 1;
                    daysCurs = Days.Monday;
                }
                if (cbcdimarts.Checked)
                {
                    cont = 1;
                    daysCurs = daysCurs | Days.Tuesday;
                }
                if (cbdimecres.Checked)
                {
                    cont = 1;
                    daysCurs = daysCurs |  Days.Wednesday;
                }
                if (cbdijous.Checked)
                {
                    cont = 1;
                    daysCurs = daysCurs | Days.Thursday;
                }
                if (cbdivendres.Checked)
                {
                    cont = 1;
                    daysCurs = daysCurs |  Days.Friday;
                }
                if (cbdisapte.Checked)
                {
                    cont = 1;
                    daysCurs = daysCurs | Days.Saturday;
                }
                if(cont == 1)
                {
                    List<int> lan = new List<int>();
                    foreach (int l in chekedLanes.CheckedItems.Cast<int>())
                    {
                        lan.Add(l);
                    }
                    if (lan.Count > 0)
                    {
                        bool inser = service.AddCourse(pSelected, txtdescripcio.Text, dStart, dfi, createTime(Int32.Parse(substrings[0]), Int32.Parse(substrings[1]), 0),
                                        new TimeSpan(0, 45, 0), daysCurs, minimAl, maxAl, price, lan);

                        if (!inser)
                        {
                            message = "No se ha insertado el curso";
                            buttons = MessageBoxButtons.OK;
                            result = MessageBox.Show(message, caption, buttons);
                        }
                        else
                        {
                            message = "Se ha insertado el curso correctamente";
                            buttons = MessageBoxButtons.OK;
                            result = MessageBox.Show(message, caption, buttons);
                            this.Close();
                        }
                    }else
                    {
                        message = "Tienes que seleccionar alguna linia";
                        buttons = MessageBoxButtons.OK;
                        result = MessageBox.Show(message, caption, buttons);
                    }
                }else
                {
                    message = "Tienes que seleccionar al menos un día";
                    buttons = MessageBoxButtons.OK;
                    result = MessageBox.Show(message, caption, buttons);
                }
               
            }
        }

        private void AltaCurs_Load(object sender, EventArgs e)
        {

        }

        private void comboSelectPicina_SelectedIndexChanged(object sender, EventArgs e)
        {
           
        }

        private void txtPreu_TextChanged(object sender, EventArgs e)
        {

        }

        private static DateTime createTime(int hours, int minutes, int seconds)
        {
            DateTime now = DateTime.Now;
            return new DateTime(now.Year, now.Month, now.Day, hours, minutes, seconds);
        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void comboSelectPicina_Click(object sender, EventArgs e)
        {

        }

        private void comboSelectPicina_SelectionChangeCommitted(object sender, EventArgs e)
        {
            chekedLanes.Items.Clear();

            //ComboBox senderComboBox = (ComboBox)sender;
            //  chekedLanes.Items.Add(senderComboBox.SelectedIndex, false);
            if (comboSelectPicina.SelectedIndex != -1)
            {
                chekedLanes.Items.Add(comboSelectPicina.SelectedIndex, false);
                Pool pSelected = service.FindPoolByZipCode(Convert.ToInt32(comboSelectPicina.SelectedItem.ToString()));

                IEnumerable<Lane> linies = pSelected.Lanes;

                foreach (Lane l in linies)
                {
                    chekedLanes.Items.Add(l.Number, false);
                }
            }
        }
    }
}

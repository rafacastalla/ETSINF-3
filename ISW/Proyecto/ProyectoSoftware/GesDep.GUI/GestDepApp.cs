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
namespace GesDep.GUI
{
    public partial class GestDepApp : Form
    {
        private IGestDepService service;
        public GestDepApp(IGestDepService service)
        {
            InitializeComponent();
            this.service = service;
        }

        private void GestDepApp_Load(object sender, EventArgs e)
        {

        }

        private void añadirMonitorToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void donarAltaCursToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
           // this.Hide();
            AltaCurs al = new AltaCurs();
            al.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            InscriureUsuariACurs al = new InscriureUsuariACurs(service);
            al.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            AssignarMonitorACurs al = new AssignarMonitorACurs(service);
            al.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            LlistarCarrersLliures al = new LlistarCarrersLliures(service);
            al.Show();
        }
    }
}

namespace GesDep.GUI
{
    partial class AltaCurs
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.txtdescripcio = new System.Windows.Forms.TextBox();
            this.comboSelectPicina = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.dateini = new System.Windows.Forms.DateTimePicker();
            this.datefi = new System.Windows.Forms.DateTimePicker();
            this.label6 = new System.Windows.Forms.Label();
            this.txtdur = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.cbdilluns = new System.Windows.Forms.CheckBox();
            this.cbcdimarts = new System.Windows.Forms.CheckBox();
            this.cbdimecres = new System.Windows.Forms.CheckBox();
            this.cbdijous = new System.Windows.Forms.CheckBox();
            this.cbdivendres = new System.Windows.Forms.CheckBox();
            this.cbdisapte = new System.Windows.Forms.CheckBox();
            this.label10 = new System.Windows.Forms.Label();
            this.txtPreu = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.txtMinimAl = new System.Windows.Forms.TextBox();
            this.txtMaxA = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.bAcceptar = new System.Windows.Forms.Button();
            this.combohores = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.chekedLanes = new System.Windows.Forms.CheckedListBox();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(44, 43);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(57, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Descripcio";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(44, 71);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(52, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "Data Inici";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(44, 148);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 13);
            this.label4.TabIndex = 4;
            this.label4.Text = "Horari";
            this.label4.Click += new System.EventHandler(this.label4_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(44, 186);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(44, 13);
            this.label5.TabIndex = 5;
            this.label5.Text = "Duració";
            this.label5.Click += new System.EventHandler(this.label5_Click);
            // 
            // txtdescripcio
            // 
            this.txtdescripcio.Location = new System.Drawing.Point(146, 36);
            this.txtdescripcio.Name = "txtdescripcio";
            this.txtdescripcio.Size = new System.Drawing.Size(334, 20);
            this.txtdescripcio.TabIndex = 6;
            // 
            // comboSelectPicina
            // 
            this.comboSelectPicina.FormattingEnabled = true;
            this.comboSelectPicina.Location = new System.Drawing.Point(145, 294);
            this.comboSelectPicina.Name = "comboSelectPicina";
            this.comboSelectPicina.Size = new System.Drawing.Size(121, 21);
            this.comboSelectPicina.TabIndex = 12;
            this.comboSelectPicina.SelectedIndexChanged += new System.EventHandler(this.comboSelectPicina_SelectedIndexChanged);
            this.comboSelectPicina.SelectionChangeCommitted += new System.EventHandler(this.comboSelectPicina_SelectionChangeCommitted);
            this.comboSelectPicina.Click += new System.EventHandler(this.comboSelectPicina_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(44, 297);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 13);
            this.label1.TabIndex = 11;
            this.label1.Text = "Picina";
            // 
            // dateini
            // 
            this.dateini.Location = new System.Drawing.Point(146, 71);
            this.dateini.Name = "dateini";
            this.dateini.Size = new System.Drawing.Size(200, 20);
            this.dateini.TabIndex = 13;
            // 
            // datefi
            // 
            this.datefi.Location = new System.Drawing.Point(146, 106);
            this.datefi.Name = "datefi";
            this.datefi.Size = new System.Drawing.Size(200, 20);
            this.datefi.TabIndex = 15;
            this.datefi.ValueChanged += new System.EventHandler(this.dateTimePicker2_ValueChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(44, 106);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(41, 13);
            this.label6.TabIndex = 14;
            this.label6.Text = "Data Fi";
            this.label6.Click += new System.EventHandler(this.label6_Click);
            // 
            // txtdur
            // 
            this.txtdur.Enabled = false;
            this.txtdur.Location = new System.Drawing.Point(148, 179);
            this.txtdur.Name = "txtdur";
            this.txtdur.Size = new System.Drawing.Size(65, 20);
            this.txtdur.TabIndex = 19;
            this.txtdur.Text = "45";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(46, 231);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(30, 13);
            this.label9.TabIndex = 20;
            this.label9.Text = "Díes";
            this.label9.Click += new System.EventHandler(this.label9_Click);
            // 
            // cbdilluns
            // 
            this.cbdilluns.AutoSize = true;
            this.cbdilluns.Location = new System.Drawing.Point(146, 227);
            this.cbdilluns.Name = "cbdilluns";
            this.cbdilluns.Size = new System.Drawing.Size(57, 17);
            this.cbdilluns.TabIndex = 21;
            this.cbdilluns.Text = "Dilluns";
            this.cbdilluns.UseVisualStyleBackColor = true;
            // 
            // cbcdimarts
            // 
            this.cbcdimarts.AutoSize = true;
            this.cbcdimarts.Location = new System.Drawing.Point(146, 250);
            this.cbcdimarts.Name = "cbcdimarts";
            this.cbcdimarts.Size = new System.Drawing.Size(61, 17);
            this.cbcdimarts.TabIndex = 22;
            this.cbcdimarts.Text = "Dimarts";
            this.cbcdimarts.UseVisualStyleBackColor = true;
            // 
            // cbdimecres
            // 
            this.cbdimecres.AutoSize = true;
            this.cbdimecres.Location = new System.Drawing.Point(210, 227);
            this.cbdimecres.Name = "cbdimecres";
            this.cbdimecres.Size = new System.Drawing.Size(70, 17);
            this.cbdimecres.TabIndex = 23;
            this.cbdimecres.Text = "Dimecres";
            this.cbdimecres.UseVisualStyleBackColor = true;
            // 
            // cbdijous
            // 
            this.cbdijous.AutoSize = true;
            this.cbdijous.Location = new System.Drawing.Point(211, 250);
            this.cbdijous.Name = "cbdijous";
            this.cbdijous.Size = new System.Drawing.Size(55, 17);
            this.cbdijous.TabIndex = 24;
            this.cbdijous.Text = "Dijous";
            this.cbdijous.UseVisualStyleBackColor = true;
            // 
            // cbdivendres
            // 
            this.cbdivendres.AutoSize = true;
            this.cbdivendres.Location = new System.Drawing.Point(279, 227);
            this.cbdivendres.Name = "cbdivendres";
            this.cbdivendres.Size = new System.Drawing.Size(74, 17);
            this.cbdivendres.TabIndex = 25;
            this.cbdivendres.Text = "Divendres";
            this.cbdivendres.UseVisualStyleBackColor = true;
            // 
            // cbdisapte
            // 
            this.cbdisapte.AutoSize = true;
            this.cbdisapte.Location = new System.Drawing.Point(279, 250);
            this.cbdisapte.Name = "cbdisapte";
            this.cbdisapte.Size = new System.Drawing.Size(67, 17);
            this.cbdisapte.TabIndex = 26;
            this.cbdisapte.Text = "Dissabte";
            this.cbdisapte.UseVisualStyleBackColor = true;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(44, 347);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(29, 13);
            this.label10.TabIndex = 28;
            this.label10.Text = "Preu";
            this.label10.Click += new System.EventHandler(this.label10_Click);
            // 
            // txtPreu
            // 
            this.txtPreu.Location = new System.Drawing.Point(146, 344);
            this.txtPreu.Name = "txtPreu";
            this.txtPreu.Size = new System.Drawing.Size(65, 20);
            this.txtPreu.TabIndex = 29;
            this.txtPreu.Text = "10";
            this.txtPreu.TextChanged += new System.EventHandler(this.txtPreu_TextChanged);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(44, 397);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(47, 13);
            this.label11.TabIndex = 30;
            this.label11.Text = "Alumnes";
            this.label11.Click += new System.EventHandler(this.label11_Click);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(142, 397);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(36, 13);
            this.label12.TabIndex = 31;
            this.label12.Text = "Mínim";
            // 
            // txtMinimAl
            // 
            this.txtMinimAl.Location = new System.Drawing.Point(184, 394);
            this.txtMinimAl.Name = "txtMinimAl";
            this.txtMinimAl.Size = new System.Drawing.Size(65, 20);
            this.txtMinimAl.TabIndex = 32;
            this.txtMinimAl.Text = "1";
            // 
            // txtMaxA
            // 
            this.txtMaxA.Location = new System.Drawing.Point(316, 394);
            this.txtMaxA.Name = "txtMaxA";
            this.txtMaxA.Size = new System.Drawing.Size(65, 20);
            this.txtMaxA.TabIndex = 34;
            this.txtMaxA.Text = "15";
            this.txtMaxA.TextChanged += new System.EventHandler(this.textBox1_TextChanged_1);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(274, 397);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(37, 13);
            this.label13.TabIndex = 33;
            this.label13.Text = "Máxim";
            this.label13.Click += new System.EventHandler(this.label13_Click);
            // 
            // bAcceptar
            // 
            this.bAcceptar.Location = new System.Drawing.Point(129, 515);
            this.bAcceptar.Name = "bAcceptar";
            this.bAcceptar.Size = new System.Drawing.Size(335, 23);
            this.bAcceptar.TabIndex = 35;
            this.bAcceptar.Text = "Acceptar";
            this.bAcceptar.UseVisualStyleBackColor = true;
            this.bAcceptar.Click += new System.EventHandler(this.bAcceptar_Click);
            // 
            // combohores
            // 
            this.combohores.FormattingEnabled = true;
            this.combohores.Items.AddRange(new object[] {
            "8:00",
            "8:45",
            "9:30",
            "10:15",
            "11:00",
            "11:45",
            "12:30",
            "13:15",
            "14:00",
            "14:45",
            "15:30",
            "16:15",
            "17:00",
            "17:45",
            "18:30",
            "19:15",
            "20:00",
            "20:45"});
            this.combohores.Location = new System.Drawing.Point(148, 145);
            this.combohores.Name = "combohores";
            this.combohores.Size = new System.Drawing.Size(85, 21);
            this.combohores.TabIndex = 36;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(47, 439);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(34, 13);
            this.label7.TabIndex = 37;
            this.label7.Text = "Linies";
            this.label7.Click += new System.EventHandler(this.label7_Click);
            // 
            // chekedLanes
            // 
            this.chekedLanes.FormattingEnabled = true;
            this.chekedLanes.Location = new System.Drawing.Point(129, 435);
            this.chekedLanes.Name = "chekedLanes";
            this.chekedLanes.Size = new System.Drawing.Size(120, 64);
            this.chekedLanes.TabIndex = 38;
            // 
            // AltaCurs
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(757, 550);
            this.Controls.Add(this.chekedLanes);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.combohores);
            this.Controls.Add(this.bAcceptar);
            this.Controls.Add(this.txtMaxA);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.txtMinimAl);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.txtPreu);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.cbdisapte);
            this.Controls.Add(this.cbdivendres);
            this.Controls.Add(this.cbdijous);
            this.Controls.Add(this.cbdimecres);
            this.Controls.Add(this.cbcdimarts);
            this.Controls.Add(this.cbdilluns);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.txtdur);
            this.Controls.Add(this.datefi);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.dateini);
            this.Controls.Add(this.comboSelectPicina);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtdescripcio);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Name = "AltaCurs";
            this.Text = "AltaCurs";
            this.Load += new System.EventHandler(this.AltaCurs_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtdescripcio;
        private System.Windows.Forms.ComboBox comboSelectPicina;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DateTimePicker dateini;
        private System.Windows.Forms.DateTimePicker datefi;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtdur;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.CheckBox cbdilluns;
        private System.Windows.Forms.CheckBox cbcdimarts;
        private System.Windows.Forms.CheckBox cbdimecres;
        private System.Windows.Forms.CheckBox cbdijous;
        private System.Windows.Forms.CheckBox cbdivendres;
        private System.Windows.Forms.CheckBox cbdisapte;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox txtPreu;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox txtMinimAl;
        private System.Windows.Forms.TextBox txtMaxA;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Button bAcceptar;
        private System.Windows.Forms.ComboBox combohores;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.CheckedListBox chekedLanes;
    }
}
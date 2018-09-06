namespace GesDep.GUI
{
    partial class AssignarMonitorACurs
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
            this.selectCurs = new System.Windows.Forms.ComboBox();
            this.cursLabel = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.informacioLabel = new System.Windows.Forms.Label();
            this.buttonAcceptar = new System.Windows.Forms.Button();
            this.mostrarDataInici = new System.Windows.Forms.Label();
            this.mostrarDataFi = new System.Windows.Forms.Label();
            this.mostrarHoraInici = new System.Windows.Forms.Label();
            this.mostrarDuracio = new System.Windows.Forms.Label();
            this.mostrarMinParticipants = new System.Windows.Forms.Label();
            this.mostrarMaxParticipants = new System.Windows.Forms.Label();
            this.mostrarCancelat = new System.Windows.Forms.Label();
            this.mostrarPreu = new System.Windows.Forms.Label();
            this.mostrarDescripcio = new System.Windows.Forms.Label();
            this.mostrarDies = new System.Windows.Forms.Label();
            this.mostrarMonitor = new System.Windows.Forms.Label();
            this.selectMonitor = new System.Windows.Forms.ComboBox();
            this.lblMonitor = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // selectCurs
            // 
            this.selectCurs.FormattingEnabled = true;
            this.selectCurs.Location = new System.Drawing.Point(124, 62);
            this.selectCurs.Name = "selectCurs";
            this.selectCurs.Size = new System.Drawing.Size(118, 21);
            this.selectCurs.TabIndex = 0;
            this.selectCurs.Text = "Seleccionar curs";
            this.selectCurs.SelectedIndexChanged += new System.EventHandler(this.Seleccionar_Curs);
            // 
            // cursLabel
            // 
            this.cursLabel.AutoSize = true;
            this.cursLabel.Location = new System.Drawing.Point(48, 62);
            this.cursLabel.Name = "cursLabel";
            this.cursLabel.Size = new System.Drawing.Size(42, 13);
            this.cursLabel.TabIndex = 1;
            this.cursLabel.Text = "Cursos:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(51, 135);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(0, 13);
            this.label1.TabIndex = 2;
            // 
            // informacioLabel
            // 
            this.informacioLabel.AutoSize = true;
            this.informacioLabel.Location = new System.Drawing.Point(48, 103);
            this.informacioLabel.Name = "informacioLabel";
            this.informacioLabel.Size = new System.Drawing.Size(59, 13);
            this.informacioLabel.TabIndex = 3;
            this.informacioLabel.Text = "Informació:";
            // 
            // buttonAcceptar
            // 
            this.buttonAcceptar.Location = new System.Drawing.Point(215, 444);
            this.buttonAcceptar.Name = "buttonAcceptar";
            this.buttonAcceptar.Size = new System.Drawing.Size(75, 23);
            this.buttonAcceptar.TabIndex = 5;
            this.buttonAcceptar.Text = "Aceptar";
            this.buttonAcceptar.UseVisualStyleBackColor = true;
            this.buttonAcceptar.Click += new System.EventHandler(this.Aceptar);
            // 
            // mostrarDataInici
            // 
            this.mostrarDataInici.AutoSize = true;
            this.mostrarDataInici.Location = new System.Drawing.Point(54, 128);
            this.mostrarDataInici.Name = "mostrarDataInici";
            this.mostrarDataInici.Size = new System.Drawing.Size(55, 13);
            this.mostrarDataInici.TabIndex = 7;
            this.mostrarDataInici.Text = "Data Inici:";
            // 
            // mostrarDataFi
            // 
            this.mostrarDataFi.AutoSize = true;
            this.mostrarDataFi.Location = new System.Drawing.Point(54, 153);
            this.mostrarDataFi.Name = "mostrarDataFi";
            this.mostrarDataFi.Size = new System.Drawing.Size(44, 13);
            this.mostrarDataFi.TabIndex = 8;
            this.mostrarDataFi.Text = "Data Fi:";
            // 
            // mostrarHoraInici
            // 
            this.mostrarHoraInici.AutoSize = true;
            this.mostrarHoraInici.Location = new System.Drawing.Point(54, 178);
            this.mostrarHoraInici.Name = "mostrarHoraInici";
            this.mostrarHoraInici.Size = new System.Drawing.Size(55, 13);
            this.mostrarHoraInici.TabIndex = 9;
            this.mostrarHoraInici.Text = "Hora Inici:";
            // 
            // mostrarDuracio
            // 
            this.mostrarDuracio.AutoSize = true;
            this.mostrarDuracio.Location = new System.Drawing.Point(53, 204);
            this.mostrarDuracio.Name = "mostrarDuracio";
            this.mostrarDuracio.Size = new System.Drawing.Size(47, 13);
            this.mostrarDuracio.TabIndex = 10;
            this.mostrarDuracio.Text = "Duració:";
            // 
            // mostrarMinParticipants
            // 
            this.mostrarMinParticipants.AutoSize = true;
            this.mostrarMinParticipants.Location = new System.Drawing.Point(53, 228);
            this.mostrarMinParticipants.Name = "mostrarMinParticipants";
            this.mostrarMinParticipants.Size = new System.Drawing.Size(97, 13);
            this.mostrarMinParticipants.TabIndex = 11;
            this.mostrarMinParticipants.Text = "Mínim Participants:";
            // 
            // mostrarMaxParticipants
            // 
            this.mostrarMaxParticipants.AutoSize = true;
            this.mostrarMaxParticipants.Location = new System.Drawing.Point(53, 255);
            this.mostrarMaxParticipants.Name = "mostrarMaxParticipants";
            this.mostrarMaxParticipants.Size = new System.Drawing.Size(98, 13);
            this.mostrarMaxParticipants.TabIndex = 12;
            this.mostrarMaxParticipants.Text = "Màxim Participants:";
            // 
            // mostrarCancelat
            // 
            this.mostrarCancelat.AutoSize = true;
            this.mostrarCancelat.Location = new System.Drawing.Point(54, 280);
            this.mostrarCancelat.Name = "mostrarCancelat";
            this.mostrarCancelat.Size = new System.Drawing.Size(52, 13);
            this.mostrarCancelat.TabIndex = 13;
            this.mostrarCancelat.Text = "Cancelat:";
            // 
            // mostrarPreu
            // 
            this.mostrarPreu.AutoSize = true;
            this.mostrarPreu.Location = new System.Drawing.Point(54, 304);
            this.mostrarPreu.Name = "mostrarPreu";
            this.mostrarPreu.Size = new System.Drawing.Size(32, 13);
            this.mostrarPreu.TabIndex = 14;
            this.mostrarPreu.Text = "Preu:";
            // 
            // mostrarDescripcio
            // 
            this.mostrarDescripcio.AutoSize = true;
            this.mostrarDescripcio.Location = new System.Drawing.Point(53, 330);
            this.mostrarDescripcio.Name = "mostrarDescripcio";
            this.mostrarDescripcio.Size = new System.Drawing.Size(60, 13);
            this.mostrarDescripcio.TabIndex = 15;
            this.mostrarDescripcio.Text = "Descripció:";
            // 
            // mostrarDies
            // 
            this.mostrarDies.AutoSize = true;
            this.mostrarDies.Location = new System.Drawing.Point(53, 356);
            this.mostrarDies.Name = "mostrarDies";
            this.mostrarDies.Size = new System.Drawing.Size(31, 13);
            this.mostrarDies.TabIndex = 16;
            this.mostrarDies.Text = "Dies:";
            // 
            // mostrarMonitor
            // 
            this.mostrarMonitor.AutoSize = true;
            this.mostrarMonitor.Location = new System.Drawing.Point(288, 62);
            this.mostrarMonitor.Name = "mostrarMonitor";
            this.mostrarMonitor.Size = new System.Drawing.Size(45, 13);
            this.mostrarMonitor.TabIndex = 17;
            this.mostrarMonitor.Text = "Monitor:";
            // 
            // selectMonitor
            // 
            this.selectMonitor.FormattingEnabled = true;
            this.selectMonitor.Location = new System.Drawing.Point(359, 62);
            this.selectMonitor.Name = "selectMonitor";
            this.selectMonitor.Size = new System.Drawing.Size(121, 21);
            this.selectMonitor.TabIndex = 18;
            this.selectMonitor.Text = "Seleccionar monitor";
            this.selectMonitor.SelectedIndexChanged += new System.EventHandler(this.Seleccionar_Monitor);
            // 
            // lblMonitor
            // 
            this.lblMonitor.AutoSize = true;
            this.lblMonitor.Location = new System.Drawing.Point(53, 378);
            this.lblMonitor.Name = "lblMonitor";
            this.lblMonitor.Size = new System.Drawing.Size(45, 13);
            this.lblMonitor.TabIndex = 19;
            this.lblMonitor.Text = "Monitor:";
            this.lblMonitor.Click += new System.EventHandler(this.label2_Click);
            // 
            // AssignarMonitorACurs
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(571, 509);
            this.Controls.Add(this.lblMonitor);
            this.Controls.Add(this.selectMonitor);
            this.Controls.Add(this.mostrarMonitor);
            this.Controls.Add(this.mostrarDies);
            this.Controls.Add(this.mostrarDescripcio);
            this.Controls.Add(this.mostrarPreu);
            this.Controls.Add(this.mostrarCancelat);
            this.Controls.Add(this.mostrarMaxParticipants);
            this.Controls.Add(this.mostrarMinParticipants);
            this.Controls.Add(this.mostrarDuracio);
            this.Controls.Add(this.mostrarHoraInici);
            this.Controls.Add(this.mostrarDataFi);
            this.Controls.Add(this.mostrarDataInici);
            this.Controls.Add(this.buttonAcceptar);
            this.Controls.Add(this.informacioLabel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cursLabel);
            this.Controls.Add(this.selectCurs);
            this.Name = "AssignarMonitorACurs";
            this.Text = "AssignarMonitorACurs";
            this.Load += new System.EventHandler(this.AssignarMonitorACurs_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox selectCurs;
        private System.Windows.Forms.Label cursLabel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label informacioLabel;
        private System.Windows.Forms.Button buttonAcceptar;
        private System.Windows.Forms.Label mostrarDataInici;
        private System.Windows.Forms.Label mostrarDataFi;
        private System.Windows.Forms.Label mostrarHoraInici;
        private System.Windows.Forms.Label mostrarDuracio;
        private System.Windows.Forms.Label mostrarMinParticipants;
        private System.Windows.Forms.Label mostrarMaxParticipants;
        private System.Windows.Forms.Label mostrarCancelat;
        private System.Windows.Forms.Label mostrarPreu;
        private System.Windows.Forms.Label mostrarDescripcio;
        private System.Windows.Forms.Label mostrarDies;
        private System.Windows.Forms.Label mostrarMonitor;
        private System.Windows.Forms.ComboBox selectMonitor;
        private System.Windows.Forms.Label lblMonitor;
    }
}
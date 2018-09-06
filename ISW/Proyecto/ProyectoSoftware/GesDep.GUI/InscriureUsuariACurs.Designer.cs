using System.Windows.Forms;

namespace GesDep.GUI
{
    partial class InscriureUsuariACurs
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
            this.cursosLabel = new System.Windows.Forms.Label();
            this.dniLabel = new System.Windows.Forms.Label();
            this.dniEscrit = new System.Windows.Forms.TextBox();
            this.buscarUsuari = new System.Windows.Forms.Button();
            this.mostrarNom = new System.Windows.Forms.Label();
            this.mostrarAdresa = new System.Windows.Forms.Label();
            this.mostrarZipcode = new System.Windows.Forms.Label();
            this.mostrarIban = new System.Windows.Forms.Label();
            this.mostrarCumple = new System.Windows.Forms.Label();
            this.mostrarRet = new System.Windows.Forms.Label();
            this.btnAceptar = new System.Windows.Forms.Button();
            this.buscarbtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // selectCurs
            // 
            this.selectCurs.FormattingEnabled = true;
            this.selectCurs.Location = new System.Drawing.Point(103, 32);
            this.selectCurs.Name = "selectCurs";
            this.selectCurs.Size = new System.Drawing.Size(282, 21);
            this.selectCurs.TabIndex = 0;
            this.selectCurs.Text = "Selecciona curs";
            this.selectCurs.SelectedIndexChanged += new System.EventHandler(this.seleccionarCursos);
            // 
            // cursosLabel
            // 
            this.cursosLabel.AutoSize = true;
            this.cursosLabel.Location = new System.Drawing.Point(32, 35);
            this.cursosLabel.Name = "cursosLabel";
            this.cursosLabel.Size = new System.Drawing.Size(39, 13);
            this.cursosLabel.TabIndex = 1;
            this.cursosLabel.Text = "Cursos";
            // 
            // dniLabel
            // 
            this.dniLabel.AutoSize = true;
            this.dniLabel.Location = new System.Drawing.Point(32, 92);
            this.dniLabel.Name = "dniLabel";
            this.dniLabel.Size = new System.Drawing.Size(26, 13);
            this.dniLabel.TabIndex = 3;
            this.dniLabel.Text = "DNI";
            // 
            // dniEscrit
            // 
            this.dniEscrit.Location = new System.Drawing.Point(103, 85);
            this.dniEscrit.Name = "dniEscrit";
            this.dniEscrit.Size = new System.Drawing.Size(282, 20);
            this.dniEscrit.TabIndex = 4;
            // 
            // buscarUsuari
            // 
            this.buscarUsuari.Location = new System.Drawing.Point(184, 127);
            this.buscarUsuari.Name = "buscarUsuari";
            this.buscarUsuari.Size = new System.Drawing.Size(121, 23);
            this.buscarUsuari.TabIndex = 5;
            this.buscarUsuari.Text = "Buscar usuari";
            this.buscarUsuari.UseVisualStyleBackColor = true;
            // 
            // mostrarNom
            // 
            this.mostrarNom.AutoSize = true;
            this.mostrarNom.Location = new System.Drawing.Point(32, 172);
            this.mostrarNom.Name = "mostrarNom";
            this.mostrarNom.Size = new System.Drawing.Size(32, 13);
            this.mostrarNom.TabIndex = 8;
            this.mostrarNom.Text = "Nom:";
            // 
            // mostrarAdresa
            // 
            this.mostrarAdresa.AutoSize = true;
            this.mostrarAdresa.Location = new System.Drawing.Point(32, 197);
            this.mostrarAdresa.Name = "mostrarAdresa";
            this.mostrarAdresa.Size = new System.Drawing.Size(44, 13);
            this.mostrarAdresa.TabIndex = 9;
            this.mostrarAdresa.Text = "Adreça:";
            // 
            // mostrarZipcode
            // 
            this.mostrarZipcode.AutoSize = true;
            this.mostrarZipcode.Location = new System.Drawing.Point(32, 220);
            this.mostrarZipcode.Name = "mostrarZipcode";
            this.mostrarZipcode.Size = new System.Drawing.Size(50, 13);
            this.mostrarZipcode.TabIndex = 10;
            this.mostrarZipcode.Text = "ZipCode:";
            // 
            // mostrarIban
            // 
            this.mostrarIban.AutoSize = true;
            this.mostrarIban.Location = new System.Drawing.Point(32, 246);
            this.mostrarIban.Name = "mostrarIban";
            this.mostrarIban.Size = new System.Drawing.Size(35, 13);
            this.mostrarIban.TabIndex = 11;
            this.mostrarIban.Text = "IBAN:";
            // 
            // mostrarCumple
            // 
            this.mostrarCumple.AutoSize = true;
            this.mostrarCumple.Location = new System.Drawing.Point(32, 275);
            this.mostrarCumple.Name = "mostrarCumple";
            this.mostrarCumple.Size = new System.Drawing.Size(86, 13);
            this.mostrarCumple.TabIndex = 12;
            this.mostrarCumple.Text = "Data Naixement:";
            // 
            // mostrarRet
            // 
            this.mostrarRet.AutoSize = true;
            this.mostrarRet.Location = new System.Drawing.Point(32, 309);
            this.mostrarRet.Name = "mostrarRet";
            this.mostrarRet.Size = new System.Drawing.Size(41, 13);
            this.mostrarRet.TabIndex = 14;
            this.mostrarRet.Text = "Retirat:";
            // 
            // btnAceptar
            // 
            this.btnAceptar.Location = new System.Drawing.Point(188, 345);
            this.btnAceptar.Name = "btnAceptar";
            this.btnAceptar.Size = new System.Drawing.Size(75, 23);
            this.btnAceptar.TabIndex = 15;
            this.btnAceptar.Text = "Aceptar";
            this.btnAceptar.UseVisualStyleBackColor = true;
            this.btnAceptar.Click += new System.EventHandler(this.aceptarForm);
            // 
            // buscarbtn
            // 
            this.buscarbtn.Location = new System.Drawing.Point(200, 111);
            this.buscarbtn.Name = "buscarbtn";
            this.buscarbtn.Size = new System.Drawing.Size(75, 23);
            this.buscarbtn.TabIndex = 16;
            this.buscarbtn.Text = "Buscar usuari";
            this.buscarbtn.UseVisualStyleBackColor = true;
            this.buscarbtn.Click += new System.EventHandler(this.findUser);
            // 
            // InscriureUsuariACurs
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(455, 448);
            this.Controls.Add(this.buscarbtn);
            this.Controls.Add(this.btnAceptar);
            this.Controls.Add(this.mostrarRet);
            this.Controls.Add(this.mostrarCumple);
            this.Controls.Add(this.mostrarIban);
            this.Controls.Add(this.mostrarZipcode);
            this.Controls.Add(this.mostrarAdresa);
            this.Controls.Add(this.mostrarNom);
            this.Controls.Add(this.dniEscrit);
            this.Controls.Add(this.dniLabel);
            this.Controls.Add(this.cursosLabel);
            this.Controls.Add(this.selectCurs);
            this.Name = "InscriureUsuariACurs";
            this.Text = "InscriureUsuariACurs";
            this.Load += new System.EventHandler(this.InscriureUsuariACurs_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox selectCurs;
        private System.Windows.Forms.Label cursosLabel;
        private System.Windows.Forms.Label dniLabel;
        private System.Windows.Forms.TextBox dniEscrit;
        private System.Windows.Forms.Button buscarUsuari;
        private System.Windows.Forms.Button aceptar;
        private System.Windows.Forms.Button cancelar;
        private System.Windows.Forms.Label mostrarNom;
        private System.Windows.Forms.Label mostrarAdresa;
        private System.Windows.Forms.Label mostrarZipcode;
        private System.Windows.Forms.Label mostrarIban;
        private System.Windows.Forms.Label mostrarCumple;
        private System.Windows.Forms.Label mostrarRet;
        private Button aceptarbtn;
        private Button cancelarbtn;
        private Button btnAceptar;
        private Button buscarbtn;
    }
}
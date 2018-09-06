namespace GesDep.GUI
{
    partial class LlistarCarrersLliures
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
            this.labelPiscina = new System.Windows.Forms.Label();
            this.selectPiscina = new System.Windows.Forms.ComboBox();
            this.labelData = new System.Windows.Forms.Label();
            this.agafarData = new System.Windows.Forms.DateTimePicker();
            this.buscarBtn = new System.Windows.Forms.Button();
            this.llistaVisual = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // labelPiscina
            // 
            this.labelPiscina.AutoSize = true;
            this.labelPiscina.Location = new System.Drawing.Point(32, 49);
            this.labelPiscina.Name = "labelPiscina";
            this.labelPiscina.Size = new System.Drawing.Size(49, 13);
            this.labelPiscina.TabIndex = 0;
            this.labelPiscina.Text = "Piscines:";
            // 
            // selectPiscina
            // 
            this.selectPiscina.FormattingEnabled = true;
            this.selectPiscina.Location = new System.Drawing.Point(154, 46);
            this.selectPiscina.Name = "selectPiscina";
            this.selectPiscina.Size = new System.Drawing.Size(200, 21);
            this.selectPiscina.TabIndex = 1;
            this.selectPiscina.Text = "Seleccionar Piscina";
            this.selectPiscina.SelectedIndexChanged += new System.EventHandler(this.seleccionarPiscina);
            // 
            // labelData
            // 
            this.labelData.AutoSize = true;
            this.labelData.Location = new System.Drawing.Point(32, 108);
            this.labelData.Name = "labelData";
            this.labelData.Size = new System.Drawing.Size(100, 13);
            this.labelData.TabIndex = 2;
            this.labelData.Text = "Seleccionar Dilluns:";
            // 
            // agafarData
            // 
            this.agafarData.Location = new System.Drawing.Point(154, 108);
            this.agafarData.Name = "agafarData";
            this.agafarData.Size = new System.Drawing.Size(200, 20);
            this.agafarData.TabIndex = 4;
            // 
            // buscarBtn
            // 
            this.buscarBtn.Location = new System.Drawing.Point(154, 149);
            this.buscarBtn.Name = "buscarBtn";
            this.buscarBtn.Size = new System.Drawing.Size(200, 23);
            this.buscarBtn.TabIndex = 6;
            this.buscarBtn.Text = "Buscar";
            this.buscarBtn.UseVisualStyleBackColor = true;
            this.buscarBtn.Click += new System.EventHandler(this.buscarCarrersLliures);
            // 
            // llistaVisual
            // 
            this.llistaVisual.FormattingEnabled = true;
            this.llistaVisual.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.llistaVisual.Location = new System.Drawing.Point(35, 192);
            this.llistaVisual.Name = "llistaVisual";
            this.llistaVisual.Size = new System.Drawing.Size(430, 303);
            this.llistaVisual.TabIndex = 7;
            this.llistaVisual.SelectedIndexChanged += new System.EventHandler(this.llistaVisual_SelectedIndexChanged_1);
            // 
            // LlistarCarrersLliures
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(489, 518);
            this.Controls.Add(this.llistaVisual);
            this.Controls.Add(this.buscarBtn);
            this.Controls.Add(this.agafarData);
            this.Controls.Add(this.labelData);
            this.Controls.Add(this.selectPiscina);
            this.Controls.Add(this.labelPiscina);
            this.Name = "LlistarCarrersLliures";
            this.Text = "LlistarCarrersLliures";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelPiscina;
        private System.Windows.Forms.ComboBox selectPiscina;
        private System.Windows.Forms.Label labelData;
        private System.Windows.Forms.DateTimePicker agafarData;
        private System.Windows.Forms.Button buscarBtn;
        private System.Windows.Forms.ListBox llistaVisual;
    }
}
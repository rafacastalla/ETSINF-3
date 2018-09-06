namespace GesDep.GUI
{
    partial class GestDepApp
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.donarAltaCursToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.assignatMonitorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.incribirCursetToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.llistarCarrersToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.donarAltaCursToolStripMenuItem,
            this.assignatMonitorToolStripMenuItem,
            this.incribirCursetToolStripMenuItem,
            this.llistarCarrersToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(166, 92);
            // 
            // donarAltaCursToolStripMenuItem
            // 
            this.donarAltaCursToolStripMenuItem.Name = "donarAltaCursToolStripMenuItem";
            this.donarAltaCursToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.donarAltaCursToolStripMenuItem.Text = "Donar alta curs";
            this.donarAltaCursToolStripMenuItem.Click += new System.EventHandler(this.donarAltaCursToolStripMenuItem_Click);
            // 
            // assignatMonitorToolStripMenuItem
            // 
            this.assignatMonitorToolStripMenuItem.Name = "assignatMonitorToolStripMenuItem";
            this.assignatMonitorToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.assignatMonitorToolStripMenuItem.Text = "Assignar monitor";
            // 
            // incribirCursetToolStripMenuItem
            // 
            this.incribirCursetToolStripMenuItem.Name = "incribirCursetToolStripMenuItem";
            this.incribirCursetToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.incribirCursetToolStripMenuItem.Text = "Incribir curset";
            // 
            // llistarCarrersToolStripMenuItem
            // 
            this.llistarCarrersToolStripMenuItem.Name = "llistarCarrersToolStripMenuItem";
            this.llistarCarrersToolStripMenuItem.Size = new System.Drawing.Size(165, 22);
            this.llistarCarrersToolStripMenuItem.Text = "Llistar carrers";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(177, 87);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(178, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Dar Alta Curso";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(177, 135);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(178, 23);
            this.button2.TabIndex = 2;
            this.button2.Text = "Inscribir En Curso";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(177, 178);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(178, 23);
            this.button3.TabIndex = 3;
            this.button3.Text = "Asignar Monitor En Curso";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(177, 218);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(178, 23);
            this.button4.TabIndex = 4;
            this.button4.Text = "Listar Calles Libres";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // GestDepApp
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(502, 378);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Name = "GestDepApp";
            this.Text = "GestDepApp";
            this.Load += new System.EventHandler(this.GestDepApp_Load);
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem donarAltaCursToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem assignatMonitorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem incribirCursetToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem llistarCarrersToolStripMenuItem;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
    }
}


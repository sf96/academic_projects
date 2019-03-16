namespace projekt11
{
    partial class Form1
    {
        /// <summary>
        /// Wymagana zmienna projektanta.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Wyczyść wszystkie używane zasoby.
        /// </summary>
        /// <param name="disposing">prawda, jeżeli zarządzane zasoby powinny zostać zlikwidowane; Fałsz w przeciwnym wypadku.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Kod generowany przez Projektanta formularzy systemu Windows

        /// <summary>
        /// Metoda wymagana do obsługi projektanta — nie należy modyfikować
        /// jej zawartości w edytorze kodu.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.button_connect = new System.Windows.Forms.Button();
            this.button_AplusB = new System.Windows.Forms.Button();
            this.dataGridView2 = new System.Windows.Forms.DataGridView();
            this.button_sort = new System.Windows.Forms.Button();
            this.button_send = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(12, 50);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 24;
            this.dataGridView1.Size = new System.Drawing.Size(556, 361);
            this.dataGridView1.TabIndex = 1;
            // 
            // button_connect
            // 
            this.button_connect.Location = new System.Drawing.Point(12, 12);
            this.button_connect.Name = "button_connect";
            this.button_connect.Size = new System.Drawing.Size(119, 23);
            this.button_connect.TabIndex = 2;
            this.button_connect.Text = "CONNECT";
            this.button_connect.UseVisualStyleBackColor = true;
            this.button_connect.Click += new System.EventHandler(this.button_connect_Click);
            // 
            // button_AplusB
            // 
            this.button_AplusB.Location = new System.Drawing.Point(607, 12);
            this.button_AplusB.Name = "button_AplusB";
            this.button_AplusB.Size = new System.Drawing.Size(110, 23);
            this.button_AplusB.TabIndex = 3;
            this.button_AplusB.Text = "A plus B";
            this.button_AplusB.UseVisualStyleBackColor = true;
            this.button_AplusB.Click += new System.EventHandler(this.button_AplusB_Click);
            // 
            // dataGridView2
            // 
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Location = new System.Drawing.Point(607, 50);
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.RowTemplate.Height = 24;
            this.dataGridView2.Size = new System.Drawing.Size(576, 361);
            this.dataGridView2.TabIndex = 4;
            // 
            // button_sort
            // 
            this.button_sort.Location = new System.Drawing.Point(786, 12);
            this.button_sort.Name = "button_sort";
            this.button_sort.Size = new System.Drawing.Size(75, 23);
            this.button_sort.TabIndex = 5;
            this.button_sort.Text = "SORT";
            this.button_sort.UseVisualStyleBackColor = true;
            this.button_sort.Click += new System.EventHandler(this.button_sort_Click);
            // 
            // button_send
            // 
            this.button_send.Location = new System.Drawing.Point(906, 12);
            this.button_send.Name = "button_send";
            this.button_send.Size = new System.Drawing.Size(75, 23);
            this.button_send.TabIndex = 6;
            this.button_send.Text = "SEND";
            this.button_send.UseVisualStyleBackColor = true;
            this.button_send.Click += new System.EventHandler(this.button_send_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1195, 423);
            this.Controls.Add(this.button_send);
            this.Controls.Add(this.button_sort);
            this.Controls.Add(this.dataGridView2);
            this.Controls.Add(this.button_AplusB);
            this.Controls.Add(this.button_connect);
            this.Controls.Add(this.dataGridView1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Button button_connect;
        private System.Windows.Forms.Button button_AplusB;
        private System.Windows.Forms.DataGridView dataGridView2;
        private System.Windows.Forms.Button button_sort;
        private System.Windows.Forms.Button button_send;
    }
}


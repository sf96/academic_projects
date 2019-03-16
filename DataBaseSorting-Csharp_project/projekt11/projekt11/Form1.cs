using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;
using Oracle.DataAccess.Client;
using System.IO;
using System.Net.Sockets;

namespace projekt11
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public class elements
        {
            public elements(decimal[] a, decimal b, decimal c, decimal d, decimal e)
            {
                tabela = a;
                zmienna_0 = b;
                zmienna_1 = c;
                kmin = d;
                kdiff = e;
            }

            public decimal[] tabela;
            public decimal zmienna_0;
            public decimal zmienna_1;
            public decimal kmin;
            public decimal kdiff;

        }

        static void _sort(List<decimal> a) // sorting
        {
            for (int j = 1; j < a.Count; j++)
            {
                for (int i = 1; i < a.Count; i++)
                {
                    if (a[i - 1] > a[i])
                    {
                        decimal c = a[i - 1];
                        decimal d = a[i];
                        a[i] = c;
                        a[i - 1] = d;
                    }
                }
            }
        }

        static void write_temp(List<decimal> temp, int a)
        {
            for (int i = 0; i < temp.Count; i++)     //temp.Count - length of temp list
            {
                temp_1[a].Add(temp[i]);
            }

        }

        static void TreadProc(object a) // while creating new thread pass through function and ONE object
        {                               // funtion defines thread's tasks
            elements b = (elements)a;   // to get acces to variables i have to convert object 'a' to element
                                        
            decimal[] x = b.tabela;
            decimal y = b.zmienna_0;
            decimal z = b.zmienna_1;
            decimal min_temp = b.kmin;
            decimal diff_temp = b.kdiff;
            int id = 0;
            if (y == min_temp) id = 0;
            else if (y == min_temp + diff_temp / 4) id = 1;
            else if (y == min_temp + (diff_temp / 4) * 2) id = 2;
            else if (y == min_temp + (diff_temp / 4) * 3) id = 3;
            

            List<decimal> temp = new List<decimal>();   // creating temp list
            for (int i = 0; i < x.Length; i++)  // x.length = lenght of array created in main function
            {
                if (x[i] >= y && x[i] < z)     // checking if value from list is in set 
                {
                    temp.Add(x[i]);         // if yes it saves to temp list
                }
                else if(id == 3 && x[i] == z)
                {
                    temp.Add(x[i]);
                }
            }



            _sort(temp);        // sorting temp list
          

            write_temp(temp, id);   // saving temp list to list[id]

            //Console.WriteLine("End using Thread nr {0}", id);
            Thread.Sleep(5000); // 5 seconds break

        }
        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button_connect_Click(object sender, EventArgs e)
        {
            OracleConnection mySqlConnection = new OracleConnection("Data source=150.254.223.99:11521;user id=ICTstudent;password=student;");
            OracleCommand mySqlCommand = mySqlConnection.CreateCommand();
            
            mySqlCommand.CommandText = "select ID,  Cast(col_A as Decimal(38,5)),Cast(col_B as Decimal(38,5)), Cast(col_C as Decimal(38,5)), Cast(col_D as Decimal(38,5)) from ICT.student_data";
            mySqlConnection.Open();

            // Connection state 
            if (mySqlConnection.State == ConnectionState.Open)
                MessageBox.Show("Stan Połączenie", "Połączenie zestawione", MessageBoxButtons.OK);


            OracleDataAdapter mySqlDataAdapter = new OracleDataAdapter(mySqlCommand);
            OracleCommandBuilder comBuild = new OracleCommandBuilder(mySqlDataAdapter);

            DataTable myDataTable = new DataTable();
            
            button_connect.Text = "CONNECTED";
            mySqlDataAdapter.Fill(myDataTable);
            mySqlConnection.Close();
            dataGridView1.DataSource = myDataTable;
        }
        
        decimal[] _array;
        private void button_AplusB_Click(object sender, EventArgs e)
        {
            DataTable table_temp = new DataTable();

            table_temp.Columns.Add("ID");
            table_temp.Columns.Add("RESULT");

            _array = new decimal[dataGridView1.RowCount-1];

            for (int i = 1; i < dataGridView1.Rows.Count; i++)
            {
                decimal a = (decimal)dataGridView1.Rows[i - 1].Cells[1].Value;
                decimal b = (decimal)dataGridView1.Rows[i - 1].Cells[2].Value;
                decimal id = (decimal)dataGridView1.Rows[i - 1].Cells[0].Value;
                decimal x = a + b;
                table_temp.Rows.Add(id, x);
                _array[i-1] = x;
            }

            dataGridView2.DataSource = table_temp;
            //dataGridView2.Sort(dataGridView2.Columns[1], ListSortDirection.Ascending);
        }

        static List<List<decimal>> temp_1;
        private void button_sort_Click(object sender, EventArgs e)
        {
            
            decimal max = _array.Max();
            decimal min = _array.Min();
            decimal diff = max - min;
            
            decimal r_0 = min;                        // lower border of searching   min
            decimal r_1 = min + diff/4;                      // upper border of searching diff/4
                        

            List<elements> all_elem = new List<elements>();     // List of elements
            temp_1 = new List<List<decimal>>();                     // List of lists

            for (int i = 0; i < 4; i++)
            {
                temp_1.Add(new List<decimal>());    // filling list with list, each will be containing numbers eg for set '0' 0 - 100
            }                                   

            for (int i = 0; i < 4; i++)         // filling elements each have different attributes
            {                                   // element nr 0 stores whole array, lower border = 0 i upper border = 100
                decimal x = i * diff/4;
                decimal a_1 = (r_0 + x);
                decimal a_2 = (r_1 + x);
                elements all = new elements(_array, a_1, a_2, min, diff);
                all_elem.Add(all);
            }

            Thread raz = new Thread(new ParameterizedThreadStart(TreadProc));   // creating thread nr 1 and passing element nr 0
            raz.Start(((object)all_elem[0]));

            Thread dwa = new Thread(new ParameterizedThreadStart(TreadProc));
            dwa.Start(((object)all_elem[1]));

            Thread trzy = new Thread(new ParameterizedThreadStart(TreadProc));
            trzy.Start(((object)all_elem[2]));

            Thread czt = new Thread(new ParameterizedThreadStart(TreadProc));
            czt.Start(((object)all_elem[3]));

            raz.Join();     // main function waits as first thread finishes work
            dwa.Join();
            trzy.Join();
            czt.Join();

            int z = 0;  // help variable, calculates where we should insert data into main array
            for (int i = 0; i < temp_1.Count; i++)  // temp_1.count - number of lists
            {
                if (i > 0)
                    z += temp_1[i - 1].Count;   // increases variable by length of previous list in order to start in good place
                for (int j = 0; j < temp_1[i].Count; j++)    // temp[i].count - length of single list
                {
                    _array[z + j] = temp_1[i][j];   // temp_1[i][j] - list number i and place on list j
                }
            }

            for (int i = 0; i < 100000; i++)
            {
                dataGridView2.Rows[i].Cells[1].Value = _array[i];
            }
        }

        private void button_send_Click(object sender, EventArgs e)
        {
            TcpClient tcp = new TcpClient();
            try
            {
                tcp.Connect("127.0.0.1", 8001);     // ip of app - localhost 
                ASCIIEncoding asciiEnc = new ASCIIEncoding();
                Stream stream = tcp.GetStream();

                for (int i = 1; i < dataGridView2.RowCount; i++)
                {
                    string str = "UPDATE ICT.STUDENT_RESULTS SET YZOZVCWC=" +
                        dataGridView2.Rows[i - 1].Cells[1].Value.ToString() + " WHERE ID=" +
                        dataGridView2.Rows[i - 1].Cells[0].Value.ToString() + ";";
                    string str2 = str.Replace(",", ".");
                    if (str2.ToLower() == "quit") break;
                    byte[] binDataOut = asciiEnc.GetBytes(str2);
                    stream.Write(binDataOut, 0, binDataOut.Length);
                }
                tcp.Close();
                Console.ReadLine();
            }  // end of try
            catch
            {
                Console.WriteLine("Error..... ");
                Console.ReadLine();
            }

        }
    }
}

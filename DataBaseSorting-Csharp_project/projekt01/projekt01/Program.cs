using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Oracle.DataAccess.Client;

namespace projekt01
{
    class Program
    {
        static void Main(string[] args)
        {
            OracleConnection connection = new OracleConnection();
            connection.ConnectionString = "User Id = ICTstudent;" + "Password = student;" + "Data Source = 150.254.223.99:11521;";
            connection.Open();
            Console.WriteLine("Connected to Oracle " + connection.ServerVersion);

            OracleCommand cmd = connection.CreateCommand();
            // adding
            /*
            cmd.CommandText = "INSERT INTO ICT.PERSONS(STUDENT_ID,FIRST_NAME,LAST_NAME) VALUES(131010,'Szymon','Fraszczak')";
            cmd.ExecuteNonQuery();
            */
            
            cmd.CommandText = "SELECT * FROM ICT.STUDENT_TASKS WHERE STUDENT_ID = 131010";
            
            OracleDataReader reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                for (int i = 0; i < reader.FieldCount; i++)
                {
                    Console.Write(reader[reader.GetName(i)].ToString() + " ");
                }
                Console.Write("\n");
            }
            Console.ReadLine();
        }
    }
}

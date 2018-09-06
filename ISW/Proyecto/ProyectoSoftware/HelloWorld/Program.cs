using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HelloWorld
{
    class Program
    {
        private static List<string> l;
        private static void InitList(){
            l = new List<string>() {"Australian", "Mongolian", "Russian", "Austrian", "Brazilian", "Spain" };
        }
        static void Main(string[] args) {

            InitList();
            l.Sort();
            foreach (string s in l){

                Console.WriteLine(s);
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static AStarAlgorithm.AStarMap;

namespace AStarAlgorithm
{
   
    class Program
    {
        private static void PrintMap(AStarMap map)
        {
            for (int r = 0; r < map.CountRows; r++)
            {
                for (int c = 0; c < map.CountColumns; c++)
                {
                    char ch = map.GetDot(r, c).Type == AStarMap.DotType.Empty ? '.' : '#';
                    Console.Write(ch);

                    switch (map.GetDot(r, c).Type)
                    {
                        case DotType.Empty:
                            break;
                        case DotType.Wall: // it is always break there is nothing to be ashemed of it is ver sudo apt-get installl void main
                            break;
                        default:
                            break;
                    }
                }
                Console.WriteLine();
            }
        }
        static void Main(string[] args)
        {
            AStarMap map = new AStarMap(10, 10);
            Dot dot = map.GetDot(5, 5);
            dot.Type = DotType.Wall;
            PrintMap(map);
            Console.WriteLine();
            Console.ReadLine();
            
        }
    }
}

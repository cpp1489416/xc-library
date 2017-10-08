using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using AStarAlgorithm;
using static AStarAlgorithm.AStarMap;

namespace AStarGUITest2
{
    public partial class Form1 : Form 
    {
        [DllImport("user32.dll")]
        private static extern void SetProcessDPIAware();

        private int countRows;
        private int countColumns;
        private AStarMap map;
        private static int d = 40;

        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
                
        }
        
        private void Form1_Load(object sender, EventArgs e)
        {
            SetProcessDPIAware();
            countRows = 20;
            countColumns = 20;
            map = new AStarMap(countRows, countColumns);
            map.StartLocation = new AStarMap.Location(10, 10);
            map.EndLocation = new AStarMap.Location(countRows - 1, countColumns - 1);

            for (int i = 4; i < 8; i++)
            {
                map.GetDot(i, 5).Type = AStarMap.DotType.Wall;
            }
      
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            
            return;
        }

        Point GetCentre(Location location)
        {
            if (location == null)
            {
                return new Point(0, 0);
            }
            return new Point(d * location.Row + d / 2, d * location.Column + d / 2);
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            //  g.DrawLine(new Pen(Color.Black), 1, 1, 1000, 1000);
            g.Clear(Color.White);
            for (int r = 0; r < countRows; r++)
            {
                for (int c = 0; c < countColumns; c++)
                {
                    int dd = 4;
                    AStarMap.Location loc = new AStarMap.Location(r, c);

                    AStarMap.Dot curDot = map.GetDot(r, c);

                    if (curDot.Type == AStarMap.DotType.Wall)
                    {
                        g.FillRectangle(Brushes.Black, new Rectangle(r * d, c * d, d, d));
                        continue;
                    }

                    if (loc.IsSame(map.StartLocation) || loc.IsSame(map.EndLocation))
                    {
                        g.DrawRectangle(new Pen(Color.Pink, 4), new Rectangle(d * r + dd, d * c + dd, d - 2 * dd, d - 2 * dd));
                        continue;
                    }

                    g.DrawRectangle(new Pen(Color.Black), new Rectangle(d * r, d * c, d, d));

                    if (map.IsInOpenList(loc))
                    {
                        g.DrawRectangle(new Pen(Color.Blue, 1), new Rectangle(d * r + dd, d * c + dd, d - 2 * dd, d - 2 * dd));
                        g.DrawString(map.GetDot(r, c).F.ToString(), new Font("consolas", 13), Brushes.Black, new PointF(d * r, d * c));
                    }
                    else if (map.IsInCloseList(loc))
                    {
                        g.DrawRectangle(new Pen(Color.Green, 1), new Rectangle(d * r + dd, d * c + dd, d - 2 * dd, d - 2 * dd));
                    }

                    Point p1 = GetCentre(curDot.Location);
                    Point p2 = GetCentre(curDot.Location);
                    if (curDot.Previous != null)
                    {
                        if (map.IsInCloseList(curDot.Location))
                        {
                            p2 = GetCentre(curDot.Previous);
                            g.DrawLine(new Pen(Color.Gray), p1, p2);
                        }
                    }
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            map.Timeout();
            pictureBox1.Refresh();
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            int row = e.X / d;
            int column = e.Y / d;
            if (row < 0 || row >= countRows || column < 0 || column > countColumns)
            {
                return;
            }
            Dot curDot = map.GetDot(row, column);

            if (curDot.Type == DotType.Empty)
            {
                curDot.Type = DotType.Wall;
            } 
            else
            {
                curDot.Type = DotType.Empty;
            }

            pictureBox1.Refresh();
        }
    }
}

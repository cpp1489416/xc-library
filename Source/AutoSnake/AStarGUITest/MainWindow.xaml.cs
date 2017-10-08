using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using AStarAlgorithm;
using System.Timers;

namespace AStarGUITest
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        AStarAlgorithm.AStarMap map;
        Timer timer;
      //  private VisualCollection graphics;
      //  private DrawingVisual visual;
     //   private DrawingContext context;

        private delegate void DrawMapDelegate();
        private static DrawMapDelegate drawMap;

        private int CountRows { get; set; }

        private int CountColumns { get; set; }

        public MainWindow()
        {
            InitializeComponent();
        }

        private void comboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            CountRows = 10;
            CountColumns = 10;
            map = new AStarMap(CountRows, CountColumns);
            map.StartLocation = new AStarMap.Location(2, 2);
            map.EndLocation = new AStarMap.Location(8, 8);
            timer = new Timer(100);
            timer.Elapsed += Timeout;
            timer.Start();

       //     graphics = new VisualCollection(canvas);
       //     visual = new DrawingVisual();
       //     graphics.Add(visual);  
       //     context = visual.RenderOpen();

            int d = 100;
         //   context.DrawRectangle(Brushes.Blue, new Pen(Brushes.Red, 100), new Rect(d, d, d, d));
          //  context.Close();
        }

        private void DrawMap()
        {
            int d = 100;
            canvas.Dispatcher.Invoke(
                new Action(
                    delegate
                    {
                 //       context = visual.RenderOpen();
                  ///      context.DrawRectangle(Brushes.Blue, new Pen(Brushes.Red, 100), new Rect(d, d, d, d));
                  //      context.Close();

                        canvas.Children.Add(new Rectangle { Width = 100, Height = 100, });
                       // canvas.Children.Add(new Rectangle { Width = 100, Height = 100 });
                    }
                )
            );
        }

        public void Timeout(object o, ElapsedEventArgs args)
        {
            map.Timeout();
            DrawMap();
        }
    }
}

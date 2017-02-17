using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AStarAlgorithm
{
    public class AStarMap
    {
        public class Location // Location is a class
        {
            public Location() { }

            public Location(Location other)
            {
                Row = other.Row;
                Column = other.Column;
            }

            public Location(int row, int column)
            {
                Row = row;
                Column = column;
            }

            public int Row { get; set; }

            public int Column { get; set; }

            public int GetDistance(Location location)
            {
                return Math.Abs(Row - location.Row) + Math.Abs(Column - location.Column);
                //return (int)(Math.Pow(Row - location.Row, 2) + Math.Pow(Column - location.Column, 2));
            }

            public bool IsSame(Location other)
            {
                return Row == other.Row && Column == other.Column;
            }
        }

        public enum DotType
        {
            Wall, Empty,
        };

        public class Dot : IComparable<Dot>
        {
            public DotType Type { get; set; }

            public Location Previous { get; set; }

            public int G { get; set; }

            public int H { get; set; }

            public Location Location { get; set; }

            public int F
            {
                get
                {
                    return G + H;
                }
            }

            public Dot()
            {
                Location = new Location(-1, -1);
                H = 0;
                G = 0;
                Previous = null;
                Type = DotType.Empty;
            }

            public Dot(Dot other)
            {
                Location = new Location(other.Location);
                H = other.H;
                G = other.G;
                Previous = other.Previous;
                Type = other.Type;
            }

            public int Row  
            {
                get
                {
                    return Location.Row;
                }
                set
                {
                    Location.Row = value;
                }
            }

            public int Column
            {
                get
                {
                    return Location.Column;
                }
                set
                {
                    Location.Column = value;
                }
            }

            public static bool operator <(Dot lhs, Dot rhs)
            {
                return lhs.F < rhs.F;
            }

            public static bool operator >(Dot lhs, Dot rhs)
            {
                return lhs.F > rhs.F;
            }

            public int CompareTo(Dot other) // every condition must have clear returned value
            {
                if (Location.Row == other.Location.Row && Location.Column == other.Location.Column) // msut same
                {
                    return 0;
                }
                else if (F == other.F)
                {
                    if (Row < other.Row)
                    {
                        return -1;
                    } else if (Row > other.Row)
                    {
                        return 1;
                    }
                    else
                    {
                        return Column < other.Column ? -1 : 1; 
                    }
                } 
                else
                {
                    return F < other.F ? -1 : 1;
                }
            }
        }
        
        public class LocationComparer : IComparer<Location>
        {
            private AStarMap mMap;

            public LocationComparer(AStarMap map)
            {
                mMap = map;
            }

            public int Compare(Location x, Location y)
            {
                int xF = mMap.GetDot(x.Row, x.Column).F;
                int yF = mMap.GetDot(y.Row, y.Column).F;
                if (xF != yF)
                {
                    return xF - yF;
                }
                else
                {
                    if (x.Row != y.Row)
                    {
                        return x.Row - y.Row;
                    } 
                    else
                    {
                        return x.Column - y.Column;
                    }
                }
            }
        }
        
        bool finished;
        Dot[,] array;
        Location startLocation;
        Location endLocation;
        SortedSet<Location> openList;
        SortedSet<Location> closeList;
        LocationComparer comparer;

        public int CountRows { get; set; }

        public int CountColumns { get; set; }
        
        public AStarMap(int countRows, int countColumns)
        {
            CountRows = countRows;
            CountColumns = countColumns;
            comparer = new LocationComparer(this);
            array = new Dot[countRows, countColumns];
            openList = new SortedSet<Location>(comparer);
            closeList = new SortedSet<Location>(comparer);
            for (int r = 0; r < countRows; r++)
            {
                for (int c = 0; c < countColumns; c++)
                {
                    array[r, c] = new Dot();
                    array[r, c].Row = r;
                    array[r, c].Column = c;
                }
            }
            finished = false;
        }
        
        public Dot GetDot(int row, int column)
        {
            if (!IsValidLocation(new Location(row, column)))
            {
                return array[0, 0];
            }
            return array[row, column];
        }
        
        public bool IsFinished()
        {
            return finished;
        }

        public Location StartLocation
        {
            get
            {
                return startLocation;
            }
            set
            {
                startLocation = value;
               // GetDot(startLocation.Row, startLocation.Column).Previous = new Location(startLocation);
                openList.Clear();
                openList.Add(new Location(startLocation));
            }
        }

        public Location EndLocation
        {
            get
            {
                return endLocation;
            }
            set
            {
                endLocation = value;
            }
        }

        public bool IsValidLocation(Location location)
        {
            return location.Row >= 0 && location.Row < CountRows && location.Column >= 0 && location.Column < CountColumns;
        }

        public bool IsInOpenList(Location location)
        {
            return openList.Contains(new Location(location));
        }

        public bool IsInCloseList(Location location)
        {
            return closeList.Contains(new Location(location));
        }

        public int GetH(Location location) // H is the Distance from end location
        {
            return location.GetDistance(endLocation);
        }
        
        public void Timeout()
        {
            if (openList.Count == 0) { return; }
            if (IsInCloseList(endLocation))
            {
                finished = true;
                return;
            }
            Location curLoc = new Location(openList.First());
            openList.Remove(new Location(curLoc));
            closeList.Add(new Location(curLoc));

            Dot curDot = array[curLoc.Row, curLoc.Column];
       
            int[] dr = { -1, 1, 0, 0, };
            int[] dc = { 0, 0, -1, 1, }; // return false; or yes??
            
            for (int i = 0; i < 4; i++)
            {
                int nr = curLoc.Row + dr[i];
                int nc = curLoc.Column + dc[i];

                Location newLoc = new Location(nr, nc);
                if (!IsValidLocation(newLoc))
                {
                    continue;
                }

                Dot newDot = GetDot(nr, nc);
                if (newDot.Type == DotType.Wall)
                {
                    continue;
                }

                if (!IsInCloseList(newLoc))
                {
                    if (IsInOpenList(newLoc))
                    {
                        if (newDot.G > curDot.G + 1)
                        {

                            openList.Remove(new Location(newLoc));
                            newDot.G = curDot.G + 1;
                            newDot.H = GetH(newLoc);
                            // newDot.Previous = new Location(curLoc);
                            openList.Add(new Location(newLoc));
                            newDot.Previous = new Location(curLoc);
                        }
                    }
                    else
                    { // sudo apt-get install void main double decker false false false true else reutrn false  
                        newDot.G = curDot.G + 1;
                        newDot.H = GetH(newLoc);
                        // newDot.Previous = new Location(curLoc);
                        openList.Add(new Location(newLoc));
                        newDot.Previous = new Location(curLoc);
                    }
                }
                else
                {
                    int newG = curDot.G + 1;
                    if (newG < array[nr, nc].G) // only compare G, H is always the same
                    {
                        // newDot.Previous = new Location(curLoc);

                        newDot.G = newG;
                        newDot.H = GetH(newLoc);
                        closeList.Remove(new Location(newLoc));
                        openList.Add(new Location(newLoc));
                        newDot.Previous = new Location(curLoc);
                    }
                }
            } // return false else reutnr 
        }
    }
}
